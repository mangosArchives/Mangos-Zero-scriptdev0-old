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
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

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

CreatureAI* Zero_GetAI_boss_drakkisath(Creature* pCreature)
{
    return new boss_drakkisathAI(pCreature);
}




/* ScriptData
SDName: Boss_Goraluk_Anvilcrack
SD%Complete: 100
SDComment: Script for boss Goraluk Anvilcrack (id 10899)
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_BACKHAND          = 6253,
    SPELL_HEAD_CRACK        = 16172,
    SPELL_STRIKE_4            = 15580
};

struct MANGOS_DLL_DECL boss_goraluk_anvilcrackAI : public ScriptedAI
{
   
    boss_goraluk_anvilcrackAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;
    
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
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE_4);
            Strike_Timer = urand(3000, 7000);
        }else Strike_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_goraluk_anvilcrack(Creature* pCreature)
{
    return new boss_goraluk_anvilcrackAI(pCreature);
}

/* ScriptData
SDName: Boss_Shadow_Hunter_Voshgajin
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_CURSEOFBLOOD = 24673,
    SPELL_HEX          = 16708,
	SPELL_CLEAVE_2     = 20691
};

struct MANGOS_DLL_DECL boss_shadowvoshAI : public ScriptedAI
{
    boss_shadowvoshAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiCurseOfBloodTimer;
    uint32 m_uiHexTimer;
    uint32 m_uiCleaveTimer;

    void Reset()
    {
        m_uiCurseOfBloodTimer = urand(1000, 4000);
        m_uiHexTimer          = urand(6000, 10000);
        m_uiCleaveTimer       = urand(12000, 18000);

        //m_creature->CastSpell(m_creature,SPELL_ICEARMOR,true);
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

        // Curse Of Blood
        if (m_uiCurseOfBloodTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_CURSEOFBLOOD);
            m_uiCurseOfBloodTimer = urand(40000, 45000);
        }
        else
            m_uiCurseOfBloodTimer -= uiDiff;

        // Hex
        if (m_uiHexTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_HEX);
            m_uiHexTimer = urand(12000, 18000);
        }
        else
            m_uiHexTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE_2);
            m_uiCleaveTimer = urand(5000, 10000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_shadowvosh(Creature* pCreature)
{
    return new boss_shadowvoshAI(pCreature);
}

/* ScriptData
SDName: Boss_Solakar_Flamewreath
SD%Complete: 100
SDComment: Script for UBRS boss Solakar Flamewreath (Entry 10264)
SDCategory: Blackrock Spire
EndScriptData */




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
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

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

bool Zero_GOHello_go_rookery_altar(Player* pPlayer, GameObject* pGo)
{
    zero_instance_blackrock_spire* m_pInstance = (zero_instance_blackrock_spire*)pGo->GetInstanceData();
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

CreatureAI* Zero_GetAI_boss_solakar_flamewreath(Creature* pCreature)
{
    return new boss_solakar_flamewreathAI(pCreature);
}

/* ScriptData
SDName: Boss_The_Best
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_FLAMEBREAK       = 16785,
    SPELL_IMMOLATE         = 15570,
    SPELL_TERRIFYINGROAR   = 14100,
    SPELL_FIREBALL         = 16788,
    SPELL_FIRE_BLAST       = 16144,
    SPELL_BERSERKER_CHARGE = 16636,
    SPELL_SUMMON           = 20477
};

struct MANGOS_DLL_DECL boss_thebeastAI : public ScriptedAI
{
    boss_thebeastAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiFlamebreakTimer;
    uint32 m_uiImmolateTimer;
    uint32 m_uiTerrifyingRoarTimer;
    uint32 m_uiFireballTimer;
    uint32 m_uiFireBlastTimer;
    uint32 m_uiBerserkChargeTimer;
    uint32 m_uiSummonTimer;

    Unit* pTarget;

    void Reset()
    {
        m_uiSummonTimer         = 15000;
        m_uiFireballTimer       = urand(3000, 7000);
        m_uiFireBlastTimer      = urand(8000, 16000);
        m_uiBerserkChargeTimer  = 0;
        m_uiFlamebreakTimer     = urand(10000, 14000);
        m_uiImmolateTimer       = urand(1000, 5000);
        m_uiTerrifyingRoarTimer = urand(20000, 25000);
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

        // Charge
        if (m_uiBerserkChargeTimer < uiDiff)
        {
            for (uint8 i = 0; i < 10; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                {                            
                    i = 10;
                    m_uiBerserkChargeTimer = 10000;

                    DoCastSpellIfCan(pTarget, SPELL_BERSERKER_CHARGE);
                }
            }
        }
        else 
            m_uiBerserkChargeTimer -= uiDiff;

        // Fireball
        if (m_uiFireballTimer < uiDiff)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {                           
                DoCastSpellIfCan(pTarget, SPELL_FIREBALL);
                m_uiFireballTimer = urand(5000, 10000);
            }
        }
        else 
            m_uiFireballTimer -= uiDiff;

        // Fire Blast
        if (m_uiFireBlastTimer < uiDiff)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {                            
                DoCastSpellIfCan(pTarget, SPELL_FIRE_BLAST);
                m_uiFireBlastTimer = 9000;
            }
        }
        else 
            m_uiFireBlastTimer -= uiDiff;

        // Flamebreak
        if (m_uiFlamebreakTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FLAMEBREAK);
            m_uiFlamebreakTimer = urand(8000, 12000);
        }
        else
            m_uiFlamebreakTimer -= uiDiff;

        // Immolate
        if (m_uiImmolateTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_IMMOLATE);
            
            m_uiImmolateTimer = urand(6000, 10000);
        }
        else
            m_uiImmolateTimer -= uiDiff;

        // Terrifying Roar
        if (m_uiTerrifyingRoarTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_TERRIFYINGROAR);
            m_uiTerrifyingRoarTimer = urand(18000, 20000);
        }
        else
            m_uiTerrifyingRoarTimer -= uiDiff;

        // Summon
        if (m_uiSummonTimer < uiDiff)
        {
            for (uint8 i = 0; i < 10; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER && pTarget->GetDistance(m_creature) > 35.0f)
                {                            
                    i = 10;
                    m_uiSummonTimer = 15000;

                    DoCastSpellIfCan(pTarget, SPELL_SUMMON);
                }
            }
        }
        else 
            m_uiSummonTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_thebeast(Creature* pCreature)
{
    return new boss_thebeastAI(pCreature);
}

/* ScriptData
SDName: Boss_Warmaster_Voone
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




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
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

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

CreatureAI* Zero_GetAI_boss_warmastervoone(Creature* pCreature)
{
    return new boss_warmastervooneAI(pCreature);
}

/* ScriptData
SDName: Boss_Gyth
SD%Complete: 100
SDComment: Event completed!
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_CORROSIVEACID     = 16359,
    SPELL_FREEZE            = 16350,                        // ID was wrong!
    SPELL_FLAMEBREATH       = 16390,
    SPELL_KNOCK_AWAY        = 10101,
    SPELL_CHROMATIC_CHAOS   = 16337,

    MODEL_ID_GYTH_MOUNTED   = 9723,
    MODEL_ID_GYTH           = 9806
};

struct MANGOS_DLL_DECL boss_gythAI : public ScriptedAI
{
    boss_gythAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 uiCorrosiveAcidTimer;
    uint32 uiFreezeTimer;
    uint32 uiFlamebreathTimer;
    uint32 uiKnockAwayTimer;
    uint32 DoorTimer;

    bool inCombat;
    bool isMove;
    bool m_bSummonedRend;
    bool m_bBuffed;

    Creature* pRend;
    Creature* pNefarius;

    void Reset()
    {
        if (!m_pInstance)
            return;

        uiCorrosiveAcidTimer = 8000;
        uiFreezeTimer = 11000;
        uiFlamebreathTimer = 4000;
        uiKnockAwayTimer = 15000;
        DoorTimer = 10000;
        inCombat = false;
        m_bSummonedRend = false;
        m_bBuffed = false;
        isMove = false;
        pRend = NULL;
        pNefarius = NULL;
        inCombat = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_OFF);
        m_creature->SetDisplayId(MODEL_ID_GYTH_MOUNTED);
        m_pInstance->SetData(TYPE_GYTH, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        if (!m_pInstance)
            return;

        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_GYTH, DONE);
            if (m_pInstance->GetData(TYPE_GYTH_LOOTED) == DONE)
                m_creature->RemoveFromWorld();

            if (m_pInstance->GetData(TYPE_GYTH_LOOTED) != DONE)
                m_pInstance->SetData(TYPE_GYTH_LOOTED, DONE);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (!inCombat)
        {
            if (m_pInstance->GetData(TYPE_GYTH) == IN_PROGRESS)
            {
                inCombat = true;
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetVisibility(VISIBILITY_ON);
                return;
            }
            return;
        }

        if (!isMove)
        {
            isMove = true;
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MovePoint(0, 153.763f, -419.833f, 110.472f);
        }

        if (GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_STADIUM_COMBAT_DOOR)))
        {
            if (pDoor->GetGoState() == GO_STATE_ACTIVE)
            {
                if (DoorTimer < uiDiff)
                    pDoor->UseDoorOrButton();
                else DoorTimer -= uiDiff;
            }
        }

        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        else EnterCombat(m_creature->getVictim());

        // Corrosive Acid
        if (uiCorrosiveAcidTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_CORROSIVEACID);
            uiCorrosiveAcidTimer = 7000;
        }
        else
            uiCorrosiveAcidTimer -= uiDiff;

        // Freeze_Timer
        if (uiFreezeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FREEZE) == CAST_OK)
            uiFreezeTimer = 16000;
        }
        else
            uiFreezeTimer -= uiDiff;

        // Flamebreath
        if (uiFlamebreathTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FLAMEBREATH);
            uiFlamebreathTimer = 10500;
        }
        else
            uiFlamebreathTimer -= uiDiff;

        // Knock Away
        if (uiKnockAwayTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_KNOCK_AWAY);
            uiKnockAwayTimer = 9000;
        }
        else
            uiKnockAwayTimer -= uiDiff;

        // Summon Rend
        if (!m_bSummonedRend && m_creature->GetHealthPercent() < 15.0f)
        {
            pRend = GetClosestCreatureWithEntry(m_creature, NPC_REND_BLACKHAND, DEFAULT_VISIBILITY_INSTANCE);
            if (pRend)
                pRend->Relocate(m_creature->GetPositionX() + 5.0f, m_creature->GetPositionY() + 5.0f, m_creature->GetPositionZ());

            m_pInstance->SetData(TYPE_REND_BLACKHAND, SPECIAL);

            // summon Rend and Change model to normal Gyth
            // Inturrupt any spell casting
            m_creature->InterruptNonMeleeSpells(false);
            // Gyth model
            m_creature->SetDisplayId(MODEL_ID_GYTH);
            m_bSummonedRend = true;
        }


        // Chromatic Chaos
        if (!m_bBuffed && m_creature->GetHealthPercent() < 50.0f)
        {
            pNefarius = GetClosestCreatureWithEntry(m_creature, NPC_LORD_VICTOR_NEFARIUS, DEFAULT_VISIBILITY_INSTANCE);
            if (pNefarius)
            {
                DoScriptText(NEFARIUS_SAY_10, pNefarius);
                DoCastSpellIfCan(m_creature, SPELL_CHROMATIC_CHAOS);
                m_bBuffed = true;
            }
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* Zero_GetAI_boss_gyth(Creature* pCreature)
{
    return new boss_gythAI(pCreature);
}

/* ScriptData
SDName: Boss_Halycon
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




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
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

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
CreatureAI* Zero_GetAI_boss_halycon(Creature* pCreature)
{
    return new boss_halyconAI(pCreature);
}

/* ScriptData
SDName: Boss_Highlord_Omokk
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_WARSTOMP    = 24375,
    SPELL_STRIKE_2    = 18368,
    SPELL_REND        = 18106,
    SPELL_SUNDERARMOR = 24317,
    SPELL_KNOCKAWAY   = 20686,
    SPELL_SLOW        = 22356
};

struct MANGOS_DLL_DECL boss_highlordomokkAI : public ScriptedAI
{
    boss_highlordomokkAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiWarStompTimer;
    uint32 m_uiStrikeTimer;
    uint32 m_uiRendTimer;
    uint32 m_uiSunderArmorTimer;
    uint32 m_uiKnockAwayTimer;
    uint32 m_uiSlowTimer;

    void Reset()
    {
        m_uiWarStompTimer    = urand(12000, 18000);
        m_uiStrikeTimer      = urand(6000, 12000);
        m_uiRendTimer        = urand(12000, 16000);
        m_uiSunderArmorTimer = urand(1000, 4000);
        m_uiKnockAwayTimer   = urand(16000, 20000);
        m_uiSlowTimer        = urand(22000, 28000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // WarStomp
        if (m_uiWarStompTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_WARSTOMP);
            m_uiWarStompTimer = urand(12000, 18000);
        }
        else
            m_uiWarStompTimer -= uiDiff;

        // Strike
        if (m_uiStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE_2);
            m_uiStrikeTimer = urand(6000, 12000);
        }
        else
            m_uiStrikeTimer -= uiDiff;

        // Rend
        if (m_uiRendTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_REND);
            m_uiRendTimer = urand(12000, 16000);
        }
        else
            m_uiRendTimer -= uiDiff;

        // Sunder Armor
        if (m_uiSunderArmorTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUNDERARMOR);
            m_uiSunderArmorTimer = urand(26000, 29000);
        }
        else
            m_uiSunderArmorTimer -= uiDiff;

        // KnockAway
        if (m_uiKnockAwayTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_KNOCKAWAY);
            m_uiKnockAwayTimer = urand(10000, 14000);
        }
        else
            m_uiKnockAwayTimer -= uiDiff;

        // Slow
        if (m_uiSlowTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_SLOW);
            m_uiSlowTimer = urand(16000, 20000);
        }
        else
            m_uiSlowTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_highlordomokk(Creature* pCreature)
{
    return new boss_highlordomokkAI(pCreature);
}

/* ScriptData
SDName: Boss_Jed_Runewatcher
SD%Complete: 100
SDComment: Script for Rare boss Jed Runewatcher (id 10509)
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_SHIELD_BASH       = 11972,
    SPELL_SHIELD_CHARGE     = 15749,
    SPELL_STRIKE_3            = 14516
};

struct MANGOS_DLL_DECL boss_jed_runewatcherAI : public ScriptedAI
{
    boss_jed_runewatcherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

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
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE_3);
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

CreatureAI* Zero_GetAI_boss_jed_runewatcher(Creature* pCreature)
{
    return new boss_jed_runewatcherAI(pCreature);
}

/* ScriptData
SDName: Boss_Mor_Grayhoof
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    //Druid spell
    SPELL_HURRICANE              =    27530,
    SPELL_MOONFIRE               =    27737,
    SPELL_SHOCK                  =    15605,
    
    //Healing spell
    SPELL_HEALING_TOUCH          =    27527,
    SPELL_REJUVENATION           =    27532,
    
    //Bear spell
    SPELL_BEAR_FORM              =    27543,
    SPELL_DEMORALIZING_ROAR      =    27551,
    SPELL_MAUL                   =    27553,
    SPELL_SWIPE                  =    27554,
    
    //Cat spell
    SPELL_CAT_FORM               =    27545,
    SPELL_SHRED                  =    27555,
    SPELL_RAKE                   =    27556,
    SPELL_FEROCIOUS_BITE         =    27557,

    //Dragon form
    SPELL_FAERIE_DRAGON_FORM     =    27546,
    SPELL_ARCANE_EXPLOSION       =    22271,
    SPELL_REFLECTION             =    27564,
    SPELL_CHAIN_LIGHTING         =    27567
};

struct MANGOS_DLL_DECL boss_mor_grayhoofAI : public ScriptedAI
{
    boss_mor_grayhoofAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 roll;
    uint32 spell;
    
    uint32 AOE_Timer;
    uint32 Shock_Timer;
    uint32 Healing_Timer;

    uint32 BearAbilities_Timer;
    uint32 CatAbilities_Timer;
    uint32 DragonSpells_Timer;

    uint32 BearForm_Timer;
    uint32 CatForm_Timer;
    uint32 DemoralizingRoar_Timer;
    
    bool BearForm_Used;
    bool CatForm_Used;

    bool m_druidForm;
    bool m_bearForm;
    bool m_catForm;
    bool m_dragonForm;

    void Reset()
    {
        roll = 0;
        spell = 0;
        AOE_Timer = urand(5000,15000);
        Healing_Timer= urand(5000,15000);
        Shock_Timer = urand(5000,10000);
        
        BearAbilities_Timer = 2500;
        CatAbilities_Timer = 2500;
        DragonSpells_Timer = urand(5000,10000);
        
        BearForm_Timer = 10000;
        CatForm_Timer = 10000;
        DemoralizingRoar_Timer = 500;
        
        BearForm_Used = false;
        CatForm_Used = false;
        
        m_druidForm = true;
        m_bearForm = false;
        m_catForm = false;
        m_dragonForm = false;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        
        if (m_druidForm)
        {
            if (AOE_Timer < diff)
            {
                roll = urand(1,2);
                if (roll == 1) spell = SPELL_HURRICANE;
                else spell = SPELL_MOONFIRE;
                DoCastSpellIfCan(m_creature->getVictim(),spell);
                AOE_Timer = urand(5000,15000);
            }else AOE_Timer -= diff;
            
            if (Shock_Timer < diff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_SHOCK);
                Shock_Timer = urand(5000,10000);
            }else Shock_Timer -= diff;
            
            if (Healing_Timer < diff)
            {
                roll = urand(1,2);
                if (roll == 1) spell = SPELL_HEALING_TOUCH;
                else spell = SPELL_REJUVENATION;
                DoCastSpellIfCan(m_creature,spell);
                Healing_Timer = urand(5000,15000);
            }else Healing_Timer -= diff;
        }
        else if (m_bearForm)
        {
            if (DemoralizingRoar_Timer < diff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_DEMORALIZING_ROAR);
                DemoralizingRoar_Timer = 30000;
            }else DemoralizingRoar_Timer -= diff;
            
            if (BearAbilities_Timer < diff)
            {
                roll = urand(1,2);
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_MAUL-1+roll); //small hack
                BearAbilities_Timer = urand(2500,5000);
            }else BearAbilities_Timer -= diff;
        }
        else if (m_catForm)
        {
            if (CatAbilities_Timer < diff)
            {
                roll = urand(1,3);
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_SHRED-1+roll); // small hack
                CatAbilities_Timer = urand(2500,5000);
            }else CatAbilities_Timer -= diff;
        }
        else if (m_dragonForm)
        {
            if (DragonSpells_Timer < diff)
            {
                roll = urand(1,3);
                if (roll == 1) spell = SPELL_ARCANE_EXPLOSION;
                else if (roll == 2) spell = SPELL_CHAIN_LIGHTING;
                else DoCastSpellIfCan(m_creature,SPELL_REFLECTION);
                if (roll != 3) DoCastSpellIfCan(m_creature->getVictim(),spell);
                DragonSpells_Timer = urand(5000,10000);
            }else DragonSpells_Timer -= diff;
        }
        
        if ((m_creature->GetHealthPercent() < 80) && !BearForm_Used && m_druidForm)
        {
            m_creature->CastStop();
            m_creature->InterruptNonMeleeSpells(false);
            DoCastSpellIfCan(m_creature,SPELL_BEAR_FORM);
            BearForm_Used = true;
            m_bearForm = true;
            m_druidForm = false;
        }
        
        if ((m_creature->GetHealthPercent() < 60) && !CatForm_Used && m_druidForm)
        {
            m_creature->CastStop();
            m_creature->InterruptNonMeleeSpells(false);
            DoCastSpellIfCan(m_creature,SPELL_CAT_FORM);
            CatForm_Used = true;
            m_catForm = true;
            m_druidForm = false;
        }
        
        if ((m_creature->GetHealthPercent() < 35) && CatForm_Used && m_druidForm)
        {
            m_creature->CastStop();
            m_creature->InterruptNonMeleeSpells(false);
            DoCastSpellIfCan(m_creature,SPELL_FAERIE_DRAGON_FORM);
            m_dragonForm = true;
            m_druidForm = false;
        }
        
        if (m_bearForm && (BearForm_Timer < diff)) {m_bearForm = false; m_druidForm = true;}
        else if (m_bearForm) BearForm_Timer -= diff;
        
        if (m_catForm && (CatForm_Timer < diff)) {m_catForm = false; m_druidForm = true;}
        else if (m_catForm) CatForm_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_mor_grayhoof(Creature* pCreature)
{
    return new boss_mor_grayhoofAI(pCreature);
};

/* ScriptData
SDName: Boss_Mother_Smolderweb
SD%Complete: 100
SDComment: Uncertain how often mother's milk is casted
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_CRYSTALIZE              = 16104,
    SPELL_MOTHERSMILK             = 16468,
    SPELL_SUMMON_SPIRE_SPIDERLING = 16103
};

struct MANGOS_DLL_DECL boss_mothersmolderwebAI : public ScriptedAI
{
    boss_mothersmolderwebAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiCrystalizeTimer;
    uint32 m_uiMothersMilkTimer;

    void Reset()
    {
        m_uiCrystalizeTimer  = urand(18000, 22000);
        m_uiMothersMilkTimer = urand(8000, 12000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (m_creature->GetHealth() <= uiDamage)
            DoCastSpellIfCan(m_creature, SPELL_SUMMON_SPIRE_SPIDERLING, CAST_TRIGGERED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Crystalize
        if (m_uiCrystalizeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_CRYSTALIZE);
            m_uiCrystalizeTimer = urand(12000, 16000);
        }
        else
            m_uiCrystalizeTimer -= uiDiff;

        // Mothers Milk
        if (m_uiMothersMilkTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_MOTHERSMILK);
            m_uiMothersMilkTimer = urand(5000, 12500);
        }
        else
            m_uiMothersMilkTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_mothersmolderweb(Creature* pCreature)
{
    return new boss_mothersmolderwebAI(pCreature);
};

/* ScriptData
SDName: Boss_Overlord_Wyrmthalak
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

enum
{
    SPELL_BLASTWAVE            = 11130,
    SPELL_SHOUT                = 23511,
    SPELL_CLEAVE_5             = 20691,
    SPELL_KNOCKAWAY_2            = 20686,
    
    NPC_SPIRESTONE_WARLORD     = 9216,
    NPC_SMOLDERTHORN_BERSERKER = 9268

};

const float afLocations[2][4]=
{
    {-39.355381f, -513.456482f, 88.472046f, 4.679872f},
    {-49.875881f, -511.896942f, 88.195160f, 4.613114f}
};

struct MANGOS_DLL_DECL boss_overlordwyrmthalakAI : public ScriptedAI
{
    boss_overlordwyrmthalakAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiBlastWaveTimer;
    uint32 m_uiShoutTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiKnockawayTimer;
    bool m_bSummoned;

    void Reset()
    {
        m_uiBlastWaveTimer = 20000;
        m_uiShoutTimer     = 2000;
        m_uiCleaveTimer    = 6000;
        m_uiKnockawayTimer = 12000;
        m_bSummoned = false;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() != NPC_SPIRESTONE_WARLORD && pSummoned->GetEntry() != NPC_SMOLDERTHORN_BERSERKER)
            return;

        if (m_creature->getVictim())
        {
            Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
            pSummoned->AI()->AttackStart(pTarget ? pTarget : m_creature->getVictim());
        }
    }
    
    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // BlastWave
        if (m_uiBlastWaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_BLASTWAVE);
            m_uiBlastWaveTimer = 20000;
        }
        else
            m_uiBlastWaveTimer -= uiDiff;

        // Shout
        if (m_uiShoutTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_SHOUT);
            m_uiShoutTimer = 10000;
        }
        else
            m_uiShoutTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE_5);
            m_uiCleaveTimer = 7000;
        }
        else
            m_uiCleaveTimer -= uiDiff;

        // Knockaway
        if (m_uiKnockawayTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_KNOCKAWAY_2);
            m_uiKnockawayTimer = 14000;
        }
        else
            m_uiKnockawayTimer -= uiDiff;

        // Summon two Beserks
        if (!m_bSummoned && m_creature->GetHealthPercent() < 51.0f)
        {
            m_creature->SummonCreature(NPC_SPIRESTONE_WARLORD, afLocations[0][0], afLocations[0][1], afLocations[0][2], afLocations[0][3], TEMPSUMMON_TIMED_DESPAWN, 300000);
            m_creature->SummonCreature(NPC_SMOLDERTHORN_BERSERKER, afLocations[1][0], afLocations[1][1], afLocations[1][2], afLocations[1][3], TEMPSUMMON_TIMED_DESPAWN, 300000);

            m_bSummoned = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_overlordwyrmthalak(Creature* pCreature)
{
    return new boss_overlordwyrmthalakAI(pCreature);
}


/* ScriptData
SDName: Boss_Pyroguard_Emberseer
SD%Complete: 100
SDComment: Event to activate Emberseer NYI
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_FIRENOVA          = 16079,
    SPELL_FLAMEBUFFET       = 16536,
    
    SAY_AGGRO_2               = -1615000,
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
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;
    
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

        DoScriptText(SAY_AGGRO_2, m_creature);
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
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

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

bool Zero_GOHello_go_blackrock_altar(Player* pPlayer, GameObject* pGo)
{
    zero_instance_blackrock_spire* m_pInstance = (zero_instance_blackrock_spire*)pGo->GetInstanceData();
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

CreatureAI* Zero_GetAI_mob_blackhand_incancerator(Creature* pCreature)
{
    return new mob_blackhand_incanceratorAI(pCreature);
}

CreatureAI* Zero_GetAI_boss_pyroguard_emberseer(Creature* pCreature)
{
    return new boss_pyroguard_emberseerAI(pCreature);
}

/* ScriptData
SDName: Boss_Quartmaster_Zigris
SD%Complete: 100
SDComment: Needs revision
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_SHOOT          = 16496,
    SPELL_STUNBOMB       = 16497,
    SPELL_HEALING_POTION = 15504,
    SPELL_HOOKEDNET      = 15609
};

struct MANGOS_DLL_DECL boss_quatermasterzigrisAI : public ScriptedAI
{
    boss_quatermasterzigrisAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiShootTimer;
    uint32 m_uiStunBombTimer;
    //uint32 HelingPotion_Timer;

    void Reset()
    {
        m_uiShootTimer    = 1000;
        m_uiStunBombTimer = urand(12000, 16000);
        //HelingPotion_Timer = 25000;
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

        // Shoot
        if (m_uiShootTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHOOT);
            m_uiShootTimer = 500;
        }
        else
            m_uiShootTimer -= uiDiff;

        // StunBomb
        if (m_uiStunBombTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_STUNBOMB);
            m_uiStunBombTimer = urand(12000, 16000);
        }
        else
            m_uiStunBombTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_quatermasterzigris(Creature* pCreature)
{
    return new boss_quatermasterzigrisAI(pCreature);
}

/* ScriptData
SDName: Boss_Rend_Blackhand
SD%Complete: 100
SDComment: Script for UBRS boss Rend Blackhand (Entry 10429) and Stadium event
SDCategory: Blackrock Spire
EndScriptData */




enum
{
    SPELL_CLEAVE_6        = 15284,
    SPELL_ENRAGE        = 8269,
    SPELL_MORTAL_STRIKE = 15708,
    SPELL_WHIRLWIND     = 13736
};

struct MANGOS_DLL_DECL boss_rend_blackhandAI : public ScriptedAI
{
    boss_rend_blackhandAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 m_uiWhirlWindTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiMortalStrikeTimer;
    uint32 m_uiEnrageTimer;

    uint32 Nefarius_Say_2_Timer;
    uint32 DoorTimer;
    uint32 PhraseTimer;
    uint32 WaitTimer;

    uint8 t_phrase, phrase;
    uint8 introCounter;

    Unit* pNefarius;
    Creature* WaveMob[5];

    bool inCombat;
    bool isWait;
    bool isWaveMove;
    bool isWaveInCombat;
    bool Nefarius_Say_1;
    bool Nefarius_Say_2;

    void Reset()
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_STADIUM_EVENT) == DONE)
        {
            inCombat = true;
            m_uiWhirlWindTimer    = urand(15000, 19000);
            m_uiCleaveTimer       = urand(3000, 7000);
            m_uiMortalStrikeTimer = urand(6000, 10000);
            m_uiEnrageTimer       = 180000;
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_creature->SetVisibility(VISIBILITY_ON);
        }
        else
        {
            for (uint8 i = 0; i < 5; i++)
                WaveMob[i] = NULL;

            phrase = 0;
            t_phrase = 0;
            introCounter = 1;

            inCombat = false;
            isWait = false;
            isWaveMove = false;
            isWaveInCombat = false;
            Nefarius_Say_1 = false;
            Nefarius_Say_2 = false;
            Nefarius_Say_2_Timer = 8000;
            PhraseTimer = 40000;
            DoorTimer = 10000;
            WaitTimer = 10000;
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_creature->SetVisibility(VISIBILITY_OFF);
        }

        m_pInstance->SetData(TYPE_REND_BLACKHAND, NOT_STARTED);
        m_pInstance->SetData(TYPE_STADIUM_WAVE, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_REND_BLACKHAND, DONE);

        pNefarius = GetClosestCreatureWithEntry(m_creature, NPC_LORD_VICTOR_NEFARIUS, DEFAULT_VISIBILITY_INSTANCE);
        if (pNefarius)
        {
            DoScriptText(NEFARIUS_SAY_11, pNefarius);
            pNefarius->RemoveFromWorld();
        }
    }

    void SummonNefarius()
    {
        if (!m_pInstance)
            return;

        // Kill Nefarius before respawn
        pNefarius = GetClosestCreatureWithEntry(m_creature, NPC_LORD_VICTOR_NEFARIUS, DEFAULT_VISIBILITY_INSTANCE);
        if (pNefarius)
            pNefarius->RemoveFromWorld();

        pNefarius = NULL;
        pNefarius = m_creature->SummonCreature(NPC_LORD_VICTOR_NEFARIUS, 168.001f, -444.285f, 121.974f, 2.119f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);

        pNefarius->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pNefarius->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
    }

    void SummonWave()
    {
        if (!m_pInstance)
            return;

        if (!WaveIsDead())
            return;

        if (m_pInstance->GetData(TYPE_STADIUM_EVENT) == DONE)
            return;

        for (uint8 i = 0; i < 5; i++)
            WaveMob[i] = NULL;

        if (isWait)
            return;

        switch (m_pInstance->GetData(TYPE_STADIUM_WAVE))
        {
            case 0:        // 1
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 1:        // 2
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 2:        // 3
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 3:        // 4
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 4:        // 5
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 5:        // 6
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -422.039f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[4] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -417.385f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 6:        // 7
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -422.039f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[4] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -417.385f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            default:
                break;
        }

        isWaveMove = false;
        isWaveInCombat = false;

        GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_STADIUM_COMBAT_DOOR));
        if (pDoor)
            pDoor->UseDoorOrButton(); // Открытие
    }

    bool WaveIsDead()
    {
        if (!m_pInstance)
            return false;

        if (m_pInstance->GetData(TYPE_STADIUM_WAVE) < 5)
        {
            for (uint8 i = 0; i < 4; i++)
                if (WaveMob[i] && WaveMob[i]->isAlive())
                    return false;

            // Если зануленые адды
            for (uint8 i = 0; i < 4; i++)
                if (!WaveMob[i])
                    return true;
        }
        else
        {
            for (uint8 i = 0; i < 5; i++)
                if (WaveMob[i] && WaveMob[i]->isAlive())
                    return false;

            // Если зануленые адды
            for (uint8 i = 0; i < 5; i++)
                if (!WaveMob[i])
                    return true;
        }

        isWait = true;
        m_pInstance->SetData(TYPE_STADIUM_WAVE, m_pInstance->GetData(TYPE_STADIUM_WAVE) + 1);
        return true;
    }

    void RandomPhrase()
    {
        phrase = urand(0,9);

        if (phrase == t_phrase)
            return;

        switch (phrase)
        {
            case 1:
                DoScriptText(NEFARIUS_SAY_3, pNefarius);
                break;
            case 2:
                DoScriptText(NEFARIUS_SAY_4, pNefarius);
                break;
            case 3:
                DoScriptText(NEFARIUS_SAY_5, pNefarius);
                break;
            case 4:
                DoScriptText(NEFARIUS_SAY_6, pNefarius);
                break;
            case 5:
                DoScriptText(NEFARIUS_SAY_7, pNefarius);
                break;
            case 6:
                DoScriptText(REND_SAY_1, m_creature);
                break;
            case 7:
                DoScriptText(REND_SAY_2, m_creature);
                break;
            case 8:
                DoScriptText(REND_SAY_3, m_creature);
                break;
            default:
                break;
        }
        t_phrase = phrase;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_REND_BLACKHAND) == SPECIAL)
        {
            Reset();
            return;
        }

        if (!inCombat)
        {
            if (m_pInstance->GetData(TYPE_STADIUM_EVENT) == IN_PROGRESS)
            {
                if (!Nefarius_Say_1)
                {
                    m_creature->SetVisibility(VISIBILITY_ON);
                    SummonNefarius();
                    if (pNefarius)
                    {
                        DoScriptText(NEFARIUS_SAY_1, pNefarius);
                        Nefarius_Say_1 = true;
                    }
                }
                
                if (!Nefarius_Say_2 && Nefarius_Say_1)
                {
                    if (Nefarius_Say_2_Timer < uiDiff)
                    {
                        DoScriptText(NEFARIUS_SAY_2, pNefarius);
                        Nefarius_Say_2 = true;
                    }
                    else Nefarius_Say_2_Timer -= uiDiff;
                }

                if (isWait)
                {
                    if (WaitTimer < uiDiff)
                    {
                        isWait = false;
                        WaitTimer = 10000;
                    }
                    else WaitTimer -= uiDiff;
                }

                if (Nefarius_Say_2 && !isWait)
                    SummonWave();

                if (!isWaveMove)
                {
                    isWaveMove = true;
                    if (m_pInstance->GetData(TYPE_STADIUM_WAVE) < 5)
                    {
                        for (uint8 i = 0; i < 4; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 4; i++)
                        {
                            WaveMob[i]->GetMotionMaster()->Clear();
                            WaveMob[i]->GetMotionMaster()->MovePoint(0, 153.763f, -419.833f, 110.472f);
                        }
                    }
                    else
                    {
                        for (uint8 i = 0; i < 5; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 5; i++)
                        {
                            WaveMob[i]->GetMotionMaster()->Clear();
                            WaveMob[i]->GetMotionMaster()->MovePoint(0, 153.763f, -419.833f, 110.472f);
                        }
                    }
                }

                if (!isWaveInCombat)
                {
                    isWaveInCombat = true;
                    if (m_pInstance->GetData(TYPE_STADIUM_WAVE) < 5)
                    {
                        for (uint8 i = 0; i < 4; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 4; i++)
                            if (WaveMob[i]->SelectHostileTarget() || WaveMob[i]->getVictim())
                                EnterCombat(WaveMob[i]->getVictim());
                    }
                    else
                    {
                        for (uint8 i = 0; i < 5; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 5; i++)
                            if (WaveMob[i]->SelectHostileTarget() || WaveMob[i]->getVictim())
                                EnterCombat(WaveMob[i]->getVictim());
                    }
                }

                if (GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_STADIUM_COMBAT_DOOR)))
                {
                    if (pDoor->GetGoState() == GO_STATE_ACTIVE)
                    {
                        if (DoorTimer < uiDiff)
                        {
                            pDoor->UseDoorOrButton();
                            DoorTimer = 10000;
                        }
                        else DoorTimer -= uiDiff;
                    }
                }
            }

            if (m_pInstance->GetData(TYPE_STADIUM_EVENT) != DONE)
            {
                if (PhraseTimer < uiDiff)
                {
                    if (isWaveInCombat)
                        RandomPhrase();
                    PhraseTimer = 40000;
                } else PhraseTimer -= uiDiff;
            }
            else
            {
                if (!introCounter)
                    return;

                switch (introCounter)
                {
                    case 1:
                        DoScriptText(NEFARIUS_SAY_8, pNefarius);
                        PhraseTimer = 3000;
                        introCounter++;
                        break;
                    case 2:
                        if (PhraseTimer < uiDiff)
                        {
                            DoScriptText(REND_SAY_4, m_creature);
                            PhraseTimer = 3000;
                            introCounter++;
                        }
                        else PhraseTimer -= uiDiff;
                        break;
                    case 3:
                        if (PhraseTimer < uiDiff)
                        {
                            DoScriptText(NEFARIUS_SAY_9, pNefarius);
                            m_creature->SetVisibility(VISIBILITY_OFF);
                            PhraseTimer = 35000;
                            introCounter++;
                        }
                        else PhraseTimer -= uiDiff;
                        break;
                    case 4:
                        if (PhraseTimer < uiDiff)
                        {
                            m_pInstance->SetData(TYPE_GYTH, IN_PROGRESS);
                            introCounter = 0;
                        }
                        else PhraseTimer -= uiDiff;
                        break;
                }
            }
            return;
        }

        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // WhirlWind
        if (m_uiWhirlWindTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_WHIRLWIND);
            m_uiWhirlWindTimer = urand(15000, 20000);
        }
        else
            m_uiWhirlWindTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE_6);
            m_uiCleaveTimer = urand(7000, 11000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        // Mortal Strike
        if (m_uiMortalStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_STRIKE);
            m_uiMortalStrikeTimer = urand(11000, 15000);
        }
        else
            m_uiMortalStrikeTimer -= uiDiff;

        // Enrage
        if (m_uiEnrageTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_ENRAGE);
            m_uiEnrageTimer = 180000;
        }
        else
            m_uiEnrageTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_boss_rend_blackhand(Creature* pCreature)
{
    return new boss_rend_blackhandAI(pCreature);
}

/* ScriptData
SDName: Blackhand Summoner, Blackhand Veteran, Blackhand Dreadweaver, Rage Talon Dragospawn, Jed Runewatcher
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */




/*######
## mob_blackhand_summoner
######*/

enum
{
    SPELL_FIREBALL_2            = 12466,
    SPELL_FROST_NOVA            = 15532,
    SPELL_SUMMON_VETERAN        = 15794,
    SPELL_SUMMON_DREADWEAVER    = 15792
};

struct MANGOS_DLL_DECL mob_blackhand_summonerAI : public ScriptedAI
{
    mob_blackhand_summonerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Fireball_Timer;
    uint32 Frost_Nova_Timer;
    
    Unit* pTarget;
    
    void Reset() 
    {
        Fireball_Timer = 0;
        Frost_Nova_Timer = urand(10000, 15000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);
        uint8 roll = urand(0,1);
        DoCastSpellIfCan(m_creature, roll == 0 ? SPELL_SUMMON_VETERAN : SPELL_SUMMON_DREADWEAVER);
    }

    void JustDied(Unit* pKiller)
    {
        m_pInstance->SetData64(TYPE_ROOM_EVENT, m_creature->GetGUID());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Fireball
        if (Fireball_Timer < uiDiff)
        {
            for (char i = 0; i < 5; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                {
                    i = 5;
                    DoCastSpellIfCan(pTarget, SPELL_FIREBALL_2);
                }
            }
            Fireball_Timer = urand(5000, 10000);
        }else Fireball_Timer -= uiDiff;

        // Frost Nova
        if (Frost_Nova_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature,SPELL_FROST_NOVA);
            Frost_Nova_Timer = urand(10000, 15000);
        } else Frost_Nova_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_blackhand_veteran
######*/

enum
{
    SPELL_SHIELD_BASH_2       = 11972,
    SPELL_SHIELD_CHARGE_2     = 15749,
    SPELL_STRIKE_5			  = 14516
};

struct MANGOS_DLL_DECL mob_blackhand_veteranAI : public ScriptedAI
{
    mob_blackhand_veteranAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Shield_Bash_Timer;
    uint32 Shield_Charge_Timer;
    uint32 Strike_Timer;
    
    void Reset() 
    {
        Shield_Charge_Timer = 0;
        Shield_Bash_Timer = urand(7000, 15000);
        Strike_Timer = urand(5000, 10000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);

        if (Unit *victim = m_creature->getVictim())
            DoCastSpellIfCan(victim, SPELL_SHIELD_CHARGE_2);
    }

    void JustDied(Unit* pKiller)
    {
        m_pInstance->SetData64(TYPE_ROOM_EVENT, m_creature->GetGUID());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Strike
        if (Strike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE_5);
            Strike_Timer = urand(5000, 10000);
        }else Strike_Timer -= uiDiff;

        // Shield Bash
        if (Shield_Bash_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHIELD_BASH_2);
            Shield_Bash_Timer = urand(8000, 15000);
        }else Shield_Bash_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_blackhand_dreadweaver
######*/

enum
{
    SPELL_CURSE_OF_THORNS   = 16247,
    SPELL_SHADOW_BOLT       = 12739,
    SPELL_VEIL_OF_SHADOW    = 7068
};

struct MANGOS_DLL_DECL mob_blackhand_dreadweaverAI : public ScriptedAI
{
    mob_blackhand_dreadweaverAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Curse_Of_Thorns_Timer;
    uint32 Shadow_Bolt_Timer;
    uint32 Veil_Of_Shadow_Timer;
    
    Unit* pTarget;
    
    void Reset() 
    {
        Curse_Of_Thorns_Timer = 0;
        Shadow_Bolt_Timer = urand(5000, 10000);
        Veil_Of_Shadow_Timer = urand(7000, 15000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);
        
        for (char i = 0; i < 5; i++)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {
                i = 5;
                DoCastSpellIfCan(pTarget, SPELL_CURSE_OF_THORNS);
            }
        }
        
        Curse_Of_Thorns_Timer = urand(15000, 30000);
    }

    void JustDied(Unit* pKiller)
    {
        m_pInstance->SetData64(TYPE_ROOM_EVENT, m_creature->GetGUID());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Shadow Bolt
        if (Shadow_Bolt_Timer < uiDiff)
        {
            for (char i = 0; i < 5; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                {
                    i = 5;
                    DoCastSpellIfCan(pTarget, SPELL_SHADOW_BOLT);
                }
            }
                Shadow_Bolt_Timer = urand(5000, 10000);
        }else Shadow_Bolt_Timer -= uiDiff;
        
        // Veil of Shadow
        if (Shadow_Bolt_Timer < uiDiff)
        {
            for (char i = 0; i < 5; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                {
                    i = 5;
                    DoCastSpellIfCan(pTarget, SPELL_VEIL_OF_SHADOW);
                }
            }
                Veil_Of_Shadow_Timer = urand(10000, 15000);
        }else Veil_Of_Shadow_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_rookery_hatcher
######*/

enum
{
    SPELL_HATCH_ROOKERY_EGG_2 = 15746,
    SPELL_SUNDER_ARMOR		  = 15572,
    SPELL_STRIKE_HATCHER      = 15580,

    MOB_HATCHER               = 10683,

    SAY_BEGIN                 = -1615001
};

struct MANGOS_DLL_DECL mob_rookery_hatcher_guardianAI : public ScriptedAI
{
    mob_rookery_hatcher_guardianAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Strike_Timer;
    uint32 Sunder_Armor_Timer;
    uint32 Wave_Timer;

    // For Hatcher
    uint32 Summon_Whelp_Timer;
    uint32 SecondCastTimer;

    bool isHatcher;
    bool inCombat;
    
    void Reset() 
    {
        inCombat = true;
        if (m_pInstance->GetData(TYPE_ROOKERY_WAVE))
        {
            inCombat = false;
            Wave_Timer = 7000;
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->SetVisibility(VISIBILITY_OFF);
        }
        isHatcher = m_creature->GetEntry() == MOB_HATCHER ? true : false;
        SecondCastTimer = 0;
        Summon_Whelp_Timer = urand(10000, 15000);
        Strike_Timer = urand(3000, 7000);
        Sunder_Armor_Timer = urand(5000, 10000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);

        if (!m_pInstance->GetData(TYPE_ROOKERY_WAVE) && isHatcher)
            DoScriptText(SAY_BEGIN, m_creature);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        if (inCombat)
            if (pWho && pWho->GetTypeId() == TYPEID_PLAYER && m_creature->IsHostileTo(pWho))
                m_creature->AddThreat(pWho);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!inCombat)
        {
            if (Wave_Timer < uiDiff)
            {
                inCombat = true;
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetVisibility(VISIBILITY_ON);
                m_creature->SetInCombatWithZone();
                return;
            }else Wave_Timer -= uiDiff;

            return;
        }

        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Strike
        if (Strike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE_HATCHER);
            Strike_Timer = urand(3000, 7000);
        }else Strike_Timer -= uiDiff;
        
        // Sunder Armor
        if (Sunder_Armor_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUNDER_ARMOR);
            Sunder_Armor_Timer = urand(5000, 10000);
        }else Sunder_Armor_Timer -= uiDiff;
        
        if (isHatcher)
        {
            if (Summon_Whelp_Timer < uiDiff)
            {
                DoCastSpellIfCan(m_creature, SPELL_HATCH_ROOKERY_EGG_2);
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
        }

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_chromatic_dragonspawn
######*/

enum
{
    SPELL_CLEAVE_7              = 12466
};

struct MANGOS_DLL_DECL mob_chromatic_dragonspawnAI : public ScriptedAI
{
    mob_chromatic_dragonspawnAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Strike_Timer;
    uint32 Cleave_Timer;
    
    void Reset() 
    {
        Strike_Timer = urand(4000, 8000);
        Cleave_Timer = urand(10000, 15000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_creature->RemoveFromWorld();
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Strike
        if (Strike_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE_HATCHER);
            Strike_Timer = urand(4000, 8000);
        }else Strike_Timer -= uiDiff;

        // Cleave
        if (Cleave_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE_7);
            Cleave_Timer = urand(10000, 15000);
        } else Cleave_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_chromatic_whelp
######*/

enum
{
    SPELL_FIREBALL_VOLLEY = 16250,
    SPELL_FROSTBOLT       = 15249,
    SPELL_LIGHTNINGBOLT   = 12167
};

struct MANGOS_DLL_DECL mob_chromatic_whelpAI : public ScriptedAI
{
    mob_chromatic_whelpAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Bolt_Timer;

    Unit* pTarget;
    
    void Reset() 
    {
        Bolt_Timer = 0;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_creature->RemoveFromWorld();
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Bolts
        if (Bolt_Timer < uiDiff)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {
                uint8 bolt = urand(0,2);
                switch (bolt)
                {
                    case 0:
                        DoCastSpellIfCan(m_creature->getVictim(), SPELL_FIREBALL_VOLLEY);
                        break;
                    case 1:
                        DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROSTBOLT);
                        break;
                    case 2:
                        DoCastSpellIfCan(m_creature->getVictim(), SPELL_LIGHTNINGBOLT);
                        break;
                }
            }
            Bolt_Timer = urand(2000, 4000);
        }else Bolt_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_dragon_handler
######*/

enum
{
    SPELL_MEND_DRAGON = 16637
};

struct MANGOS_DLL_DECL mob_dragon_handlerAI : public ScriptedAI
{
    mob_dragon_handlerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (zero_instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    zero_instance_blackrock_spire* m_pInstance;

    uint32 Mend_Dragon_Timer;

    Creature* pDragon;
    
    void Reset() 
    {
        Mend_Dragon_Timer = urand(4000, 8000);
        pDragon = NULL;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_creature->RemoveFromWorld();
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Mend Dragon
        if (Mend_Dragon_Timer < uiDiff)
        {
            pDragon = GetClosestCreatureWithEntry(m_creature, NPC_CHROMATIC_DRAGONSPAWN, DEFAULT_VISIBILITY_INSTANCE);
            if (pDragon && pDragon->GetHealthPercent() < 50.0f)
                DoCastSpellIfCan(pDragon, SPELL_MEND_DRAGON);

            Mend_Dragon_Timer = urand(4000, 8000);
        }else Mend_Dragon_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* Zero_GetAI_mob_dragon_handler(Creature* pCreature)
{
    return new mob_dragon_handlerAI(pCreature);
}

CreatureAI* Zero_GetAI_mob_chromatic_whelp(Creature* pCreature)
{
    return new mob_chromatic_whelpAI(pCreature);
}

CreatureAI* Zero_GetAI_mob_chromatic_dragonspawn(Creature* pCreature)
{
    return new mob_chromatic_dragonspawnAI(pCreature);
}

CreatureAI* Zero_GetAI_mob_rookery_hatcher_guardian(Creature* pCreature)
{
    return new mob_rookery_hatcher_guardianAI(pCreature);
}

CreatureAI* Zero_GetAI_mob_blackhand_summoner(Creature* pCreature)
{
    return new mob_blackhand_summonerAI(pCreature);
}

CreatureAI* Zero_GetAI_mob_blackhand_veteran(Creature* pCreature)
{
    return new mob_blackhand_veteranAI(pCreature);
}

CreatureAI* Zero_GetAI_mob_blackhand_dreadweaver(Creature* pCreature)
{
    return new mob_blackhand_dreadweaverAI(pCreature);
}

/* ScriptData
SDName: zero_instance_blackrock_spire
SD%Complete: 100
SDComment: Events scripts are completed!
SDCategory: Blackrock Spire
EndScriptData */




zero_instance_blackrock_spire::zero_instance_blackrock_spire(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void zero_instance_blackrock_spire::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    memset(&m_auiRoomRuneGUID, 0, sizeof(m_auiRoomRuneGUID));

    for (uint8 i = 0; i < MAX_ALTAR_SLOT; i++)
        t_AltarGuid[i] = 0;
}

void zero_instance_blackrock_spire::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_ENTER_UBRS_DOOR:
            m_uiEnterUBRSDoorGUID = pGo->GetGUID();
            if (GetData(TYPE_ROOM_EVENT) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
        case GO_EMBERSEER_ENTRY_DOOR:
            m_uiEmberseerEntryDoorGUID = pGo->GetGUID();
            if (GetData(TYPE_ROOM_EVENT) == DONE)            
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_EMBERSEER_COMBAT_DOOR:
            m_uiEmberseerCombatDoorGUID = pGo->GetGUID();
            if (GetData(TYPE_EMBERSEER) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_EMBERSEER_EXIT_DOOR:
            m_uiEmberseerExitDoorGUID = pGo->GetGUID();
            break;
        case GO_EMBERSEER_ALTAR:
            m_uiEmberseerAltarGUID = pGo->GetGUID();
            break;
        case GO_STADIUM_ENTRY_DOOR:
            m_uiStadiumEntryDoorGUID = pGo->GetGUID();
            break;
        case GO_STADIUM_COMBAT_DOOR:
            m_uiStadiumCombatDoorGUID = pGo->GetGUID();
            break;
        case GO_STADIUM_EXIT_DOOR:
            m_uiStadiumExitDoorGUID = pGo->GetGUID();
            if (GetData(TYPE_REND_BLACKHAND) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_ROOM_1_RUNE: m_auiRoomRuneGUID[0] = pGo->GetGUID(); break;
        case GO_ROOM_2_RUNE: m_auiRoomRuneGUID[1] = pGo->GetGUID(); break;
        case GO_ROOM_3_RUNE: m_auiRoomRuneGUID[2] = pGo->GetGUID(); break;
        case GO_ROOM_4_RUNE: m_auiRoomRuneGUID[3] = pGo->GetGUID(); break;
        case GO_ROOM_5_RUNE: m_auiRoomRuneGUID[4] = pGo->GetGUID(); break;
        case GO_ROOM_6_RUNE: m_auiRoomRuneGUID[5] = pGo->GetGUID(); break;
        case GO_ROOM_7_RUNE: m_auiRoomRuneGUID[6] = pGo->GetGUID(); break;

        case GO_EMBERSEER_RUNE_1: m_auiEmberseerRuneGUID[0] = pGo->GetGUID(); break;
        case GO_EMBERSEER_RUNE_2: m_auiEmberseerRuneGUID[1] = pGo->GetGUID(); break;
        case GO_EMBERSEER_RUNE_3: m_auiEmberseerRuneGUID[2] = pGo->GetGUID(); break;
        case GO_EMBERSEER_RUNE_4: m_auiEmberseerRuneGUID[3] = pGo->GetGUID(); break;
        case GO_EMBERSEER_RUNE_5: m_auiEmberseerRuneGUID[4] = pGo->GetGUID(); break;
        case GO_EMBERSEER_RUNE_6: m_auiEmberseerRuneGUID[5] = pGo->GetGUID(); break;
        case GO_EMBERSEER_RUNE_7: m_auiEmberseerRuneGUID[6] = pGo->GetGUID(); break;

        case GO_ROOKERY_EGG: m_lRookeryEggGUIDList.push_back(pGo->GetGUID());   break;
    }
}

void zero_instance_blackrock_spire::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_PYROGUARD_EMBERSEER:    m_uiEmberseerGUID = pCreature->GetEntry();  break;
        case NPC_LORD_VICTOR_NEFARIUS:   m_uiNefariusGUID = pCreature->GetGUID();    break;
        case NPC_GYTH:                   m_uiGythGUID = pCreature->GetGUID();        break;
        case NPC_REND_BLACKHAND:         m_uiBlackhandGUID = pCreature->GetGUID();   break;
        case NPC_SCARSHIELD_INFILTRATOR: m_uiInfiltratorGUID = pCreature->GetGUID(); break;
        case NPC_BLACKHAND_DREADWEAVER:
        case NPC_BLACKHAND_SUMMONER:
        case NPC_BLACKHAND_VETERAN:      m_lRoomEventMobGUIDList.push_back(pCreature->GetGUID()); break;
        case NPC_BLACKHAND_INCANCERATOR: m_lIncanceratorGUIDList.push_back(pCreature->GetGUID()); break;
    }
}

void zero_instance_blackrock_spire::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_ROOM_EVENT:
            if (uiData == IN_PROGRESS)
                DoUseDoorOrButton(m_uiEnterUBRSDoorGUID);
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiEmberseerEntryDoorGUID);
            m_auiEncounter[TYPE_ROOM_EVENT] = uiData;
            break;
        case TYPE_EMBERSEER_ALTAR:
            if (uiData == 3)
                DoUseDoorOrButton(m_uiEmberseerCombatDoorGUID);
            m_auiEncounter[TYPE_EMBERSEER_ALTAR] = uiData;
            break;
        case TYPE_EMBERSEER_GUARDS:
            m_auiEncounter[TYPE_EMBERSEER_GUARDS] = uiData;
            break;
        case TYPE_EMBERSEER:
            if (uiData == IN_PROGRESS)
            {
                for (uint8 i = 0; i < MAX_ROOMS; i++)
                {
                    GameObject* pRune = instance->GetGameObject(m_auiEmberseerRuneGUID[i]);
                    if (pRune)
                        pRune->SetGoState(GO_STATE_ACTIVE);
                }
            }
            if (uiData == NOT_STARTED)
            {
                GameObject* Door = instance->GetGameObject(GetData64(GO_EMBERSEER_COMBAT_DOOR));
                if (Door)
                    Door->SetGoState(GO_STATE_ACTIVE);
            
                for (uint8 i = 0; i < MAX_ROOMS; i++)
                {
                    GameObject* pRune = instance->GetGameObject(m_auiEmberseerRuneGUID[i]);
                    if (pRune)
                        pRune->SetGoState(GO_STATE_READY);
                }
            }
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiEmberseerCombatDoorGUID);
                for (uint8 i = 0; i < MAX_ROOMS; i++)
                    DoUseDoorOrButton(m_auiEmberseerRuneGUID[i]);
                DoUseDoorOrButton(m_uiEmberseerExitDoorGUID);
            }
            m_auiEncounter[TYPE_EMBERSEER] = uiData;
            break;
        case TYPE_ROOKERY_WAVE:
            if (uiData == MAX_ROOKERY_WAVES)
                SetData(TYPE_ROOKERY_EVENT, DONE);
            m_auiEncounter[TYPE_ROOKERY_WAVE] = uiData;
            break;
        case TYPE_ROOKERY_EVENT:
            m_auiEncounter[TYPE_ROOKERY_EVENT] = uiData;
            break;
        case TYPE_SOLAKAR_FLAMEWREATH:
            m_auiEncounter[TYPE_SOLAKAR_FLAMEWREATH] = uiData;
            break;
        case TYPE_STADIUM_EVENT:
            m_auiEncounter[TYPE_STADIUM_EVENT] = uiData;
            if (uiData == NOT_STARTED)
            {
                GameObject* pEntDoor = instance->GetGameObject(m_uiStadiumEntryDoorGUID);
                if (pEntDoor)
                    pEntDoor->SetGoState(GO_STATE_ACTIVE);

                Creature* pRend = instance->GetCreature(m_uiBlackhandGUID);
                if (pRend)
                {
                    pRend->SetDeathState(JUST_DIED);
                    pRend->Respawn();
                }

                Creature* pGyth = instance->GetCreature(m_uiGythGUID);
                if (pGyth)
                {
                    pGyth->SetDeathState(JUST_DIED);
                    pGyth->Respawn();
                }
            }
            if (uiData == IN_PROGRESS)
                DoUseDoorOrButton(m_uiStadiumEntryDoorGUID);
            break;
        case TYPE_STADIUM_WAVE:
            if (uiData == 7)
                SetData(TYPE_STADIUM_EVENT, DONE);
            m_auiEncounter[TYPE_STADIUM_WAVE] = uiData;
            break;
        case TYPE_GYTH:
            if (uiData == IN_PROGRESS)
                DoUseDoorOrButton(m_uiStadiumCombatDoorGUID);
            if (uiData == NOT_STARTED)
            {
                GameObject* pEntDoor = instance->GetGameObject(m_uiStadiumEntryDoorGUID);
                if (pEntDoor)
                    pEntDoor->SetGoState(GO_STATE_ACTIVE);
            }
            m_auiEncounter[TYPE_GYTH] = uiData;
            break;
        case TYPE_GYTH_LOOTED:
            m_auiEncounter[TYPE_GYTH_LOOTED] = uiData;
            break;
        case TYPE_REND_BLACKHAND:
            m_auiEncounter[TYPE_REND_BLACKHAND] = uiData;
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiStadiumEntryDoorGUID);
                DoUseDoorOrButton(m_uiStadiumExitDoorGUID);
            }
            break;
        case TYPE_VALTHALAK:
            m_auiEncounter[TYPE_VALTHALAK] = uiData;
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream  << m_auiEncounter[TYPE_ROOM_EVENT] << " "
                    << m_auiEncounter[TYPE_EMBERSEER] << " "
                    << m_auiEncounter[TYPE_ROOKERY_EVENT] << " "
                    << m_auiEncounter[TYPE_SOLAKAR_FLAMEWREATH] << " "
                    << m_auiEncounter[TYPE_STADIUM_EVENT] << " "
                    << m_auiEncounter[TYPE_GYTH] << " "
                    << m_auiEncounter[TYPE_GYTH_LOOTED] << " "
                    << m_auiEncounter[TYPE_REND_BLACKHAND];

        strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void zero_instance_blackrock_spire::SetData64(uint32 uiType, uint64 uiData)
{
    if (uiType == TYPE_ROOM_EVENT && GetData(TYPE_ROOM_EVENT) == IN_PROGRESS)
    {
        uint8 uiNotEmptyRoomsCount = 0;
        for (uint8 i = 0; i< MAX_ROOMS; i++)
        {
            if (m_auiRoomRuneGUID[i])                       // This check is used, to ensure which runes still need processing
            {
                m_alRoomEventMobGUIDSorted[i].remove(uiData);
                if (m_alRoomEventMobGUIDSorted[i].empty())
                {
                    DoUseDoorOrButton(m_auiRoomRuneGUID[i]);
                    m_auiRoomRuneGUID[i] = 0;
                }
                else
                    uiNotEmptyRoomsCount++;                 // found an not empty room
            }
        }
        if (!uiNotEmptyRoomsCount)
            SetData(TYPE_ROOM_EVENT, DONE);
    }
}

void zero_instance_blackrock_spire::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream  >> m_auiEncounter[TYPE_ROOM_EVENT]
                >> m_auiEncounter[TYPE_EMBERSEER]
                >> m_auiEncounter[TYPE_ROOKERY_EVENT]
                >> m_auiEncounter[TYPE_SOLAKAR_FLAMEWREATH]
                >> m_auiEncounter[TYPE_STADIUM_EVENT]
                >> m_auiEncounter[TYPE_GYTH]
                >> m_auiEncounter[TYPE_GYTH_LOOTED]
                >> m_auiEncounter[TYPE_REND_BLACKHAND];

    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    if (m_auiEncounter[TYPE_GYTH] == NOT_STARTED ||
        m_auiEncounter[TYPE_REND_BLACKHAND] == NOT_STARTED)
        SetData(TYPE_STADIUM_EVENT, NOT_STARTED);

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 zero_instance_blackrock_spire::GetData(uint32 uiType)
{
    switch (uiType)
    {
        case TYPE_ROOM_EVENT:           return m_auiEncounter[TYPE_ROOM_EVENT];
        case TYPE_EMBERSEER_GUARDS:     return m_auiEncounter[TYPE_EMBERSEER_GUARDS];
        case TYPE_EMBERSEER_ALTAR:      return m_auiEncounter[TYPE_EMBERSEER_ALTAR];
        case TYPE_EMBERSEER:            return m_auiEncounter[TYPE_EMBERSEER];
        case TYPE_ROOKERY_WAVE:         return m_auiEncounter[TYPE_ROOKERY_WAVE];
        case TYPE_ROOKERY_EVENT:        return m_auiEncounter[TYPE_ROOKERY_EVENT];
        case TYPE_SOLAKAR_FLAMEWREATH:  return m_auiEncounter[TYPE_SOLAKAR_FLAMEWREATH];
        case TYPE_STADIUM_EVENT:        return m_auiEncounter[TYPE_STADIUM_EVENT];
        case TYPE_STADIUM_WAVE:         return m_auiEncounter[TYPE_STADIUM_WAVE];
        case TYPE_GYTH:                 return m_auiEncounter[TYPE_GYTH];
        case TYPE_GYTH_LOOTED:          return m_auiEncounter[TYPE_GYTH_LOOTED];
        case TYPE_REND_BLACKHAND:       return m_auiEncounter[TYPE_REND_BLACKHAND];
        case TYPE_VALTHALAK:            return m_auiEncounter[TYPE_VALTHALAK];
    }
    return 0;
}

uint64 zero_instance_blackrock_spire::GetData64(uint32 uiType)
{
    switch (uiType)
    {
        case NPC_PYROGUARD_EMBERSEER:    return m_uiEmberseerGUID;
        case NPC_LORD_VICTOR_NEFARIUS:   return m_uiNefariusGUID;
        case NPC_GYTH:                   return m_uiGythGUID;
        case NPC_REND_BLACKHAND:         return m_uiBlackhandGUID;
        case NPC_SCARSHIELD_INFILTRATOR: return m_uiInfiltratorGUID;
        case GO_STADIUM_COMBAT_DOOR:     return m_uiStadiumCombatDoorGUID;
        case GO_EMBERSEER_COMBAT_DOOR:   return m_uiEmberseerCombatDoorGUID;
    }
    return 0;
}

void zero_instance_blackrock_spire::DoSortRoomEventMobs()
{
    if (GetData(TYPE_ROOM_EVENT) != NOT_STARTED)
        return;

    for (uint8 i = 0; i < MAX_ROOMS; i++)
        if (GameObject* pRune = instance->GetGameObject(m_auiRoomRuneGUID[i]))
            for (std::list<uint64>::const_iterator itr = m_lRoomEventMobGUIDList.begin(); itr != m_lRoomEventMobGUIDList.end(); itr++)
                if (Creature* pCreature = instance->GetCreature(*itr))
                    if (pCreature->isAlive() && pCreature->GetDistance(pRune) < 10.0f)
                        m_alRoomEventMobGUIDSorted[i].push_back(*itr);

    SetData(TYPE_ROOM_EVENT, IN_PROGRESS);
}

InstanceData* Zero_GetInstanceData_instance_blackrock_spire(Map* pMap)
{
    return new zero_instance_blackrock_spire(pMap);
}

bool Zero_AreaTrigger_at_blackrock_spire(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (pPlayer->isDead())
        return false;

    switch (pAt->id)
    {
        case AREATRIGGER_ENTER_UBRS:
            if (zero_instance_blackrock_spire* pInstance = (zero_instance_blackrock_spire*) pPlayer->GetInstanceData())
                if (pPlayer->HasItemCount(ITEM_SEAL_OF_ASCENSION,1,false))
                    pInstance->DoSortRoomEventMobs();
            break;
        case AREATRIGGER_STADIUM:
            if (zero_instance_blackrock_spire* pInstance = (zero_instance_blackrock_spire*) pPlayer->GetInstanceData())
                if (pInstance->GetData(TYPE_STADIUM_EVENT) == NOT_STARTED)
                    pInstance->SetData(TYPE_STADIUM_EVENT, IN_PROGRESS);
            break;
    }
    return false;
}

void AddSC_blackrock_spire()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "zero_instance_blackrock_spire";
    pNewScript->GetInstanceData = &Zero_GetInstanceData_instance_blackrock_spire;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_at_blackrock_spire";
    pNewScript->pAreaTrigger = &Zero_AreaTrigger_at_blackrock_spire;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_chromatic_dragonspawn";
    pNewScript->GetAI = &Zero_GetAI_mob_chromatic_dragonspawn;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_chromatic_whelp";
    pNewScript->GetAI = &Zero_GetAI_mob_chromatic_whelp;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_dragon_handler";
    pNewScript->GetAI = &Zero_GetAI_mob_dragon_handler;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_rookery_hatcher_guardian";
    pNewScript->GetAI = &Zero_GetAI_mob_rookery_hatcher_guardian;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_blackhand_summoner";
    pNewScript->GetAI = &Zero_GetAI_mob_blackhand_summoner;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_blackhand_veteran";
    pNewScript->GetAI = &Zero_GetAI_mob_blackhand_veteran;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_mob_blackhand_dreadweaver";
    pNewScript->GetAI = &Zero_GetAI_mob_blackhand_dreadweaver;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_rend_blackhand";
    pNewScript->GetAI = &Zero_GetAI_boss_rend_blackhand;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_quartermaster_zigris";
    pNewScript->GetAI = &Zero_GetAI_boss_quatermasterzigris;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_pyroguard_emberseer";
    pNewScript->GetAI = &Zero_GetAI_boss_pyroguard_emberseer;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "zero_mob_blackhand_incancerator";
    pNewScript->GetAI = &Zero_GetAI_mob_blackhand_incancerator;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "zero_go_blackrock_altar";
    pNewScript->pGOUse = &Zero_GOHello_go_blackrock_altar;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_overlord_wyrmthalak";
    pNewScript->GetAI = &Zero_GetAI_boss_overlordwyrmthalak;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_mother_smolderweb";
    pNewScript->GetAI = &Zero_GetAI_boss_mothersmolderweb;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_boss_mor_grayhoof";
    pNewScript->GetAI = &Zero_GetAI_boss_mor_grayhoof;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_jed_runewatcher";
    pNewScript->GetAI = &Zero_GetAI_boss_jed_runewatcher;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_highlord_omokk";
    pNewScript->GetAI = &Zero_GetAI_boss_highlordomokk;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_boss_halycon";
    pNewScript->GetAI = &Zero_GetAI_boss_halycon;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_gyth";
    pNewScript->GetAI = &Zero_GetAI_boss_gyth;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "zero_boss_warmaster_voone";
    pNewScript->GetAI = &Zero_GetAI_boss_warmastervoone;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_the_beast";
    pNewScript->GetAI = &Zero_GetAI_boss_thebeast;
    pNewScript->RegisterSelf();
	
    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_solakar_flamewreath";
    pNewScript->GetAI = &Zero_GetAI_boss_solakar_flamewreath;
    pNewScript->RegisterSelf();
    
    pNewScript = new Script;
    pNewScript->Name = "zero_go_rookery_altar";
    pNewScript->pGOUse = &Zero_GOHello_go_rookery_altar;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_shadow_hunter_voshgajin";
    pNewScript->GetAI = &Zero_GetAI_boss_shadowvosh;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_goraluk_anvilcrack";
    pNewScript->GetAI = &Zero_GetAI_boss_goraluk_anvilcrack;
    pNewScript->RegisterSelf();

    
    pNewScript = new Script;
    pNewScript->Name = "zero_boss_drakkisath";
    pNewScript->GetAI = &Zero_GetAI_boss_drakkisath;
    pNewScript->RegisterSelf();
}
