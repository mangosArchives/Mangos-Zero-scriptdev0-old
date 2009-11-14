/* 
 * Scripted for --> Mangos-Zero Special Thanks for VladimirMangos, Yehonal, Theluda, Drkotas, Shin, Wrath Team.
 * Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Instance_Wailing_Caverns
SD%Complete: 0
SDComment: Placeholder
SDCategory: Wailing Caverns
EndScriptData */

#include "precompiled.h"
#include "def_wailing_caverns.h"

struct MANGOS_DLL_DECL instance_wailing_caverns : public ScriptedInstance
{
    instance_wailing_caverns(Map* pMap) : ScriptedInstance(pMap) {Initialize();}

    uint32 m_auiEncounter[MAX_ENCOUNTER];

    uint64 m_uiNaralexGUID;

    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        m_uiNaralexGUID = 0;
    }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch (pCreature->GetEntry())
        {
            case 3679: m_uiNaralexGUID = pCreature->GetGUID(); break;
        }
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_ANACONDRA:
                m_auiEncounter[0] = uiData;
                break;
			case TYPE_COBRAHN:
				m_auiEncounter[1] = uiData;
				break;
			case TYPE_PYTHAS:
				m_auiEncounter[2] = uiData;
				break;
			case TYPE_SERPENTIS:
				m_auiEncounter[3] = uiData;
				break;
			case TYPE_DISCIPLE:
				m_auiEncounter[4] = uiData;
				break;
            case TYPE_MUTANOUS:
                m_auiEncounter[5] = uiData;
                break;
			default:
                error_log("SD2: Instance Wiling Caverns: ERROR SetData = %u for type %u does not exist/not implemented.",uiType,uiData);
				break;
        }
		if (m_auiEncounter[0] == DONE && m_auiEncounter[1] == DONE && m_auiEncounter[2] == DONE && m_auiEncounter[3] == DONE && m_auiEncounter[4] == NOT_STARTED)
		{
			error_log("Debug:Wailing Caverns encounters done");
			SetData(TYPE_DISCIPLE,SPECIAL);
		}
    }

    uint32 GetData(uint32 uiType)
    {
		switch (uiType)
		{
			case TYPE_ANACONDRA:		return m_auiEncounter[0]; break;
			case TYPE_COBRAHN:			return m_auiEncounter[1]; break;
			case TYPE_PYTHAS:			return m_auiEncounter[2]; break;
			case TYPE_SERPENTIS:		return m_auiEncounter[3]; break;
			case TYPE_DISCIPLE:			return m_auiEncounter[4]; break;
            case TYPE_MUTANOUS:         return m_auiEncounter[5]; break;
		}
        return 0;
    }

    uint64 GetData64(uint32 uiData)
    {
        switch (uiData)
        {
            case DATA_NARALEX: return m_uiNaralexGUID;
        }
        return 0;
    }
};

InstanceData* GetInstanceData_instance_wailing_caverns(Map* pMap)
{
    return new instance_wailing_caverns(pMap);
}

void AddSC_instance_wailing_caverns()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_wailing_caverns";
    newscript->GetInstanceData = &GetInstanceData_instance_wailing_caverns;
    newscript->RegisterSelf();
}
