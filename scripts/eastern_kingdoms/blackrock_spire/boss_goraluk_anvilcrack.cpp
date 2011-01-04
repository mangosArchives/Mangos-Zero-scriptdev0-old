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
SDName: Boss_Goraluk_Anvilcrack
SD%Complete: 100
SDComment: Script for boss Goraluk Anvilcrack (id 10899)
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_BACKHAND          = 6253,
    SPELL_HEAD_CRACK        = 16172,
    SPELL_STRIKE            = 15580
};

struct MANGOS_DLL_DECL boss_goraluk_anvilcrackAI : public ScriptedAI
{
   
    boss_goraluk_anvilcrackAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;
    
    uint32 Backhand_Timer;
    uint32 Head_Crack_Timer;
    uint32 Strike_Timer;
    
    void Reset() 
    {
        Backhand_Timer = urand(4000, 8000);
        Head_Crack_Timer = 0;
        Strike_Timer = urand(3000, 7000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Backhand
        if (Backhand_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_BACKHAND);
            Backhand_Timer = urand(4000, 8000);
        }else Backhand_Timer -= uiDiff;

        // Head Crack
        if (Head_Crack_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_HEAD_CRACK);
            Head_Crack_Timer = urand(6000, 12000);
        }else Head_Crack_Timer -= uiDiff;
        
        // Strike
        if (Strike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE);
            Strike_Timer = urand(3000, 7000);
        }else Strike_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_goraluk_anvilcrack(Creature* pCreature)
{
    return new boss_goraluk_anvilcrackAI(pCreature);
}

void AddSC_boss_goraluk_anvilcrack()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_goraluk_anvilcrack";
    pNewScript->GetAI = &GetAI_boss_goraluk_anvilcrack;
    pNewScript->RegisterSelf();
}
