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
SDName: instance_blackrock_spire
SD%Complete: 100
SDComment: Events scripts are completed!
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

instance_blackrock_spire::instance_blackrock_spire(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_blackrock_spire::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    memset(&m_auiRoomRuneGUID, 0, sizeof(m_auiRoomRuneGUID));

    for (uint8 i = 0; i < MAX_ALTAR_SLOT; i++)
        t_AltarGuid[i] = 0;
}

void instance_blackrock_spire::OnObjectCreate(GameObject* pGo)
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

void instance_blackrock_spire::OnCreatureCreate(Creature* pCreature)
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

void instance_blackrock_spire::SetData(uint32 uiType, uint32 uiData)
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

void instance_blackrock_spire::SetData64(uint32 uiType, uint64 uiData)
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

void instance_blackrock_spire::Load(const char* chrIn)
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

uint32 instance_blackrock_spire::GetData(uint32 uiType)
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

uint64 instance_blackrock_spire::GetData64(uint32 uiType)
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

void instance_blackrock_spire::DoSortRoomEventMobs()
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

InstanceData* GetInstanceData_instance_blackrock_spire(Map* pMap)
{
    return new instance_blackrock_spire(pMap);
}

bool AreaTrigger_at_blackrock_spire(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (pPlayer->isDead())
        return false;

    switch (pAt->id)
    {
        case AREATRIGGER_ENTER_UBRS:
            if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*) pPlayer->GetInstanceData())
                if (pPlayer->HasItemCount(ITEM_SEAL_OF_ASCENSION,1,false))
                    pInstance->DoSortRoomEventMobs();
            break;
        case AREATRIGGER_STADIUM:
            if (instance_blackrock_spire* pInstance = (instance_blackrock_spire*) pPlayer->GetInstanceData())
                if (pInstance->GetData(TYPE_STADIUM_EVENT) == NOT_STARTED)
                    pInstance->SetData(TYPE_STADIUM_EVENT, IN_PROGRESS);
            break;
    }
    return false;
}

void AddSC_instance_blackrock_spire()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "instance_blackrock_spire";
    pNewScript->GetInstanceData = &GetInstanceData_instance_blackrock_spire;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_blackrock_spire";
    pNewScript->pAreaTrigger = &AreaTrigger_at_blackrock_spire;
    pNewScript->RegisterSelf();
}
