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
SDName: Blackhand Summoner, Blackhand Veteran, Blackhand Dreadweaver, Rage Talon Dragospawn, Jed Runewatcher
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

/*######
## mob_blackhand_summoner
######*/

enum
{
    SPELL_FIREBALL              = 12466,
    SPELL_FROST_NOVA            = 15532,
    SPELL_SUMMON_VETERAN        = 15794,
    SPELL_SUMMON_DREADWEAVER    = 15792
};

struct MANGOS_DLL_DECL mob_blackhand_summonerAI : public ScriptedAI
{
    mob_blackhand_summonerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

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
                    DoCastSpellIfCan(pTarget, SPELL_FIREBALL);
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
    SPELL_SHIELD_BASH       = 11972,
    SPELL_SHIELD_CHARGE     = 15749,
    SPELL_STRIKE            = 14516
};

struct MANGOS_DLL_DECL mob_blackhand_veteranAI : public ScriptedAI
{
    mob_blackhand_veteranAI(Creature* pCreature) : ScriptedAI(pCreature)
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
        Shield_Bash_Timer = urand(7000, 15000);
        Strike_Timer = urand(5000, 10000);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(15.0f);

        if (Unit *victim = m_creature->getVictim())
            DoCastSpellIfCan(victim, SPELL_SHIELD_CHARGE);
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
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_STRIKE);
            Strike_Timer = urand(5000, 10000);
        }else Strike_Timer -= uiDiff;

        // Shield Bash
        if (Shield_Bash_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHIELD_BASH);
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
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

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
    SPELL_HATCH_ROOKERY_EGG = 15746,
    SPELL_SUNDER_ARMOR      = 15572,
    SPELL_STRIKE_HATCHER    = 15580,

    MOB_HATCHER             = 10683,

    SAY_BEGIN               = -1615001
};

struct MANGOS_DLL_DECL mob_rookery_hatcher_guardianAI : public ScriptedAI
{
    mob_rookery_hatcher_guardianAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

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
        }

        DoMeleeAttackIfReady();
    }
};

/*######
## mob_chromatic_dragonspawn
######*/

enum
{
    SPELL_CLEAVE              = 12466
};

struct MANGOS_DLL_DECL mob_chromatic_dragonspawnAI : public ScriptedAI
{
    mob_chromatic_dragonspawnAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

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
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE);
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
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

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
        m_pInstance = (instance_blackrock_spire*)pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

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

CreatureAI* GetAI_mob_dragon_handler(Creature* pCreature)
{
    return new mob_dragon_handlerAI(pCreature);
}

CreatureAI* GetAI_mob_chromatic_whelp(Creature* pCreature)
{
    return new mob_chromatic_whelpAI(pCreature);
}

CreatureAI* GetAI_mob_chromatic_dragonspawn(Creature* pCreature)
{
    return new mob_chromatic_dragonspawnAI(pCreature);
}

CreatureAI* GetAI_mob_rookery_hatcher_guardian(Creature* pCreature)
{
    return new mob_rookery_hatcher_guardianAI(pCreature);
}

CreatureAI* GetAI_mob_blackhand_summoner(Creature* pCreature)
{
    return new mob_blackhand_summonerAI(pCreature);
}

CreatureAI* GetAI_mob_blackhand_veteran(Creature* pCreature)
{
    return new mob_blackhand_veteranAI(pCreature);
}

CreatureAI* GetAI_mob_blackhand_dreadweaver(Creature* pCreature)
{
    return new mob_blackhand_dreadweaverAI(pCreature);
}

void AddSC_brs_mob_trash()
{
    Script *NewScript;

    NewScript = new Script;
    NewScript->Name = "mob_chromatic_dragonspawn";
    NewScript->GetAI = &GetAI_mob_chromatic_dragonspawn;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_chromatic_whelp";
    NewScript->GetAI = &GetAI_mob_chromatic_whelp;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_dragon_handler";
    NewScript->GetAI = &GetAI_mob_dragon_handler;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_rookery_hatcher_guardian";
    NewScript->GetAI = &GetAI_mob_rookery_hatcher_guardian;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_blackhand_summoner";
    NewScript->GetAI = &GetAI_mob_blackhand_summoner;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_blackhand_veteran";
    NewScript->GetAI = &GetAI_mob_blackhand_veteran;
    NewScript->RegisterSelf();

    NewScript = new Script;
    NewScript->Name = "mob_blackhand_dreadweaver";
    NewScript->GetAI = &GetAI_mob_blackhand_dreadweaver;
    NewScript->RegisterSelf();
}
