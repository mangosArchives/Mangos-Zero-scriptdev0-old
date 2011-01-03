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
SDName: Guards
SD%Complete: 100
SDComment: All Guard gossip data, quite some npc_text-id's still missing, adding constantly as new id's are known. CombatAI should be organized better for future.
SDCategory: Guards
EndScriptData */

/* ContentData
guard_contested
guard_darnassus
guard_dunmorogh
guard_durotar
guard_elwynnforest
guard_ironforge
guard_mulgore
guard_orgrimmar
guard_stormwind
guard_teldrassil
guard_tirisfal
guard_undercity
EndContentData */

#include "precompiled.h"
#include "guard_ai.h"



/*******************************************************
 * guard_contested start
 *******************************************************/

CreatureAI* GetAI_guard_contested(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_contested end
 *******************************************************/

/*******************************************************
 * guard_darnassus start
 *******************************************************/

bool GossipHello_guard_darnassus(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(3016, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction house
            pPlayer->SEND_POI(9861.23f, 2334.55f, 7, 6, 0, "Darnassus Auction House");
            pPlayer->SEND_GOSSIP_MENU(3833, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(9938.45f, 2512.35f, 7, 6, 0, "Darnassus Bank");
            pPlayer->SEND_GOSSIP_MENU(3017, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Wind master
            pPlayer->SEND_POI(9945.65f, 2618.94f, 7, 6, 0, "Rut'theran Village");
            pPlayer->SEND_GOSSIP_MENU(3018, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Guild master
            pPlayer->SEND_POI(10076.40f, 2199.59f, 7, 6, 0, "Darnassus Guild Master");
            pPlayer->SEND_GOSSIP_MENU(3019, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Inn
            pPlayer->SEND_POI(10133.29f, 2222.52f, 7, 6, 0, "Darnassus Inn");
            pPlayer->SEND_GOSSIP_MENU(3020, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Mailbox
            pPlayer->SEND_POI(9942.17f, 2495.48f, 7, 6, 0, "Darnassus Mailbox");
            pPlayer->SEND_GOSSIP_MENU(3021, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Stable master
            pPlayer->SEND_POI(10167.20f, 2522.66f, 7, 6, 0, "Alassin");
            pPlayer->SEND_GOSSIP_MENU(5980, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon trainer
            pPlayer->SEND_POI(9907.11f, 2329.70f, 7, 6, 0, "Ilyenia Moonfire");
            pPlayer->SEND_GOSSIP_MENU(4517, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(4264, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(4273, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(9923.61f, 2327.43f, 7, 6, 0, "Brogun Stoneshield");
            pPlayer->SEND_GOSSIP_MENU(7518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(9977.37f, 2324.39f, 7, 6, 0, "Keras Wolfheart");
            pPlayer->SEND_GOSSIP_MENU(7651,  pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(9979.84f, 2315.79f, 7, 6, 0, "Aethalas");
            pPlayer->SEND_GOSSIP_MENU(7482, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(10186.0f, 2570.46f, 7, 6, 0, "Darnassus Druid Trainer");
            pPlayer->SEND_GOSSIP_MENU(3024, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(10177.29f, 2511.10f, 7, 6, 0, "Darnassus Hunter Trainer");
            pPlayer->SEND_GOSSIP_MENU(3023, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(9659.12f, 2524.88f, 7, 6, 0, "Temple of the Moon");
            pPlayer->SEND_GOSSIP_MENU(3025, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
            pPlayer->SEND_POI(10122.0f, 2599.12f, 7, 6, 0, "Darnassus Rogue Trainer");
            pPlayer->SEND_GOSSIP_MENU(3026, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(9951.91f, 2280.38f, 7, 6, 0, "Warrior's Terrace");
            pPlayer->SEND_GOSSIP_MENU(3033, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(10075.90f, 2356.76f, 7, 6, 0, "Darnassus Alchemy Trainer");
            pPlayer->SEND_GOSSIP_MENU(3035, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Cooking
            pPlayer->SEND_POI(10088.59f, 2419.21f, 7, 6, 0, "Darnassus Cooking Trainer");
            pPlayer->SEND_GOSSIP_MENU(3036, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Enchanting
            pPlayer->SEND_POI(10146.09f, 2313.42f, 7, 6, 0, "Darnassus Enchanting Trainer");
            pPlayer->SEND_GOSSIP_MENU(3337, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //First Aid
            pPlayer->SEND_POI(10150.09f, 2390.43f, 7, 6, 0, "Darnassus First Aid Trainer");
            pPlayer->SEND_GOSSIP_MENU(3037, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Fishing
            pPlayer->SEND_POI(9836.20f, 2432.17f, 7, 6, 0, "Darnassus Fishing Trainer");
            pPlayer->SEND_GOSSIP_MENU(3038, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Herbalism
            pPlayer->SEND_POI(9757.17f, 2430.16f, 7, 6, 0, "Darnassus Herbalism Trainer");
            pPlayer->SEND_GOSSIP_MENU(3039, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(10086.59f, 2255.77f, 7, 6, 0, "Darnassus Leatherworking Trainer");
            pPlayer->SEND_GOSSIP_MENU(3040, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(10081.40f, 2257.18f, 7, 6, 0, "Darnassus Skinning Trainer");
            pPlayer->SEND_GOSSIP_MENU(3042, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Tailoring
            pPlayer->SEND_POI(10079.70f, 2268.19f, 7, 6, 0, "Darnassus Tailor");
            pPlayer->SEND_GOSSIP_MENU(3044, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_darnassus(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_darnassus(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_darnassus end
 *******************************************************/

CreatureAI* GetAI_guard_darnassus(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_dunmorogh start
 *******************************************************/

bool GossipHello_guard_dunmorogh(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HIPPOGRYPH       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN              , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(4287, pCreature->GetGUID());

    return true;
}

void SendDefaultMenu_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4288, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Gryphon master
            pPlayer->SEND_GOSSIP_MENU(4289, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(4290, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-5582.66f, -525.89f, 7, 6, 0, "Thunderbrew Distillery");
            pPlayer->SEND_GOSSIP_MENU(4291, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
            pPlayer->SEND_POI(-5604.0f, -509.58f, 7, 6, 0, "Shelby Stoneflint");
            pPlayer->SEND_GOSSIP_MENU(5985, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(4292, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4300, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(-5618.29f, -454.25f, 7, 6, 0, "Grif Wildheart");
            pPlayer->SEND_GOSSIP_MENU(4293, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(-5585.6f, -539.99f, 7, 6, 0, "Magis Sparkmantle");
            pPlayer->SEND_GOSSIP_MENU(4294, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Paladin
            pPlayer->SEND_POI(-5585.6f, -539.99f, 7, 6, 0, "Azar Stronghammer");
            pPlayer->SEND_GOSSIP_MENU(4295, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
            pPlayer->SEND_POI(-5591.74f, -525.61f, 7, 6, 0, "Maxan Anvol");
            pPlayer->SEND_GOSSIP_MENU(4296, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
            pPlayer->SEND_POI(-5602.75f, -542.4f, 7, 6, 0, "Hogral Bakkan");
            pPlayer->SEND_GOSSIP_MENU(4297, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(-5641.97f, -523.76f, 7, 6, 0, "Gimrizz Shadowcog");
            pPlayer->SEND_GOSSIP_MENU(4298, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(-5604.79f, -529.38f, 7, 6, 0, "Granis Swiftaxe");
            pPlayer->SEND_GOSSIP_MENU(4299, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_GOSSIP_MENU(4301, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-5584.72f, -428.41f, 7, 6, 0, "Tognus Flintfire");
            pPlayer->SEND_GOSSIP_MENU(4302, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-5596.85f, -541.43f, 7, 6, 0, "Gremlock Pilsnor");
            pPlayer->SEND_GOSSIP_MENU(4303, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4304, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-5531.0f, -666.53f, 7, 6, 0, "Bronk Guzzlegear");
            pPlayer->SEND_GOSSIP_MENU(4305, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-5603.67f, -523.57f, 7, 6, 0, "Thamner Pol");
            pPlayer->SEND_GOSSIP_MENU(4306, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-5199.9f, 58.58f, 7, 6, 0, "Paxton Ganter");
            pPlayer->SEND_GOSSIP_MENU(4307, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_GOSSIP_MENU(4308, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_GOSSIP_MENU(4310, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(-5531.0f, -666.53f, 7, 6, 0, "Yarr Hamerstone");
            pPlayer->SEND_GOSSIP_MENU(4311, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_GOSSIP_MENU(4312, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4313, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_dunmorogh(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_dunmorogh(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_dunmorogh(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_dunmorogh(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_dunmorogh end
 *******************************************************/

CreatureAI* GetAI_guard_dunmorogh(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_durotar start
 *******************************************************/

bool GossipHello_guard_durotar(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(4037, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4032, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind rider
            pPlayer->SEND_GOSSIP_MENU(4033, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(338.7f, -4688.87f, 7, 6, 0, "Razor Hill Inn");
            pPlayer->SEND_GOSSIP_MENU(4034, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable master
            pPlayer->SEND_POI(330.31f, -4710.66f, 7, 6, 0, "Shoja'my");
            pPlayer->SEND_GOSSIP_MENU(5973, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->SEND_GOSSIP_MENU(4035, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4036, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(276.0f, -4706.72f, 7, 6, 0, "Thotar");
            pPlayer->SEND_GOSSIP_MENU(4013, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(-839.33f, -4935.6f, 7, 6, 0, "Un'Thuwa");
            pPlayer->SEND_GOSSIP_MENU(4014, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(296.22f, -4828.1f, 7, 6, 0, "Tai'jin");
            pPlayer->SEND_GOSSIP_MENU(4015, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
            pPlayer->SEND_POI(265.76f, -4709.0f, 7, 6, 0, "Kaplak");
            pPlayer->SEND_GOSSIP_MENU(4016, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Shaman
            pPlayer->SEND_POI(307.79f, -4836.97f, 7, 6, 0, "Swart");
            pPlayer->SEND_GOSSIP_MENU(4017, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(355.88f, -4836.45f, 7, 6, 0, "Dhugru Gorelust");
            pPlayer->SEND_GOSSIP_MENU(4018, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(312.3f, -4824.66f, 7, 6, 0, "Tarshaw Jaggedscar");
            pPlayer->SEND_GOSSIP_MENU(4019, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-800.25f, -4894.33f, 7, 6, 0, "Miao'zan");
            pPlayer->SEND_GOSSIP_MENU(4020, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(373.24f, -4716.45f, 7, 6, 0, "Dwukk");
            pPlayer->SEND_GOSSIP_MENU(4021, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_GOSSIP_MENU(4022, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4023, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(368.95f, -4723.95f, 7, 6, 0, "Mukdrak");
            pPlayer->SEND_GOSSIP_MENU(4024, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(327.17f, -4825.62f, 7, 6, 0, "Rawrk");
            pPlayer->SEND_GOSSIP_MENU(4025, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-1065.48f, -4777.43f, 7, 6, 0, "Lau'Tiki");
            pPlayer->SEND_GOSSIP_MENU(4026, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-836.25f, -4896.89f, 7, 6, 0, "Mishiki");
            pPlayer->SEND_GOSSIP_MENU(4027, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_GOSSIP_MENU(4028, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(366.94f, -4705.0f, 7, 6, 0, "Krunn");
            pPlayer->SEND_GOSSIP_MENU(4029, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_GOSSIP_MENU(4030, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4031, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_durotar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_durotar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_durotar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_durotar(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_durotar end
 *******************************************************/

CreatureAI* GetAI_guard_durotar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_elwynnforest start
 *******************************************************/

bool GossipHello_guard_elwynnforest(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(933, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4260, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Gryphon master
            pPlayer->SEND_GOSSIP_MENU(4261, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(4262, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-9459.34f, 42.08f, 7, 6, 0, "Lion's Pride Inn");
            pPlayer->SEND_GOSSIP_MENU(4263, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Stable Master
            pPlayer->SEND_POI(-9466.62f, 45.87f, 7, 6, 0, "Erma");
            pPlayer->SEND_GOSSIP_MENU(5983, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(4264, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4273, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_GOSSIP_MENU(4265, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_GOSSIP_MENU(4266, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(-9471.12f, 33.44f, 7, 6, 0, "Zaldimar Wefhellt");
            pPlayer->SEND_GOSSIP_MENU(4268, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Paladin
            pPlayer->SEND_POI(-9469.0f, 108.05f, 7, 6, 0, "Brother Wilhelm");
            pPlayer->SEND_GOSSIP_MENU(4269, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(-9461.07f, 32.6f, 7, 6, 0, "Priestess Josetta");
            pPlayer->SEND_GOSSIP_MENU(4267, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Rogue
            pPlayer->SEND_POI(-9465.13f, 13.29f, 7, 6, 0, "Keryn Sylvius");
            pPlayer->SEND_GOSSIP_MENU(4270, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warlock
            pPlayer->SEND_POI(-9473.21f, -4.08f, 7, 6, 0, "Maximillian Crowe");
            pPlayer->SEND_GOSSIP_MENU(4272, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Warrior
            pPlayer->SEND_POI(-9461.82f, 109.50f, 7, 6, 0, "Lyria Du Lac");
            pPlayer->SEND_GOSSIP_MENU(4271, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-9057.04f, 153.63f, 7, 6, 0, "Alchemist Mallory");
            pPlayer->SEND_GOSSIP_MENU(4274, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-9456.58f, 87.90f, 7, 6, 0, "Smith Argus");
            pPlayer->SEND_GOSSIP_MENU(4275, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-9467.54f, -3.16f, 7, 6, 0, "Tomas");
            pPlayer->SEND_GOSSIP_MENU(4276, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4277, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_GOSSIP_MENU(4278, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-9456.82f, 30.49f, 7, 6, 0, "Michelle Belle");
            pPlayer->SEND_GOSSIP_MENU(4279, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-9386.54f, -118.73f, 7, 6, 0, "Lee Brown");
            pPlayer->SEND_GOSSIP_MENU(4280, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-9060.70f, 149.23f, 7, 6, 0, "Herbalist Pomeroy");
            pPlayer->SEND_GOSSIP_MENU(4281, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(-9376.12f, -75.23f, 7, 6, 0, "Adele Fielder");
            pPlayer->SEND_GOSSIP_MENU(4282, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_GOSSIP_MENU(4283, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(-9536.91f, -1212.76f, 7, 6, 0, "Helene Peltskinner");
            pPlayer->SEND_GOSSIP_MENU(4284, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(-9376.12f, -75.23f, 7, 6, 0, "Eldrin");
            pPlayer->SEND_GOSSIP_MENU(4285, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_elwynnforest(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_elwynnforest(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_elwynnforest(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_elwynnforest(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_elwynnforest end
 *******************************************************/

CreatureAI* GetAI_guard_elwynnforest(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_ironforge start
 *******************************************************/

bool GossipHello_guard_ironforge(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_IRONFORGE_BANK    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DEEPRUNTRAM       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN               , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->SEND_GOSSIP_MENU(2760, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction House
            pPlayer->SEND_POI(-4957.39f, -911.6f, 7, 6, 0, "Ironforge Auction House");
            pPlayer->SEND_GOSSIP_MENU(3014, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-4891.91f, -991.47f, 7, 6, 0, "The Vault");
            pPlayer->SEND_GOSSIP_MENU(2761, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Tram
            pPlayer->SEND_POI(-4835.27f, -1294.69f, 7, 6, 0, "Deeprun Tram");
            pPlayer->SEND_GOSSIP_MENU(3814, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Gryphon Master
            pPlayer->SEND_POI(-4821.52f, -1152.3f, 7, 6, 0, "Ironforge Gryphon Master");
            pPlayer->SEND_GOSSIP_MENU(2762, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Guild Master
            pPlayer->SEND_POI(-5021.0f, -996.45f, 7, 6, 0, "Ironforge Visitor's Center");
            pPlayer->SEND_GOSSIP_MENU(2764, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Inn
            pPlayer->SEND_POI(-4850.47f, -872.57f, 7, 6, 0, "Stonefire Tavern");
            pPlayer->SEND_GOSSIP_MENU(2768, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Mailbox
            pPlayer->SEND_POI(-4845.7f, -880.55f, 7, 6, 0, "Ironforge Mailbox");
            pPlayer->SEND_GOSSIP_MENU(2769, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable Master
            pPlayer->SEND_POI(-5010.2f, -1262.0f, 7, 6, 0, "Ulbrek Firehand");
            pPlayer->SEND_GOSSIP_MENU(5986, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Weapons Trainer
            pPlayer->SEND_POI(-5040.0f, -1201.88f, 7, 6, 0, "Bixi and Buliwyf");
            pPlayer->SEND_GOSSIP_MENU(4518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7529, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Class Trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE            , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);           
            pPlayer->SEND_GOSSIP_MENU(2766, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Profession Trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING   , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING     , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(2793, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-5047.87f, -1263.77f, 7, 6, 0, "Glordrum Steelbeard");
            pPlayer->SEND_GOSSIP_MENU(7483, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-5038.37f, -1266.39f, 7, 6, 0, "Donal Osgood");
            pPlayer->SEND_GOSSIP_MENU(7649, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(-5037.24f, -1274.82f, 7, 6, 0, "Lylandris");
            pPlayer->SEND_GOSSIP_MENU(7528, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(-5023.0f, -1253.68f, 7, 6, 0, "Hall of Arms");
            pPlayer->SEND_GOSSIP_MENU(2770, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(-4627.0f, -926.45f, 7, 6, 0, "Hall of Mysteries");
            pPlayer->SEND_GOSSIP_MENU(2771, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Paladin
            pPlayer->SEND_POI(-4627.02f, -926.45f, 7, 6, 0, "Hall of Mysteries");
            pPlayer->SEND_GOSSIP_MENU(2773, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
            pPlayer->SEND_POI(-4627.0f, -926.45f, 7, 6, 0, "Hall of Mysteries");
            pPlayer->SEND_GOSSIP_MENU(2772, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
            pPlayer->SEND_POI(-4647.83f, -1124.0f, 7, 6, 0, "Ironforge Rogue Trainer");
            pPlayer->SEND_GOSSIP_MENU(2774, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(-4605.0f, -1110.45f, 7, 6, 0, "Ironforge Warlock Trainer");
            pPlayer->SEND_GOSSIP_MENU(2775, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(-5023.08f, -1253.68f, 7, 6, 0, "Hall of Arms");
            pPlayer->SEND_GOSSIP_MENU(2776, pCreature->GetGUID());
            break;
            pPlayer->SEND_GOSSIP_MENU(2766, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-4858.5f, -1241.83f, 7, 6, 0, "Berryfizz's Potions and Mixed Drinks");
            pPlayer->SEND_GOSSIP_MENU(2794, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-4796.97f, -1110.17f, 7, 6, 0, "The Great Forge");
            pPlayer->SEND_GOSSIP_MENU(2795, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-4767.83f, -1184.59f, 7, 6, 0, "The Bronze Kettle");
            pPlayer->SEND_GOSSIP_MENU(2796, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-4803.72f, -1196.53f, 7, 6, 0, "Thistlefuzz Arcanery");
            pPlayer->SEND_GOSSIP_MENU(2797, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-4799.56f, -1250.23f, 7, 6, 0, "Springspindle's Gadgets");
            pPlayer->SEND_GOSSIP_MENU(2798, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-4881.6f, -1153.13f, 7, 6, 0, "Ironforge Physician");
            pPlayer->SEND_GOSSIP_MENU(2799, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-4597.91f, -1091.93f, 7, 6, 0, "Traveling Fisherman");
            pPlayer->SEND_GOSSIP_MENU(2800, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-4876.9f, -1151.92f, 7, 6, 0, "Ironforge Physician");
            pPlayer->SEND_GOSSIP_MENU(2801, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(-4745.0f, -1027.57f, 7, 6, 0, "Finespindle's Leather Goods");
            pPlayer->SEND_GOSSIP_MENU(2802, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Minning
            pPlayer->SEND_POI(-4705.06f, -1116.43f, 7, 6, 0, "Deepmountain Mining Guild");
            pPlayer->SEND_GOSSIP_MENU(2804, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(-4745.0f, -1027.57f, 7, 6, 0, "Finespindle's Leather Goods");
            pPlayer->SEND_GOSSIP_MENU(2805, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(-4719.60f, -1056.96f, 7, 6, 0, "Stonebrow's Clothier");
            pPlayer->SEND_GOSSIP_MENU(2807, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_ironforge(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_ironforge(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_ironforge end
 *******************************************************/

CreatureAI* GetAI_guard_ironforge(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_mulgore start
 *******************************************************/

bool GossipHello_guard_mulgore(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(3543, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4051, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind rider
            pPlayer->SEND_GOSSIP_MENU(4052, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(-2361.38f, -349.19f, 7, 6, 0, "Bloodhoof Village Inn");
            pPlayer->SEND_GOSSIP_MENU(4053, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable master
            pPlayer->SEND_POI(-2338.86f, -357.56f, 7, 6, 0, "Seikwa");
            pPlayer->SEND_GOSSIP_MENU(5976, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(4069, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING   , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(4070, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(-2312.15f, -443.69f, 7, 6, 0, "Gennia Runetotem");
            pPlayer->SEND_GOSSIP_MENU(4054, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(-2178.14f, -406.14f, 7, 6, 0, "Yaw Sharpmane");
            pPlayer->SEND_GOSSIP_MENU(4055, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Shaman
            pPlayer->SEND_POI(-2301.5f, -439.87f, 7, 6, 0, "Narm Skychaser");
            pPlayer->SEND_GOSSIP_MENU(4056, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Warrior
            pPlayer->SEND_POI(-2345.43f, -494.11f, 7, 6, 0, "Krang Stonehoof");
            pPlayer->SEND_GOSSIP_MENU(4057, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_GOSSIP_MENU(4058, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_GOSSIP_MENU(4059, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-2263.34f, -287.91f, 7, 6, 0, "Pyall Silentstride");
            pPlayer->SEND_GOSSIP_MENU(4060, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_GOSSIP_MENU(4061, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-2353.52f, -355.82f, 7, 6, 0, "Vira Younghoof");
            pPlayer->SEND_GOSSIP_MENU(4062, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
            pPlayer->SEND_POI(-2349.21f, -241.37f, 7, 6, 0, "Uthan Stillwater");
            pPlayer->SEND_GOSSIP_MENU(4063, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
            pPlayer->SEND_GOSSIP_MENU(4064, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Leatherworking
            pPlayer->SEND_POI(-2257.12f, -288.63f, 7, 6, 0, "Chaw Stronghide");
            pPlayer->SEND_GOSSIP_MENU(4065, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mining
            pPlayer->SEND_GOSSIP_MENU(4066, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Skinning
            pPlayer->SEND_POI(-2252.94f, -291.32f, 7, 6, 0, "Yonn Deepcut");
            pPlayer->SEND_GOSSIP_MENU(4067, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4068, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_mulgore(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_mulgore(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_mulgore(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_mulgore(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_mulgore end
 *******************************************************/

CreatureAI* GetAI_guard_mulgore(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_orgrimmar start
 *******************************************************/

bool GossipHello_guard_orgrimmar(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ZEPPLINMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_OFFICERS      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
    pPlayer->SEND_GOSSIP_MENU(2593, pCreature->GetGUID());

    return true;
}

void SendDefaultMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(1631.51f, -4375.33f, 7, 6, 0, "Bank of Orgrimmar");
            pPlayer->SEND_GOSSIP_MENU(2554, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //wind rider
            pPlayer->SEND_POI(1676.6f, -4332.72f, 7, 6, 0, "The Sky Tower");
            pPlayer->SEND_GOSSIP_MENU(2555, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //guild master
            pPlayer->SEND_POI(1576.93f, -4294.75f, 7, 6, 0, "Horde Embassy");
            pPlayer->SEND_GOSSIP_MENU(2556, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(1644.51f, -4447.27f, 7, 6, 0, "Orgrimmar Inn");
            pPlayer->SEND_GOSSIP_MENU(2557, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //mailbox
            pPlayer->SEND_POI(1622.53f, -4388.79f, 7, 6, 0, "Orgrimmar Mailbox");
            pPlayer->SEND_GOSSIP_MENU(2558, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //auction house
            pPlayer->SEND_POI(1679.21f, -4450.1f, 7, 6, 0, "Orgrimmar Auction House");
            pPlayer->SEND_GOSSIP_MENU(3075, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //zeppelin
            pPlayer->SEND_POI(1337.36f, -4632.7f, 7, 6, 0, "Orgrimmar Zeppelin Tower");
            pPlayer->SEND_GOSSIP_MENU(3173, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //weapon master
            pPlayer->SEND_POI(2092.56f, -4823.95f, 7, 6, 0, "Sayoc & Hanashi");
            pPlayer->SEND_GOSSIP_MENU(4519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //stable master
            pPlayer->SEND_POI(2133.12f, -4663.93f, 7, 6, 0, "Xon'cha");
            pPlayer->SEND_GOSSIP_MENU(5974, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //officers lounge
            pPlayer->SEND_POI(1633.56f, -4249.37f, 7, 6, 0, "Hall of Legends");
            pPlayer->SEND_GOSSIP_MENU(7046, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY       , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(2599, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(2594, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Hall of the Brave");
            pPlayer->SEND_GOSSIP_MENU(7484, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Hall of the Brave");
            pPlayer->SEND_GOSSIP_MENU(7644, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Hall of the Brave");
            pPlayer->SEND_GOSSIP_MENU(7520, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Hunter
            pPlayer->SEND_POI(2114.84f, -4625.31f, 7, 6, 0, "Orgrimmar Hunter's Hall");
            pPlayer->SEND_GOSSIP_MENU(2559, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Mage
            pPlayer->SEND_POI(1451.26f, -4223.33f, 7, 6, 0, "Darkbriar Lodge");
            pPlayer->SEND_GOSSIP_MENU(2560, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(1442.21f, -4183.24f, 7, 6, 0, "Spirit Lodge");
            pPlayer->SEND_GOSSIP_MENU(2561, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Shaman
            pPlayer->SEND_POI(1925.34f, -4181.89f, 7, 6, 0, "Thrall's Fortress");
            pPlayer->SEND_GOSSIP_MENU(2562, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Rogue
            pPlayer->SEND_POI(1773.39f, -4278.97f, 7, 6, 0, "Shadowswift Brotherhood");
            pPlayer->SEND_GOSSIP_MENU(2563, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warlock
            pPlayer->SEND_POI(1849.57f, -4359.68f, 7, 6, 0, "Darkfire Enclave");
            pPlayer->SEND_GOSSIP_MENU(2564, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Warrior
            pPlayer->SEND_POI(1983.92f, -4794.2f, 7, 6, 0, "Hall of the Brave");
            pPlayer->SEND_GOSSIP_MENU(2565, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(1955.17f, -4475.79f, 7, 6, 0, "Yelmak's Alchemy and Potions");
            pPlayer->SEND_GOSSIP_MENU(2497, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(2054.34f, -4831.85f, 7, 6, 0, "The Burning Anvil");
            pPlayer->SEND_GOSSIP_MENU(2499, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(1780.96f, -4481.31f, 7, 6, 0, "Borstan's Firepit");
            pPlayer->SEND_GOSSIP_MENU(2500, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(1917.5f, -4434.95f, 7, 6, 0, "Godan's Runeworks");
            pPlayer->SEND_GOSSIP_MENU(2501, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(2038.45f, -4744.75f, 7, 6, 0, "Nogg's Machine Shop");
            pPlayer->SEND_GOSSIP_MENU(2653, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(1485.21f, -4160.91f, 7, 6, 0, "Survival of the Fittest");
            pPlayer->SEND_GOSSIP_MENU(2502, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(1994.15f, -4655.7f, 7, 6, 0, "Lumak's Fishing");
            pPlayer->SEND_GOSSIP_MENU(2503, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(1898.61f, -4454.93f, 7, 6, 0, "Jandi's Arboretum");
            pPlayer->SEND_GOSSIP_MENU(2504, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(1852.82f, -4562.31f, 7, 6, 0, "Kodohide Leatherworkers");
            pPlayer->SEND_GOSSIP_MENU(2513, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(2029.79f, -4704.0f, 7, 6, 0, "Red Canyon Mining");
            pPlayer->SEND_GOSSIP_MENU(2515, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(1852.82f, -4562.31f, 7, 6, 0, "Kodohide Leatherworkers");
            pPlayer->SEND_GOSSIP_MENU(2516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(1802.66f, -4560.66f, 7, 6, 0, "Magar's Cloth Goods");
            pPlayer->SEND_GOSSIP_MENU(2518, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_orgrimmar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_orgrimmar(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_orgrimmar end
 *******************************************************/

CreatureAI* GetAI_guard_orgrimmar(Creature* pCreature)
{
    return new guardAI_orgrimmar (pCreature);
}

/*******************************************************
 * guard_stormwind start
 *******************************************************/

bool GossipHello_guard_stormwind(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STORMWIND_BANK    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DEEPRUNTRAM       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN               , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GRYPHON           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_OFFICERS          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
    pPlayer->SEND_GOSSIP_MENU(933, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Auction House
            pPlayer->SEND_POI(-8811.46f, 667.46f, 7, 6, 0, "Stormwind Auction House");
            pPlayer->SEND_GOSSIP_MENU(3834, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bank
            pPlayer->SEND_POI(-8916.87f, 622.87f, 7, 6, 0, "Stormwind Bank");
            pPlayer->SEND_GOSSIP_MENU(764, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Deeprun tram
            pPlayer->SEND_POI(-8378.88f, 554.23f, 7, 6, 0, "The Deeprun Tram");
            pPlayer->SEND_GOSSIP_MENU(3813, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-8869.0f, 675.4f, 7, 6, 0, "The Gilded Rose");
            pPlayer->SEND_GOSSIP_MENU(3860, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Gryphon Master
            pPlayer->SEND_POI(-8837.0f, 493.5f, 7, 6, 0, "Stormwind Gryphon Master");
            pPlayer->SEND_GOSSIP_MENU(879, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Guild Master
            pPlayer->SEND_POI(-8894.0f, 611.2f, 7, 6, 0, "Stormwind Vistor`s Center");
            pPlayer->SEND_GOSSIP_MENU(882, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Mailbox
            pPlayer->SEND_POI(-8876.48f, 649.18f, 7, 6, 0, "Stormwind Mailbox");
            pPlayer->SEND_GOSSIP_MENU(3861, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable Master
            pPlayer->SEND_POI(-8433.0f, 554.7f, 7, 6, 0, "Jenova Stoneshield");
            pPlayer->SEND_GOSSIP_MENU(5984, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Weapon Trainer
            pPlayer->SEND_POI(-8797.0f, 612.8f, 7, 6, 0, "Woo Ping");
            pPlayer->SEND_GOSSIP_MENU(4516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Officers Lounge
            pPlayer->SEND_POI(-8759.92f, 399.69f, 7, 6, 0, "Champions` Hall");
            pPlayer->SEND_GOSSIP_MENU(7047, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Battlemasters
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY        , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN          , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH          , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7499, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Class trainers
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PALADIN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->SEND_GOSSIP_MENU(898, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:                   //Profession trainers
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(918, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-8443.88f, 335.99f, 7, 6, 0, "Thelman Slatefist");
            pPlayer->SEND_GOSSIP_MENU(7500, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-8443.88f, 335.99f, 7, 6, 0, "Lady Hoteshem");
            pPlayer->SEND_GOSSIP_MENU(7650, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(-8443.88f, 335.99f, 7, 6, 0, "Elfarran");
            pPlayer->SEND_GOSSIP_MENU(7501, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
            pPlayer->SEND_POI(-9012.0f, 867.6f, 7, 6, 0, "Wizard`s Sanctum");
            pPlayer->SEND_GOSSIP_MENU(899, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Rogue
            pPlayer->SEND_POI(-8753.0f, 367.8f, 7, 6, 0, "Stormwind - Rogue House");
            pPlayer->SEND_GOSSIP_MENU(900, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Warrior
            pPlayer->SEND_POI(-8624.54f, 402.61f, 7, 6, 0, "Pig and Whistle Tavern");
            pPlayer->SEND_GOSSIP_MENU(901, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Druid
            pPlayer->SEND_POI(-8751.0f, 1124.5f, 7, 6, 0, "The Park");
            pPlayer->SEND_GOSSIP_MENU(902, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Priest
            pPlayer->SEND_POI(-8512.0f, 862.4f, 7, 6, 0, "Catedral Of Light");
            pPlayer->SEND_GOSSIP_MENU(903, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Paladin
            pPlayer->SEND_POI(-8577.0f, 881.7f, 7, 6, 0, "Catedral Of Light");
            pPlayer->SEND_GOSSIP_MENU(904, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Hunter
            pPlayer->SEND_POI(-8413.0f, 541.5f, 7, 6, 0, "Hunter Lodge");
            pPlayer->SEND_GOSSIP_MENU(905, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Warlock
            pPlayer->SEND_POI(-8948.91f, 998.35f, 7, 6, 0, "The Slaughtered Lamb");
            pPlayer->SEND_GOSSIP_MENU(906, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-8988.0f, 759.60f, 7, 6, 0, "Alchemy Needs");
            pPlayer->SEND_GOSSIP_MENU(919, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-8424.0f, 616.9f, 7, 6, 0, "Therum Deepforge");
            pPlayer->SEND_GOSSIP_MENU(920, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-8611.0f, 364.6f, 7, 6, 0, "Pig and Whistle Tavern");
            pPlayer->SEND_GOSSIP_MENU(921, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-8858.0f, 803.7f, 7, 6, 0, "Lucan Cordell");
            pPlayer->SEND_GOSSIP_MENU(941, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(-8347.0f, 644.1f, 7, 6, 0, "Lilliam Sparkspindle");
            pPlayer->SEND_GOSSIP_MENU(922, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(-8513.0f, 801.8f, 7, 6, 0, "Shaina Fuller");
            pPlayer->SEND_GOSSIP_MENU(923, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(-8803.0f, 767.5f, 7, 6, 0, "Arnold Leland");
            pPlayer->SEND_GOSSIP_MENU(940, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(-8967.0f, 779.5f, 7, 6, 0, "Alchemy Needs");
            pPlayer->SEND_GOSSIP_MENU(924, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(-8726.0f, 477.4f, 7, 6, 0, "The Protective Hide");
            pPlayer->SEND_GOSSIP_MENU(925, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(-8434.0f, 692.8f, 7, 6, 0, "Gelman Stonehand");
            pPlayer->SEND_GOSSIP_MENU(927, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(-8716.0f, 469.4f, 7, 6, 0, "The Protective Hide");
            pPlayer->SEND_GOSSIP_MENU(928, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(-8938.0f, 800.7f, 7, 6, 0, "Duncan`s Textiles");
            pPlayer->SEND_GOSSIP_MENU(929, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_stormwind(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_stormwind(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_stormwind end
 *******************************************************/

CreatureAI* GetAI_guard_stormwind(Creature* pCreature)
{
    return new guardAI_stormwind (pCreature);
}

/*******************************************************
 * guard_teldrassil start
 *******************************************************/

bool GossipHello_guard_teldrassil(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FERRY        , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->SEND_GOSSIP_MENU(4316, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4317, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Rut`theran
            pPlayer->SEND_GOSSIP_MENU(4318, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_GOSSIP_MENU(4319, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(9821.49f, 960.13f, 7, 6, 0, "Dolanaar Inn");
            pPlayer->SEND_GOSSIP_MENU(4320, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //stable master
            pPlayer->SEND_POI(9808.37f, 931.1f, 7, 6, 0, "Seriadne");
            pPlayer->SEND_GOSSIP_MENU(5982, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(4264, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->SEND_GOSSIP_MENU(4273, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(9741.58f, 963.7f, 7, 6, 0, "Kal");
            pPlayer->SEND_GOSSIP_MENU(4323, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(9815.12f, 926.28f, 7, 6, 0, "Dazalar");
            pPlayer->SEND_GOSSIP_MENU(4324, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Priest
            pPlayer->SEND_POI(9906.16f, 986.63f, 7, 6, 0, "Laurna Morninglight");
            pPlayer->SEND_GOSSIP_MENU(4325, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Rogue
            pPlayer->SEND_POI(9789.0f, 942.86f, 7, 6, 0, "Jannok Breezesong");
            pPlayer->SEND_GOSSIP_MENU(4326, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(9821.96f, 950.61f, 7, 6, 0, "Kyra Windblade");
            pPlayer->SEND_GOSSIP_MENU(4327, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(9767.59f, 878.81f, 7, 6, 0, "Cyndra Kindwhisper");
            pPlayer->SEND_GOSSIP_MENU(4329, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Cooking
            pPlayer->SEND_POI(9751.19f, 906.13f, 7, 6, 0, "Zarrin");
            pPlayer->SEND_GOSSIP_MENU(4330, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Enchanting
            pPlayer->SEND_POI(10677.59f, 1946.56f, 7, 6, 0, "Alanna Raveneye");
            pPlayer->SEND_GOSSIP_MENU(4331, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //First Aid
            pPlayer->SEND_POI(9903.12f, 999.0f, 7, 6, 0, "Byancie");
            pPlayer->SEND_GOSSIP_MENU(4332, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Fishing
            pPlayer->SEND_GOSSIP_MENU(4333, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Herbalism
            pPlayer->SEND_POI(9773.78f, 875.88f, 7, 6, 0, "Malorne Bladeleaf");
            pPlayer->SEND_GOSSIP_MENU(4334, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Leatherworking
            pPlayer->SEND_POI(10152.59f, 1681.46f, 7, 6, 0, "Nadyia Maneweaver");
            pPlayer->SEND_GOSSIP_MENU(4335, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Skinning
            pPlayer->SEND_POI(10135.59f, 1673.18f, 7, 6, 0, "Radnaal Maneweaver");
            pPlayer->SEND_GOSSIP_MENU(4336, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Tailoring
            pPlayer->SEND_GOSSIP_MENU(4337, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_teldrassil(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_teldrassil(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_teldrassil(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_teldrassil(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_teldrassil end
 *******************************************************/

CreatureAI* GetAI_guard_teldrassil(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_tirisfal start
 *******************************************************/

bool GossipHello_guard_tirisfal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK            , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN             , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER     , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->SEND_GOSSIP_MENU(4097, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_GOSSIP_MENU(4074, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //bat handler
            pPlayer->SEND_GOSSIP_MENU(4075, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Inn
            pPlayer->SEND_POI(2246.68f, 241.89f, 7, 6, 0, "Gallows` End Tavern");
            pPlayer->SEND_GOSSIP_MENU(4076, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Stable Master
            pPlayer->SEND_POI(2267.66f, 319.32f, 7, 6, 0, "Morganus");
            pPlayer->SEND_GOSSIP_MENU(5978, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                 , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(4292, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING               , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(4096, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Cain Firesong");
            pPlayer->SEND_GOSSIP_MENU(4077, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Priest
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Dark Cleric Beryl");
            pPlayer->SEND_GOSSIP_MENU(4078, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Rogue
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Marion Call");
            pPlayer->SEND_GOSSIP_MENU(4079, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Warlock
            pPlayer->SEND_POI(2259.18f, 240.93f, 7, 6, 0, "Rupert Boch");
            pPlayer->SEND_GOSSIP_MENU(4080, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(2256.48f, 240.32f, 7, 6, 0, "Austil de Mon");
            pPlayer->SEND_GOSSIP_MENU(4081, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(2263.25f, 344.23f, 7, 6, 0, "Carolai Anise");
            pPlayer->SEND_GOSSIP_MENU(4082, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_GOSSIP_MENU(4083, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_GOSSIP_MENU(4084, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(2250.35f, 249.12f, 7, 6, 0, "Vance Undergloom");
            pPlayer->SEND_GOSSIP_MENU(4085, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_GOSSIP_MENU(4086, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(2246.68f, 241.89f, 7, 6, 0, "Nurse Neela");
            pPlayer->SEND_GOSSIP_MENU(4087, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(2292.37f, -10.72f, 7, 6, 0, "Clyde Kellen");
            pPlayer->SEND_GOSSIP_MENU(4088, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(2268.21f, 331.69f, 7, 6, 0, "Faruza");
            pPlayer->SEND_GOSSIP_MENU(4089, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(2027.0f, 78.72f, 7, 6, 0, "Shelene Rhobart");
            pPlayer->SEND_GOSSIP_MENU(4090, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_GOSSIP_MENU(4091, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(2027.0f, 78.72f, 7, 6, 0, "Rand Rhobart");
            pPlayer->SEND_GOSSIP_MENU(4092, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(2160.45f, 659.93f, 7, 6, 0, "Bowen Brisboise");
            pPlayer->SEND_GOSSIP_MENU(4093, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_tirisfal(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_tirisfal(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_tirisfal(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_tirisfal(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_tirisfal end
 *******************************************************/

CreatureAI* GetAI_guard_tirisfal(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_undercity start
 *******************************************************/

bool GossipHello_guard_undercity(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATHANDLER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN           , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX       , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ZEPPLINMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER   , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->SEND_GOSSIP_MENU(3543, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(1595.64f, 232.45f, 7, 6, 0, "Undercity Bank");
            pPlayer->SEND_GOSSIP_MENU(3514, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Bat handler
            pPlayer->SEND_POI(1565.9f, 271.43f, 7, 6, 0, "Undercity Bat Handler");
            pPlayer->SEND_GOSSIP_MENU(3515, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(1594.17f, 205.57f, 7, 6, 0, "Undercity Guild Master");
            pPlayer->SEND_GOSSIP_MENU(3516, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(1639.43f, 220.99f, 7, 6, 0, "Undercity Inn");
            pPlayer->SEND_GOSSIP_MENU(3517, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(1632.68f, 219.4f, 7, 6, 0, "Undercity Mailbox");
            pPlayer->SEND_GOSSIP_MENU(3518, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Auction House
            pPlayer->SEND_POI(1647.9f, 258.49f, 7, 6, 0, "Undercity Auction House");
            pPlayer->SEND_GOSSIP_MENU(3519, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Zeppelin
            pPlayer->SEND_POI(2059.0f, 274.86f, 7, 6, 0, "Undercity Zeppelin");
            pPlayer->SEND_GOSSIP_MENU(3520, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Weapon Master
            pPlayer->SEND_POI(1670.31f, 324.66f, 7, 6, 0, "Archibald");
            pPlayer->SEND_GOSSIP_MENU(4521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Stable master
            pPlayer->SEND_POI(1634.18f, 226.76f, 7, 6, 0, "Anya Maulray");
            pPlayer->SEND_GOSSIP_MENU(5979, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY   , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH     , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7527, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE            , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST          , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ROGUE           , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARLOCK         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR         , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(3542, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING   , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENGINEERING     , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING         , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING  , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING        , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(3541, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(1329.0f, 333.92f, 7, 6, 0, "Grizzle Halfmane");
            pPlayer->SEND_GOSSIP_MENU(7525, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(1283.3f, 287.16f, 7, 6, 0, "Sir Malory Wheeler");
            pPlayer->SEND_GOSSIP_MENU(7646, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(1265.0f, 351.18f, 7, 6, 0, "Kurden Bloodclaw");
            pPlayer->SEND_GOSSIP_MENU(7526, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Mage
            pPlayer->SEND_POI(1781.0f, 53.0f, 7, 6, 0, "Undercity Mage Trainers");
            pPlayer->SEND_GOSSIP_MENU(3513, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Priest
            pPlayer->SEND_POI(1758.33f, 401.5f, 7, 6, 0, "Undercity Priest Trainers");
            pPlayer->SEND_GOSSIP_MENU(3521, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Rogue
            pPlayer->SEND_POI(1418.56f, 65.0f, 7, 6, 0, "Undercity Rogue Trainers");
            pPlayer->SEND_GOSSIP_MENU(3524, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Warlock
            pPlayer->SEND_POI(1780.92f, 53.16f, 7, 6, 0, "Undercity Warlock Trainers");
            pPlayer->SEND_GOSSIP_MENU(3526, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Warrior
            pPlayer->SEND_POI(1775.59f, 418.19f, 7, 6, 0, "Undercity Warrior Trainers");
            pPlayer->SEND_GOSSIP_MENU(3527, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(1419.82f, 417.19f, 7, 6, 0, "The Apothecarium");
            pPlayer->SEND_GOSSIP_MENU(3528, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(1696.0f, 285.0f, 7, 6, 0, "Undercity Blacksmithing Trainer");
            pPlayer->SEND_GOSSIP_MENU(3529, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(1596.34f, 274.68f, 7, 6, 0, "Undercity Cooking Trainer");
            pPlayer->SEND_GOSSIP_MENU(3530, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(1488.54f, 280.19f, 7, 6, 0, "Undercity Enchanting Trainer");
            pPlayer->SEND_GOSSIP_MENU(3531, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Engineering
            pPlayer->SEND_POI(1408.58f, 143.43f, 7, 6, 0, "Undercity Engineering Trainer");
            pPlayer->SEND_GOSSIP_MENU(3532, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //First Aid
            pPlayer->SEND_POI(1519.65f, 167.19f, 7, 6, 0, "Undercity First Aid Trainer");
            pPlayer->SEND_GOSSIP_MENU(3533, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Fishing
            pPlayer->SEND_POI(1679.9f, 89.0f, 7, 6, 0, "Undercity Fishing Trainer");
            pPlayer->SEND_GOSSIP_MENU(3534, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Herbalism
            pPlayer->SEND_POI(1558.0f, 349.36f, 7, 6, 0, "Undercity Herbalism Trainer");
            pPlayer->SEND_GOSSIP_MENU(3535, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Leatherworking
            pPlayer->SEND_POI(1498.76f, 196.43f, 7, 6, 0, "Undercity Leatherworking Trainer");
            pPlayer->SEND_GOSSIP_MENU(3536, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Mining
            pPlayer->SEND_POI(1642.88f, 335.58f, 7, 6, 0, "Undercity Mining Trainer");
            pPlayer->SEND_GOSSIP_MENU(3537, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Skinning
            pPlayer->SEND_POI(1498.6f, 196.46f, 7, 6, 0, "Undercity Skinning Trainer");
            pPlayer->SEND_GOSSIP_MENU(3538, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:                   //Tailoring
            pPlayer->SEND_POI(1689.55f, 193.0f, 7, 6, 0, "Undercity Tailoring Trainer");
            pPlayer->SEND_GOSSIP_MENU(3539, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_undercity(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_undercity(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_undercity end
 *******************************************************/

CreatureAI* GetAI_guard_undercity(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_bluffwatcher start
 *******************************************************/

bool GossipHello_guard_bluffwatcher(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK         , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WINDRIDER    , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN          , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX      , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_AUCTIONHOUSE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WEAPONMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CLASSTRAINER , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PROFTRAINER  , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
    pPlayer->SEND_GOSSIP_MENU(3543, pCreature->GetGUID());
    return true;
}

void SendDefaultMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Bank
            pPlayer->SEND_POI(-1257.8f, 24.14f, 7, 6, 0, "Thunder Bluff Bank");
            pPlayer->SEND_GOSSIP_MENU(1292, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Wind master
            pPlayer->SEND_POI(-1196.43f, 28.26f, 7, 6, 0, "Wind Rider Roost");
            pPlayer->SEND_GOSSIP_MENU(1293, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Guild master
            pPlayer->SEND_POI(-1296.5f, 127.57f, 7, 6, 0, "Thunder Bluff Civic Information");
            pPlayer->SEND_GOSSIP_MENU(1291, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Inn
            pPlayer->SEND_POI(-1296.0f, 39.7f, 7, 6, 0, "Thunder Bluff Inn");
            pPlayer->SEND_GOSSIP_MENU(3153, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Mailbox
            pPlayer->SEND_POI(-1263.59f, 44.36f, 7, 6, 0, "Thunder Bluff Mailbox");
            pPlayer->SEND_GOSSIP_MENU(3154, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Auction House
            pPlayer->SEND_POI(1381.77f, -4371.16f, 7, 6, 0, GOSSIP_TEXT_AUCTIONHOUSE);
            pPlayer->SEND_GOSSIP_MENU(3155, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Weapon master
            pPlayer->SEND_POI(-1282.31f, 89.56f, 7, 6, 0, "Ansekhwa");
            pPlayer->SEND_GOSSIP_MENU(4520, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Stable master
            pPlayer->SEND_POI(-1270.19f, 48.84f, 7, 6, 0, "Bulrug");
            pPlayer->SEND_GOSSIP_MENU(5977, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //battlemaster
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALTERACVALLEY       , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARATHIBASIN         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARSONGULCH         , GOSSIP_SENDER_SEC_BATTLEINFO, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(7527, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Class trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_DRUID               , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HUNTER              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAGE                , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_PRIEST              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SHAMAN              , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_WARRIOR             , GOSSIP_SENDER_SEC_CLASSTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(3542, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Profession trainer
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ALCHEMY             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BLACKSMITHING       , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_COOKING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ENCHANTING          , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FIRSTAID            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FISHING             , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_HERBALISM           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 7);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LEATHERWORKING      , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 8);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MINING              , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 9);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SKINNING            , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 10);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TAILORING           , GOSSIP_SENDER_SEC_PROFTRAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(3541, pCreature->GetGUID());
            break;
    }
}

void SendBattleMasterMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //AV
            pPlayer->SEND_POI(-1387.82f, -97.55f, 7, 6, 0, "Taim Ragetotem");
            pPlayer->SEND_GOSSIP_MENU(7522, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //AB
            pPlayer->SEND_POI(-997.0f, 214.12f, 7, 6, 0, "Martin Lindsey");
            pPlayer->SEND_GOSSIP_MENU(7648, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //WSG
            pPlayer->SEND_POI(-1384.94f, -75.91f, 7, 6, 0, "Kergul Bloodaxe");
            pPlayer->SEND_GOSSIP_MENU(7523, pCreature->GetGUID());
            break;
    }
}

void SendClassTrainerMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Druid
            pPlayer->SEND_POI(-1054.47f, -285.0f, 7, 6, 0, "Hall of Elders");
            pPlayer->SEND_GOSSIP_MENU(1294, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Hunter
            pPlayer->SEND_POI(-1416.32f, -114.28f, 7, 6, 0, "Hunter's Hall");
            pPlayer->SEND_GOSSIP_MENU(1295, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Mage
            pPlayer->SEND_POI(-1061.2f, 195.5f, 7, 6, 0, "Pools of Vision");
            pPlayer->SEND_GOSSIP_MENU(1296, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Priest
            pPlayer->SEND_POI(-1061.2f, 195.5f, 7, 6, 0, "Pools of Vision");
            pPlayer->SEND_GOSSIP_MENU(1297, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //Shaman
            pPlayer->SEND_POI(-989.54f, 278.25f, 7, 6, 0, "Hall of Spirits");
            pPlayer->SEND_GOSSIP_MENU(1298, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Warrior
            pPlayer->SEND_POI(-1416.32f, -114.28f, 7, 6, 0, "Hunter's Hall");
            pPlayer->SEND_GOSSIP_MENU(1299, pCreature->GetGUID());
            break;
    }
}

void SendProfTrainerMenu_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:                    //Alchemy
            pPlayer->SEND_POI(-1085.56f, 27.29f, 7, 6, 0, "Bena's Alchemy");
            pPlayer->SEND_GOSSIP_MENU(1332, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:                    //Blacksmithing
            pPlayer->SEND_POI(-1239.75f, 104.88f, 7, 6, 0, "Karn's Smithy");
            pPlayer->SEND_GOSSIP_MENU(1333, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:                    //Cooking
            pPlayer->SEND_POI(-1214.5f, -21.23f, 7, 6, 0, "Aska's Kitchen");
            pPlayer->SEND_GOSSIP_MENU(1334, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:                    //Enchanting
            pPlayer->SEND_POI(-1112.65f, 48.26f, 7, 6, 0, "Dawnstrider Enchanters");
            pPlayer->SEND_GOSSIP_MENU(1335, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:                    //First Aid
            pPlayer->SEND_POI(-996.58f, 200.5f, 7, 6, 0, "Spiritual Healing");
            pPlayer->SEND_GOSSIP_MENU(1336, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:                    //Fishing
            pPlayer->SEND_POI(-1169.35f, -68.87f, 7, 6, 0, "Mountaintop Bait & Tackle");
            pPlayer->SEND_GOSSIP_MENU(1337, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:                    //Herbalism
            pPlayer->SEND_POI(-1137.7f, -1.51f, 7, 6, 0, "Holistic Herbalism");
            pPlayer->SEND_GOSSIP_MENU(1338, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 8:                    //Leatherworking
            pPlayer->SEND_POI(-1156.22f, 66.86f, 7, 6, 0, "Thunder Bluff Armorers");
            pPlayer->SEND_GOSSIP_MENU(1339, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:                    //Mining
            pPlayer->SEND_POI(-1249.17f, 155.0f, 7, 6, 0, "Stonehoof Geology");
            pPlayer->SEND_GOSSIP_MENU(1340, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:                   //Skinning
            pPlayer->SEND_POI(-1148.56f, 51.18f, 7, 6, 0, "Mooranta");
            pPlayer->SEND_GOSSIP_MENU(1343, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:                   //Tailoring
            pPlayer->SEND_POI(-1156.22f, 66.86f, 7, 6, 0, "Thunder Bluff Armorers");
            pPlayer->SEND_GOSSIP_MENU(1341, pCreature->GetGUID());
            break;
    }
}

bool GossipSelect_guard_bluffwatcher(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiSender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_CLASSTRAIN:  SendClassTrainerMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_PROFTRAIN:   SendProfTrainerMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_SEC_BATTLEINFO:  SendBattleMasterMenu_guard_bluffwatcher(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

/*******************************************************
 * guard_bluffwatcher end
 *******************************************************/

CreatureAI* GetAI_guard_bluffwatcher(Creature* pCreature)
{
    return new guardAI(pCreature);
} 

/*******************************************************
 * AddSC
 *******************************************************/

void AddSC_guards()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "guard_contested";
    newscript->GetAI = &GetAI_guard_contested;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_darnassus";
    newscript->pGossipHello          = &GossipHello_guard_darnassus;
    newscript->pGossipSelect         = &GossipSelect_guard_darnassus;
    newscript->GetAI = &GetAI_guard_darnassus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_dunmorogh";
    newscript->pGossipHello          = &GossipHello_guard_dunmorogh;
    newscript->pGossipSelect         = &GossipSelect_guard_dunmorogh;
    newscript->GetAI = &GetAI_guard_dunmorogh;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_durotar";
    newscript->pGossipHello          = &GossipHello_guard_durotar;
    newscript->pGossipSelect         = &GossipSelect_guard_durotar;
    newscript->GetAI = &GetAI_guard_durotar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_elwynnforest";
    newscript->pGossipHello          = &GossipHello_guard_elwynnforest;
    newscript->pGossipSelect         = &GossipSelect_guard_elwynnforest;
    newscript->GetAI = &GetAI_guard_elwynnforest;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_ironforge";
    newscript->pGossipHello          = &GossipHello_guard_ironforge;
    newscript->pGossipSelect         = &GossipSelect_guard_ironforge;
    newscript->GetAI = &GetAI_guard_ironforge;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_mulgore";
    newscript->pGossipHello          = &GossipHello_guard_mulgore;
    newscript->pGossipSelect         = &GossipSelect_guard_mulgore;
    newscript->GetAI = &GetAI_guard_mulgore;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_orgrimmar";
    newscript->pGossipHello          = &GossipHello_guard_orgrimmar;
    newscript->pGossipSelect         = &GossipSelect_guard_orgrimmar;
    newscript->GetAI = &GetAI_guard_orgrimmar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_stormwind";
    newscript->pGossipHello          = &GossipHello_guard_stormwind;
    newscript->pGossipSelect         = &GossipSelect_guard_stormwind;
    newscript->GetAI = &GetAI_guard_stormwind;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_teldrassil";
    newscript->pGossipHello          = &GossipHello_guard_teldrassil;
    newscript->pGossipSelect         = &GossipSelect_guard_teldrassil;
    newscript->GetAI = &GetAI_guard_teldrassil;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_tirisfal";
    newscript->pGossipHello          = &GossipHello_guard_tirisfal;
    newscript->pGossipSelect         = &GossipSelect_guard_tirisfal;
    newscript->GetAI = &GetAI_guard_tirisfal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_undercity";
    newscript->pGossipHello          = &GossipHello_guard_undercity;
    newscript->pGossipSelect         = &GossipSelect_guard_undercity;
    newscript->GetAI = &GetAI_guard_undercity;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "guard_bluffwatcher";
    newscript->pGossipHello = &GossipHello_guard_bluffwatcher;
    newscript->pGossipSelect = &GossipSelect_guard_bluffwatcher;
    newscript->GetAI = &GetAI_guard_bluffwatcher;
    newscript->RegisterSelf();
	
}
