/*
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2010-2011 ScriptDev0 <http://github.com/scriptdev/scriptdevzero>
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
SDComment: Quest support: 7785, 8304.
SDCategory: Silithus
EndScriptData */

/* ContentData
npc_highlord_demitrian
npcs_rutgar_and_frankal
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
    if(pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if(pPlayer->GetQuestStatus(QUEST_EXAMINE_THE_VESSEL) == QUEST_STATUS_NONE &&
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
            if(msg == EQUIP_ERR_OK)
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
    if(pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if(pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
            pCreature->GetEntry() == NPC_RUTGAR &&
            !pPlayer->GetReqKillOrCastCurrentCount(QUEST_DEAREST_NATALIA, TRIGGER_RUTGAR))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_SEEK1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    if(pPlayer->GetQuestStatus(QUEST_DEAREST_NATALIA) == QUEST_STATUS_INCOMPLETE &&
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

enum
{
    // 4 dragons and Fandral Staghelm
    NPC_ANACHRONOS                  =   15381,
    NPC_STAGHELM                    =   15382,
    NPC_MERITHRA                    =   15378,
    NPC_CAELESTRASZ                 =   15379,
    NPC_ARYGOS                      =   15380,

    // Qiraj creatures
    NPC_ANUBISATH                   =   15424,
    NPC_TANK                        =   15422,
    NPC_DRONE                       =   15421,
    NPC_WASP                        =   15314,

    // Kaldorei infantry
    NPC_INFANTRY                    =   15323,

    // Ahn'Qiraj shadows of the past event
    ANACHRONOS_SAY_1                =   -1900000,
    STAGHELM_SAY_1                  =   -1900001,
    MERITHRA_SAY_1                  =   -1900002,
    ARYGOS_SAY_1                    =   -1900003,
    CAELESTRASZ_SAY_1               =   -1900004,
    MERITHRA_SAY_2                  =   -1900005,
    MERITHRA_SAY_3                  =   -1900006,
    MERITHRA_SAY_4                  =   -1900007,
    ARYGOS_SAY_2                    =   -1900008,
    ARYGOS_SAY_3                    =   -1900009,
    CAELESTRASZ_SAY_2               =   -1900010,
    CAELESTRASZ_SAY_3               =   -1900011,
    STAGHELM_SAY_2                  =   -1900012,
    ANACHRONOS_SAY_2                =   -1900013,
    ANACHRONOS_SAY_3                =   -1900014,
    ANACHRONOS_SAY_4                =   -1900015,
    ANACHRONOS_SAY_5                =   -1900016,
    STAGHELM_SAY_3                  =   -1900017,
    STAGHELM_SAY_4                  =   -1900018,
    ANACHRONOS_SAY_6                =   -1900019,
    ANACHRONOS_SAY_7                =   -1900020,
    ANACHRONOS_SAY_8                =   -1900021,
    ANACHRONOS_SAY_9                =   -1900022,
    STAGHELM_SAY_5                  =   -1900023,
    STAGHELM_SAY_6                  =   -1900024,
    STAGHELM_SAY_7                  =   -1900025,
    ANACHRONOS_SAY_10               =   -1900026,
    STAGHELM_SAY_8                  =   -1900027,
    ANACHRONOS_SAY_11               =   -1900028,
    ANACHRONOS_SAY_12               =   -1900029,
    ANACHRONOS_SAY_13               =   -1900030
};

struct MANGOS_DLL_DECL Crystalline_Tear_eventAI : public ScriptedAI
{
    Crystalline_Tear_eventAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }
    uint32 summon;
    uint32 SpeachTimer;
    uint32 SpeachNum;

    uint64 AnachronosGUID;
    uint64 StaghelmGUID;
    uint64 MerithraGUID;
    uint64 CaelestraszGUID;
    uint64 ArygosGUID;
    void Reset()
    {
        summon = 1;
        AnachronosGUID = 0;
        StaghelmGUID = 0;
        MerithraGUID = 0;
        CaelestraszGUID = 0;
        ArygosGUID = 0;

        SpeachTimer = 0;
        SpeachNum = 0;


    }

    void Aggro(Unit* pWho)
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if(summon == 1)
        {
            // Summons the 4 dragons and Staghelm
            Creature* Anachronos = m_creature->SummonCreature(NPC_ANACHRONOS,-8028.350098f, 1538.756714f, 2.609658f, 3.149353f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 339000);
            Creature* Staghelm = m_creature->SummonCreature(NPC_STAGHELM,-8028.728516f, 1535.176147f, 2.609771f, 2.932328f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 291000);
            Creature* Merithra = m_creature->SummonCreature(NPC_MERITHRA,-8032.645996f, 1534.544189f, 2.609757f, 0.138675f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 84000);
            Creature* Caelestrasz = m_creature->SummonCreature(NPC_CAELESTRASZ,-8032.501953f, 1532.901123f, 2.609757f, 0.181872f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 144000);
            Creature* Arygos = m_creature->SummonCreature(NPC_ARYGOS,-8032.587402f, 1537.418091f, 2.609757f, 6.123408f,TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 114000);
            AnachronosGUID = Anachronos->GetGUID();
            StaghelmGUID = Staghelm->GetGUID();
            MerithraGUID = Merithra->GetGUID();
            CaelestraszGUID = Caelestrasz->GetGUID();
            ArygosGUID = Arygos->GetGUID();
            summon = 0;


        }
        else summon -= diff;

        if(SpeachTimer < diff)
        {
            Unit* AnachronosA = m_creature->GetMap()->GetUnit(AnachronosGUID);
            Unit* StaghelmA = m_creature->GetMap()->GetUnit(StaghelmGUID);
            Unit* MerithraA = m_creature->GetMap()->GetUnit(MerithraGUID);
            Unit* CaelestraszA = m_creature->GetMap()->GetUnit(CaelestraszGUID);
            Unit* ArygosA = m_creature->GetMap()->GetUnit(ArygosGUID);

            switch(SpeachNum)
            {
                case 0:
                    //8000 = 8sec. This is where the talk starts
                    DoScriptText(ANACHRONOS_SAY_1, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 1:
                    DoScriptText(STAGHELM_SAY_1, StaghelmA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 2:
                    DoScriptText(MERITHRA_SAY_1, MerithraA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 3:
                    DoScriptText(ARYGOS_SAY_1, ArygosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 4:
                    DoScriptText(CAELESTRASZ_SAY_1, CaelestraszA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 5:
                    DoScriptText(MERITHRA_SAY_2, MerithraA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 6:
                    DoScriptText(MERITHRA_SAY_3, MerithraA);
                    SpeachTimer = 6000;
                    ++SpeachNum;
                    break;
                case 7: //Merithra moves to the middle
                    MerithraA->MonsterMove(-8064.169922f, 1534.229980f, 2.692740f, 5000);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 8:
                    DoScriptText(MERITHRA_SAY_4, MerithraA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 9: //Merithra becomes dragon
                    MerithraA->SetDisplayId(15412);
                    MerithraA->CastSpell(MerithraA, 25145, true, 0, 0);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 10: //Merithra despawns
                    DoScriptText(ARYGOS_SAY_2, ArygosA);
                    MerithraA->SendMonsterMove(-8183.842285f, 1525.377075f, 80.0f, SPLINETYPE_NORMAL, SPLINEFLAG_FLYING, 5500);
                    SpeachTimer = 6000;
                    ++SpeachNum;
                    break;
                case 11: //Arygos moves to the middle
                    ArygosA->MonsterMove(-8064.169922f, 1534.229980f, 2.692740f, 5000);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 12:
                    DoScriptText(ARYGOS_SAY_3, ArygosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 13: //Arygos becomes dragon
                    ArygosA->SetDisplayId(15413);
                    ArygosA->CastSpell(ArygosA, 25149, true, 0, 0);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 14: //Arygos despawns
                    DoScriptText(CAELESTRASZ_SAY_2, CaelestraszA);
                    ArygosA->SendMonsterMove(-8183.842285f, 1525.377075f, 80.0f, SPLINETYPE_NORMAL, SPLINEFLAG_FLYING, 5500);
                    SpeachTimer = 6000;
                    ++SpeachNum;
                    break;
                case 15: //Cael moves to the middle
                    CaelestraszA->MonsterMove(-8064.169922f, 1534.229980f, 2.692740f, 5000);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 16:
                    DoScriptText(CAELESTRASZ_SAY_3, CaelestraszA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 17: //Cael becomes dragon
                    CaelestraszA->SetDisplayId(15414);
                    CaelestraszA->CastSpell(CaelestraszA, 25150, true, 0, 0);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 18: //Cael despawns
                    DoScriptText(ANACHRONOS_SAY_2, AnachronosA);
                    CaelestraszA->SendMonsterMove(-8183.842285f, 1525.377075f, 80.0f, SPLINETYPE_NORMAL, SPLINEFLAG_FLYING, 5500);
                    SpeachTimer = 6000;
                    ++SpeachNum;
                    break;
                case 19:
                    DoScriptText(STAGHELM_SAY_2, StaghelmA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 20:
                    DoScriptText(ANACHRONOS_SAY_3, AnachronosA);
                    SpeachTimer = 5000;
                    ++SpeachNum;
                    break;
                case 21: //Staghelm and Anachronos moves to the gate
                    AnachronosA->MonsterMove(-8111.562500f, 1524.341675f, 2.646308f, 8000);
                    StaghelmA->MonsterMove(-8110.092285f, 1524.279541f, 2.624866f, 8000);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 22: //Staghelm and Anachronos closes the gate
                    DoScriptText(ANACHRONOS_SAY_4, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 23:
                    DoScriptText(ANACHRONOS_SAY_5, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 24:
                    DoScriptText(STAGHELM_SAY_3, StaghelmA);
                    StaghelmA->CastSpell(StaghelmA, 25167, true, 0, 0); //Root spell from Staghelm
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 25:
                    DoScriptText(STAGHELM_SAY_4, StaghelmA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 26:
                    DoScriptText(ANACHRONOS_SAY_6, AnachronosA);
                    AnachronosA->MonsterMove(-8111.156738f, 1524.443359f, 2.643003f, 1);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 27:
                    DoScriptText(ANACHRONOS_SAY_7, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 28:
                    DoScriptText(ANACHRONOS_SAY_8, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 29:
                    DoScriptText(ANACHRONOS_SAY_9, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 30:
                    DoScriptText(STAGHELM_SAY_5, StaghelmA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 31:
                    DoScriptText(STAGHELM_SAY_6, StaghelmA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 32:
                    DoScriptText(STAGHELM_SAY_7, StaghelmA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 33:
                    DoScriptText(ANACHRONOS_SAY_10, AnachronosA);
                    StaghelmA->MonsterMove(-8101.749023f, 1526.578735f, 2.790386f, 4000);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 34:
                    StaghelmA->MonsterMove(-8102.176270f, 1526.577393f, 2.778292f, 1);
                    DoScriptText(STAGHELM_SAY_8, StaghelmA);
                    SpeachTimer = 5000;
                    ++SpeachNum;
                    break;
                case 35:
                    StaghelmA->MonsterMove(-8028.728516f, 1535.176147f, 2.609771f, 25000); //Staghelm despawns
                    SpeachTimer = 3000;
                    ++SpeachNum;
                    break;
                case 36:
                    DoScriptText(ANACHRONOS_SAY_11, AnachronosA);
                    AnachronosA->MonsterMove(-8116.770996f, 1520.069092f, 3.570893f, 4000);
                    SpeachTimer = 4000;
                    ++SpeachNum;
                    break;
                case 37:
                    DoScriptText(ANACHRONOS_SAY_12, AnachronosA);
                    SpeachTimer = 8000;
                    ++SpeachNum;
                    break;
                case 38:
                    AnachronosA->MonsterMove(-8118.689941f, 1526.789917f, 4.300494f, 6000);
                    SpeachTimer = 6000;
                    ++SpeachNum;
                    break;
                case 39:
                    AnachronosA->MonsterMove(-8118.495605f, 1526.773315f, 4.248041f, 1000);
                    DoScriptText(ANACHRONOS_SAY_13, AnachronosA);
                    SpeachTimer = 3000;
                    ++SpeachNum;
                    break;
                case 40:
                    AnachronosA->MonsterMove(-8060.369141f, 1479.786377f, 2.610108f, 25000);
                    SpeachTimer = 25000;
                    ++SpeachNum;
                    break;
                case 41: // Anachronos becomes dragon and flies away
                    AnachronosA->SetDisplayId(15500);
                    SpeachTimer = 4000;
                    ++SpeachNum;
                    break;
                case 42:
                    AnachronosA->SendMonsterMove(-7935.592773f, 1431.213135f, 50.0f, SPLINETYPE_NORMAL, SPLINEFLAG_FLYING, 20000); //Anachronos despawns
                    SpeachTimer = SpeachTimer;
                    ++SpeachNum;
                    break;
            }
        }
        else SpeachTimer -= diff;

    }
};
CreatureAI* GetAI_Crystalline_Tear_event(Creature* pCreature)
{
    return new Crystalline_Tear_eventAI(pCreature);
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
    pNewScript->Name = "Crystalline_Tear_event";
    pNewScript->GetAI = &GetAI_Crystalline_Tear_event;
    pNewScript->RegisterSelf();
}
