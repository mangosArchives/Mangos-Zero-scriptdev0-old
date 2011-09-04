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
SDName: boss_lord_kazzak
SD%Complete: 70
SDComment:
SDCategory: Dark-Portal
EndScriptData */

#include "precompiled.h"

enum
{
    SAY_INTRO                 = -1000147,
    SAY_AGGRO1                = -1000148,
    SAY_AGGRO2                = -1000149,
    SAY_SURPREME1             = -1000150,
    SAY_SURPREME2             = -1000151,
    SAY_KILL1                 = -1000152,
    SAY_KILL2                 = -1000153,
    SAY_KILL3                 = -1000154,
    SAY_DEATH                 = -1000155,
    EMOTE_FRENZY              = -1000002,
    SAY_RAND1                 = -1000157,
    SAY_RAND2                 = -1000158,

    SPELL_SHADOW_VOLLEY       = 25586,
    SPELL_CLEAVE              = 20691,
    SPELL_THUNDERCLAP         = 26554,
    SPELL_VOIDBOLT            = 21066,
    SPELL_MARK_OF_KAZZAK      = 21056,
    SPELL_MARK_OF_KAZZAK_EXP  = 21058,
    SPELL_CAPTURESOUL         = 21054,
    SPELL_TWISTEDREFLECTION   = 21063
};

struct MANGOS_DLL_DECL boss_lordkazzakAI : public ScriptedAI
{
    boss_lordkazzakAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiShadowVolleyTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiThunderClapTimer;
    uint32 m_uiVoidBoltTimer;
    uint32 m_uiMarkOfKazzakTimer;
    uint32 m_uiTwistedReflectionTimer;
    uint32 m_uiSupremeTimer;

    bool m_bSupremeMode, m_bEnraged;

    void Reset()
    {
        m_uiShadowVolleyTimer = urand(3000,12000);
        m_uiCleaveTimer = 7000;
        m_uiThunderClapTimer = urand(16000,20000);
        m_uiVoidBoltTimer = 30000;
        m_uiMarkOfKazzakTimer = 25000;
        m_uiTwistedReflectionTimer = 33000;
        m_uiSupremeTimer = 3*MINUTE*IN_MILLISECONDS;

        m_bSupremeMode = false;
        m_bEnraged = false;
    }

    void JustRespawned()
    {
        DoScriptText(SAY_INTRO, m_creature);
    }

    void Aggro(Unit* /*pWho*/)
    {
        switch(urand(0,1))
        {
            case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
        }
    }

    void KilledUnit(Unit* pVictim)
    {

        if (pVictim->GetTypeId() != TYPEID_PLAYER)
            return;

        DoCastSpellIfCan(m_creature, SPELL_CAPTURESOUL);

        switch(urand(0,3))
        {
            case 0: DoScriptText(SAY_KILL1, m_creature); break;
            case 1: DoScriptText(SAY_KILL2, m_creature); break;
            case 2: DoScriptText(SAY_KILL3, m_creature); break;
        }
    }

    void JustDied(Unit* /*pVictim*/)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Supreme mode - Causes Kazzak to cast his Shadowbolt every second.
        if (m_uiSupremeTimer < uiDiff && !m_bSupremeMode)
            m_bSupremeMode = true;
        else if (!m_bSupremeMode)
            m_uiSupremeTimer -= uiDiff;

        // Shadowbolt Volley
        if (m_uiShadowVolleyTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOW_VOLLEY);
            if (m_bSupremeMode)
                m_uiShadowVolleyTimer = 1000;
            else
                m_uiShadowVolleyTimer = urand(4000,20000);
        }
        else
            m_uiShadowVolleyTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE);
            m_uiCleaveTimer = urand(8000,12000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        // Thunder Clap
        if (m_uiThunderClapTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_THUNDERCLAP);
            m_uiThunderClapTimer = urand(10000,14000);
        }
        else
            m_uiThunderClapTimer -= uiDiff;

        // Void Bolt
        if (m_uiVoidBoltTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_VOIDBOLT);
            m_uiVoidBoltTimer = urand(15000,28000);
        }
        else
            m_uiVoidBoltTimer -= uiDiff;

        // Mark of Kazzak
        if (m_uiMarkOfKazzakTimer < uiDiff)
        {
            Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
            if (pTarget && pTarget->getPowerType() == POWER_MANA && pTarget->GetPower(POWER_MANA) > 1000)
            {
                DoCastSpellIfCan(pTarget, SPELL_MARK_OF_KAZZAK);
                m_uiMarkOfKazzakTimer = 20000;
            }
        }
        else
            m_uiMarkOfKazzakTimer -= uiDiff;

        // Mark of Kazzak - Explode the target when does not have more mana
        ThreatList const& tMarkList = m_creature->getThreatManager().getThreatList();
        for (ThreatList::const_iterator iter = tMarkList.begin(); iter != tMarkList.end(); ++iter)
        {
            Unit* pMarked = m_creature->GetMap()->GetUnit((*iter)->getUnitGuid());
            if (pMarked && pMarked->HasAura(SPELL_MARK_OF_KAZZAK, EFFECT_INDEX_0) && pMarked->GetPower(POWER_MANA) < 250)
            {
                pMarked->RemoveAurasDueToSpell(SPELL_MARK_OF_KAZZAK);
                pMarked->CastSpell(pMarked, SPELL_MARK_OF_KAZZAK_EXP, false);
                break;
            }
        }

        // Twisted Reflection
        if (m_uiTwistedReflectionTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_TWISTEDREFLECTION);

            m_uiTwistedReflectionTimer = 15000;
        }
        else
            m_uiTwistedReflectionTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_boss_lordkazzak(Creature *_Creature)
{
    return new boss_lordkazzakAI (_Creature);
}

void AddSC_boss_lord_kazzak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_lord_kazzak";
    pNewScript->GetAI = &GetAI_boss_lordkazzak;
    pNewScript->RegisterSelf();
}
