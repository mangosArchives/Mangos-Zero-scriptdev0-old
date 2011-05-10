/*
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2010-2011 ScriptDev0 <http://github.com/scriptdev/scriptdevzero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_emerald_dragons
SD%Complete:
SDComment:
SDCategory: Emerald Dragons
EndScriptData */

#include "precompiled.h"

enum
{
    // common spells
    SPELL_NOXIOUS_BREATH        = 24818,
    SPELL_TAIL_SWEEP            = 15847,
    SPELL_SLEEPING_FOG_1        = 24813,
    SPELL_SLEEPING_FOG_2        = 24814,
    SPELL_MARK_OF_NATURE        = 25041,            // Aura on boss; triggers stun debuff 25043 on player if player has aura 25040
    SPELL_MARK_OF_NATURE_PLAYER = 25040,            // Cast on a player when dies
    SPELL_SUMMON_PLAYER         = 24776,            // Summons the main aggro target when tries to run; this was added in 2.0.1 in order to not allow players run with the dragons into big cities - needs research

    NPC_DREAM_FOG               = 15224,
    SPELL_DREAM_FOG             = 24777,            // maybe this one: 24780, but missing spell from DBC
};

struct MANGOS_DLL_DECL emerald_dragonsBaseAI : public ScriptedAI
{
    emerald_dragonsBaseAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiSleepingFogTimer;
    uint32 m_uiNoxiousBreathTimer;
    uint32 m_uiTailSweepTimer;
    uint8 m_uiAbilityUsed;

    void Reset()
    {
        m_uiSleepingFogTimer    = urand(15000, 20000);
        m_uiNoxiousBreathTimer  = 8000;
        m_uiTailSweepTimer      = 4000;
        m_uiAbilityUsed         = 1;
    }

    void Aggro(Unit* pWho)
    {
        // boss aura which stunns the resurrected players
        DoCastSpellIfCan(m_creature, SPELL_MARK_OF_NATURE);
    }

    void KilledUnit(Unit* pVictim)
    {
        // cast when a player dies; will trigger stun debuff
        pVictim->CastSpell(pVictim, SPELL_MARK_OF_NATURE_PLAYER, true);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_DREAM_FOG)
            pSummoned->CastSpell(pSummoned, SPELL_DREAM_FOG, false);
    }

    // each dragon has a special ability
    virtual void DoUseSpecialAbility() {}

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Sleep_Timer
        if (m_uiSleepingFogTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_SLEEPING_FOG_1, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_SLEEPING_FOG_2, CAST_TRIGGERED);

            m_uiSleepingFogTimer = urand(8000, 15000);
        }
        else
            m_uiSleepingFogTimer -= uiDiff;

        // NoxiousBreath_Timer
        if (m_uiNoxiousBreathTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_NOXIOUS_BREATH) == CAST_OK)
                m_uiNoxiousBreathTimer = urand(14000, 20000);
        }
        else
            m_uiNoxiousBreathTimer -= uiDiff;

        // Tailsweep every 2 seconds
        if (m_uiTailSweepTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_TAIL_SWEEP) == CAST_OK)
                m_uiTailSweepTimer = 2000;
        }
        else
            m_uiTailSweepTimer -= uiDiff;

        // do special ability at 75%, 50% and 25% hp
        if (m_creature->GetHealthPercent() < float(100 - 25*m_uiAbilityUsed))
        {
            ++m_uiAbilityUsed;
            DoUseSpecialAbility();
        }

        DoMeleeAttackIfReady();
    }
};

enum
{
    // emeriss
    SAY_EMERISS_AGGRO           = -1000401,
    SAY_EMERISS_CORRUPTION      = -1000402,

    SPELL_VOLATILE_INFECTION    = 24928,
    SPELL_CORRUPTION_OF_EARTH   = 24910,
    SPELL_PUTRID_MUSHROOM       = 24904,            // Summons a mushroom on killing a player
};

struct MANGOS_DLL_DECL boss_emerissAI : public emerald_dragonsBaseAI
{
    boss_emerissAI(Creature* pCreature) : emerald_dragonsBaseAI(pCreature)
    {
        Reset();

        emerald_dragonsBaseAI::emerald_dragonsBaseAI(pCreature);
    }

    uint32 m_uiVolatileInfectionTimer;

    void Reset()
    {
        m_uiVolatileInfectionTimer = 12000;

        emerald_dragonsBaseAI::Reset();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_EMERISS_AGGRO, m_creature);

        emerald_dragonsBaseAI::Aggro(pWho);
    }

    void DoUseSpecialAbility()
    {
        if (DoCastSpellIfCan(m_creature, SPELL_CORRUPTION_OF_EARTH) == CAST_OK)
            DoScriptText(SAY_EMERISS_CORRUPTION, m_creature);
    }

    void KilledUnit(Unit* pVictim)
    {
        // summon a mushroom on the spot the player dies
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            pVictim->CastSpell(pVictim, SPELL_PUTRID_MUSHROOM, true);

        emerald_dragonsBaseAI::KilledUnit(pVictim);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        emerald_dragonsBaseAI::UpdateAI(uiDiff);

        // VolatileInfection_Timer
        if (m_uiVolatileInfectionTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_VOLATILE_INFECTION) == CAST_OK)
                    m_uiVolatileInfectionTimer = urand(7000, 12000);
            }
        }
        else
            m_uiVolatileInfectionTimer -= uiDiff;
    }
};

enum
{
    // lethon
    SAY_LETHON_AGGRO            = -1000694,
    SAY_LETHON_SHADE            = -1000695,

    SPELL_SHADOW_BOLT_WIRL      = 24834,            // Periodic aura; should trigger 24820, 24821, 24822, 24823 and 24835, 24836, 24837, 24838
    SPELL_DRAW_SPIRIT           = 24811,

    NPC_SPIRIT_SHADE            = 15261,            // Scripted in eventAI
};

struct MANGOS_DLL_DECL boss_lethonAI : public emerald_dragonsBaseAI
{
    boss_lethonAI(Creature* pCreature) : emerald_dragonsBaseAI(pCreature)
    {
        Reset();

        emerald_dragonsBaseAI::emerald_dragonsBaseAI(pCreature);
    }

    uint32 m_uiShadowBoltTimer;

    void Reset()
    {
        m_uiShadowBoltTimer = 12000;

        emerald_dragonsBaseAI::Reset();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_LETHON_AGGRO, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_SHADOW_BOLT_WIRL);

        emerald_dragonsBaseAI::Aggro(pWho);
    }

    void DoUseSpecialAbility()
    {
        if (DoCastSpellIfCan(m_creature, SPELL_DRAW_SPIRIT) == CAST_OK)
            DoScriptText(SAY_LETHON_SHADE, m_creature);
    }

    void SpellHitTarget(Unit* pTarget, const SpellEntry* pSpell)
    {
        // summon a shade for each player hit
        if (pTarget->GetTypeId() == TYPEID_PLAYER && pSpell->Id == SPELL_DRAW_SPIRIT)
            pTarget->SummonCreature(NPC_SPIRIT_SHADE, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pTarget->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0);
    }

    void JustSummoned(Creature* pSummoned)
    {
        // move the shade to lethon
        if (pSummoned->GetEntry() == NPC_SPIRIT_SHADE)
            pSummoned->GetMotionMaster()->MovePoint(0, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ());

        emerald_dragonsBaseAI::JustSummoned(pSummoned);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        emerald_dragonsBaseAI::UpdateAI(uiDiff);
    }
};

enum
{
    // taerar
    SAY_TAERAR_AGGRO            = -1000399,
    SAY_TAERAR_SHADE            = -1000400,

    SPELL_ARCANE_BLAST          = 24857,
    SPELL_BELLOWING_ROAR        = 22686,
    SPELL_SUMMON_SHADE_1        = 24841,
    SPELL_SUMMON_SHADE_2        = 24842,
    SPELL_SUMMON_SHADE_3        = 24843,
    SPELL_SELF_STUN             = 24883,            // Stunns the main boss until the shades are dead

    NPC_SHADE_OF_TAERAR         = 15302,

    /*
     * Notes for dev of npc 15302 in eventAI:
     * Spell poison cloud - 24840; initial timer = 8000; combat timer = 30000;
     * Spell poison breath - 20667; initial timer = 12000; combat timer = 12000;
     */
};

struct MANGOS_DLL_DECL boss_taerarAI : public emerald_dragonsBaseAI
{
    boss_taerarAI(Creature* pCreature) : emerald_dragonsBaseAI(pCreature)
    {
        Reset();

        emerald_dragonsBaseAI::emerald_dragonsBaseAI(pCreature);
    }

    uint32 m_uiArcaneBlastTimer;
    uint32 m_uiBellowingRoarTimer;
    uint32 m_uiShadesTimeoutTimer;

    GUIDList m_luiShadeGUIDs;

    void Reset()
    {
        m_uiArcaneBlastTimer    = 12000;
        m_uiBellowingRoarTimer  = 30000;
        m_uiShadesTimeoutTimer  = 0;

        emerald_dragonsBaseAI::Reset();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_TAERAR_AGGRO, m_creature);

        emerald_dragonsBaseAI::Aggro(pWho);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_SHADE_OF_TAERAR)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                pSummoned->AI()->AttackStart(pTarget);
                m_luiShadeGUIDs.push_back(pSummoned->GetGUID());
            }
        }

        emerald_dragonsBaseAI::JustSummoned(pSummoned);
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_SHADE_OF_TAERAR)
        {
            m_luiShadeGUIDs.remove(pSummoned->GetGUID());

            if (m_luiShadeGUIDs.empty())
            {
                // unbanish
                m_creature->RemoveAurasDueToSpell(SPELL_SELF_STUN);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                m_uiShadesTimeoutTimer = 0;
            }
        }
    }

    void DoUseSpecialAbility()
    {
        // banis self
        if (DoCastSpellIfCan(m_creature, SPELL_SELF_STUN) == CAST_OK)
        {
            DoCastSpellIfCan(m_creature, SPELL_SUMMON_SHADE_1, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_SUMMON_SHADE_2, CAST_TRIGGERED);
            DoCastSpellIfCan(m_creature, SPELL_SUMMON_SHADE_3, CAST_TRIGGERED);

            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

            DoScriptText(SAY_TAERAR_SHADE, m_creature);
            m_uiShadesTimeoutTimer = 60000;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        emerald_dragonsBaseAI::UpdateAI(uiDiff);

        // unbanish on timer
        if (m_uiShadesTimeoutTimer)
        {
            if (m_uiShadesTimeoutTimer <= uiDiff)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_SELF_STUN);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

                m_uiShadesTimeoutTimer = 0;
            }
            else
                m_uiShadesTimeoutTimer -= uiDiff;
        }

        // ArcaneBlast_Timer
        if (m_uiArcaneBlastTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_ARCANE_BLAST) == CAST_OK)
                    m_uiArcaneBlastTimer = urand(7000, 12000);
            }
        }
        else
            m_uiArcaneBlastTimer -= uiDiff;

        // BellowingRoar_Timer
        if (m_uiBellowingRoarTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_BELLOWING_ROAR) == CAST_OK)
                m_uiBellowingRoarTimer = urand(20000, 30000);
        }
        else
            m_uiBellowingRoarTimer -= uiDiff;
    }
};

enum
{
    // ysondre
    SAY_YSONDRE_AGGRO           = -1000360,
    SAY_YSONDRE_DRUIDS          = -1000361,

    SPELL_LIGHTNING_WAVE        = 24819,
    SPELL_SUMMON_DRUIDS         = 24795,

    NPC_DRUID_SPIRIT            = 15260

    /*
     * Notes for dev of npc 15260 in eventAI:
     * Spell moonfire - 21669; initial timer = 3000; combat timer = 5000;
     */
};

struct MANGOS_DLL_DECL boss_ysondreAI : public emerald_dragonsBaseAI
{
    boss_ysondreAI(Creature* pCreature) : emerald_dragonsBaseAI(pCreature)
    {
        Reset();

        emerald_dragonsBaseAI::emerald_dragonsBaseAI(pCreature);
    }

    uint32 m_uiLightningWaveTimer;

    void Reset()
    {
        m_uiLightningWaveTimer = 12000;

        emerald_dragonsBaseAI::Reset();
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_YSONDRE_AGGRO, m_creature);

        emerald_dragonsBaseAI::Aggro(pWho);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_DRUID_SPIRIT)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }

        emerald_dragonsBaseAI::JustSummoned(pSummoned);
    }

    void DoUseSpecialAbility()
    {
        // summon 10 druids; we don't know how many druids are summoned but in old script there were 10 so we just leave it like this
        for (uint8 i = 0; i < 10; i++)
            DoCastSpellIfCan(m_creature, SPELL_SUMMON_DRUIDS, CAST_TRIGGERED);

        DoScriptText(SAY_YSONDRE_DRUIDS, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        emerald_dragonsBaseAI::UpdateAI(uiDiff);

        // LightningWave_Timer
        if (m_uiLightningWaveTimer < uiDiff)
        {
            if (Unit *pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_LIGHTNING_WAVE) == CAST_OK)
                    m_uiLightningWaveTimer = urand(7000, 12000);
            }
        }
        else
            m_uiLightningWaveTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_emeriss(Creature* pCreature)
{
    return new boss_emerissAI(pCreature);
}

CreatureAI* GetAI_boss_lethon(Creature* pCreature)
{
    return new boss_lethonAI(pCreature);
}

CreatureAI* GetAI_boss_taerar(Creature* pCreature)
{
    return new boss_taerarAI(pCreature);
}

CreatureAI* GetAI_boss_ysondre(Creature* pCreature)
{
    return new boss_ysondreAI(pCreature);
}

void AddSC_boss_emerald_dragons()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_emeriss";
    pNewScript->GetAI = &GetAI_boss_emeriss;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_lethon";
    pNewScript->GetAI = &GetAI_boss_lethon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_taerar";
    pNewScript->GetAI = &GetAI_boss_taerar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_ysondre";
    pNewScript->GetAI = &GetAI_boss_ysondre;
    pNewScript->RegisterSelf();
}
