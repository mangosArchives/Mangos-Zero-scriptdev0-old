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

#ifndef DEF_SUNKEN_TEMPLE_H
#define DEF_SUNKEN_TEMPLE_H

enum
{
    MAX_ENCOUNTER         = 6,
    MAX_STATUES           = 6,
    MAX_FLAMES            = 4,
    MAX_AVATAR_LOCS       = 8,

    TYPE_ATALARION        = 1,
    TYPE_PROTECTORS       = 2,
    TYPE_JAMMALAN         = 3,
    TYPE_MALFURION        = 4,
    TYPE_STATUES          = 5,
    TYPE_AVATAR           = 6,

    NPC_ATALARION         = 8580,
    NPC_DREAMSCYTH        = 5721,
    NPC_WEAVER            = 5720,
    NPC_AVATAR_OF_HAKKAR  = 8443,
    NPC_SHADE_OF_ERANIKUS = 5709,
    NPC_JAMMALAN          = 5710,

    // avatar of hakkar
    NPC_SHADE_OF_HAKKAR   = 8440,       // npc which appears before the flames are doused
    NPC_BLOODKEEPER       = 8438,       // hakkari bloodkeeper; is spawned rarely and contains the hakkari blood, used to extinguish the flames
    NPC_HAKKARI_MINION    = 8437,       // npc randomly spawned during the event
    NPC_SUPPRESSOR        = 8497,       // npc which tries to light the suppressed flames again

    // Jammalain min-bosses
    NPC_ZOLO              = 5712,
    NPC_GASHER            = 5713,
    NPC_LORO              = 5714,
    NPC_HUKKU             = 5715,
    NPC_ZULLOR            = 5716,
    NPC_MIJAN             = 5717,

    NPC_MALFURION         = 15362,

    GO_ALTAR_OF_HAKKAR    = 148836,     // used in order to show the player the order of the statue activation
    GO_IDOL_OF_HAKKAR     = 148838,     // appears when atalarion is summoned; this was removed in 4.0.1

    // Statues must be activated in this order
    // S, N, SW, SE, NW, NE
    GO_ATALAI_STATUE_1    = 148830,     // S
    GO_ATALAI_STATUE_2    = 148831,     // N
    GO_ATALAI_STATUE_3    = 148832,     // SW
    GO_ATALAI_STATUE_4    = 148833,     // SE
    GO_ATALAI_STATUE_5    = 148834,     // NW
    GO_ATALAI_STATUE_6    = 148835,     // NE

    GO_ATALAI_LIGHT       = 148883,     // green light, activates when the correct statue is chosen
    GO_ATALAI_LIGHT_BIG   = 148937,     // big light, used at the altar event

    GO_ATALAI_TRAP_1      = 177484,     // trapps triggered if the wrong statue is activated
    GO_ATALAI_TRAP_2      = 177485,     // the traps are spawned in DB randomly around the statues (we don't know exactly which statue has which trap)
    GO_ATALAI_TRAP_3      = 148837,

    // flames used at the Avatar of Hakkar encounter
    GO_ETERNAL_FLAME_1    = 148418,
    GO_ETERNAL_FLAME_2    = 148419,
    GO_ETERNAL_FLAME_3    = 148420,
    GO_ETERNAL_FLAME_4    = 148421,

    // circles used at the avatar event. they are spawned when the event starts, and the mobs are summon on them
    GO_EVIL_CIRCLE        = 148998,

    // Jammalan chamber door
    GO_JAMMALAN_BARRIER   = 149431,

    // Avatar of Hakkar combat doors
    GO_HAKKAR_DOOR_1      = 149432,
    GO_HAKKAR_DOOR_2      = 149433,

    // event ids -> related to the statue activation
    EVENT_ID_STATUE_1     = 3094,
    EVENT_ID_STATUE_2     = 3095,
    EVENT_ID_STATUE_3     = 3097,
    EVENT_ID_STATUE_4     = 3098,
    EVENT_ID_STATUE_5     = 3099,
    EVENT_ID_STATUE_6     = 3100,

    // event sent by the spell which summons the avatar of hakkar and used to start the event
    EVENT_ID_HAKKAR_EVENT = 8502,

    SPELL_SUMMON_AVATAR   = 12948,      // dummy spell to summon the avatar
    SPELL_SUPPRESSION     = 12623,      // used by the suppressors to banish the shade
    SPELL_SUMMONED        = 7741,       // spawn effect for the suppressor

    SAY_JAMMALAN_INTRO    = -1109005,
    SAY_AVATAR_BRAZIER_1  = -1109006,
    SAY_AVATAR_BRAZIER_2  = -1109007,
    SAY_AVATAR_BRAZIER_3  = -1109008,
    SAY_AVATAR_BRAZIER_4  = -1109009,
    SAY_AVATAR_AGGRO      = -1109010,
    SAY_SUPPRESSOR_WARN   = -1109011
};

struct sAtalaiSequence
{
    uint8 m_uiOrder;
    uint32 m_uiEventId;
};

static sAtalaiSequence m_sAtalaiStatueSequence[MAX_STATUES] =
{
    {0, EVENT_ID_STATUE_1},
    {1, EVENT_ID_STATUE_2},
    {2, EVENT_ID_STATUE_3},
    {3, EVENT_ID_STATUE_4},
    {4, EVENT_ID_STATUE_5},
    {5, EVENT_ID_STATUE_6}
};

struct sSummonLocations
{
    float m_fX, m_fY, m_fZ, m_fO;
};

static sSummonLocations sSunkenTempleLocation[] =
{
    {-480.399f, 96.566f, -189.729f, 6.19f},                 // atalarion summon loc
    {-466.716f, 273.025f, -90.450f, 3.13f}                  // avatar and shade of hakkar summon
};

// Summoning circle locations; used for minions and bloodkeepers
static sSummonLocations sHakkariSummonLocations[MAX_AVATAR_LOCS] =
{
    {-451.389f, 272.707f, -90.582f},
    {-467.622f, 290.573f, -90.582f},
    {-477.915f, 285.49f, -90.582f},
    {-456.843f, 261.305f, -90.582f},
    {-467.861f, 257.761f, -90.582f},
    {-456.914f, 286.912f, -90.582f},
    {-482.814f, 271.267f, -90.582f},
    {-476.698f, 260.68f, -90.582f}
};

// Summon location for the suppressors
static sSummonLocations sHakkariDoorLocations[2] =
{
    {-420.629f, 276.682f, -90.827f},
    {-512.015f, 276.134f, -90.827f}
};

class MANGOS_DLL_DECL instance_sunken_temple : public ScriptedInstance
{
    public:
        instance_sunken_temple(Map* pMap);
        ~instance_sunken_temple() {}

        void Initialize();

        void OnObjectCreate(GameObject* pGo);
        void OnCreatureCreate(Creature* pCreature);
        void OnCreatureEnterCombat(Creature* pCreature);
        void OnCreatureEvade(Creature* pCreature);
        void OnCreatureDeath(Creature* pCreature);
        void OnPlayerEnter(Player* pPlayer);

        void SetData(uint32 uiType, uint32 uiData);
        uint32 GetData(uint32 uiType);
        uint64 GetData64(uint32 uiType);

        void Update(uint32 uiDiff);

        bool ProcessStatueEvent(uint32 uiEventId);

        const char* Save() { return strInstData.c_str(); }
        void Load(const char* chrIn);

    protected:
        void DoSpawnAtalarionIfCan(bool bByPlayerEnter = false);

        uint32 m_auiEncounter[MAX_ENCOUNTER];
        std::string strInstData;

        uint64 m_uiAtalarionGUID;
        uint64 m_uiJammalanGUID;
        uint64 m_uiShadeGUID;
        uint64 m_uiAvatarGUID;
        uint64 m_uiIdolOfHakkarGUID;
        uint64 m_uiJammalanBarrierGUID;
        uint64 m_uiAvatarDoor1GUID;
        uint64 m_uiAvatarDoor2GUID;
        uint32 m_uiAvatarSummonTimer;
        uint32 m_uiSuppressorTimer;
        uint8 m_uiProtectorsRemaining;
        uint8 m_uiStatueCounter;
        uint8 m_uiFlameCounter;
        bool m_bIsFirstSummon;

        std::list<uint64> m_luiStatueGUIDs;
        std::list<uint64> m_luiCircleGUIDs;
        std::list<uint64> m_luiFlameGUIDs;
};
#endif
