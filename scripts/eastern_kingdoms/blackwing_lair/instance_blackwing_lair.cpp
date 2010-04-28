/* Copyright (C) 2009 - 2010 ScriptDevZero <http://github.com/scriptdevzero/scriptdevzero> 
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
SDName: Instance_Blackwing_Lair
SD%Complete: 90
SDComment:
SDCategory: Blackwing Lair
EndScriptData */

#include "precompiled.h"
#include "blackwing_lair.h"

enum
{
    MAX_ENCOUNTER           = 5,

    NPC_RAZORGORE           =12435,
	NPC_VAELASTRASZ         =13020,
	NPC_BROODLORD           =12017,
	NPC_FIREMAW             =11983,
	NPC_EBONROC             =14601,
	NPC_FLAMEGOR            =11981,
	NPC_CHROMAGGUS          =14020,
	NPC_NEFARIAN            =11583, 

    GO_PORTCULLIS_RAZORGORE       = 176965,                        //Door after Razorgore
    GO_PORTCULLIS_VAELASTRASZ     = 179364,                        //Door after Vaelastrasz
    GO_PORTCULLIS_BROODLORD       = 179365,                        //Door after Broodlord
	GO_PORTCULLIS_CHROMAGGUS      = 179116,                        //Door before Chromaggus
    GO_PORTCULLIS_NEFARIAN        = 179117                         //Door before Nefarian
};

struct MANGOS_DLL_DECL instance_blackwing_lair : public ScriptedInstance
{
    instance_blackwing_lair(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint32 m_auiEncounter[MAX_ENCOUNTER];
    std::string strInstData;

    uint64 m_uiRazorgoreGUID;
	uint64 m_uiVaelastraszGUID;
	uint64 m_uiBroodlordGUID;
	uint64 m_uiFiremawGUID;
	uint64 m_uiEbonrocGUID;
	uint64 m_uiFlamegorGUID;
	uint64 m_uiChromaggusGUID;
	uint64 m_uiNefarianGUID;

    uint64 m_uiPortcullisRazorgoreGUID;
    uint64 m_uiPortcullisVaelastraszGUID;
    uint64 m_uiPortcullisBroodlordGUID;
	uint64 m_uiPortcullisChromaggusGUID;
	uint64 m_uiPortcullisNefarianGUID;


    void Initialize()
    {

         memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

         m_uiRazorgoreGUID        = 0;
	     m_uiVaelastraszGUID      = 0;
	     m_uiBroodlordGUID        = 0;
	     m_uiFiremawGUID          = 0;
	     m_uiEbonrocGUID          = 0;
	     m_uiFlamegorGUID         = 0;
	     m_uiChromaggusGUID       = 0;
	     m_uiNefarianGUID         = 0;

         m_uiPortcullisRazorgoreGUID     = 0;
         m_uiPortcullisVaelastraszGUID   = 0;
         m_uiPortcullisBroodlordGUID     = 0;
         m_uiPortcullisChromaggusGUID    = 0;
         m_uiPortcullisNefarianGUID      = 0;

    }

	void OnCreatureCreate(Creature* pCreature)
    {
        switch(pCreature->GetEntry())
        {
			
			case NPC_RAZORGORE:   m_uiRazorgoreGUID   = pCreature->GetGUID(); break;
            case NPC_VAELASTRASZ: m_uiVaelastraszGUID = pCreature->GetGUID(); break;
			case NPC_BROODLORD:   m_uiBroodlordGUID   = pCreature->GetGUID(); break;
			case NPC_FIREMAW:     m_uiFiremawGUID     = pCreature->GetGUID(); break;
			case NPC_EBONROC:     m_uiEbonrocGUID     = pCreature->GetGUID(); break;
			case NPC_FLAMEGOR:    m_uiFlamegorGUID    = pCreature->GetGUID(); break;
			case NPC_CHROMAGGUS:  m_uiChromaggusGUID  = pCreature->GetGUID(); break;
			case NPC_NEFARIAN:    m_uiNefarianGUID    = pCreature->GetGUID(); break;
			
        }
    }
	

    void OnObjectCreate(GameObject* pGo)
    {
        switch(pGo->GetEntry())
        {

            case GO_PORTCULLIS_RAZORGORE:
			    m_uiPortcullisRazorgoreGUID = pGo->GetGUID();
				if (m_auiEncounter[1] == DONE)
				pGo->SetGoState(GO_STATE_ACTIVE);
				break;
				
			case GO_PORTCULLIS_VAELASTRASZ:
				m_uiPortcullisVaelastraszGUID = pGo->GetGUID();
			    if (m_auiEncounter[2] == DONE)
				pGo->SetGoState(GO_STATE_ACTIVE);
				break;

			case GO_PORTCULLIS_BROODLORD:
				m_uiPortcullisBroodlordGUID = pGo->GetGUID();
			    if (m_auiEncounter[3] == DONE)
				pGo->SetGoState(GO_STATE_ACTIVE);
				break;

			case GO_PORTCULLIS_CHROMAGGUS:
				m_uiPortcullisChromaggusGUID = pGo->GetGUID();
			    if (m_auiEncounter[4] == DONE)
				pGo->SetGoState(GO_STATE_ACTIVE);
				break;

			case GO_PORTCULLIS_NEFARIAN:
				m_uiPortcullisNefarianGUID = pGo->GetGUID();
			    if (m_auiEncounter[5] == DONE)
				pGo->SetGoState(GO_STATE_ACTIVE);
				break;
        }
    }

    void SetData(uint32 uiType, uint32 uiData)
    {
        switch(uiType)
        {
            case TYPE_RAZORGORE:
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiPortcullisRazorgoreGUID);
                m_auiEncounter[1] = uiData;
                break;

            case TYPE_VAELASTRASZ:
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiPortcullisVaelastraszGUID);
                m_auiEncounter[2] = uiData;
                break;

			case TYPE_BROODLORD:
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiPortcullisBroodlordGUID);
                m_auiEncounter[3] = uiData;
                break;

			case TYPE_FLAMEGOR:
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiPortcullisChromaggusGUID);
                m_auiEncounter[4] = uiData;
                break;

			case TYPE_CHROMAGGUS:
                if (uiData == DONE)
                    DoUseDoorOrButton(m_uiPortcullisNefarianGUID);
                m_auiEncounter[5] = uiData;
                break;
        }

        if (uiData == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3] << " " << m_auiEncounter[4]
                 << " " << m_auiEncounter[5];

            strInstData = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }
    }

    uint32 GetData(uint32 uiType)
    {
        switch(uiType)
        {
            case TYPE_RAZORGORE:
                return m_auiEncounter[1];
            case TYPE_VAELASTRASZ:
                return m_auiEncounter[2];
            case TYPE_BROODLORD:
                return m_auiEncounter[3];
            case TYPE_FLAMEGOR:
                return m_auiEncounter[4];
            case TYPE_CHROMAGGUS:
                return m_auiEncounter[5];
        }
        return 0;
    }

    const char* Save()
    {
        return strInstData.c_str();
    }

    void Load(const char* chrIn)
    {
        if (!chrIn)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(chrIn);

        std::istringstream loadStream(chrIn);
        loadStream >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3] >> m_auiEncounter[4] 
            >> m_auiEncounter[5];

        for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        {
            if (m_auiEncounter[i] == IN_PROGRESS)
                m_auiEncounter[i] = NOT_STARTED;
        }

        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_blackwing_lair(Map* pMap)
{
    return new instance_blackwing_lair(pMap);
}

void AddSC_instance_blackwing_lair()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_blackwing_lair";
    newscript->GetInstanceData = &GetInstanceData_instance_blackwing_lair;
    newscript->RegisterSelf();
}
