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
SDName: Boss_Solakar_Flamewreath
SD%Complete: 100
SDComment: Script for UBRS boss Solakar Flamewreath (Entry 10264)
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_WAR_STOMP         = 16079,
    SPELL_HATCH_ROOKERY_EGG = 15746,
    
    SAY_AGGRO               = -1615002
};

struct MANGOS_DLL_DECL boss_solakar_flamewreathAI : public ScriptedAI
{
   
    boss_solakar_flamewreathAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 War_Stomp_Timer;
    uint32 Summon_Whelp_Timer;
    uint32 SecondCastTimer;

    Creature* WaveMob[2];
    
    bool inCombat;

    void Reset()
    {
        if (!m_pInstance)
            return;

        WaveMob[0] = NULL;
        WaveMob[1] = NULL;
        inCombat = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_OFF);
        War_Stomp_Timer = urand(4000, 8000);
        Summon_Whelp_Timer = urand(10000, 15000);
        m_pInstance->SetData(TYPE_ROOKERY_WAVE, NOT_STARTED);
        m_pInstance->SetData(TYPE_SOLAKAR_FLAMEWREATH, NOT_STARTED);
        SummonWave();
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SOLAKAR_FLAMEWREATH, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->SetInCombatWithZone();
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (inCombat)
            if (pWho && pWho->GetTypeId() == TYPEID_PLAYER && m_creature->IsHostileTo(pWho))
                m_creature->AddThreat(pWho);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SOLAKAR_FLAMEWREATH, DONE);
    }
    
    void SummonWave()
    {
        if (!m_pInstance)
            return;

        if (!WaveIsDead())
            return;

        if (m_pInstance->GetData(TYPE_ROOKERY_EVENT) == DONE)
            return;

        
        WaveMob[0] = NULL;
        WaveMob[1] = NULL;

        WaveMob[0] = m_creature->SummonCreature(NPC_ROOKERY_HATCHER, 46.678f, -261.432f, 91.881f, 5.930f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
        WaveMob[1] = m_creature->SummonCreature(NPC_ROOKERY_GUARDIAN, 47.805f, -257.153f, 94.636f, 5.745f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
    }

    bool WaveIsDead()
    {
        if (!m_pInstance)
            return false;

        for (uint8 i = 0; i < 2; i++)
            if (WaveMob[i] && WaveMob[i]->isAlive())
                return false;

        // Если зануленые адды (нужно для 1 волны, она без таймера)
        for (uint8 i = 0; i < 2; i++)
            if (!WaveMob[i])
                return true;

        m_pInstance->SetData(TYPE_ROOKERY_WAVE, m_pInstance->GetData(TYPE_ROOKERY_WAVE) + 1);
        return true;
    }
    
    void JustReachedHome()
    {
        Reset();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (!inCombat)
        {
            if (m_pInstance->GetData(TYPE_ROOKERY_EVENT) == DONE)
            {
                inCombat = true;
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->SetInCombatWithZone();
                return;
            }

            SummonWave();

            return;
        }
            
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // War Stomp Timer
        if (War_Stomp_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_WAR_STOMP);
            War_Stomp_Timer = urand(4000, 8000);
        }
        else
            War_Stomp_Timer -= uiDiff;

        if (Summon_Whelp_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_HATCH_ROOKERY_EGG);
            SecondCastTimer = 1100;
            Summon_Whelp_Timer = 9999999;
        }else Summon_Whelp_Timer -= uiDiff;


        if (SecondCastTimer)
        {
            if (SecondCastTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_HATCH_ROOKERY_EGG);
                SecondCastTimer = 0;
                Summon_Whelp_Timer = 10000;
            } else SecondCastTimer -= uiDiff;
        }

        DoMeleeAttackIfReady();
    }

};

bool GOHello_go_rookery_altar(Player* pPlayer, GameObject* pGo)
{
    instance_blackrock_spire* m_pInstance = (instance_blackrock_spire*)pGo->GetInstanceData();
    if (m_pInstance &&
        ((m_pInstance->GetData(TYPE_ROOKERY_EVENT) == NOT_STARTED &&
        m_pInstance->GetData(TYPE_SOLAKAR_FLAMEWREATH) != DONE &&
        m_pInstance->GetData(TYPE_EMBERSEER) == DONE) || pPlayer->isGameMaster()))
    {
        pPlayer->SendLoot(pGo->GetObjectGuid(), LOOT_CORPSE);
        m_pInstance->SetData(TYPE_ROOKERY_EVENT, IN_PROGRESS);
        pGo->SummonCreature(NPC_SOLAKAR_FLAMEWREATH, 46.582f, -259.351f, 92.801f, 5.776f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
        pGo->UseDoorOrButton();
    }

    return true;
}

CreatureAI* GetAI_boss_solakar_flamewreath(Creature* pCreature)
{
    return new boss_solakar_flamewreathAI(pCreature);
}

void AddSC_boss_solakar_flamewreath()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_solakar_flamewreath";
    pNewScript->GetAI = &GetAI_boss_solakar_flamewreath;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "go_rookery_altar";
    pNewScript->pGOUse = &GOHello_go_rookery_altar;
    pNewScript->RegisterSelf();
}
