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
SDName: Instance_Naxxramas
SD%Complete: 90%
SDComment:
SDCategory: Naxxramas
EndScriptData */

#include "precompiled.h"
#include "naxxramas.h"

instance_naxxramas::instance_naxxramas(Map* pMap) : ScriptedInstance(pMap),
    m_uiAracEyeRampGUID(0),
    m_uiPlagEyeRampGUID(0),
    m_uiMiliEyeRampGUID(0),
    m_uiConsEyeRampGUID(0),

    m_uiAracPortalGUID(0),
    m_uiPlagPortalGUID(0),
    m_uiMiliPortalGUID(0),
    m_uiConsPortalGUID(0),

    m_uiAnubRekhanGUID(0),
    m_uiFaerlinanGUID(0),

    m_uiZeliekGUID(0),
    m_uiThaneGUID(0),
    m_uiBlaumeuxGUID(0),
    m_uiMograineGUID(0),

    m_uiThaddiusGUID(0),
    m_uiStalaggGUID(0),
    m_uiFeugenGUID(0),

    m_uiKelthuzadGUID(0),

    m_uiPathExitDoorGUID(0),
    m_uiGlutExitDoorGUID(0),
    m_uiThadDoorGUID(0),
    m_uiThadNoxTeslaFeugenGUID(0),
    m_uiThadNoxTeslaStalaggGUID(0),

    m_uiAnubDoorGUID(0),
    m_uiAnubGateGUID(0),
    m_uiFaerDoorGUID(0),
    m_uiFaerWebGUID(0),
    m_uiMaexOuterGUID(0),
    m_uiMaexInnerGUID(0),

    m_uiGothikGUID(0),
    m_uiGothCombatGateGUID(0),
    m_uiGothikEntryDoorGUID(0),
    m_uiGothikExitDoorGUID(0),
    m_uiHorsemenDoorGUID(0),
    m_uiHorsemenChestGUID(0),

    m_uiNothEntryDoorGUID(0),
    m_uiNothExitDoorGUID(0),
    m_uiHeigEntryDoorGUID(0),
    m_uiHeigExitDoorGUID(0),
    m_uiLoathebDoorGUID(0),

    m_uiKelthuzadDoorGUID(0),
    m_uiKelthuzadExitDoorGUID(0),

    m_fChamberCenterX(0.0f),
    m_fChamberCenterY(0.0f),
    m_fChamberCenterZ(0.0f)
{
    Initialize();
}

void instance_naxxramas::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_naxxramas::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_ANUB_REKHAN:       m_uiAnubRekhanGUID = pCreature->GetObjectGuid();  break;
        case NPC_FAERLINA:          m_uiFaerlinanGUID = pCreature->GetObjectGuid();   break;
        case NPC_THADDIUS:          m_uiThaddiusGUID = pCreature->GetObjectGuid();    break;
        case NPC_STALAGG:           m_uiStalaggGUID = pCreature->GetObjectGuid();     break;
        case NPC_FEUGEN:            m_uiFeugenGUID = pCreature->GetObjectGuid();      break;
        case NPC_ZELIEK:            m_uiZeliekGUID = pCreature->GetObjectGuid();      break;
        case NPC_THANE:             m_uiThaneGUID = pCreature->GetObjectGuid();       break;
        case NPC_BLAUMEUX:          m_uiBlaumeuxGUID = pCreature->GetObjectGuid();    break;
        case NPC_MOGRAINE:          m_uiMograineGUID = pCreature->GetObjectGuid();   break;
        case NPC_GOTHIK:            m_uiGothikGUID = pCreature->GetObjectGuid();      break;
        case NPC_KELTHUZAD:         m_uiKelthuzadGUID = pCreature->GetObjectGuid();   break;
        case NPC_SUB_BOSS_TRIGGER:  m_lGothTriggerList.push_back(pCreature->GetObjectGuid()); break;
        case NPC_TESLA_COIL:        m_lThadTeslaCoilList.push_back(pCreature->GetObjectGuid()); break;

        case NPC_NAXXRAMAS_FOLLOWER:
        case NPC_NAXXRAMAS_WORSHIPPER:
            m_lFaerlinaAddGUIDs.push_back(pCreature->GetObjectGuid());
            break;
    }
}

void instance_naxxramas::OnObjectCreate(GameObject* pGo)
{
    switch(pGo->GetEntry())
    {
        case GO_ARAC_ANUB_DOOR:
            m_uiAnubDoorGUID = pGo->GetObjectGuid();
            break;
        case GO_ARAC_ANUB_GATE:
            m_uiAnubGateGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_ANUB_REKHAN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ARAC_FAER_WEB:
            m_uiFaerWebGUID = pGo->GetObjectGuid();
            break;
        case GO_ARAC_FAER_DOOR:
            m_uiFaerDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_FAERLINA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ARAC_MAEX_INNER_DOOR:
            m_uiMaexInnerGUID = pGo->GetObjectGuid();
            break;
        case GO_ARAC_MAEX_OUTER_DOOR:
            m_uiMaexOuterGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_FAERLINA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_PLAG_NOTH_ENTRY_DOOR:
            m_uiNothEntryDoorGUID = pGo->GetObjectGuid();
            break;
        case GO_PLAG_NOTH_EXIT_DOOR:
            m_uiNothExitDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_NOTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_HEIG_ENTRY_DOOR:
            m_uiHeigEntryDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_NOTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_HEIG_EXIT_DOOR:
            m_uiHeigExitDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_HEIGAN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_LOAT_DOOR:
            m_uiLoathebDoorGUID = pGo->GetObjectGuid();
            break;

        case GO_MILI_GOTH_ENTRY_GATE:
            m_uiGothikEntryDoorGUID = pGo->GetObjectGuid();
            break;
        case GO_MILI_GOTH_EXIT_GATE:
            m_uiGothikExitDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_GOTHIK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_MILI_GOTH_COMBAT_GATE:
            m_uiGothCombatGateGUID = pGo->GetObjectGuid();
            break;
        case GO_MILI_HORSEMEN_DOOR:
            m_uiHorsemenDoorGUID  = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_GOTHIK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_CHEST_HORSEMEN:
            m_uiHorsemenChestGUID = pGo->GetObjectGuid();
            break;

        case GO_CONS_PATH_EXIT_DOOR:
            m_uiPathExitDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_PATCHWERK] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_GLUT_EXIT_DOOR:
            m_uiGlutExitDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_GLUTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_THAD_DOOR:
            m_uiThadDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_GLUTH] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_NOX_TESLA_FEUGEN:
            m_uiThadNoxTeslaFeugenGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_THADDIUS] == DONE)
                pGo->SetGoState(GO_STATE_READY);
            break;
        case GO_CONS_NOX_TESLA_STALAGG:
            m_uiThadNoxTeslaStalaggGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_THADDIUS] == DONE)
                pGo->SetGoState(GO_STATE_READY);
            break;

        case GO_KELTHUZAD_WATERFALL_DOOR:
            m_uiKelthuzadDoorGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_SAPPHIRON] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_KELTHUZAD_EXIT_DOOR:
            m_uiKelthuzadExitDoorGUID = pGo->GetObjectGuid();
            break;

        case GO_ARAC_EYE_RAMP:
            m_uiAracEyeRampGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_MAEXXNA] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_PLAG_EYE_RAMP:
            m_uiPlagEyeRampGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_LOATHEB] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_MILI_EYE_RAMP:
            m_uiMiliEyeRampGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_FOUR_HORSEMEN] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_CONS_EYE_RAMP:
            m_uiConsEyeRampGUID = pGo->GetObjectGuid();
            if (m_auiEncounter[TYPE_THADDIUS] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;

        case GO_ARAC_PORTAL:
            m_uiAracPortalGUID = pGo->GetObjectGuid();
            break;
        case GO_PLAG_PORTAL:
            m_uiPlagPortalGUID = pGo->GetObjectGuid();
            break;
        case GO_MILI_PORTAL:
            m_uiMiliPortalGUID = pGo->GetObjectGuid();
            break;
        case GO_CONS_PORTAL:
            m_uiConsPortalGUID = pGo->GetObjectGuid();
            break;
    }
}

bool instance_naxxramas::IsEncounterInProgress() const
{
    for (uint8 i = 0; i < TYPE_KELTHUZAD; ++i)
        if (m_auiEncounter[i] == IN_PROGRESS || m_auiEncounter[i] == SPECIAL)
            return true;

    return false;
}

void instance_naxxramas::SetData(uint32 uiType, uint32 uiData)
{
    switch(uiType)
    {
        case TYPE_ANUB_REKHAN:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiAnubDoorGUID);
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiAnubGateGUID);
            break;
        case TYPE_FAERLINA:
            DoUseDoorOrButton(m_uiFaerWebGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiFaerDoorGUID);
                DoUseDoorOrButton(m_uiMaexOuterGUID);
            }
            if (uiData == FAIL)
            {
                for (GUIDList::const_iterator itr = m_lFaerlinaAddGUIDs.begin(); itr != m_lFaerlinaAddGUIDs.end(); ++itr)
                {
                    Creature* pAdd = instance->GetCreature(*itr);
                    if (pAdd && !pAdd->isAlive())
                        pAdd->Respawn();
                }
            }
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_MAEXXNA:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiMaexInnerGUID, uiData);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiAracEyeRampGUID);
                DoRespawnGameObject(m_uiAracPortalGUID, 30*MINUTE);
                DoTaunt();
            }
            break;
        case TYPE_NOTH:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiNothEntryDoorGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiNothExitDoorGUID);
                DoUseDoorOrButton(m_uiHeigEntryDoorGUID);
            }
            break;
        case TYPE_HEIGAN:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiHeigEntryDoorGUID);
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiHeigExitDoorGUID);
            break;
        case TYPE_LOATHEB:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiLoathebDoorGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiPlagEyeRampGUID);
                DoRespawnGameObject(m_uiPlagPortalGUID, 30*MINUTE);
                DoTaunt();
            }
            break;
        case TYPE_RAZUVIOUS:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_GOTHIK:
            switch(uiData)
            {
                case IN_PROGRESS:
                    DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
                    DoUseDoorOrButton(m_uiGothCombatGateGUID);
                    break;
                case SPECIAL:
                    DoUseDoorOrButton(m_uiGothCombatGateGUID);
                    break;
                case FAIL:
                    if (m_auiEncounter[uiType] == IN_PROGRESS)
                        DoUseDoorOrButton(m_uiGothCombatGateGUID);

                    DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
                    break;
                case DONE:
                    DoUseDoorOrButton(m_uiGothikEntryDoorGUID);
                    DoUseDoorOrButton(m_uiGothikExitDoorGUID);
                    DoUseDoorOrButton(m_uiHorsemenDoorGUID);
                    break;
            }
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_FOUR_HORSEMEN:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiHorsemenDoorGUID);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiMiliEyeRampGUID);
                DoRespawnGameObject(m_uiMiliPortalGUID, 30*MINUTE);
                DoRespawnGameObject(m_uiHorsemenChestGUID, 30*MINUTE);
                DoTaunt();
            }
            break;
        case TYPE_PATCHWERK:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiPathExitDoorGUID);
            break;
        case TYPE_GROBBULUS:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_GLUTH:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiGlutExitDoorGUID);
                DoUseDoorOrButton(m_uiThadDoorGUID);
            }
            break;
        case TYPE_THADDIUS:
            // Only process real changes here
            if (m_auiEncounter[uiType] == uiData)
                return;

            m_auiEncounter[uiType] = uiData;
            if (uiData != SPECIAL)
                DoUseDoorOrButton(m_uiThadDoorGUID, uiData);
            if (uiData == DONE)
            {
                DoUseDoorOrButton(m_uiConsEyeRampGUID);
                DoRespawnGameObject(m_uiConsPortalGUID, 30*MINUTE);
                DoTaunt();
            }
            break;
        case TYPE_SAPPHIRON:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
                DoUseDoorOrButton(m_uiKelthuzadDoorGUID);
            break;
        case TYPE_KELTHUZAD:
            m_auiEncounter[uiType] = uiData;
            DoUseDoorOrButton(m_uiKelthuzadExitDoorGUID);
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
            << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5] << " "
            << m_auiEncounter[6] << " " << m_auiEncounter[7] << " " << m_auiEncounter[8] << " "
            << m_auiEncounter[9] << " " << m_auiEncounter[10] << " " << m_auiEncounter[11] << " "
            << m_auiEncounter[12] << " " << m_auiEncounter[13] << " " << m_auiEncounter[14] << " " << m_auiEncounter[15];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_naxxramas::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
        >> m_auiEncounter[4] >> m_auiEncounter[5] >> m_auiEncounter[6] >> m_auiEncounter[7]
        >> m_auiEncounter[8] >> m_auiEncounter[9] >> m_auiEncounter[10] >> m_auiEncounter[11]
        >> m_auiEncounter[12] >> m_auiEncounter[13] >> m_auiEncounter[14] >> m_auiEncounter[15];

    for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
    {
        if (m_auiEncounter[i] == IN_PROGRESS)
            m_auiEncounter[i] = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_naxxramas::GetData(uint32 uiType)
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

uint64 instance_naxxramas::GetData64(uint32 uiData)
{
    switch(uiData)
    {
        case NPC_ANUB_REKHAN:           return m_uiAnubRekhanGUID;
        case NPC_FAERLINA:              return m_uiFaerlinanGUID;
        case GO_MILI_GOTH_COMBAT_GATE:  return m_uiGothCombatGateGUID;
        case NPC_ZELIEK:                return m_uiZeliekGUID;
        case NPC_THANE:                 return m_uiThaneGUID;
        case NPC_BLAUMEUX:              return m_uiBlaumeuxGUID;
        case NPC_MOGRAINE:              return m_uiMograineGUID;
        case NPC_THADDIUS:              return m_uiThaddiusGUID;
        case NPC_STALAGG:               return m_uiStalaggGUID;
        case NPC_FEUGEN:                return m_uiFeugenGUID;
        case GO_CONS_NOX_TESLA_FEUGEN:  return m_uiThadNoxTeslaFeugenGUID;
        case GO_CONS_NOX_TESLA_STALAGG: return m_uiThadNoxTeslaStalaggGUID;
        case NPC_GOTHIK:                return m_uiGothikGUID;
        case NPC_KELTHUZAD:             return m_uiKelthuzadGUID;
        default:
            return 0;
    }
}

void instance_naxxramas::SetGothTriggers()
{
    Creature* pGoth = instance->GetCreature(m_uiGothikGUID);

    if (!pGoth)
        return;

    for(GUIDList::iterator itr = m_lGothTriggerList.begin(); itr != m_lGothTriggerList.end(); ++itr)
    {
        if (Creature* pTrigger = instance->GetCreature(*itr))
        {
            GothTrigger pGt;
            pGt.bIsAnchorHigh = (pTrigger->GetPositionZ() >= (pGoth->GetPositionZ() - 5.0f));
            pGt.bIsRightSide = IsInRightSideGothArea(pTrigger);

            m_mGothTriggerMap[pTrigger->GetObjectGuid()] = pGt;
        }
    }
}

Creature* instance_naxxramas::GetClosestAnchorForGoth(Creature* pSource, bool bRightSide)
{
    std::list<Creature* > lList;

    for (UNORDERED_MAP<uint64, GothTrigger>::iterator itr = m_mGothTriggerMap.begin(); itr != m_mGothTriggerMap.end(); ++itr)
    {
        if (!itr->second.bIsAnchorHigh)
            continue;

        if (itr->second.bIsRightSide != bRightSide)
            continue;

        if (Creature* pCreature = instance->GetCreature(itr->first))
            lList.push_back(pCreature);
    }

    if (!lList.empty())
    {
        lList.sort(ObjectDistanceOrder(pSource));
        return lList.front();
    }

    return NULL;
}

void instance_naxxramas::GetGothSummonPointCreatures(std::list<Creature*> &lList, bool bRightSide)
{
    for (UNORDERED_MAP<uint64, GothTrigger>::iterator itr = m_mGothTriggerMap.begin(); itr != m_mGothTriggerMap.end(); ++itr)
    {
        if (itr->second.bIsAnchorHigh)
            continue;

        if (itr->second.bIsRightSide != bRightSide)
            continue;

        if (Creature* pCreature = instance->GetCreature(itr->first))
            lList.push_back(pCreature);
    }
}

bool instance_naxxramas::IsInRightSideGothArea(Unit* pUnit)
{
    if (GameObject* pCombatGate = instance->GetGameObject(m_uiGothCombatGateGUID))
        return (pCombatGate->GetPositionY() >= pUnit->GetPositionY());

    error_log("SD0: left/right side check, Gothik combat area failed.");
    return true;
}

void instance_naxxramas::SetChamberCenterCoords(float fX, float fY, float fZ)
{
    m_fChamberCenterX = fX;
    m_fChamberCenterY = fY;
    m_fChamberCenterZ = fZ;
}

void instance_naxxramas::DoTaunt()
{
    Creature* pKelThuzad = instance->GetCreature(m_uiKelthuzadGUID);

    if (pKelThuzad && pKelThuzad->isAlive())
    {
        uint8 uiWingsCleared = 0;

        if (m_auiEncounter[2] == DONE)
            ++uiWingsCleared;

        if (m_auiEncounter[5] == DONE)
            ++uiWingsCleared;

        if (m_auiEncounter[8] == DONE)
            ++uiWingsCleared;

        if (m_auiEncounter[12] == DONE)
            ++uiWingsCleared;

        switch(uiWingsCleared)
        {
            case 1: DoScriptText(SAY_KELTHUZAD_TAUNT1, pKelThuzad); break;
            case 2: DoScriptText(SAY_KELTHUZAD_TAUNT2, pKelThuzad); break;
            case 3: DoScriptText(SAY_KELTHUZAD_TAUNT3, pKelThuzad); break;
            case 4: DoScriptText(SAY_KELTHUZAD_TAUNT4, pKelThuzad); break;
        }
    }
}

InstanceData* GetInstanceData_instance_naxxramas(Map* pMap)
{
    return new instance_naxxramas(pMap);
}

bool AreaTrigger_at_naxxramas(Player* pPlayer, AreaTriggerEntry const* pAt)
{
    if (pAt->id == AREATRIGGER_KELTHUZAD)
    {
        if (pPlayer->isGameMaster() || pPlayer->isDead())
            return false;

        instance_naxxramas* pInstance = (instance_naxxramas*)pPlayer->GetInstanceData();

        if (!pInstance)
            return false;

        pInstance->SetChamberCenterCoords(pAt->x, pAt->y, pAt->z);

        if (pInstance->GetData(TYPE_KELTHUZAD) == NOT_STARTED)
        {
            if (Creature* pKelthuzad = pInstance->instance->GetCreature(pInstance->GetData64(NPC_KELTHUZAD)))
            {
                if (pKelthuzad->isAlive())
                {
                    pInstance->SetData(TYPE_KELTHUZAD, IN_PROGRESS);
                    pKelthuzad->SetInCombatWithZone();
                }
            }
        }
    }

    if (pAt->id == AREATRIGGER_THADDIUS_DOOR)
    {
        if (instance_naxxramas* pInstance = (instance_naxxramas*)pPlayer->GetInstanceData())
        {
            if (pInstance->GetData(TYPE_THADDIUS) == NOT_STARTED)
            {
                if (Creature* pThaddius = pInstance->instance->GetCreature(pInstance->GetData64(NPC_THADDIUS)))
                {
                    pInstance->SetData(TYPE_THADDIUS, SPECIAL);
                    DoScriptText(SAY_THADDIUS_GREET, pThaddius);
                }
            }
        }
    }

    return false;
}

void AddSC_instance_naxxramas()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_naxxramas";
    pNewScript->GetInstanceData = &GetInstanceData_instance_naxxramas;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_naxxramas";
    pNewScript->pAreaTrigger = &AreaTrigger_at_naxxramas;
    pNewScript->RegisterSelf();
}
