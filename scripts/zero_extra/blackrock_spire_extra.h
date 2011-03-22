/* Copyright (C) 2006 - 2011 ScriptDev2 <http://www.scriptdev2.com/>
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

#ifndef DEF_BLACKROCK_SPIRE_H
#define DEF_BLACKROCK_SPIRE_H

enum
{
    /* Areatrigger
    1470 Instance Entry
    1628 LBRS, between Spiders and Ogres
    1946 LBRS, ubrs pre-quest giver (1)
    1986 LBRS, ubrs pre-quest giver (2)
    1987 LBRS, ubrs pre-quest giver (3)
    2026 UBRS, stadium event trigger
    2046 UBRS, way to upper
    2066 UBRS, The Beast - Exit (to the dark chamber)
    2067 UBRS, The Beast - Entry
    2068 LBRS, fall out of map
    3726 UBRS, entrance to BWL
    */

    MAX_ENCOUNTER               = 30,

    /* LOWER BLACKROCK SPIRE DATA */

    TYPE_VALTHALAK              = 5,

    NPC_SCARSHIELD_INFILTRATOR  = 10299,

    /* UPPER BLACKROCK SPIRE DATA */

    AREATRIGGER_ENTER_UBRS      = 2046,
    AREATRIGGER_STADIUM         = 2026,

    ITEM_SEAL_OF_ASCENSION      = 12344,
    MAX_ROOMS                   = 7,
    MAX_ALTAR_SLOT              = 3,
    MAX_ROOKERY_WAVES           = 5,

    TYPE_ROOM_EVENT             = 16,
    TYPE_EMBERSEER              = 17,
    TYPE_EMBERSEER_GUARDS       = 18,
    TYPE_EMBERSEER_ALTAR        = 19,
    TYPE_ROOKERY_WAVE           = 20,
    TYPE_ROOKERY_EVENT          = 21,
    TYPE_SOLAKAR_FLAMEWREATH    = 22,
    TYPE_STADIUM_EVENT          = 23,
    TYPE_STADIUM_WAVE           = 24,
    TYPE_GYTH                   = 25,
    TYPE_GYTH_LOOTED            = 26,
    TYPE_REND_BLACKHAND         = 27,

    NPC_PYROGUARD_EMBERSEER     = 9816,
    NPC_BLACKHAND_INCANCERATOR  = 10316,
    NPC_BLACKHAND_DREADWEAVER   = 9817,
    NPC_BLACKHAND_SUMMONER      = 9818,
    NPC_BLACKHAND_VETERAN       = 9819,
    NPC_SOLAKAR_FLAMEWREATH     = 10264,
    NPC_ROOKERY_HATCHER         = 10683,
    NPC_ROOKERY_GUARDIAN        = 10258,
    NPC_LORD_VICTOR_NEFARIUS    = 50001,
    NPC_CHROMATIC_DRAGONSPAWN   = 10447,
    NPC_CHROMATIC_WHELP         = 10442,
    NPC_DRAGON_HANDLER          = 10742,
    NPC_GYTH                    = 10339,
    NPC_REND_BLACKHAND          = 10429,

    GO_ENTER_UBRS_DOOR          = 164725,
    GO_EMBERSEER_ENTRY_DOOR     = 175244,
    GO_EMBERSEER_COMBAT_DOOR    = 175705,
    GO_EMBERSEER_EXIT_DOOR      = 175153,
    GO_EMBERSEER_ALTAR          = 175706,
    GO_ROOKERY_EGG              = 175124,
    GO_STADIUM_ENTRY_DOOR       = 164726,
    GO_STADIUM_COMBAT_DOOR      = 175185,
    GO_STADIUM_EXIT_DOOR        = 175186,

    GO_ROOM_7_RUNE              = 175194,
    GO_ROOM_3_RUNE              = 175195,
    GO_ROOM_6_RUNE              = 175196,
    GO_ROOM_1_RUNE              = 175197,
    GO_ROOM_5_RUNE              = 175198,
    GO_ROOM_2_RUNE              = 175199,
    GO_ROOM_4_RUNE              = 175200,

    GO_EMBERSEER_RUNE_1         = 175266,
    GO_EMBERSEER_RUNE_2         = 175267,
    GO_EMBERSEER_RUNE_3         = 175268,
    GO_EMBERSEER_RUNE_4         = 175269,
    GO_EMBERSEER_RUNE_5         = 175270,
    GO_EMBERSEER_RUNE_6         = 175271,
    GO_EMBERSEER_RUNE_7         = 175272,

    // Texts
    REND_SAY_1                  = -1615003,
    REND_SAY_2                  = -1615004,
    REND_SAY_3                  = -1615005,
    REND_SAY_4                  = -1615006,
    NEFARIUS_SAY_1              = -1615007,
    NEFARIUS_SAY_2              = -1615008,
    NEFARIUS_SAY_3              = -1615009,
    NEFARIUS_SAY_4              = -1615010,
    NEFARIUS_SAY_5              = -1615011,
    NEFARIUS_SAY_6              = -1615012,
    NEFARIUS_SAY_7              = -1615013,
    NEFARIUS_SAY_8              = -1615014,
    NEFARIUS_SAY_9              = -1615015,
    NEFARIUS_SAY_10             = -1615016,
    NEFARIUS_SAY_11             = -1615017
};

class MANGOS_DLL_DECL zero_instance_blackrock_spire : public ScriptedInstance
{
    public:
        zero_instance_blackrock_spire(Map* pMap);
        ~zero_instance_blackrock_spire() {}

        void Initialize();

        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);

        void SetData(uint32 uiType, uint32 uiData);
        void SetData64(uint32 uiType, uint64 uiData);
        uint32 GetData(uint32 uiType);
        uint64 GetData64(uint32 uiType);

        const char* Save() { return strInstData.c_str(); }
        void Load(const char* chrIn);

        void DoSortRoomEventMobs();
        void GetIncanceratorGUIDList(std::list<uint64> &lList) { lList = m_lIncanceratorGUIDList; }
        void GetRookeryEggGUIDList(std::list<uint64> &lList) { lList = m_lRookeryEggGUIDList; }

        void SetEmberseerAltarGuid(uint64 guid, uint8 slot) { t_AltarGuid[slot] = guid; }
        uint64 GetEmberseerAltarGuid(uint8 slot) { return t_AltarGuid[slot]; }

    protected:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string strInstData;

        uint64 m_uiEmberseerGUID;
        uint64 m_uiNefariusGUID;
        uint64 m_uiGythGUID;
        uint64 m_uiInfiltratorGUID;
        uint64 m_uiBlackhandGUID;

        uint64 m_uiEnterUBRSDoorGUID;
        uint64 m_uiEmberseerEntryDoorGUID;
        uint64 m_uiEmberseerCombatDoorGUID;
        uint64 m_uiEmberseerExitDoorGUID;
        uint64 m_uiEmberseerAltarGUID;
        uint64 m_uiStadiumEntryDoorGUID;
        uint64 m_uiStadiumCombatDoorGUID;
        uint64 m_uiStadiumExitDoorGUID;

        uint64 m_auiRoomRuneGUID[MAX_ROOMS];
        uint64 m_auiEmberseerRuneGUID[MAX_ROOMS];

        std::list<uint64> m_alRoomEventMobGUIDSorted[MAX_ROOMS];
        std::list<uint64> m_lRoomEventMobGUIDList;
        std::list<uint64> m_lIncanceratorGUIDList;
        std::list<uint64> m_lRookeryEggGUIDList;

        uint64 t_AltarGuid[MAX_ALTAR_SLOT];
};

#endif
