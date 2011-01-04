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
SDName: Boss_Warmaster_Voone
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

#define SPELL_SNAPKICK          15618
#define SPELL_CLEAVE            15284
#define SPELL_UPPERCUT          10966
#define SPELL_MORTALSTRIKE      15708
#define SPELL_PUMMEL            15615
#define SPELL_THROWAXE          16075

struct MANGOS_DLL_DECL boss_warmastervooneAI : public ScriptedAI
{
    boss_warmastervooneAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 Snapkick_Timer;
    uint32 Cleave_Timer;
    uint32 Uppercut_Timer;
    uint32 MortalStrike_Timer;
    uint32 Pummel_Timer;
    uint32 ThrowAxe_Timer;

    void Reset()
    {
        Snapkick_Timer = urand(6000, 12000);
        Cleave_Timer = urand(12000, 16000);
        Uppercut_Timer = urand(18000, 22000);
        MortalStrike_Timer = urand(10000, 14000);
        Pummel_Timer = urand(28000, 32000);
        ThrowAxe_Timer = 1000;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        //Snapkick_Timer
        if (Snapkick_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_SNAPKICK);
            Snapkick_Timer = urand(4000, 8000);
        }else Snapkick_Timer -= diff;

        //Cleave_Timer
        if (Cleave_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE);
            Cleave_Timer = urand(10000, 14000);
        }else Cleave_Timer -= diff;

        //Uppercut_Timer
        if (Uppercut_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_UPPERCUT);
            Uppercut_Timer = urand(12000, 16000);
        }else Uppercut_Timer -= diff;

        //MortalStrike_Timer
        if (MortalStrike_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_MORTALSTRIKE);
            MortalStrike_Timer = urand(8000, 12000);
        }else MortalStrike_Timer -= diff;

        //Pummel_Timer
        if (Pummel_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_PUMMEL);
            Pummel_Timer = urand(14000, 18000);
        }else Pummel_Timer -= diff;

        //ThrowAxe_Timer
        if (ThrowAxe_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_THROWAXE);
            ThrowAxe_Timer = urand(6000, 10000);
        }else ThrowAxe_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_warmastervoone(Creature* pCreature)
{
    return new boss_warmastervooneAI(pCreature);
}

void AddSC_boss_warmastervoone()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_warmaster_voone";
    newscript->GetAI = &GetAI_boss_warmastervoone;
    newscript->RegisterSelf();
}
