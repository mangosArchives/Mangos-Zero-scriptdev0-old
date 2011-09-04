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
SDName: Orgrimmar
SD%Complete: 100
SDComment: Quest support: 2460, 4941, 5727, 6566
SDCategory: Orgrimmar
EndScriptData */

/* ContentData
npc_neeru_fireblade
npc_shenthul
npc_thrall_warchief
npc_eitrigg
EndContentData */

#include "precompiled.h"

/*######
## npc_neeru_fireblade
######*/

enum
{
    ITEM_INSIGNIA           = 14544,
    QUEST_HIDDEN_ENEMIES    = 5727,

    GOSSIP_MENU_1           = 4513,
    GOSSIP_MENU_2           = 4533,
    GOSSIP_MENU_3           = 4534,
    GOSSIP_MENU_4           = 4535,
    GOSSIP_MENU_5           = 4536,

    GOSSIP_ITEM_1           = -3001000,
    GOSSIP_ITEM_2           = -3001001,
    GOSSIP_ITEM_3           = -3001002,
    GOSSIP_ITEM_4           = -3001003
};

bool GossipHello_npc_neeru_fireblade(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_HIDDEN_ENEMIES) == QUEST_STATUS_INCOMPLETE && pPlayer->HasItemCount(ITEM_INSIGNIA,1))
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_1, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_neeru_fireblade(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_2, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_3, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_4, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_MENU_5, pCreature->GetObjectGuid());
            if (pPlayer->GetQuestStatus(QUEST_HIDDEN_ENEMIES) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(QUEST_HIDDEN_ENEMIES);
            break;
    }
    return true;
}

/*######
## npc_shenthul
######*/

enum
{
    QUEST_SHATTERED_SALUTE   = 2460
};

struct MANGOS_DLL_DECL npc_shenthulAI : public ScriptedAI
{
    npc_shenthulAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    bool m_bCanTalk;
    bool m_bCanEmote;
    uint32 m_uiSaluteTimer;
    uint32 m_uiResetTimer;
    ObjectGuid m_playerGuid;

    void Reset()
    {
        m_bCanTalk = false;
        m_bCanEmote = false;
        m_uiSaluteTimer = 6000;
        m_uiResetTimer = 0;
        m_playerGuid.Clear();
    }

    void ReceiveEmote(Player* pPlayer, uint32 uiEmote)
    {
        if (m_bCanEmote && uiEmote == TEXTEMOTE_SALUTE && pPlayer->GetQuestStatus(QUEST_SHATTERED_SALUTE) == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->AreaExploredOrEventHappens(QUEST_SHATTERED_SALUTE);
            Reset();
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bCanEmote)
        {
            if (m_uiResetTimer < uiDiff)
            {
                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
                {
                    if (pPlayer->GetTypeId() == TYPEID_PLAYER && pPlayer->GetQuestStatus(QUEST_SHATTERED_SALUTE) == QUEST_STATUS_INCOMPLETE)
                        pPlayer->FailQuest(QUEST_SHATTERED_SALUTE);
                }
                Reset();
            }
            else m_uiResetTimer -= uiDiff;
        }

        if (m_bCanTalk && !m_bCanEmote)
        {
            if (m_uiSaluteTimer < uiDiff)
            {
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                m_bCanEmote = true;
                m_uiResetTimer = 60000;
            }
            else m_uiSaluteTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_shenthul(Creature* pCreature)
{
    return new npc_shenthulAI(pCreature);
}

bool QuestAccept_npc_shenthul(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    npc_shenthulAI* pShenthulAI = dynamic_cast<npc_shenthulAI*>(pCreature->AI());
    if (pShenthulAI && pQuest->GetQuestId() == QUEST_SHATTERED_SALUTE)
    {
        pShenthulAI->m_bCanTalk = true;
        pShenthulAI->m_playerGuid = pPlayer->GetObjectGuid();
    }

    return true;
}

/*######
## npc_thrall_warchief
######*/

enum
{
    QUEST_WHAT_THE_WIND_CARRIES  = 6566,

    SPELL_CHAIN_LIGHTNING        = 16033,
    SPELL_SHOCK                  = 16034,

    THRALL_GOSSIP_ITEM_1         = -3001004,
    THRALL_GOSSIP_ITEM_2         = -3001005,
    THRALL_GOSSIP_ITEM_3         = -3001006,
    THRALL_GOSSIP_ITEM_4         = -3001007,
    THRALL_GOSSIP_ITEM_5         = -3001008,
    THRALL_GOSSIP_ITEM_6         = -3001009,
    THRALL_GOSSIP_ITEM_7         = -3001010,
};

struct MANGOS_DLL_DECL npc_thrall_warchiefAI : public ScriptedAI
{
    npc_thrall_warchiefAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiChainLightningTimer;
    uint32 m_uiShockTimer;

    void Reset()
    {
        m_uiChainLightningTimer = 2000;
        m_uiShockTimer = 8000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiChainLightningTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(),SPELL_CHAIN_LIGHTNING) == CAST_OK)
                m_uiChainLightningTimer = 9000;
        }
        else m_uiChainLightningTimer -= uiDiff;

        if (m_uiShockTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(),SPELL_SHOCK) == CAST_OK)
                m_uiShockTimer = 15000;
        }
        else m_uiShockTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_npc_thrall_warchief(Creature* pCreature)
{
    return new npc_thrall_warchiefAI(pCreature);
}

bool GossipHello_npc_thrall_warchief(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_WHAT_THE_WIND_CARRIES) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(4477, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_thrall_warchief(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(5733, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(5734, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(5735, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(5736, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(5737, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            pPlayer->SEND_GOSSIP_MENU(5738, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->CLOSE_GOSSIP_MENU();
            if (pPlayer->GetQuestStatus(QUEST_WHAT_THE_WIND_CARRIES) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(QUEST_WHAT_THE_WIND_CARRIES);
            break;
    }
    return true;
}

/*######
## npc_eitrigg
######*/

enum
{
    QUEST_EITRIGGS_WISDOM   = 4941,

    EITRIGG_GOSSIP_ITEM_1   = -3001011,
    EITRIGG_GOSSIP_ITEM_2   = -3001012,
    EITRIGG_GOSSIP_ITEM_3   = -3001013,
    EITRIGG_GOSSIP_ITEM_4   = -3001014,
    EITRIGG_GOSSIP_ITEM_5   = -3001015,
    EITRIGG_GOSSIP_ITEM_6   = -3001016,
    EITRIGG_GOSSIP_ITEM_7   = -3001017,
    EITRIGG_GOSSIP_ITEM_8   = -3001018,
};

bool GossipHello_npc_eitrigg(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_EITRIGGS_WISDOM) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, THRALL_GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(3573, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_eitrigg(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(3574, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
            pPlayer->SEND_GOSSIP_MENU(3575, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+4);
            pPlayer->SEND_GOSSIP_MENU(3576, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+5);
            pPlayer->SEND_GOSSIP_MENU(3577, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+6);
            pPlayer->SEND_GOSSIP_MENU(3578, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+7);
            pPlayer->SEND_GOSSIP_MENU(3579, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, EITRIGG_GOSSIP_ITEM_8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+8);
            pPlayer->SEND_GOSSIP_MENU(3580, pCreature->GetObjectGuid());
            if (pPlayer->GetQuestStatus(QUEST_EITRIGGS_WISDOM) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(QUEST_EITRIGGS_WISDOM);
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
    return true;
}

void AddSC_orgrimmar()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_neeru_fireblade";
    pNewScript->pGossipHello = &GossipHello_npc_neeru_fireblade;
    pNewScript->pGossipSelect = &GossipSelect_npc_neeru_fireblade;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_shenthul";
    pNewScript->GetAI = &GetAI_npc_shenthul;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_shenthul;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_thrall_warchief";
    pNewScript->GetAI = &GetAI_npc_thrall_warchief;
    pNewScript->pGossipHello = &GossipHello_npc_thrall_warchief;
    pNewScript->pGossipSelect = &GossipSelect_npc_thrall_warchief;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_eitrigg";
    pNewScript->pGossipHello = &GossipHello_npc_eitrigg;
    pNewScript->pGossipSelect = &GossipSelect_npc_eitrigg;
    pNewScript->RegisterSelf();

}
