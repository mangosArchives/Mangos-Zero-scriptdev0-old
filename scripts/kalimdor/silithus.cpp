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
SDName: Silithus
SD%Complete: 100
SDComment: Quest support: 7785, 8304, 8519.
SDCategory: Silithus
EndScriptData */

/* ContentData
npc_highlord_demitrian
npcs_rutgar_and_frankal
npc_anachronos_the_ancient
EndContentData */

#include "precompiled.h"

/*###
## npc_highlord_demitrian
###*/

#define GOSSIP_ITEM_DEMITRIAN1 "What do you know of it?"
#define GOSSIP_ITEM_DEMITRIAN2 "I am listening , Demitrian."
#define GOSSIP_ITEM_DEMITRIAN3 "Continue, please."
#define GOSSIP_ITEM_DEMITRIAN4 "A battle?"
#define GOSSIP_ITEM_DEMITRIAN5 "<Nod>"
#define GOSSIP_ITEM_DEMITRIAN6 "Caught unaware? How?"
#define GOSSIP_ITEM_DEMITRIAN7 "So what did Ragnaros do next?"

enum
{
    QUEST_EXAMINE_THE_VESSEL        =   7785,
    ITEM_BINDINGS_WINDSEEKER_LEFT   =   18563,
    ITEM_BINDINGS_WINDSEEKER_RIGHT  =   18564,
    ITEM_VESSEL_OF_REBIRTH          =   19016,
    GOSSIP_TEXTID_DEMITRIAN1        =   6842,
    GOSSIP_TEXTID_DEMITRIAN2        =   6843,
    GOSSIP_TEXTID_DEMITRIAN3        =   6844,
    GOSSIP_TEXTID_DEMITRIAN4        =   6867,
    GOSSIP_TEXTID_DEMITRIAN5        =   6868,
    GOSSIP_TEXTID_DEMITRIAN6        =   6869,
    GOSSIP_TEXTID_DEMITRIAN7        =   6870
};

bool GossipHello_npc_highlord_demitrian(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_EXAMINE_THE_VESSEL) == QUEST_STATUS_NONE &&
        (pPlayer->HasItemCount(ITEM_BINDINGS_WINDSEEKER_LEFT,1,false) || pPlayer->HasItemCount(ITEM_BINDINGS_WINDSEEKER_RIGHT,1,false)))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_highlord_demitrian(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN1, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN5, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DEMITRIAN7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN6, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_DEMITRIAN7, pCreature->GetObjectGuid());

            ItemPosCountVec dest;
            uint8 msg = pPlayer->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, ITEM_VESSEL_OF_REBIRTH, 1);
            if (msg == EQUIP_ERR_OK)
                pPlayer->StoreNewItem(dest, ITEM_VESSEL_OF_REBIRTH, true);
            break;
    }
    return true;
}

/*###
## npcs_rutgar_and_frankal
###*/

//gossip item text best guess
#define GOSSIP_ITEM_SEEK1 "I seek information about Natalia"

#define GOSSIP_ITEM_RUTGAR2 "That sounds dangerous!"
#define GOSSIP_ITEM_RUTGAR3 "What did you do?"
#define GOSSIP_ITEM_RUTGAR4 "Who?"
#define GOSSIP_ITEM_RUTGAR5 "Women do that. What did she demand?"
#define GOSSIP_ITEM_RUTGAR6 "What do you mean?"
#define GOSSIP_ITEM_RUTGAR7 "What happened next?"

#define GOSSIP_ITEM_FRANKAL11 "Yes, please continue"
#define GOSSIP_ITEM_FRANKAL12 "What language?"
#define GOSSIP_ITEM_FRANKAL13 "The Priestess attacked you?!"
#define GOSSIP_ITEM_FRANKAL14 "I should ask the monkey about this"
#define GOSSIP_ITEM_FRANKAL15 "Then what..."

enum
{
    QUEST_DEAREST_NATALIA       =   8304,
    NPC_RUTGAR                  =   15170,
    NPC_FRANKAL                 =   15171,
    TRIGGER_RUTGAR              =   15222,
    TRIGGER_FRANKAL             =   15221,
    GOSSIP_TEXTID_RF            =   7754,
    GOSSIP_TEXTID_RUTGAR1       =   7755,
    GOSSIP_TEXTID_RUTGAR2       =   7756,
    GOSSIP_TEXTID_RUTGAR3       =   7757,
    GOSSIP_TEXTID_RUTGAR4       =   7758,
    GOSSIP_TEXTID_RUTGAR5       =   7759,
    GOSSIP_TEXTID_RUTGAR6       =   7760,
    GOSSIP_TEXTID_RUTGAR7       =   7761,
    GOSSIP_TEXTID_FRANKAL1      =   7762,
    GOSSIP_TEXTID_FRANKAL2      =   7763,
    GOSSIP_TEXTID_FRANKAL3      =   7764,
    GOSSIP_TEXTID_FRANKAL4      =   7765,
    GOSSIP_TEXTID_FRANKAL5      =   7766,
    GOSSIP_TEXTID_FRANKAL6      =   7767
};

bool GossipHello_npcs_rutgar_and_frankal(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
        pCreature->GetEntry() == NPC_RUTGAR &&
        !pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    if (pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
        pCreature->GetEntry() == NPC_FRANKAL &&
        pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+9);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RF, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npcs_rutgar_and_frankal(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR1, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR5, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_RUTGAR7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR6, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RUTGAR7, pCreature->GetObjectGuid());
            //'kill' our trigger to update quest status
            pPlayer->KilledMonsterCredit(TRIGGER_RUTGAR, pCreature->GetObjectGuid());
            break;

        case GOSSIP_ACTION_INFO_DEF + 9:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL11, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL1, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL12, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 11:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL13, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 12:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL14, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 13:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_FRANKAL15, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL5, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF + 14:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_FRANKAL6, pCreature->GetObjectGuid());
            //'kill' our trigger to update quest status
            pPlayer->KilledMonsterCredit(TRIGGER_FRANKAL, pCreature->GetObjectGuid());
            break;
    }
    return true;
}

/*###
## npc_anachronos_the_ancient
###*/

enum
{
    // Dragons
    NPC_MERITHRA_OF_THE_DREAM           = 15378,
    NPC_CAELESTRASZ                     = 15379,
    NPC_ARYGOS                          = 15380,
    NPC_ANACHRONOS_THE_ANCIENT          = 15381,
    NPC_ANACHRONOS_QUEST_TRIGGER        = 15454,            // marks some movement for the dragons

    // Elfs
    NPC_FANDRAL_STAGHELM                = 15382,
    NPC_KALDOREI_INFANTRY               = 15423,

    // Qiraji warriors
    NPC_QIRAJI_WASP                     = 15414,
    NPC_QIRAJI_DRONE                    = 15421,
    NPC_QIRAJI_TANK                     = 15422,
    NPC_ANUBISATH_CONQUEROR             = 15424,

    QUEST_A_PAWN_ON_THE_ETERNAL_BOARD   = 8519,

    // Yells -> in chronological order
    SAY_ANACHRONOS_INTRO_1              = -1000753,
    SAY_FANDRAL_INTRO_2                 = -1000754,
    SAY_MERITHRA_INTRO_3                = -1000755,
    EMOTE_ARYGOS_NOD                    = -1000756,
    SAY_CAELESTRASZ_INTRO_4             = -1000757,
    EMOTE_MERITHRA_GLANCE               = -1000758,
    SAY_MERITHRA_INTRO_5                = -1000759,

    SAY_MERITHRA_ATTACK_1               = -1000760,
    SAY_ARYGOS_ATTACK_2                 = -1000761,
    SAY_ARYGOS_ATTACK_3                 = -1000762,
    SAY_CAELESTRASZ_ATTACK_4            = -1000763,
    SAY_CAELESTRASZ_ATTACK_5            = -1000764,

    SAY_ANACHRONOS_SEAL_1               = -1000765,
    SAY_FANDRAL_SEAL_2                  = -1000766,
    SAY_ANACHRONOS_SEAL_3               = -1000767,
    SAY_ANACHRONOS_SEAL_4               = -1000768,
    SAY_ANACHRONOS_SEAL_5               = -1000769,
    SAY_FANDRAL_SEAL_6                  = -1000770,

    EMOTE_FANDRAL_EXHAUSTED             = -1000771,
    SAY_ANACHRONOS_EPILOGUE_1           = -1000772,
    SAY_ANACHRONOS_EPILOGUE_2           = -1000773,
    SAY_ANACHRONOS_EPILOGUE_3           = -1000774,
    EMOTE_ANACHRONOS_SCEPTER            = -1000775,
    SAY_FANDRAL_EPILOGUE_4              = -1000776,
    SAY_FANDRAL_EPILOGUE_5              = -1000777,
    EMOTE_FANDRAL_SHATTER               = -1000778,
    SAY_ANACHRONOS_EPILOGUE_6           = -1000779,
    SAY_FANDRAL_EPILOGUE_7              = -1000780,
    EMOTE_ANACHRONOS_DISPPOINTED        = -1000781,
    EMOTE_ANACHRONOS_PICKUP             = -1000782,
    SAY_ANACHRONOS_EPILOGUE_8           = -1000783,

    // The transform spell for Anachronos was removed from DBC
    DISPLAY_ID_BRONZE_DRAGON            = 15500,

    // Spells
    SPELL_GREEN_DRAGON_TRANSFORM        = 25105,
    SPELL_RED_DRAGON_TRANSFORM          = 25106,
    SPELL_BLUE_DRAGON_TRANSFORM         = 25107,
    //SPELL_BRONZE_DRAGON_TRANSFORM       = 25108,          // Spell was removed - exists only before 2.0.1

    SPELL_MERITHRA_WAKE                 = 25145,            // should trigger 25172 on targets
    SPELL_ARYGOS_VENGEANCE              = 25149,
    SPELL_CAELESTRASZ_MOLTEN_RAIN       = 25150,

    SPELL_TIME_STOP                     = 25158,            // Anachronos stops the battle - should trigger 25171
    SPELL_GLYPH_OF_WARDING              = 25166,            // Sends event 9427 - should activate Go 176148
    SPELL_PRISMATIC_BARRIER             = 25159,            // Sends event 9425 - should activate Go 176146
    SPELL_CALL_ANCIENTS                 = 25167,            // Sends event 9426 - should activate Go 176147
    SPELL_SHATTER_HAMMER                = 25182,            // Breakes the scepter - needs DB coords

    POINT_ID_DRAGON_ATTACK              = 0,
    POINT_ID_EXIT                       = 1,
    POINT_ID_GATE                       = 2,
    POINT_ID_SCEPTER                    = 3,
    POINT_ID_EPILOGUE                   = 4,

    MAX_DRAGONS                         = 4,
    MAX_CONQUERORS                      = 3,
    MAX_QIRAJI                          = 6,
    MAX_KALDOREI                        = 20,
};

struct EventLocations
{
    float m_fX, m_fY, m_fZ, m_fO;
    uint32 m_uiEntry;
};

static EventLocations aEternalBoardNPCs[MAX_DRAGONS] =
{
    {-8029.301f, 1534.612f, 2.609f, 3.121f, NPC_FANDRAL_STAGHELM},
    {-8034.227f, 1536.580f, 2.609f, 6.161f, NPC_ARYGOS},
    {-8031.935f, 1532.658f, 2.609f, 1.012f, NPC_CAELESTRASZ},
    {-8034.106f, 1534.224f, 2.609f, 0.290f, NPC_MERITHRA_OF_THE_DREAM},
};

static EventLocations aQirajiWarriors[MAX_CONQUERORS] =
{
    {-8092.12f, 1508.32f, 2.94f},
    {-8096.54f, 1525.84f, 2.83f},               // Also used as an anchor point for the rest of the summons
    {-8097.81f, 1541.74f, 2.88f},
};

static EventLocations aEternalBoardMovement[] =
{
    {-8159.951f, 1525.241f, 74.994f},           // Flight position for dragons
    {-8107.867f, 1526.102f, 2.645f},            // Anachronos gate location
    {-8103.861f, 1525.923f, 2.677f},            // Fandral gate location
    {-8110.313f, 1522.049f, 2.618f},            // Shattered scepter
    {-8100.921f, 1527.740f, 2.871f},            // Fandral epilogue location
    {-8115.270f, 1515.926f, 3.305f},            // Anachronos gather broken scepter 1
    {-8116.879f, 1530.615f, 3.762f},            // Anachronos gather broken scepter 2
    {-7997.790f, 1548.664f, 3.738f},            // Fandral exit location
    {-8061.933f, 1496.196f, 2.556f},            // Anachronos launch location
    {-8008.705f, 1446.063f, 44.104f},           // Anachronos flyght location
};

struct MANGOS_DLL_DECL npc_anachronos_the_ancientAI : public ScriptedAI
{
    npc_anachronos_the_ancientAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiEventTimer;

    uint8 m_uiEventStage;

    ObjectGuid m_uiFandralGUID;
    ObjectGuid m_uiMerithraGUID;
    ObjectGuid m_uiCaelestraszGUID;
    ObjectGuid m_uiArygosGUID;
    ObjectGuid m_uiPlayerGUID;
    ObjectGuid m_uiTriggerGUID;

    GUIDList m_lQirajiWarriorsList;

    void Reset()
    {
        // We summon the rest of the dragons on timer
        m_uiEventTimer  = 100;
        m_uiEventStage  = 0;

        m_uiFandralGUID.Clear();
        m_uiMerithraGUID.Clear();
        m_uiCaelestraszGUID.Clear();
        m_uiArygosGUID.Clear();
        m_uiPlayerGUID.Clear();
        m_uiTriggerGUID.Clear();

        m_creature->SetRespawnDelay(DAY);
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        // Set the current quest owner
        if (!m_uiPlayerGUID)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER && pWho->IsWithinDistInMap(m_creature, 10.0f))
                m_uiPlayerGUID = pWho->GetObjectGuid();
        }
    }

    void DoSummonDragons()
    {
        for (uint8 i = 0; i < MAX_DRAGONS; ++i)
            m_creature->SummonCreature(aEternalBoardNPCs[i].m_uiEntry, aEternalBoardNPCs[i].m_fX, aEternalBoardNPCs[i].m_fY, aEternalBoardNPCs[i].m_fZ, aEternalBoardNPCs[i].m_fO, TEMPSUMMON_CORPSE_DESPAWN, 0);

        // Also summon the 3 anubisath conquerors
        for (uint8 i = 0; i < MAX_CONQUERORS; ++i)
            m_creature->SummonCreature(NPC_ANUBISATH_CONQUEROR, aQirajiWarriors[i].m_fX, aQirajiWarriors[i].m_fY, aQirajiWarriors[i].m_fZ, 0, TEMPSUMMON_CORPSE_DESPAWN, 0);
    }

    void DoSummonWarriors()
    {
        float fX, fY, fZ;
        // Summon kaldorei warriors
        for(uint8 i = 0; i < MAX_KALDOREI; ++i)
        {
            m_creature->GetRandomPoint(aQirajiWarriors[1].m_fX, aQirajiWarriors[1].m_fY, aQirajiWarriors[1].m_fZ, 20.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_KALDOREI_INFANTRY, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
        }

        // Summon Qiraji warriors
        for(uint8 i = 0; i < MAX_QIRAJI; ++i)
        {
            m_creature->GetRandomPoint(aQirajiWarriors[1].m_fX, aQirajiWarriors[1].m_fY, aQirajiWarriors[1].m_fZ, 20.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_QIRAJI_WASP, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);

            m_creature->GetRandomPoint(aQirajiWarriors[1].m_fX, aQirajiWarriors[1].m_fY, aQirajiWarriors[1].m_fZ, 20.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_QIRAJI_DRONE, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);

            m_creature->GetRandomPoint(aQirajiWarriors[1].m_fX, aQirajiWarriors[1].m_fY, aQirajiWarriors[1].m_fZ, 20.0f, fX, fY, fZ);
            m_creature->SummonCreature(NPC_QIRAJI_TANK, fX, fY, fZ, 0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0);
        }
    }

    void DoUnsummonArmy()
    {
        for (GUIDList::const_iterator itr = m_lQirajiWarriorsList.begin(); itr != m_lQirajiWarriorsList.end(); ++itr)
        {
            if (Creature* pTemp = m_creature->GetMap()->GetCreature(*itr))
                pTemp->ForcedDespawn();
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        // Also remove npc flags where needed
        switch(pSummoned->GetEntry())
        {
            case NPC_FANDRAL_STAGHELM:
                m_uiFandralGUID = pSummoned->GetObjectGuid();
                break;
            case NPC_MERITHRA_OF_THE_DREAM:
                m_uiMerithraGUID = pSummoned->GetObjectGuid();
                pSummoned->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                break;
            case NPC_CAELESTRASZ:
                m_uiCaelestraszGUID = pSummoned->GetObjectGuid();
                pSummoned->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                break;
            case NPC_ARYGOS:
                m_uiArygosGUID = pSummoned->GetObjectGuid();
                pSummoned->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
                break;
            case NPC_ANUBISATH_CONQUEROR:
            case NPC_QIRAJI_WASP:
            case NPC_QIRAJI_DRONE:
            case NPC_QIRAJI_TANK:
                // ToDo: set faction and flags in DB
                pSummoned->setFaction(16);
                pSummoned->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_lQirajiWarriorsList.push_back(pSummoned->GetObjectGuid());
                break;
            case NPC_KALDOREI_INFANTRY:
                pSummoned->setFaction(1608);
                m_lQirajiWarriorsList.push_back(pSummoned->GetObjectGuid());
                break;
        }

        pSummoned->SetRespawnDelay(DAY);
    }

    void MovementInform(uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        switch(uiPointId)
        {
            case POINT_ID_GATE:
                // Cast time stop when he reaches the gate
                DoCastSpellIfCan(m_creature, SPELL_TIME_STOP);
                m_uiEventTimer = 7000;
                break;
            case POINT_ID_SCEPTER:
                // Pickup the pieces
                if (m_uiEventStage == 46)
                {
                    DoScriptText(EMOTE_ANACHRONOS_PICKUP, m_creature);
                    m_uiEventTimer = 2000;
                }
                else if (m_uiEventStage == 47)
                {
                    DoScriptText(SAY_ANACHRONOS_EPILOGUE_8, m_creature);
                    m_uiEventTimer = 4000;
                }
                m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case POINT_ID_EXIT:
                // Spell was removed, manually change the display
                //DoCastSpellIfCan(m_creature, SPELL_BRONZE_DRAGON_TRANSFORM);
                m_creature->SetDisplayId(DISPLAY_ID_BRONZE_DRAGON);
                m_uiEventTimer = 4000;
                break;
        }
    }

    void SummonedMovementInform(Creature* pSummoned, uint32 uiType, uint32 uiPointId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;

        if (pSummoned->GetEntry() == NPC_FANDRAL_STAGHELM)
        {
            switch(uiPointId)
            {
                case POINT_ID_EPILOGUE:
                    DoScriptText(SAY_FANDRAL_EPILOGUE_7, pSummoned);
                    pSummoned->SetFacingToObject(m_creature);
                    DoUnsummonArmy();
                    m_uiEventTimer = 8000;
                    break;
                case POINT_ID_SCEPTER:
                    pSummoned->GetMotionMaster()->MovePoint(POINT_ID_EPILOGUE, aEternalBoardMovement[4].m_fX, aEternalBoardMovement[4].m_fY, aEternalBoardMovement[4].m_fZ);
                    break;
                case POINT_ID_EXIT:
                    pSummoned->ForcedDespawn();
                    break;
            }
        }
        else if (uiPointId == POINT_ID_DRAGON_ATTACK)
        {
            switch(pSummoned->GetEntry())
            {
                case NPC_MERITHRA_OF_THE_DREAM:
                    m_uiEventTimer = 5000;
                    break;
                case NPC_CAELESTRASZ:
                    m_uiEventTimer = 3000;
                    break;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_uiEventTimer)
        {
            if (m_uiEventTimer <= uiDiff)
            {
                switch(m_uiEventStage)
                {
                    case 0:
                        // Summon the other dragons
                        DoSummonDragons();
                        m_uiEventTimer = 2000;
                        break;
                    case 1:
                        DoScriptText(SAY_ANACHRONOS_INTRO_1, m_creature);
                        m_uiEventTimer = 3000;
                        break;
                    case 2:
                        // Summon warriors
                        DoSummonWarriors();
                        m_creature->HandleEmote(EMOTE_ONESHOT_SHOUT);
                        m_uiEventTimer = 3000;
                        break;
                    case 3:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                        {
                            pFandral->SetFacingToObject(m_creature);
                            DoScriptText(SAY_FANDRAL_INTRO_2, pFandral);
                        }
                        m_uiEventTimer = 6000;
                        break;
                    case 4:
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                        {
                            if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                                pFandral->SetFacingToObject(pMerithra);

                            DoScriptText(EMOTE_MERITHRA_GLANCE, pMerithra);
                        }
                        m_uiEventTimer = 2000;
                        break;
                    case 5:
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                            DoScriptText(SAY_MERITHRA_INTRO_3, pMerithra);
                        m_uiEventTimer = 3000;
                        break;
                    case 6:
                        if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                            DoScriptText(EMOTE_ARYGOS_NOD, pArygos);
                        m_uiEventTimer = 4000;
                        break;
                    case 7:
                        if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                            DoScriptText(SAY_CAELESTRASZ_INTRO_4, pCaelestrasz);
                        m_uiEventTimer = 9000;
                        break;
                    case 8:
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                            DoScriptText(SAY_MERITHRA_INTRO_5, pMerithra);
                        m_uiEventTimer = 5000;
                        break;
                    case 9:
                        // Send Merithra to attack - continue when point is reached
                        if (Creature* pTrigger = GetClosestCreatureWithEntry(m_creature, NPC_ANACHRONOS_QUEST_TRIGGER, 35.0f))
                        {
                            m_uiTriggerGUID = pTrigger->GetObjectGuid();
                            if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                                pMerithra->GetMotionMaster()->MovePoint(POINT_ID_DRAGON_ATTACK, pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ());
                        }
                        m_uiEventTimer = 0;
                        break;
                    case 10:
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                            DoScriptText(SAY_MERITHRA_ATTACK_1, pMerithra);
                        m_uiEventTimer = 1000;
                        break;
                    case 11:
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                            pMerithra->CastSpell(pMerithra, SPELL_GREEN_DRAGON_TRANSFORM, false);
                        m_uiEventTimer = 6000;
                        break;
                    case 12:
                        if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                            DoScriptText(SAY_ARYGOS_ATTACK_2, pArygos);
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                            pMerithra->CastSpell(pMerithra, SPELL_MERITHRA_WAKE, false);
                        m_uiEventTimer = 5000;
                        break;
                    case 13:
                        // Send Arygos in combat
                        if (Creature* pTrigger = m_creature->GetMap()->GetCreature(m_uiTriggerGUID))
                        {
                            if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                                pArygos->GetMotionMaster()->MovePoint(POINT_ID_DRAGON_ATTACK, pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ());
                        }
                        m_uiEventTimer = 1000;
                        break;
                    case 14:
                        // Send Merithra on flight
                        if (Creature* pMerithra = m_creature->GetMap()->GetCreature(m_uiMerithraGUID))
                        {
                            pMerithra->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND/* | UNIT_BYTE1_FLAG_UNK_2*/);
                            pMerithra->AddSplineFlag(SPLINEFLAG_FLYING);
                            pMerithra->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[0].m_fX, aEternalBoardMovement[0].m_fY, aEternalBoardMovement[0].m_fZ);
                            pMerithra->ForcedDespawn(10000);
                        }
                        m_uiEventTimer = 4000;
                        break;
                    case 15:
                        if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                            DoScriptText(SAY_ARYGOS_ATTACK_3, pArygos);
                        m_uiEventTimer = 4000;
                        break;
                    case 16:
                        if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                            pArygos->CastSpell(pArygos, SPELL_BLUE_DRAGON_TRANSFORM, false);
                        m_uiEventTimer = 5000;
                        break;
                    case 17:
                        if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                            pArygos->CastSpell(pArygos, SPELL_ARYGOS_VENGEANCE, false);
                        m_uiEventTimer = 7000;
                        break;
                    case 18:
                        // Send Arygos on flight
                        if (Creature* pArygos = m_creature->GetMap()->GetCreature(m_uiArygosGUID))
                        {
                            pArygos->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND/* | UNIT_BYTE1_FLAG_UNK_2*/);
                            pArygos->AddSplineFlag(SPLINEFLAG_FLYING);
                            pArygos->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[0].m_fX, aEternalBoardMovement[0].m_fY, aEternalBoardMovement[0].m_fZ);
                            pArygos->ForcedDespawn(10000);
                        }
                        m_uiEventTimer = 1000;
                        break;
                    case 19:
                        if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                            DoScriptText(SAY_CAELESTRASZ_ATTACK_4, pCaelestrasz);
                        m_uiEventTimer = 5000;
                        break;
                    case 20:
                        // Send Caelastrasz in combat
                        if (Creature* pTrigger = m_creature->GetMap()->GetCreature(m_uiTriggerGUID))
                        {
                            if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                                pCaelestrasz->GetMotionMaster()->MovePoint(POINT_ID_DRAGON_ATTACK, pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ());
                        }
                        m_uiEventTimer = 0;
                        break;
                    case 21:
                        if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                            DoScriptText(SAY_CAELESTRASZ_ATTACK_5, pCaelestrasz);
                        m_uiEventTimer = 5000;
                        break;
                    case 22:
                        if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                            pCaelestrasz->CastSpell(pCaelestrasz, SPELL_RED_DRAGON_TRANSFORM, false);
                        m_uiEventTimer = 4000;
                        break;
                    case 23:
                        if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                            pCaelestrasz->CastSpell(pCaelestrasz, SPELL_CAELESTRASZ_MOLTEN_RAIN, false);
                        m_uiEventTimer = 6000;
                        break;
                    case 24:
                        // Send Caelestrasz on flight
                        if (Creature* pCaelestrasz = m_creature->GetMap()->GetCreature(m_uiCaelestraszGUID))
                        {
                            pCaelestrasz->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND/* | UNIT_BYTE1_FLAG_UNK_2*/);
                            pCaelestrasz->AddSplineFlag(SPLINEFLAG_FLYING);
                            pCaelestrasz->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[0].m_fX, aEternalBoardMovement[0].m_fY, aEternalBoardMovement[0].m_fZ);
                            pCaelestrasz->ForcedDespawn(10000);
                        }
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                            m_creature->SetFacingToObject(pFandral);
                        DoScriptText(SAY_ANACHRONOS_SEAL_1, m_creature);
                        m_uiEventTimer = 5000;
                        break;
                    case 25:
                         if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                         {
                            pFandral->SetFacingToObject(m_creature);
                            DoScriptText(SAY_FANDRAL_SEAL_2, pFandral);
                         }
                        m_uiEventTimer = 3000;
                        break;
                    case 26:
                        DoScriptText(SAY_ANACHRONOS_SEAL_3, m_creature);
                        m_uiEventTimer = 1000;
                        break;
                    case 27:
                        // Send Anachronos and Fandral to the gate
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_GATE, aEternalBoardMovement[1].m_fX, aEternalBoardMovement[1].m_fY, aEternalBoardMovement[1].m_fZ);
                        m_uiEventTimer = 1000;
                        break;
                    case 28:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                            pFandral->GetMotionMaster()->MovePoint(POINT_ID_GATE, aEternalBoardMovement[2].m_fX, aEternalBoardMovement[2].m_fY, aEternalBoardMovement[2].m_fZ);
                        m_uiEventTimer = 0;
                        break;
                    case 29:
                        DoCastSpellIfCan(m_creature, SPELL_PRISMATIC_BARRIER);
                        m_uiEventTimer = 15000;
                        break;
                    case 30:
                        DoCastSpellIfCan(m_creature, SPELL_GLYPH_OF_WARDING);
                        m_uiEventTimer = 4000;
                        break;
                    case 31:
                        DoScriptText(SAY_ANACHRONOS_SEAL_5, m_creature);
                        m_uiEventTimer = 3000;
                        break;
                    case 32:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                        {
                            pFandral->CastSpell(pFandral, SPELL_CALL_ANCIENTS, false);
                            DoScriptText(SAY_FANDRAL_SEAL_6, pFandral);
                        }
                        m_uiEventTimer = 9000;
                        break;
                    case 33:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                        {
                            DoScriptText(EMOTE_FANDRAL_EXHAUSTED, pFandral);
                            pFandral->SetStandState(UNIT_STAND_STATE_KNEEL);
                            m_creature->SetFacingToObject(pFandral);
                        }
                        m_uiEventTimer = 1000;
                        break;
                    case 34:
                        DoScriptText(SAY_ANACHRONOS_EPILOGUE_1, m_creature);
                        m_uiEventTimer = 6000;
                        break;
                    case 35:
                        DoScriptText(SAY_ANACHRONOS_EPILOGUE_2, m_creature);
                        m_uiEventTimer = 5000;
                        break;
                    case 36:
                        DoScriptText(SAY_ANACHRONOS_EPILOGUE_3, m_creature);
                        m_uiEventTimer = 15000;
                        break;
                    case 37:
                        // ToDo: Make Fandral equip the scepter
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                            DoScriptText(EMOTE_ANACHRONOS_SCEPTER, m_creature, pFandral);
                        m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                        m_uiEventTimer = 3000;
                        break;
                    case 38:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                        {
                            pFandral->SetStandState(UNIT_STAND_STATE_STAND);
                            DoScriptText(SAY_FANDRAL_EPILOGUE_4, pFandral);
                        }
                        m_uiEventTimer = 3000;
                        break;
                    case 39:
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 4000;
                        break;
                    case 40:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                            DoScriptText(SAY_FANDRAL_EPILOGUE_5, pFandral);
                        m_uiEventTimer = 12000;
                        break;
                    case 41:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                        {
                            pFandral->CastSpell(pFandral, SPELL_SHATTER_HAMMER, false);
                            DoScriptText(EMOTE_FANDRAL_SHATTER, pFandral);
                        }
                        m_uiEventTimer = 3000;
                        break;
                    case 42:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                        {
                            pFandral->AddSplineFlag(SPLINEFLAG_WALKMODE);
                            pFandral->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER, aEternalBoardMovement[3].m_fX, aEternalBoardMovement[3].m_fY, aEternalBoardMovement[3].m_fZ);
                        }
                        DoScriptText(SAY_ANACHRONOS_EPILOGUE_6, m_creature);
                        m_uiEventTimer = 0;
                        break;
                    case 43:
                        if (Creature* pFandral = m_creature->GetMap()->GetCreature(m_uiFandralGUID))
                            pFandral->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[7].m_fX, aEternalBoardMovement[7].m_fY, aEternalBoardMovement[7].m_fZ);
                        m_uiEventTimer = 4000;
                        break;
                    case 44:
                        DoScriptText(EMOTE_ANACHRONOS_DISPPOINTED, m_creature);
                        m_uiEventTimer = 1000;
                        break;
                    case 45:
                        m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER, aEternalBoardMovement[5].m_fX, aEternalBoardMovement[5].m_fY, aEternalBoardMovement[5].m_fZ);
                        m_uiEventTimer = 0;
                        break;
                    case 46:
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_SCEPTER, aEternalBoardMovement[6].m_fX, aEternalBoardMovement[6].m_fY, aEternalBoardMovement[6].m_fZ);
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 0;
                        break;
                    case 47:
                        // Complete quest and despawn gate
                        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                            pPlayer->AreaExploredOrEventHappens(QUEST_A_PAWN_ON_THE_ETERNAL_BOARD);
                        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                        m_uiEventTimer = 4000;
                        break;
                    case 48:
                        // Move to exit
                        m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        m_creature->GetMotionMaster()->MovePoint(POINT_ID_EXIT, aEternalBoardMovement[8].m_fX, aEternalBoardMovement[8].m_fY, aEternalBoardMovement[8].m_fZ);
                        m_uiEventTimer = 0;
                        break;
                    case 49:
                        m_creature->GetMotionMaster()->MovePoint(0, aEternalBoardMovement[9].m_fX, aEternalBoardMovement[9].m_fY, aEternalBoardMovement[9].m_fZ);
                        m_creature->SetByteValue(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND/* | UNIT_BYTE1_FLAG_UNK_2*/);
                        m_creature->AddSplineFlag(SPLINEFLAG_FLYING);
                        m_creature->ForcedDespawn(15000);
                        m_uiEventTimer = 0;
                        break;
                }
                ++m_uiEventStage;
            }
            else
                m_uiEventTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_anachronos_the_ancient(Creature* pCreature)
{
    return new npc_anachronos_the_ancientAI(pCreature);
}

bool QuestAcceptGO_crystalline_tear(Player* pPlayer, GameObject* pGo, const Quest* pQuest)
{
    // Summon the controller dragon at GO position (orientation is wrong - hardcoded)
    if (pQuest->GetQuestId() == QUEST_A_PAWN_ON_THE_ETERNAL_BOARD)
        pPlayer->SummonCreature(NPC_ANACHRONOS_THE_ANCIENT, pGo->GetPositionX(), pGo->GetPositionY(), pGo->GetPositionZ(), 3.75f, TEMPSUMMON_CORPSE_DESPAWN, 0);

    return true;
}

void AddSC_silithus()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_highlord_demitrian";
    pNewScript->pGossipHello = &GossipHello_npc_highlord_demitrian;
    pNewScript->pGossipSelect = &GossipSelect_npc_highlord_demitrian;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npcs_rutgar_and_frankal";
    pNewScript->pGossipHello = &GossipHello_npcs_rutgar_and_frankal;
    pNewScript->pGossipSelect = &GossipSelect_npcs_rutgar_and_frankal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_anachronos_the_ancient";
    pNewScript->GetAI = &GetAI_npc_anachronos_the_ancient;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_crystalline_tear";
    pNewScript->pQuestAcceptGO = &QuestAcceptGO_crystalline_tear;
    pNewScript->RegisterSelf();
}
