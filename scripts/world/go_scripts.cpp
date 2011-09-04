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
SDName: GO_Scripts
SD%Complete: 100
SDComment: Quest support: 1126, 4285, 4287, 4288, 4296, 5088, 5097, 5098, 5381, 6481, 8961.
           Field_Repair_Bot->Teaches spell 22704. Barov_journal->Teaches spell 26089
SDCategory: Game Objects
EndScriptData */

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_northern_crystal_pylon
go_eastern_crystal_pylon
go_western_crystal_pylon
go_barov_journal
go_field_repair_bot_74A
go_orb_of_command
go_resonite_cask
go_sacred_fire_of_life
go_tablet_of_madness
go_tablet_of_the_seven
go_andorhal_tower
go_hand_of_iruxos_crystal
go_wind_stones
go_hiveashi_pod
EndContentData */

#include "precompiled.h"

/*######
## go_cat_figurine
######*/

bool GOUse_go_cat_figurine(Player* pPlayer, GameObject* pGo)
{
    pPlayer->CastSpell(pPlayer, 5968, true);

    return false;
}

/*######
## go_crystal_pylons (3x)
######*/

bool GOUse_go_northern_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetObjectGuid());
        pPlayer->SendPreparedQuest(pGo->GetObjectGuid());
    }

    if (pPlayer->GetQuestStatus(4285) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4285);

    return true;
}

bool GOUse_go_eastern_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetObjectGuid());
        pPlayer->SendPreparedQuest(pGo->GetObjectGuid());
    }

    if (pPlayer->GetQuestStatus(4287) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4287);

    return true;
}

bool GOUse_go_western_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetObjectGuid());
        pPlayer->SendPreparedQuest(pGo->GetObjectGuid());
    }

    if (pPlayer->GetQuestStatus(4288) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4288);

    return true;
}

/*######
## go_barov_journal
######*/

bool GOUse_go_barov_journal(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_TAILORING) && pPlayer->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !pPlayer->HasSpell(26086))
        pPlayer->CastSpell(pPlayer, 26095, false);

    return true;
}

/*######
## go_field_repair_bot_74A
######*/

bool GOUse_go_field_repair_bot_74A(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ENGINEERING) && pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !pPlayer->HasSpell(22704))
        pPlayer->CastSpell(pPlayer, 22864, false);

    return true;
}

/*######
## go_gilded_brazier
######*/

bool GOUse_go_gilded_brazier(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
    {
        if (Creature* pCreature = pPlayer->SummonCreature(17716, 8087.632f, -7542.740f, 151.568f, 0.122f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
            pCreature->AI()->AttackStart(pPlayer);
    }

    return true;
}

/*######
## go_orb_of_command
######*/

bool GOUse_go_orb_of_command(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestRewardStatus(7761))
        pPlayer->CastSpell(pPlayer, 23460, true);

    return true;
}

/*######
## go_resonite_cask
######*/

bool GOUse_go_resonite_cask(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pGO->SummonCreature(11920, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

    return false;
}

/*######
## go_sacred_fire_of_life
######*/

bool GOUse_go_sacred_fire_of_life(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pPlayer->SummonCreature(10882, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

    return true;
}

/*######
## go_tablet_of_madness
######*/

bool GOUse_go_tablet_of_madness(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ALCHEMY) && pPlayer->GetSkillValue(SKILL_ALCHEMY) >= 300 && !pPlayer->HasSpell(24266))
        pPlayer->CastSpell(pPlayer, 24267, false);

    return true;
}

/*######
## go_tablet_of_the_seven
######*/

//TODO: use gossip option ("Transcript the Tablet") instead, if Mangos adds support.
bool GOUse_go_tablet_of_the_seven(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
        return true;

    if (pPlayer->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
        pPlayer->CastSpell(pPlayer, 15065, false);

    return true;
}

/*######
## go_andorhal_tower
######*/

enum
{
    QUEST_ALL_ALONG_THE_WATCHTOWERS_ALLIANCE   = 5097,
    QUEST_ALL_ALONG_THE_WATCHTOWERS_HORDE      = 5098,
    NPC_ANDORHAL_TOWER_1                       = 10902,
    NPC_ANDORHAL_TOWER_2                       = 10903,
    NPC_ANDORHAL_TOWER_3                       = 10904,
    NPC_ANDORHAL_TOWER_4                       = 10905,
    GO_ANDORHAL_TOWER_1                        = 176094,
    GO_ANDORHAL_TOWER_2                        = 176095,
    GO_ANDORHAL_TOWER_3                        = 176096,
    GO_ANDORHAL_TOWER_4                        = 176097
};

bool GOUse_go_andorhal_tower(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(QUEST_ALL_ALONG_THE_WATCHTOWERS_ALLIANCE) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(QUEST_ALL_ALONG_THE_WATCHTOWERS_HORDE) == QUEST_STATUS_INCOMPLETE)
    {
        uint32 uiKillCredit = 0;
        switch(pGo->GetEntry())
        {
            case GO_ANDORHAL_TOWER_1:   uiKillCredit = NPC_ANDORHAL_TOWER_1;   break;
            case GO_ANDORHAL_TOWER_2:   uiKillCredit = NPC_ANDORHAL_TOWER_2;   break;
            case GO_ANDORHAL_TOWER_3:   uiKillCredit = NPC_ANDORHAL_TOWER_3;   break;
            case GO_ANDORHAL_TOWER_4:   uiKillCredit = NPC_ANDORHAL_TOWER_4;   break;
        }
        if (uiKillCredit)
            pPlayer->KilledMonsterCredit(uiKillCredit);
    }
    return true;
}

/*######
## go_hand_of_iruxos_crystal
######*/

bool GOUse_go_hand_of_iruxos_crystal(Player* pPlayer, GameObject* pGo)
{
    if (Creature* pIruxos = pGo->SummonCreature(11876, 0.0f, 0.0f, 0.0f, pPlayer->GetOrientation() + M_PI_F, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000))
        pIruxos->AI()->AttackStart(pPlayer);

    return false;
}

/*######
## go_demon_portal
######*/

bool GOUse_go_demon_portal(Player* pPlayer, GameObject* pGo)
{
  Creature* pCreature = GetClosestCreatureWithEntry(pPlayer, 11937, 5.0f);

    if (pCreature)
        return true;

    if (pPlayer->GetQuestStatus(5581) == QUEST_STATUS_INCOMPLETE)
        pPlayer->SummonCreature(11937, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000);

    return true;
};

/*######
## go_wind_stones
######*/

enum
{
    TYPE_LESSER_STONE          = 1,
    TYPE_STONE                 = 2,
    TYPE_GREATER_STONE         = 3,

    SPELL_ABYSSAL_PUNISHMENT   = 24803,
    SPELL_TWILIGHT_DISGUISE    = 24746
};

bool GOUse_go_wind_stones(Player* pPlayer, GameObject* pGo)
{
    uint8 uiStoneType = 0;

    // Close the gossip for now, as we do not have proper text inside :(
    pPlayer->CLOSE_GOSSIP_MENU();

    // Basic stone type definition
    // TODO: Simplify this switch thing
    switch(pGo->GetEntry())
    {
        // Lesser Wind Stone
        case 180456: case 180518: case 180529: case 180544: case 180549: case 180564:
            uiStoneType = TYPE_LESSER_STONE;
            break;
        // Wind Stone
        case 180461: case 180534: case 180554:
            uiStoneType = TYPE_STONE;
            break;
        // Greater Wind Stone
        case 180466: case 180539: case 180559:
            uiStoneType = TYPE_GREATER_STONE;
            break;
        default:
            debug_log("SD0: go_wind_stones is assigned to invalid gameobject entry. Check your database.");
            return true;
    }

    // If the creature does not have the twilight set, cast punishment and return
    if (!pPlayer->HasAura(SPELL_TWILIGHT_DISGUISE, EFFECT_INDEX_0))
    {
        pPlayer->CastSpell(pPlayer, SPELL_ABYSSAL_PUNISHMENT, false);
        return true;
    }

    // Summonings
    // TODO: Simplify code, remove magic numbers
    //       Possible that the summoning is hack-like
    switch(uiStoneType)
    {
        // Templars
        case TYPE_LESSER_STONE:
        {
            // Earthen
            if (pPlayer->HasItemCount(20419, 1))
            {
                pGo->SummonCreature(15307, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24759, false);
            }
            // Hoary
            else if (pPlayer->HasItemCount(20418, 1))
            {
                pGo->SummonCreature(15212, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24757, false);
            }
            // Azure
            else if (pPlayer->HasItemCount(20420, 1))
            {
                pGo->SummonCreature(15211, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24761, false);
            }
            // Crimson
            else if (pPlayer->HasItemCount(20416, 1))
            {
                pGo->SummonCreature(15209, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24747, false);
            }
            // Random
            else
            {
                pPlayer->CastSpell(pPlayer, 24745, false);
                uint8 uiRandom = urand(0, 3);
                switch(uiRandom)
                {
                    case 0: pGo->SummonCreature(15307, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 1: pGo->SummonCreature(15212, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 2: pGo->SummonCreature(15211, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 3: pGo->SummonCreature(15209, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                }
            }
            break;
        }
        // Dukes
        case TYPE_STONE:
        {
            if (!pPlayer->HasItemCount(20422, 1)) // We need item 20422 as well
                break;

            // Shards
            if (pPlayer->HasItemCount(20435, 1))
            {
                pGo->SummonCreature(15208, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24771, false);
            }
            // Zephyrs
            else if (pPlayer->HasItemCount(20433, 1))
            {
                pGo->SummonCreature(15220, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24769, false);
            }
            // Fathoms
            else if (pPlayer->HasItemCount(20436, 1))
            {
                pGo->SummonCreature(15207, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24773, false);
            }
            // Cynders
            else if (pPlayer->HasItemCount(20432, 1))
            {
                pGo->SummonCreature(15206, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24766, false);
            }
            // Random
            else
            {
                pPlayer->CastSpell(pPlayer, 24762, false);
                uint8 uiRandom = urand(0, 3);
                switch(uiRandom)
                {
                    case 0: pGo->SummonCreature(15208, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 1: pGo->SummonCreature(15220, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 2: pGo->SummonCreature(15207, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 3: pGo->SummonCreature(15206, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                }
            }
            break;
        }
        // Bosses
        case TYPE_GREATER_STONE:
        {
            if (!pPlayer->HasItemCount(20422, 1) || !pPlayer->HasItemCount(20451, 1)) // We need item 20422 and 20451 as well
                break;

            // Kazum
            if (pPlayer->HasItemCount(20449, 1))
            {
                pGo->SummonCreature(15205, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24792, false);
            }
            // Whirlaxis
            else if (pPlayer->HasItemCount(20448, 1))
            {
                pGo->SummonCreature(15204, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24791, false);
            }
            // Skwol
            else if (pPlayer->HasItemCount(20450, 1))
            {
                pGo->SummonCreature(15305, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24793, false);
            }
            // Skaldrenox
            else if (pPlayer->HasItemCount(20447, 1))
            {
                pGo->SummonCreature(15203, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0);
                pPlayer->CastSpell(pPlayer, 24787, false);
            }
            // Random
            else
            {
                pPlayer->CastSpell(pPlayer, 24784, false);
                uint8 uiRandom = urand(0, 3);
                switch(uiRandom)
                {
                    case 0: pGo->SummonCreature(15205, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 1: pGo->SummonCreature(15204, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 2: pGo->SummonCreature(15305, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                    case 3: pGo->SummonCreature(15203, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_DEAD_DESPAWN, 0); break;
                }
            }
            break;
        }
    }

    return true;
};

/*######
## go_hiveashi_pod
######*/

// TODO: Implement this to Database?
bool GOUse_go_hiveashi_pod(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestStatus(1126) == QUEST_STATUS_INCOMPLETE)
        pPlayer->SummonCreature(13301, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), pPlayer->GetOrientation(), TEMPSUMMON_TIMED_DESPAWN, 300000);

    return true;
};

/*######
## go_panther_cage
######*/

bool GOUse_go_panther_cage(Player* pPlayer, GameObject* pGo)
{
  Creature* pCreature = GetClosestCreatureWithEntry(pPlayer, 10992, 10.0f);

    if (pCreature)
        pCreature->setFaction(16);

    return true;
};

void AddSC_go_scripts()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "go_cat_figurine";
    pNewScript->pGOUse = &GOUse_go_cat_figurine;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_northern_crystal_pylon";
    pNewScript->pGOUse = &GOUse_go_northern_crystal_pylon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_eastern_crystal_pylon";
    pNewScript->pGOUse = &GOUse_go_eastern_crystal_pylon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_western_crystal_pylon";
    pNewScript->pGOUse = &GOUse_go_western_crystal_pylon;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_barov_journal";
    pNewScript->pGOUse = &GOUse_go_barov_journal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_field_repair_bot_74A";
    pNewScript->pGOUse = &GOUse_go_field_repair_bot_74A;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_gilded_brazier";
    pNewScript->pGOUse = &GOUse_go_gilded_brazier;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_orb_of_command";
    pNewScript->pGOUse = &GOUse_go_orb_of_command;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_resonite_cask";
    pNewScript->pGOUse = &GOUse_go_resonite_cask;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_sacred_fire_of_life";
    pNewScript->pGOUse = &GOUse_go_sacred_fire_of_life;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_tablet_of_madness";
    pNewScript->pGOUse = &GOUse_go_tablet_of_madness;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_tablet_of_the_seven";
    pNewScript->pGOUse = &GOUse_go_tablet_of_the_seven;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_andorhal_tower";
    pNewScript->pGOUse = &GOUse_go_andorhal_tower;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_hand_of_iruxos_crystal";
    pNewScript->pGOUse = &GOUse_go_hand_of_iruxos_crystal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_demon_portal";
    pNewScript->pGOUse = &GOUse_go_demon_portal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_wind_stones";
    pNewScript->pGOUse = &GOUse_go_wind_stones;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_hiveashi_pod";
    pNewScript->pGOUse = &GOUse_go_hiveashi_pod;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_panther_cage";
    pNewScript->pGOUse = &GOUse_go_panther_cage;
    pNewScript->RegisterSelf();
}
