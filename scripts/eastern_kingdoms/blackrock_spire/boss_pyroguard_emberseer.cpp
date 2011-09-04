/*
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2010-2011 ScriptDev0 <http://github.com/mangos-zero/scriptdev0>
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
SDName: Boss_Pyroguard_Emberseer
SD%Complete: 100
SDComment: Event to activate Emberseer NYI
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SAY_AGGRO               = -1229000,

    SPELL_FIRENOVA          = 23462,
    SPELL_FLAMEBUFFET       = 23341,
    SPELL_PYROBLAST         = 20228,                        // guesswork, but best fitting in spells-area, was 17274 (has mana cost)

    // dummy spells
    SPELL_ENCAGED_EMBERSEER = 15282,                        // aura triggered by the incarcerators; removed on combat
    SPELL_DESPAWN_EMBERSEER = 16078,                        // cast on death - guesswork
    SPELL_GROWING           = 16049,                        // stacking aura
    SPELL_FULL_STRENGTH     = 16047,                        // on full grow
    SPELL_BONUS_DAMAGE      = 16534,                        // triggered on full grow
    SPELL_TRANSFORM         = 16052,                        // remove encaged aura and set in combat -> guesswork

    MAX_GROWING_STACKS      = 19,
};

/*
 *  Event doc
 *  The Emberseer is encaged by the incarcerators
 *  These channel 15281 on the boss and triggers 15282 on the boss
 *  When a player clicks on the altar a script event is sent and all the incarcerators stop casting
 *  In the same time the Emberseer casts 16048 and starts to grow
 *  When he reaches the max stacks of 16049, he will blow up casting 16047 (which triggers 16534)
 *  He also casts 16052 - which removes all the flags, activates the runes and sets him in combat
 *  On death he casts 16078, which deactivates all the runes in the room
 *  In case of wipe the event resets to initial state and the incarcerators are respawned
 *  In case of wipe before the Emberseer is at full strength, then the boss will fight the orcs and reset the event
 */

struct MANGOS_DLL_DECL boss_pyroguard_emberseerAI : public ScriptedAI
{
    boss_pyroguard_emberseerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;
    uint32 m_uiFireNovaTimer;
    uint32 m_uiFlameBuffetTimer;
    uint32 m_uiPyroBlastTimer;

    void Reset()
    {
        m_uiFireNovaTimer = 6000;
        m_uiFlameBuffetTimer = 3000;
        m_uiPyroBlastTimer = 14000;
    }

    void Aggro(Unit* pWho)
    {
        DoScriptText(SAY_AGGRO, m_creature);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, DONE);

        DoCastSpellIfCan(m_creature, SPELL_DESPAWN_EMBERSEER, CAST_TRIGGERED);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, FAIL);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // FireNova Timer
        if (m_uiFireNovaTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FIRENOVA);
            m_uiFireNovaTimer = 6000;
        }
        else
            m_uiFireNovaTimer -= uiDiff;

        // FlameBuffet Timer
        if (m_uiFlameBuffetTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FLAMEBUFFET);
            m_uiFlameBuffetTimer = 14000;
        }
        else
            m_uiFlameBuffetTimer -= uiDiff;

        // PyroBlast Timer
        if (m_uiPyroBlastTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_PYROBLAST);
            m_uiPyroBlastTimer = 15000;
        }
        else
            m_uiPyroBlastTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_pyroguard_emberseer(Creature* pCreature)
{
    return new boss_pyroguard_emberseerAI(pCreature);
}

bool EffectDummyCreature_pyroguard_emberseer(Unit* pCaster, uint32 uiSpellId, SpellEffectIndex uiEffIndex, Creature* pCreatureTarget)
{
    //always check spellid and effectindex
    if (uiSpellId == SPELL_DESPAWN_EMBERSEER && uiEffIndex == EFFECT_INDEX_0)
    {
        // extinguish all runes
        if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*)pCreatureTarget->GetInstanceData())
            pInstance->DoUseEmberseerRunes();

        //always return true when we are handling this spell and effect
        return true;
    }
    else if (uiSpellId == SPELL_GROWING && uiEffIndex == EFFECT_INDEX_0)
    {
        if (SpellAuraHolder* pGrow = pCreatureTarget->GetSpellAuraHolder(SPELL_GROWING))
        {
            if (pGrow->GetStackAmount() == MAX_GROWING_STACKS)
            {
                pCreatureTarget->CastSpell(pCreatureTarget, SPELL_FULL_STRENGTH, true);
                pCreatureTarget->CastSpell(pCreatureTarget, SPELL_TRANSFORM, true);
            }
        }
    }
    else if (uiSpellId == SPELL_FULL_STRENGTH && uiEffIndex == EFFECT_INDEX_0)
    {
        pCreatureTarget->CastSpell(pCreatureTarget, SPELL_BONUS_DAMAGE, true);
    }
    else if (uiSpellId == SPELL_TRANSFORM && uiEffIndex == EFFECT_INDEX_0)
    {
        // activate runes all runes
        if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*)pCreatureTarget->GetInstanceData())
            pInstance->DoUseEmberseerRunes();

        pCreatureTarget->SetInCombatWithZone();
        pCreatureTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        pCreatureTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        pCreatureTarget->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
    }

    return false;
}

void AddSC_boss_pyroguard_emberseer()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_pyroguard_emberseer";
    pNewScript->GetAI = &GetAI_boss_pyroguard_emberseer;
    pNewScript->pEffectDummyNPC = &EffectDummyCreature_pyroguard_emberseer;
    pNewScript->RegisterSelf();
}
