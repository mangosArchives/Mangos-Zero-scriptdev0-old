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
SDName: instance_sunken_temple
SD%Complete: 30
SDComment:
SDCategory: Sunken Temple
EndScriptData */

#include "precompiled.h"
#include "sunken_temple.h"

instance_sunken_temple::instance_sunken_temple(Map* pMap) : ScriptedInstance(pMap),
    m_uiStatueCounter(0),
    m_uiFlameCounter(0),
    m_uiAtalarionGUID(0),
    m_uiJammalanGUID(0),
    m_uiAvatarGUID(0),
    m_uiIdolOfHakkarGUID(0),
    m_uiAvatarDoor1GUID(0),
    m_uiAvatarDoor2GUID(0),
    m_uiAvatarSummonTimer(0),
    m_uiSuppressorTimer(0),
    m_uiJammalanBarrierGUID(0),
    m_uiProtectorsRemaining(0),
    m_bIsFirstSummon(false)
{
    Initialize();
}

void instance_sunken_temple::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_sunken_temple::OnPlayerEnter(Player *pPlayer)
{
    // Spawn Atalarion
    DoSpawnAtalarionIfCan(true);
}

void instance_sunken_temple::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_JAMMALAN_BARRIER:
            m_uiJammalanBarrierGUID = pGo->GetGUID();
            if (m_auiEncounter[1] == DONE)
                DoUseDoorOrButton(m_uiJammalanBarrierGUID);
            break;
        case GO_IDOL_OF_HAKKAR:
            m_uiIdolOfHakkarGUID = pGo->GetGUID();
            break;
        case GO_ATALAI_STATUE_1:
        case GO_ATALAI_STATUE_2:
        case GO_ATALAI_STATUE_3:
        case GO_ATALAI_STATUE_4:
        case GO_ATALAI_STATUE_5:
        case GO_ATALAI_STATUE_6:
            m_luiStatueGUIDs.push_back(pGo->GetGUID());
            break;
        case GO_HAKKAR_DOOR_1:
            m_uiAvatarDoor1GUID = pGo->GetGUID();
            break;
        case GO_HAKKAR_DOOR_2:
            m_uiAvatarDoor2GUID = pGo->GetGUID();
            break;
        case GO_EVIL_CIRCLE:
            m_luiCircleGUIDs.push_back(pGo->GetGUID());
            break;
        case GO_ETERNAL_FLAME_1:
        case GO_ETERNAL_FLAME_2:
        case GO_ETERNAL_FLAME_3:
        case GO_ETERNAL_FLAME_4:
            m_luiFlameGUIDs.push_back(pGo->GetGUID());
            if (m_auiEncounter[5] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
    }
}

void instance_sunken_temple::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_ZOLO:
        case NPC_GASHER:
        case NPC_LORO:
        case NPC_HUKKU:
        case NPC_ZULLOR:
        case NPC_MIJAN:
            ++m_uiProtectorsRemaining;
            break;
        case NPC_JAMMALAN:
            m_uiJammalanGUID = pCreature->GetGUID();
            break;
        case NPC_AVATAR_OF_HAKKAR:
            m_uiAvatarGUID = pCreature->GetGUID();
            pCreature->SetRespawnDelay(DAY);
            break;
    }
}

void instance_sunken_temple::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_ATALARION:
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_PROTECTORS:
            if (uiData == DONE)
            {
                --m_uiProtectorsRemaining;
                if (!m_uiProtectorsRemaining)
                {
                    m_auiEncounter[1] = uiData;
                    DoUseDoorOrButton(m_uiJammalanBarrierGUID);
                    // intro yell
                    if (Creature* pJammalan = instance->GetCreature(m_uiJammalanGUID))
                        DoScriptText(SAY_JAMMALAN_INTRO, pJammalan);
                }
            }
            break;
        case TYPE_JAMMALAN:
            m_auiEncounter[2] = uiData;
            break;
        case TYPE_MALFURION:
            m_auiEncounter[3] = uiData;
            break;
        case TYPE_STATUES:
            m_auiEncounter[4] = uiData;
            if (uiData == DONE)
                DoSpawnAtalarionIfCan();
            break;
        case TYPE_AVATAR:
            if (uiData != SPECIAL)
            {
                m_auiEncounter[5] = uiData;
                // combat doors
                DoUseDoorOrButton(m_uiAvatarDoor1GUID);
                DoUseDoorOrButton(m_uiAvatarDoor2GUID);
            }
            if (uiData == SPECIAL)
            {
                ++m_uiFlameCounter;

                Creature* pShade = instance->GetCreature(m_uiShadeGUID);
                if (!pShade)
                    return;

                if (m_uiFlameCounter == 1)
                    DoScriptText(SAY_AVATAR_BRAZIER_1, pShade);
                else if (m_uiFlameCounter == 2)
                    DoScriptText(SAY_AVATAR_BRAZIER_2, pShade);
                else if (m_uiFlameCounter == 3)
                    DoScriptText(SAY_AVATAR_BRAZIER_3, pShade);
                // summon the avatar of all flames are used
                else if (m_uiFlameCounter == MAX_FLAMES)
                {
                    DoScriptText(SAY_AVATAR_BRAZIER_4, pShade);
                    // summon avatar
                    pShade->CastSpell(pShade, SPELL_SUMMON_AVATAR, true);

                    m_uiAvatarSummonTimer = 0;
                    m_uiSuppressorTimer = 0;
                }

                // summon the suppressors only after the flames are doused
                // use a random timer
                if (m_uiFlameCounter != MAX_FLAMES)
                    m_uiSuppressorTimer = urand(10000, 30000);
            }
            else if (uiData == IN_PROGRESS)
            {
                // summon timers
                m_uiAvatarSummonTimer   = 3000;
                m_uiSuppressorTimer     = urand(50000, 60000);
                m_bIsFirstSummon        = true;

                // respawn circles
                for (GUIDList::const_iterator itr = m_luiCircleGUIDs.begin(); itr != m_luiCircleGUIDs.end(); ++itr)
                    DoRespawnGameObject(*itr, 30*MINUTE*IN_MILLISECONDS);

                // summon the shade
                Player* pPlayer = GetPlayerInMap();
                if (!pPlayer)
                    return;

                if (Creature* pShade = pPlayer->SummonCreature(NPC_SHADE_OF_HAKKAR, sSunkenTempleLocation[1].m_fX, sSunkenTempleLocation[1].m_fY, sSunkenTempleLocation[1].m_fZ, sSunkenTempleLocation[1].m_fO, TEMPSUMMON_MANUAL_DESPAWN, 0))
                {
                    m_uiShadeGUID = pShade->GetGUID();
                    pShade->SetRespawnDelay(DAY);
                }

                // remove the flames flags, so they can be used
                for (GUIDList::const_iterator itr = m_luiFlameGUIDs.begin(); itr != m_luiFlameGUIDs.end(); ++itr)
                {
                    if (GameObject* pFlame = instance->GetGameObject(*itr))
                        pFlame->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                }
            }
            else if (uiData == FAIL)
            {
                // despawn the shade and the avatar if needed
                if (Creature* pShade = instance->GetCreature(m_uiShadeGUID))
                    pShade->ForcedDespawn();

                if (Creature* pAvatar = instance->GetCreature(m_uiAvatarGUID))
                    pAvatar->ForcedDespawn();

                // reset flames
                for (GUIDList::const_iterator itr = m_luiFlameGUIDs.begin(); itr != m_luiFlameGUIDs.end(); ++itr)
                {
                    if (GameObject* pFlame = instance->GetGameObject(*itr))
                        pFlame->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
                }
            }
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
            << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5];
        strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_sunken_temple::OnCreatureDeath(Creature* pCreature)
{
    if (pCreature->GetEntry() == NPC_AVATAR_OF_HAKKAR)
        SetData(TYPE_AVATAR, DONE);
}

void instance_sunken_temple::OnCreatureEvade(Creature *pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_BLOODKEEPER:
        case NPC_HAKKARI_MINION:
        case NPC_SUPPRESSOR:
        case NPC_AVATAR_OF_HAKKAR:
            if (GetData(TYPE_AVATAR) == IN_PROGRESS)
                SetData(TYPE_AVATAR, FAIL);
            break;
    }
}

void instance_sunken_temple::OnCreatureEnterCombat(Creature* pCreature)
{
    if (pCreature->GetEntry() == NPC_AVATAR_OF_HAKKAR)
    {
        if (Creature* pAvatar = instance->GetCreature(m_uiAvatarGUID))
            DoScriptText(SAY_AVATAR_AGGRO, pAvatar);
    }
}

bool instance_sunken_temple::ProcessStatueEvent(uint32 uiEventId)
{
    bool m_bEventStatus = false;

    // do check if the statues are activated correctly
    // increase the counter when the correct statue is activated
    for (uint8 i = 0; i < MAX_STATUES; i++)
    {
        // if right statue is used return true
        if (uiEventId == m_sAtalaiStatueSequence[i].m_uiEventId && m_uiStatueCounter == m_sAtalaiStatueSequence[i].m_uiOrder)
        {
            ++m_uiStatueCounter;
            m_bEventStatus = true;
            break;
        }
    }

    // check if all statues are active
    if (m_uiStatueCounter == 6)
        SetData(TYPE_STATUES, DONE);

    return m_bEventStatus;
}

void instance_sunken_temple::DoSpawnAtalarionIfCan(bool bByPlayerEnter /*=false*/)
{
    // return if statue event not finished or if boss already killed
    if (m_auiEncounter[4] != DONE || m_auiEncounter[0] == DONE)
        return;

    // return if already summoned
    if (m_uiAtalarionGUID)
        return;

    Player* pPlayer = GetPlayerInMap();
    if (!pPlayer)
        return;

    if (Creature* pAtalarion = pPlayer->SummonCreature(NPC_ATALARION, sSunkenTempleLocation[0].m_fX, sSunkenTempleLocation[0].m_fY, sSunkenTempleLocation[0].m_fZ, sSunkenTempleLocation[0].m_fO, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30*MINUTE*IN_MILLISECONDS))
        m_uiAtalarionGUID = pAtalarion->GetGUID();

    // Spawn the idol of Hakkar
    DoRespawnGameObject(m_uiIdolOfHakkarGUID, 30);

    // spawn all the green lights
    for (GUIDList::const_iterator itr = m_luiStatueGUIDs.begin(); itr != m_luiStatueGUIDs.end(); ++itr)
    {
        if (GameObject* pStatue = instance->GetGameObject(*itr))
        {
            if (GameObject* pLight = GetClosestGameObjectWithEntry(pStatue, GO_ATALAI_LIGHT_BIG, 30.0f))
                DoRespawnGameObject(pLight->GetGUID(), 30*MINUTE*IN_MILLISECONDS);
            // respawn the small lights too on reset
            if (bByPlayerEnter)
            {
                if (GameObject* pLight = GetClosestGameObjectWithEntry(pStatue, GO_ATALAI_LIGHT, 5.0f))
                    DoRespawnGameObject(pLight->GetGUID(), 30*MINUTE*IN_MILLISECONDS);
            }
        }
    }
}

void instance_sunken_temple::Load(const char* chrIn)
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
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_sunken_temple::GetData(uint32 uiType)
{
    switch(uiType)
    {
        case TYPE_ATALARION:
            return m_auiEncounter[0];
        case TYPE_PROTECTORS:
            return m_auiEncounter[1];
        case TYPE_JAMMALAN:
            return m_auiEncounter[2];
        case TYPE_MALFURION:
            return m_auiEncounter[3];
        case TYPE_STATUES:
            return m_auiEncounter[4];
        case TYPE_AVATAR:
            return m_auiEncounter[5];
    }
    return 0;
}

uint64 instance_sunken_temple::GetData64(uint32 uiType)
{
    if (uiType == NPC_SHADE_OF_HAKKAR)
        return m_uiShadeGUID;

    return 0;
}

void instance_sunken_temple::Update(uint32 uiDiff)
{
    if (GetData(TYPE_AVATAR) != IN_PROGRESS)
        return;

    if (m_uiAvatarSummonTimer)
    {
        if (m_uiAvatarSummonTimer < uiDiff)
        {
            Creature* pShade = instance->GetCreature(m_uiShadeGUID);
            if (!pShade)
                return;

            // if is first time, summon on all circles
            if (m_bIsFirstSummon)
            {
                for (uint8 i = 0; i < MAX_AVATAR_LOCS; i++)
                {
                    uint32 m_uiSummonEntry = 0;
                    // 10% chance to summon a bloodkeeper
                    if (roll_chance_i(10))
                        m_uiSummonEntry = NPC_BLOODKEEPER;
                    else
                        m_uiSummonEntry = NPC_HAKKARI_MINION;

                    if (Creature* pTemp = pShade->SummonCreature(m_uiSummonEntry, sHakkariSummonLocations[i].m_fX, sHakkariSummonLocations[i].m_fY, sHakkariSummonLocations[i].m_fZ, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                        pTemp->SetRespawnDelay(DAY);
                }
                m_bIsFirstSummon = false;
                m_uiAvatarSummonTimer = 60000;
            }
            // if not, summon 1-2-3 creatures on random circles
            else
            {
                // ToDo: randomize summon spots
                uint8 uiMaxSummons = urand(1, 3);
                for (uint8 i = 0; i < uiMaxSummons; i++)
                {
                    uint32 m_uiSummonEntry = 0;
                    // 10% chance to summon a bloodkeeper
                    if (roll_chance_i(10))
                        m_uiSummonEntry = NPC_BLOODKEEPER;
                    else
                        m_uiSummonEntry = NPC_HAKKARI_MINION;

                    if (Creature* pTemp = pShade->SummonCreature(m_uiSummonEntry, sHakkariSummonLocations[i].m_fX, sHakkariSummonLocations[i].m_fY, sHakkariSummonLocations[i].m_fZ, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
                        pTemp->SetRespawnDelay(DAY);
                }
                m_uiAvatarSummonTimer = urand(5000, 10000);
            }
        }
        else
            m_uiAvatarSummonTimer -= uiDiff;
    }

    if (m_uiSuppressorTimer)
    {
        if (m_uiSuppressorTimer < uiDiff)
        {
            Creature* pShade = instance->GetCreature(m_uiShadeGUID);
            if (!pShade)
                return;

            uint8 uiSummonLoc = urand(0, 1);

            if (Creature* pTemp = pShade->SummonCreature(NPC_SUPPRESSOR, sHakkariDoorLocations[uiSummonLoc].m_fX, sHakkariDoorLocations[uiSummonLoc].m_fY, sHakkariDoorLocations[uiSummonLoc].m_fZ, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
            {
                DoScriptText(SAY_SUPPRESSOR_WARN, pTemp);
                pTemp->CastSpell(pTemp, SPELL_SUMMONED, true);
                pTemp->GetMotionMaster()->MovePoint(0, pShade->GetPositionX(), pShade->GetPositionY(), pShade->GetPositionZ());
                pTemp->SetRespawnDelay(DAY);
            }

            // don't summon another
            m_uiSuppressorTimer = 0;
        }
        else
            m_uiSuppressorTimer -= uiDiff;
    }
}

InstanceData* GetInstanceData_instance_sunken_temple(Map* pMap)
{
    return new instance_sunken_temple(pMap);
}

void AddSC_instance_sunken_temple()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_sunken_temple";
    pNewScript->GetInstanceData = &GetInstanceData_instance_sunken_temple;
    pNewScript->RegisterSelf();
}
