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
SDName: Mulgore
SD%Complete: 100
SDComment: Quest support: 772, Skorn Whitecloud: Just a story if not rewarded for quest
SDCategory: Mulgore
EndScriptData */

/* ContentData
npc_plains_vision
npc_skorn_whitecloud
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*#####
# npc_plains_vision
######*/

struct MANGOS_DLL_DECL npc_plains_visionAI : public npc_escortAI
{
    npc_plains_visionAI(Creature* pCreature) : npc_escortAI(pCreature) {Reset();}

    void Reset() {Start();}

    void WaypointReached(uint32 uiPointId)
    {
        if (uiPointId == 49)
        {
            m_creature->SetDeathState(JUST_DIED);
            m_creature->RemoveCorpse();
        }
    }
};

/*######
# npc_skorn_whitecloud
######*/

bool GossipHello_npc_skorn_whitecloud(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (!pPlayer->GetQuestRewardStatus(770))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tell me a story, Skorn.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(522, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_skorn_whitecloud(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
        pPlayer->SEND_GOSSIP_MENU(523, pCreature->GetObjectGuid());

    return true;
}

CreatureAI* GetAI_npc_plains_vision(Creature* pCreature)
{
    return new npc_plains_visionAI(pCreature);
}

void AddSC_mulgore()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_plains_vision";
    pNewScript->GetAI = &GetAI_npc_plains_vision;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_skorn_whitecloud";
    pNewScript->pGossipHello = &GossipHello_npc_skorn_whitecloud;
    pNewScript->pGossipSelect = &GossipSelect_npc_skorn_whitecloud;
    pNewScript->RegisterSelf();
}
