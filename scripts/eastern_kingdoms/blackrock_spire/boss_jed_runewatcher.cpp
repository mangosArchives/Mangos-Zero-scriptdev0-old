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
SDName: Boss_Jed_Runewatcher
SD%Complete: 100
SDComment: Script for Rare boss Jed Runewatcher (id 10509)
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_SHIELD_BASH       = 11972,
    SPELL_SHIELD_CHARGE     = 15749,
    SPELL_STRIKE            = 14516
};

struct MANGOS_DLL_DECL boss_jed_runewatcherAI : public ScriptedAI
{
    boss_jed_runewatcherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 Shield_Bash_Timer;
    uint32 Shield_Charge_Timer;
    uint32 Strike_Timer;
    
    void Reset() 
    {
        Shield_Charge_Timer = 0;
        Shield_Bash_Timer = urand(6000, 12000);
        Strike_Timer = urand(3000, 7000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);

        if (Unit *victim = m_creature->getVictim())
            DoCastSpellIfCan(victim, SPELL_SHIELD_CHARGE);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Strike
        if (Strike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE);
            Strike_Timer = urand(3000, 7000);
        }else Strike_Timer -= uiDiff;

        // Shield Bash
        if (Shield_Bash_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHIELD_BASH);
            Shield_Bash_Timer = urand(6000, 12000);
        }else Shield_Bash_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_jed_runewatcher(Creature* pCreature)
{
    return new boss_jed_runewatcherAI(pCreature);
}

void AddSC_boss_jed_runewatcher()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_jed_runewatcher";
    pNewScript->GetAI = &GetAI_boss_jed_runewatcher;
    pNewScript->RegisterSelf();
}
