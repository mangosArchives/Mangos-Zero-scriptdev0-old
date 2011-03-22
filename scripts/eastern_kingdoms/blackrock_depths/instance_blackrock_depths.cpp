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

/* ScriptData
SDName: Instance_Blackrock_Depths
SD%Complete: 80
SDComment:
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"
#include "blackrock_depths.h"

instance_blackrock_depths::instance_blackrock_depths(Map* pMap) : ScriptedInstance(pMap),
    m_uiEmperorGUID(0),
    m_uiPrincessGUID(0),
    m_uiPhalanxGUID(0),
    m_uiHaterelGUID(0),
    m_uiAngerrelGUID(0),
    m_uiVilerelGUID(0),
    m_uiGloomrelGUID(0),
    m_uiSeethrelGUID(0),
    m_uiDoomrelGUID(0),
    m_uiDoperelGUID(0),

    m_uiOgrabisiGUID(0),
    m_uiShillGUID(0),
    m_uiCrestGUID(0),
    m_uiJazGUID(0),

    m_uiGoArena1GUID(0),
    m_uiGoArena2GUID(0),
    m_uiGoArena3GUID(0),
    m_uiGoArena4GUID(0),

    m_uiGoJailSupplyRoomGUID(0),
    m_uiGoJailSupplyCrateGUID(0),

    m_uiGoShadowLockGUID(0),
    m_uiGoShadowMechGUID(0),
    m_uiGoShadowGiantGUID(0),
    m_uiGoShadowDummyGUID(0),
    m_uiGoBarKegGUID(0),
    m_uiGoBarKegTrapGUID(0),
    m_uiGoBarDoorGUID(0),
    m_uiGoTombEnterGUID(0),
    m_uiGoTombExitGUID(0),
    m_uiGoLyceumGUID(0),
    m_uiGoGolemNGUID(0),
    m_uiGoGolemSGUID(0),
    m_uiGoThroneGUID(0),

    m_uiSpectralChaliceGUID(0),
    m_uiSevensChestGUID(0),
    m_uiArenaSpoilsGUID(0),

    m_uiBarAleCount(0),

    m_fArenaCenterX(0.0f),
    m_fArenaCenterY(0.0f),
    m_fArenaCenterZ(0.0f)

{
    Initialize();
}

void instance_blackrock_depths::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    SetOpenedDoor(GO_JAIL_DOOR_DUGHAL, false);
    SetOpenedDoor(GO_JAIL_DOOR_TOBIAS, false);
    SetOpenedDoor(GO_JAIL_DOOR_JAZ,    false);
    SetOpenedDoor(GO_JAIL_DOOR_CREST,  false);
    SetOpenedDoor(GO_JAIL_DOOR_SHILL,  false);
    SetOpenedDoor(GO_JAIL_DOOR_SUPPLY, false);
}

void instance_blackrock_depths::SetOpenedDoor(uint64 m_uiGoEntry, bool opened)
{
    switch(m_uiGoEntry)
    {
        case GO_JAIL_DOOR_DUGHAL: m_bDoorDughalOpened = opened; break;
        case GO_JAIL_DOOR_TOBIAS: m_bDoorTobiasOpened = opened; break;
        case GO_JAIL_DOOR_CREST:  m_bDoorCrestOpened  = opened; break;
        case GO_JAIL_DOOR_JAZ:    m_bDoorJazOpened    = opened; break;
        case GO_JAIL_DOOR_SHILL:  m_bDoorShillOpened  = opened; break;
        case GO_JAIL_DOOR_SUPPLY: m_bDoorSupplyOpened = opened; break;
    }
}

bool instance_blackrock_depths::GetOpenedDoor(uint64 m_uiGoEntry)
{
    switch(m_uiGoEntry)
    {
        case GO_JAIL_DOOR_DUGHAL: return m_bDoorDughalOpened;
        case GO_JAIL_DOOR_TOBIAS: return m_bDoorTobiasOpened;
        case GO_JAIL_DOOR_CREST:  return m_bDoorCrestOpened;
        case GO_JAIL_DOOR_JAZ:    return m_bDoorJazOpened;
        case GO_JAIL_DOOR_SHILL:  return m_bDoorShillOpened;
        case GO_JAIL_DOOR_SUPPLY: return m_bDoorSupplyOpened;
    }
    return false;
}

void instance_blackrock_depths::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_EMPEROR:  m_uiEmperorGUID =  pCreature->GetGUID(); break;
        case NPC_PRINCESS: m_uiPrincessGUID = pCreature->GetGUID(); break;
        case NPC_PHALANX:  m_uiPhalanxGUID =  pCreature->GetGUID(); break;
        case NPC_HATEREL:  m_uiHaterelGUID =  pCreature->GetGUID(); break;
        case NPC_ANGERREL: m_uiAngerrelGUID = pCreature->GetGUID(); break;
        case NPC_VILEREL:  m_uiVilerelGUID =  pCreature->GetGUID(); break;
        case NPC_GLOOMREL: m_uiGloomrelGUID = pCreature->GetGUID(); break;
        case NPC_SEETHREL: m_uiSeethrelGUID = pCreature->GetGUID(); break;
        case NPC_DOOMREL:  m_uiDoomrelGUID =  pCreature->GetGUID(); break;
        case NPC_DOPEREL:  m_uiDoperelGUID =  pCreature->GetGUID(); break;
        case NPC_OGRABISI: m_uiOgrabisiGUID = pCreature->GetGUID(); break;
        case NPC_SHILL:    m_uiShillGUID = pCreature->GetGUID(); break;
        case NPC_CREST:    m_uiCrestGUID =  pCreature->GetGUID(); break;
        case NPC_JAZ:      m_uiJazGUID =  pCreature->GetGUID(); break;
    }
}

void instance_blackrock_depths::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_ARENA_1:            m_uiGoArena1GUID = pGo->GetGUID(); break;
        case GO_ARENA_2:            m_uiGoArena2GUID = pGo->GetGUID(); break;
        case GO_ARENA_3:            m_uiGoArena3GUID = pGo->GetGUID(); break;
        case GO_ARENA_4:            m_uiGoArena4GUID = pGo->GetGUID(); break;

        case GO_JAIL_DOOR_SUPPLY:   m_uiGoJailSupplyRoomGUID = pGo->GetGUID(); break;
        case GO_JAIL_SUPPLY_CRATE:  m_uiGoJailSupplyCrateGUID = pGo->GetGUID(); break;

        case GO_SHADOW_LOCK:        m_uiGoShadowLockGUID = pGo->GetGUID(); break;
        case GO_SHADOW_MECHANISM:   m_uiGoShadowMechGUID = pGo->GetGUID(); break;
        case GO_SHADOW_GIANT_DOOR:  m_uiGoShadowGiantGUID = pGo->GetGUID(); break;
        case GO_SHADOW_DUMMY:       m_uiGoShadowDummyGUID = pGo->GetGUID(); break;
        case GO_BAR_KEG_SHOT:       m_uiGoBarKegGUID = pGo->GetGUID(); break;
        case GO_BAR_KEG_TRAP:       m_uiGoBarKegTrapGUID = pGo->GetGUID(); break;
        case GO_BAR_DOOR:           m_uiGoBarDoorGUID = pGo->GetGUID(); break;
        case GO_TOMB_ENTER:         m_uiGoTombEnterGUID = pGo->GetGUID(); break;
        case GO_TOMB_EXIT:          m_uiGoTombExitGUID = pGo->GetGUID(); break;
        case GO_LYCEUM:             m_uiGoLyceumGUID = pGo->GetGUID(); break;
        case GO_GOLEM_ROOM_N:       m_uiGoGolemNGUID = pGo->GetGUID(); break;
        case GO_GOLEM_ROOM_S:       m_uiGoGolemSGUID = pGo->GetGUID(); break;
        case GO_THRONE_ROOM:        m_uiGoThroneGUID = pGo->GetGUID(); break;
        case GO_SPECTRAL_CHALICE:   m_uiSpectralChaliceGUID = pGo->GetGUID(); break;
        case GO_CHEST_SEVEN:        m_uiSevensChestGUID = pGo->GetGUID(); break;
        case GO_ARENA_SPOILS:       m_uiArenaSpoilsGUID = pGo->GetGUID(); break;
    }
}

void instance_blackrock_depths::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_RING_OF_LAW:
            // If finished the arena event after theldren fight
            if (uiData == DONE && m_auiEncounter[0] == SPECIAL)
                DoRespawnGameObject(m_uiArenaSpoilsGUID, HOUR*IN_MILLISECONDS);
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_VAULT:
            m_auiEncounter[1] = uiData;
            break;
        case TYPE_BAR:
            if (uiData == SPECIAL)
                ++m_uiBarAleCount;
            else
                m_auiEncounter[2] = uiData;
            break;
        case TYPE_TOMB_OF_SEVEN:
            switch(uiData)
            {
                case IN_PROGRESS:
                    DoUseDoorOrButton(m_uiGoTombEnterGUID);
                    break;
                case FAIL:
                    if (m_auiEncounter[3] == IN_PROGRESS)//prevent use more than one time
                        DoUseDoorOrButton(m_uiGoTombEnterGUID);
                    break;
                case DONE:
                    DoRespawnGameObject(m_uiSevensChestGUID, HOUR*IN_MILLISECONDS);
                    DoUseDoorOrButton(m_uiGoTombExitGUID);
                    DoUseDoorOrButton(m_uiGoTombEnterGUID);
                    break;
            }
            m_auiEncounter[3] = uiData;
            break;
        case TYPE_LYCEUM:
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiGoGolemNGUID);
                DoUseDoorOrButton(m_uiGoGolemSGUID);
            }
            m_auiEncounter[4] = uiData;
            break;
        case TYPE_IRON_HALL:
            switch(uiData)
            {
                case IN_PROGRESS:
                    DoUseDoorOrButton(m_uiGoGolemNGUID);
                    DoUseDoorOrButton(m_uiGoGolemSGUID);
                    break;
                case FAIL:
                    DoUseDoorOrButton(m_uiGoGolemNGUID);
                    DoUseDoorOrButton(m_uiGoGolemSGUID);
                    break;
                case DONE:
                    DoUseDoorOrButton(m_uiGoGolemNGUID);
                    DoUseDoorOrButton(m_uiGoGolemSGUID);
                    DoUseDoorOrButton(m_uiGoThroneGUID);
                    break;
            }
            m_auiEncounter[5] = uiData;
            break;
        case TYPE_QUEST_JAIL_BREAK:
            if (uiData == FAIL)
            {
                Map::PlayerList const &PlayerList = instance->GetPlayers();

                for (Map::PlayerList::const_iterator itr = PlayerList.begin(); itr != PlayerList.end(); ++itr)
                {
                Player* pPlayer = itr->getSource();
                if (pPlayer && pPlayer->GetQuestStatus(QUEST_JAIL_BREAK) == QUEST_STATUS_INCOMPLETE)
                    pPlayer->SendQuestFailed(QUEST_JAIL_BREAK);
                }
            }
            m_auiEncounter[6] = uiData;
            break;
        case TYPE_JAIL_DUGHAL:
            m_auiEncounter[7] = uiData;
            break;
        case TYPE_JAIL_SUPPLY_ROOM:
            m_auiEncounter[8] = uiData;
            break;
        case TYPE_JAIL_TOBIAS:
            m_auiEncounter[9] = uiData;
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
            << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

uint32 instance_blackrock_depths::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_RING_OF_LAW:
            return m_auiEncounter[0];
        case TYPE_VAULT:
            return m_auiEncounter[1];
        case TYPE_BAR:
            if (m_auiEncounter[2] == IN_PROGRESS && m_uiBarAleCount == 3)
                return SPECIAL;
            else
                return m_auiEncounter[2];
        case TYPE_TOMB_OF_SEVEN:
            return m_auiEncounter[3];
        case TYPE_LYCEUM:
            return m_auiEncounter[4];
        case TYPE_IRON_HALL:
            return m_auiEncounter[5];
        case TYPE_QUEST_JAIL_BREAK:
            return m_auiEncounter[6];
        case TYPE_JAIL_DUGHAL:
            return m_auiEncounter[7];
        case TYPE_JAIL_SUPPLY_ROOM:
            return m_auiEncounter[8];
        case TYPE_JAIL_TOBIAS:
            return m_auiEncounter[9];
        default:
            return 0;
    }
}

uint64 instance_blackrock_depths::GetData64(uint32 uiData)
{
    switch(uiData)
    {
        case NPC_EMPEROR:           return m_uiEmperorGUID;
        case NPC_PRINCESS:          return m_uiPrincessGUID;
        case NPC_PHALANX:           return m_uiPhalanxGUID;
        case NPC_HATEREL:           return m_uiHaterelGUID;
        case NPC_ANGERREL:          return m_uiAngerrelGUID;
        case NPC_VILEREL:           return m_uiVilerelGUID;
        case NPC_GLOOMREL:          return m_uiGloomrelGUID;
        case NPC_SEETHREL:          return m_uiSeethrelGUID;
        case NPC_DOOMREL:           return m_uiDoomrelGUID;
        case NPC_DOPEREL:           return m_uiDoperelGUID;
        case NPC_OGRABISI:          return m_uiOgrabisiGUID;
        case NPC_SHILL:             return  m_uiShillGUID;
        case NPC_CREST:             return  m_uiCrestGUID;
        case NPC_JAZ:               return m_uiJazGUID;

        case GO_ARENA_1:            return m_uiGoArena1GUID;
        case GO_ARENA_2:            return m_uiGoArena2GUID;
        case GO_ARENA_3:            return m_uiGoArena3GUID;
        case GO_ARENA_4:            return m_uiGoArena4GUID;

        case GO_JAIL_DOOR_SUPPLY:   return m_uiGoJailSupplyRoomGUID;
        case GO_JAIL_SUPPLY_CRATE:  return m_uiGoJailSupplyCrateGUID;

        case GO_BAR_KEG_SHOT:       return m_uiGoBarKegGUID;
        case GO_BAR_KEG_TRAP:       return m_uiGoBarKegTrapGUID;
        case GO_BAR_DOOR:           return m_uiGoBarDoorGUID;
        case GO_SPECTRAL_CHALICE:   return m_uiSpectralChaliceGUID;
        case GO_TOMB_EXIT:          return m_uiGoTombExitGUID;

        default:
            return 0;
    }
}

void instance_blackrock_depths::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
        >> m_auiEncounter[4] >> m_auiEncounter[5];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;

    OUT_LOAD_INST_DATA_COMPLETE;
}

void instance_blackrock_depths::OnCreatureEvade(Creature* pCreature)
{
    if (GetData(TYPE_RING_OF_LAW) == IN_PROGRESS || GetData(TYPE_RING_OF_LAW) == SPECIAL)
    {
        for (uint8 i = 0; i < sizeof(aArenaNPCs)/sizeof(uint32); ++i)
        {
            if (pCreature->GetEntry() == aArenaNPCs[i])
            {
                 SetData(TYPE_RING_OF_LAW, FAIL);
                 return;
             }
        }
    }
}

InstanceData* GetInstanceData_instance_blackrock_depths(Map* pMap)
{
    return new instance_blackrock_depths(pMap);
}

void AddSC_instance_blackrock_depths()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_blackrock_depths";
    pNewScript->GetInstanceData = &GetInstanceData_instance_blackrock_depths;
    pNewScript->RegisterSelf();
}
