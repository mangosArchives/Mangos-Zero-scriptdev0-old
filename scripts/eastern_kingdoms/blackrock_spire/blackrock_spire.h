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

#ifndef DEF_BLACKROCK_SPIRE_H
#define DEF_BLACKROCK_SPIRE_H

enum
{
    MAX_ENCOUNTER               = 5,
    MAX_ROOMS                   = 7,

    TYPE_ROOM_EVENT             = 1,
    TYPE_EMBERSEER              = 2,
    TYPE_FLAMEWREATH            = 3,                        // Only summon once per instance
    TYPE_GYTH                   = 4,
    TYPE_VALTHALAK              = 5,                        // Only summon once per instance

    NPC_SCARSHIELD_INFILTRATOR  = 10299,
    NPC_BLACKHAND_SUMMONER      = 9818,
    NPC_BLACKHAND_VETERAN       = 9819,
    NPC_PYROGUARD_EMBERSEER     = 9816,
    NPC_BLACKHAND_INCANCERATOR  = 10316,
    NPC_LORD_VICTOR_NEFARIUS    = 10162,
    NPC_GYTH                    = 10339,
    NPC_DRAKKISATH              = 10363,
    NPC_ELITE_GUARD             = 10814,

    // Doors
    GO_EMBERSEER_IN             = 175244,
    GO_DOORS                    = 175705,
    GO_EMBERSEER_OUT            = 175153,
    GO_GYTH_ENTRY_DOOR          = 164726,
    GO_GYTH_COMBAT_DOOR         = 175185,                   // control in boss_script, because will auto-close after each wave
    GO_GYTH_EXIT_DOOR           = 175186,

    GO_ROOM_7_RUNE              = 175194,
    GO_ROOM_3_RUNE              = 175195,
    GO_ROOM_6_RUNE              = 175196,
    GO_ROOM_1_RUNE              = 175197,
    GO_ROOM_5_RUNE              = 175198,
    GO_ROOM_2_RUNE              = 175199,
    GO_ROOM_4_RUNE              = 175200,

    GO_ROOKERY_EGG              = 175124,

    GO_EMBERSEER_RUNE_1         = 175272,
    GO_EMBERSEER_RUNE_2         = 175271,
    GO_EMBERSEER_RUNE_3         = 175270,
    GO_EMBERSEER_RUNE_4         = 175269,
    GO_EMBERSEER_RUNE_5         = 175268,
    GO_EMBERSEER_RUNE_6         = 175267,
    GO_EMBERSEER_RUNE_7         = 175266,


    SPELL_EMBERSEER_GROW        = 16048,
};

class MANGOS_DLL_DECL instance_blackrock_spire : public ScriptedInstance
{
    public:
        instance_blackrock_spire(Map* pMap);
        ~instance_blackrock_spire() {}

        void Initialize();

        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);
        void OnCreatureEnterCombat(Creature* pCreature);

        void SetData(uint32 uiType, uint32 uiData);
        void SetData64(uint32 uiType, uint64 uiData);
        uint32 GetData(uint32 uiType);
        uint64 GetData64(uint32 uiType);

        void ProcessEmberseerEvent();

        const char* Save() { return m_strInstData.c_str(); }
        void Load(const char* chrIn);

        void DoUseEmberseerRunes();
        void DoSortRoomEventMobs();
        void GetIncanceratorGUIDList(GUIDList &lList) { lList = m_lIncanceratorGUIDList; }
        void GetRookeryEggGUIDList(GUIDList &lList) { lList = m_lRookeryEggGUIDList; }

    protected:
        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string m_strInstData;

        uint64 m_uiEmberseerGUID;
        uint64 m_uiNefariusGUID;
        uint64 m_uiGythGUID;
        uint64 m_uiInfiltratorGUID;

        uint64 m_uiEmberseerInDoorGUID;
        uint64 m_uiEmberseerCombatDoorGUID;
        uint64 m_uiEmberseerOutDoorGUID;
        uint64 m_uiGythEntryDoorGUID;
        uint64 m_uiGythCombatDoorGUID;
        uint64 m_uiGythExitDoorGUID;

        uint64 m_auiRoomRuneGUID[MAX_ROOMS];
        GUIDList m_alRoomEventMobGUIDSorted[MAX_ROOMS];
        GUIDList m_lRoomEventMobGUIDList;
        GUIDList m_lIncanceratorGUIDList;
        GUIDList m_lRookeryEggGUIDList;
        GUIDList m_lEmberseerRunesGUIDList;
        GUIDList m_lDrakkisathNpcGUIDList;
};

#endif
