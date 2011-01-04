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
SDName: Boss_Pyroguard_Emberseer
SD%Complete: 100
SDComment: Event to activate Emberseer NYI
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_FIRENOVA          = 16079,
    SPELL_FLAMEBUFFET       = 16536,
    
    SAY_AGGRO               = -1615000,
};

float CoordGuards[7][4]=
{
    {125.722f, -276.794f, 91.554f, 0.770f},     // First
    {126.000f, -258.695f, 91.552f, 6.146f},     // Second
    {125.855f, -240.363f, 91.537f, 5.502f},     // Third
    {144.317f, -240.554f, 91.538f, 4.764f},     // Fourth
    {163.149f, -240.429f, 91.543f, 3.912f},     // Fifth
    {162.610f, -258.860f, 91.535f, 3.209f},     // Sixth
    {162.671f, -277.141f, 91.611f, 2.357f}      // Seventh
};

struct MANGOS_DLL_DECL boss_pyroguard_emberseerAI : public ScriptedAI
{
   
    boss_pyroguard_emberseerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;
    
    Creature* pGuards[7];
    
    bool inCombat;

    uint32 m_uiFireNovaTimer;
    uint32 m_uiFlameBuffetTimer;
    
    uint32 uiIntro_Timer;

    void Reset()
    {
        if (!m_pInstance)
            return;
            
        for (uint8 i = 0; i < MAX_ALTAR_SLOT; i++)
            m_pInstance->SetEmberseerAltarGuid(0, i);

        inCombat = false;
        SummonGuards();
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        m_uiFireNovaTimer = urand(4000, 8000);
        m_uiFlameBuffetTimer = urand(1000, 4000);
        uiIntro_Timer = urand(10000, 15000);
        m_pInstance->SetData(TYPE_EMBERSEER, NOT_STARTED);
        m_pInstance->SetData(TYPE_EMBERSEER_ALTAR, 0);
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, IN_PROGRESS);

        DoScriptText(SAY_AGGRO, m_creature);
        m_creature->SetInCombatWithZone();
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, DONE);
    }
    
    void SummonGuards()
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_EMBERSEER) == DONE)
            return;

        m_pInstance->SetData(TYPE_EMBERSEER_GUARDS, 0);

        // Kill guards before respawn
        for (char i = 0 ; i < 7; ++i)
        {
            pGuards[i] = GetClosestCreatureWithEntry(m_creature, NPC_BLACKHAND_INCANCERATOR, DEFAULT_VISIBILITY_INSTANCE);
            if (pGuards[i])
                pGuards[i]->RemoveFromWorld();
        }

        for (char i = 0; i < 7 ; ++i)
            pGuards[i] = NULL;

        for (char i = 0; i < 7 ; ++i)
            pGuards[i] = m_creature->SummonCreature(NPC_BLACKHAND_INCANCERATOR, CoordGuards[i][0], CoordGuards[i][1], CoordGuards[i][2], CoordGuards[i][3], TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
    }
    
    bool GuardsAreDead()
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_EMBERSEER_GUARDS) < 7)
            return false;
        return true;
    }
    
    void JustReachedHome()
    {
        Reset();
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance || !GuardsAreDead())
            return;

        if (!inCombat)
        {
            if (uiIntro_Timer < uiDiff)
            {
                inCombat = true;
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                m_creature->SetInCombatWithZone();
            }
            else
                uiIntro_Timer -= uiDiff;
                
            return;
        }
            
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // FireNova Timer
        if (m_uiFireNovaTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FIRENOVA);
            m_uiFireNovaTimer = urand(4000, 8000);
        }
        else
            m_uiFireNovaTimer -= uiDiff;

        // FlameBuffet Timer
        if (m_uiFlameBuffetTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FLAMEBUFFET);
            m_uiFlameBuffetTimer = urand(12000, 16000);
        }
        else
            m_uiFlameBuffetTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }

};

enum
{
    SPELL_ENCAGE             = 16045,
    SPELL_STRIKE             = 15580,
    SPELL_ENCAGE_EMBERSEER   = 15281
};

struct MANGOS_DLL_DECL mob_blackhand_incanceratorAI : public ScriptedAI
{
    mob_blackhand_incanceratorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 Encage_Timer;
    uint32 Strike_Timer;

    Creature *pPyro;

    bool inCombat;

    void Reset()
    {
        inCombat = false;
        Strike_Timer = urand(5000, 10000);
        Encage_Timer = urand(15000, 30000);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->InterruptNonMeleeSpells(false,SPELL_ENCAGE_EMBERSEER);
        m_creature->RemoveAurasDueToSpell(SPELL_ENCAGE_EMBERSEER);
        m_creature->SetInCombatWithZone();
    }

    void JustReachedHome()
    {
        pPyro = GetClosestCreatureWithEntry(m_creature, NPC_PYROGUARD_EMBERSEER, DEFAULT_VISIBILITY_INSTANCE);
        if (pPyro)
            ((boss_pyroguard_emberseerAI*)pPyro->AI())->Reset();
    }
    
    void DamageTaken(Unit *pDoneBy, uint32 &damage)
    {
        if (!m_pInstance)
            return;

        m_creature->InterruptNonMeleeSpells(true);
        m_creature->RemoveAurasDueToSpell(SPELL_ENCAGE);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER_GUARDS, m_pInstance->GetData(TYPE_EMBERSEER_GUARDS) + 1);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!inCombat)
        {
            if (m_pInstance->GetData(TYPE_EMBERSEER_ALTAR) < 3)
            {
                DoCastSpellIfCan(m_creature, SPELL_ENCAGE_EMBERSEER);
                return;
            }
            else
            {
                inCombat = true;
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                m_creature->SetInCombatWithZone();
            }
        }

        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (Strike_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE);
            Strike_Timer = urand(5000, 7000);
        }
        else
            Strike_Timer -= diff;

        if (Encage_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_ENCAGE);
            Encage_Timer = urand(30000, 45000);
        }
        else
            Encage_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

bool GOHello_go_blackrock_altar(Player* pPlayer, GameObject* pGo)
{
    instance_blackrock_spire* m_pInstance = (instance_blackrock_spire*)pGo->GetInstanceData();
    if (m_pInstance)
    {
        if (pPlayer->isGameMaster())
            m_pInstance->SetData(TYPE_EMBERSEER_ALTAR, MAX_ALTAR_SLOT);
        else
        {
            for (uint8 i = 0; i < MAX_ALTAR_SLOT; i++)
            {
                if (m_pInstance->GetEmberseerAltarGuid(i) == 0 && m_pInstance->GetEmberseerAltarGuid(i) != pPlayer->GetGUID())
                {
                    for (uint8 j = 0; j < MAX_ALTAR_SLOT; j++)
                        if (m_pInstance->GetEmberseerAltarGuid(i) == pPlayer->GetGUID())
                            return true;

                    m_pInstance->SetEmberseerAltarGuid(pPlayer->GetGUID(), i);
                    m_pInstance->SetData(TYPE_EMBERSEER_ALTAR, m_pInstance->GetData(TYPE_EMBERSEER_ALTAR) + 1);
                    return true;
                }
                else continue;
            }
        }
    }

    return true;
}

CreatureAI* GetAI_mob_blackhand_incancerator(Creature* pCreature)
{
    return new mob_blackhand_incanceratorAI(pCreature);
}

CreatureAI* GetAI_boss_pyroguard_emberseer(Creature* pCreature)
{
    return new boss_pyroguard_emberseerAI(pCreature);
}

void AddSC_boss_pyroguard_emberseer()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_pyroguard_emberseer";
    pNewScript->GetAI = &GetAI_boss_pyroguard_emberseer;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "mob_blackhand_incancerator";
    pNewScript->GetAI = &GetAI_mob_blackhand_incancerator;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "go_blackrock_altar";
    pNewScript->pGOUse = &GOHello_go_blackrock_altar;
    pNewScript->RegisterSelf();
}
