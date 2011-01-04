/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Drakkisath
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_FLAMESTRIKE    = 16419,
    SPELL_CLEAVE         = 15284,
    SPELL_CONFLIGURATION = 16805,
    SPELL_THUNDERCLAP    = 15588,
    SPELL_PIERCE_ARMOR   = 12097,
    SPELL_RAGE           = 16789
};

struct MANGOS_DLL_DECL boss_drakkisathAI : public ScriptedAI
{
    boss_drakkisathAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 m_uiFlamestrikeTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiConfligurationTimer;
    uint32 m_uiThunderclapTimer;
    uint32 m_uiPierceArmorTimer;

    Unit* pTarget;

    bool Rage1;
    bool Rage2;

    void Reset()
    {
        Rage1 = false;
        Rage2 = false;
        m_uiFlamestrikeTimer    = urand(4000, 8000);
        m_uiCleaveTimer         = urand(6000, 10000);
        m_uiConfligurationTimer = urand(12000, 18000);
        m_uiThunderclapTimer    = urand(15000, 19000);
        m_uiPierceArmorTimer    = 0;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (!Rage1 && m_creature->GetHealthPercent() < 80.0f)
        {
            Rage1 = true;
            DoCastSpellIfCan(m_creature, SPELL_RAGE);
        }

        if (!Rage2 && m_creature->GetHealthPercent() < 50.0f)
        {
            Rage2 = true;
            DoCastSpellIfCan(m_creature, SPELL_RAGE);
        }

        // Pierce Armor
        if (m_uiPierceArmorTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_PIERCE_ARMOR);
            m_uiPierceArmorTimer = urand(15000, 18000);
        }
        else
            m_uiPierceArmorTimer -= uiDiff;

        // Flamestrike
        if (m_uiFlamestrikeTimer < uiDiff)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {                            
                DoCastSpellIfCan(pTarget, SPELL_FLAMESTRIKE);
                m_uiFlamestrikeTimer = urand(5000, 10000);
            }
        }
        else 
            m_uiFlamestrikeTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
            m_uiCleaveTimer = urand(6000, 10000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        // Confliguration
        if (m_uiConfligurationTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CONFLIGURATION);
            m_uiConfligurationTimer = urand(15000, 25000);
        }
        else
            m_uiConfligurationTimer -= uiDiff;

        // Thunderclap
        if (m_uiThunderclapTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_THUNDERCLAP);
            m_uiThunderclapTimer = urand(15000, 19000);
        }
        else
            m_uiThunderclapTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_drakkisath(Creature* pCreature)
{
    return new boss_drakkisathAI(pCreature);
}

void AddSC_boss_drakkisath()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_drakkisath";
    newscript->GetAI = &GetAI_boss_drakkisath;
    newscript->RegisterSelf();
}
