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
SDName: Boss_Halycon
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

#define SPELL_CROWDPUMMEL       10887
#define SPELL_MIGHTYBLOW        14099
#define NPC_GIZRUL                10268

#define ADD_X                  -169.839203f
#define ADD_Y                  -324.961395f
#define ADD_Z                  64.401443f
#define ADD_O                  3.124724f

struct MANGOS_DLL_DECL boss_halyconAI : public ScriptedAI
{
    boss_halyconAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 CrowdPummel_Timer;
    uint32 MightyBlow_Timer;
    bool bSummoned;
    Creature* crSummoned;

    void Reset()
    {
        CrowdPummel_Timer = urand(6000, 10000);
        MightyBlow_Timer = urand(8000, 12000);
        bSummoned = false;
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

        //CrowdPummel_Timer
        if (CrowdPummel_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CROWDPUMMEL);
            CrowdPummel_Timer = urand(6000, 10000);
        }
        else
            CrowdPummel_Timer -= diff;

        //MightyBlow_Timer
        if (MightyBlow_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_MIGHTYBLOW);
            MightyBlow_Timer = urand(8000, 12000);
        }
        else
            MightyBlow_Timer -= diff;

        //Summon Gizrul
        if (!bSummoned && m_creature->GetHealthPercent() < 33.0f)
        {
            crSummoned = m_creature->SummonCreature(NPC_GIZRUL, ADD_X, ADD_Y, ADD_Z, ADD_O, TEMPSUMMON_TIMED_DESPAWN, 300000);
            ((CreatureAI*)crSummoned->AI())->AttackStart(m_creature->getVictim());

            bSummoned = true;
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_halycon(Creature* pCreature)
{
    return new boss_halyconAI(pCreature);
}

void AddSC_boss_halycon()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_halycon";
    newscript->GetAI = &GetAI_boss_halycon;
    newscript->RegisterSelf();
}
