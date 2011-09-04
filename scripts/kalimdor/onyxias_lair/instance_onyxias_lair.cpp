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
SDName: Instance_Onyxias_Lair
SD%Complete: 50%
SDComment:
SDCategory: Onyxia's Lair
EndScriptData */

#include "precompiled.h"
#include "onyxias_lair.h"

instance_onyxias_lair::instance_onyxias_lair(Map* pMap) : ScriptedInstance(pMap)
{
    Initialize();
}

void instance_onyxias_lair::Initialize()
{
    m_uiEncounter = NOT_STARTED;
    m_tPhaseTwoStart = time(NULL);
}

bool instance_onyxias_lair::IsEncounterInProgress() const
{
    return m_uiEncounter == IN_PROGRESS || m_uiEncounter >= DATA_LIFTOFF;
}

void instance_onyxias_lair::OnCreatureCreate(Creature* pCreature)
{
    switch(pCreature->GetEntry())
    {
        case NPC_ONYXIA_TRIGGER:
            m_mNpcEntryGuidStore[NPC_ONYXIA_TRIGGER] = pCreature->GetObjectGuid();
            break;
        case NPC_ONYXIA_WARDER:
            m_uiOnyxianWarderGuids.push_back(pCreature->GetObjectGuid());
            break;
    }
}

void instance_onyxias_lair::OnCreatureDeath(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_ONYXIA:
            if(!m_uiOnyxianWarderGuids.empty())
            {
                for (std::list<ObjectGuid>::iterator itr = m_uiOnyxianWarderGuids.begin(); itr != m_uiOnyxianWarderGuids.end(); ++itr)
                {
                    Creature* pWarder = instance->GetCreature(*itr);
                    if (pWarder)
                        pWarder->ForcedDespawn();
                }
            }
            break;
    }
}

void instance_onyxias_lair::OnCreatureEnterCombat(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_ONYXIA:
            if(!m_uiOnyxianWarderGuids.empty())
            {
                for (std::list<ObjectGuid>::iterator itr = m_uiOnyxianWarderGuids.begin(); itr != m_uiOnyxianWarderGuids.end(); ++itr)
                {
                    Creature* pWarder = instance->GetCreature(*itr);
                    if (pWarder)
                        pWarder->Respawn();
                }
            }
            break;
    }
}

void instance_onyxias_lair::SetData(uint32 uiType, uint32 uiData)
{
    if (uiType != TYPE_ONYXIA)
        return;

    m_uiEncounter = uiData;
    if (uiData == DATA_LIFTOFF)
        m_tPhaseTwoStart = time(NULL);

    // Currently no reason to save anything
}

InstanceData* GetInstanceData_instance_onyxias_lair(Map* pMap)
{
    return new instance_onyxias_lair(pMap);
}

void AddSC_instance_onyxias_lair()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "instance_onyxias_lair";
    pNewScript->GetInstanceData = &GetInstanceData_instance_onyxias_lair;
    pNewScript->RegisterSelf();
}
