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
SDName: Npc_Professions
SD%Complete: 95
SDComment: Provides learn options for Engineering and Blacksmith. Missing npc_texts for weapon spec. learning.
SDCategory: NPCs
EndScriptData */

#include "precompiled.h"

enum
{
    GOSSIP_SENDER_LEARN       = 50,
    GOSSIP_SENDER_CHECK       = 52,

    // Blacksmith
    GOSSIP_TEACH_HAMMER       = -3001019,
    GOSSIP_TEACH_AXE          = -3001020,
    GOSSIP_TEACH_SWORD        = -3001021,

    SPELL_WEAPONSMITH         = 9787,
    SPELL_LEARN_HAMMERSMITH   = 17044,
    SPELL_LEARN_AXESMITH      = 17043,
    SPELL_LEARN_SWORDSMITH    = 17042,
    SPELL_HAMMERSMITH         = 17040,
    SPELL_AXESMITH            = 17041,
    SPELL_SWORDSMITH          = 17039,
    SPELL_REP_ARMORSMITH      = 17451,
    SPELL_REP_WEAPONSMITH     = 17452,

    NPC_LILITH                = 11191,
    NPC_KILRAM                = 11192,
    NPC_SERIL                 = 11193,

    // Engineering
    GOSSIP_ITEM_ZAP           = -3001022,
    GOSSIP_ITEM_JHORDY        = -3001023,

    SPELL_GOBLIN_ENG          = 20222,
    SPELL_GNOMISH_ENG         = 20219,
    SPELL_LEARN_TO_EVERLOOK   = 23490,
    SPELL_LEARN_TO_GADGET     = 23491,
    SPELL_TO_EVERLOOK         = 23486,
    SPELL_TO_GADGET           = 23489,

    NPC_ZAP                   = 14742,
    NPC_JHORDY                = 14743,

    ITEM_GNOMISH_CARD         = 10790,
    ITEM_GOBLIN_CARD          = 10791
};

/*###
# Blacksmith
###*/

bool HasWeaponSub(Player* pPlayer)
{
    if (pPlayer->HasSpell(SPELL_HAMMERSMITH) || pPlayer->HasSpell(SPELL_AXESMITH) || pPlayer->HasSpell(SPELL_SWORDSMITH))
        return true;
    return false;
}

bool GossipHello_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
    if (pCreature->isVendor())
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if (pCreature->isTrainer())
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_TRAINER, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    uint32 eCreature = pCreature->GetEntry();

    // Weaponsmith Specilization
    if (pPlayer->HasSpell(SPELL_WEAPONSMITH) && pPlayer->getLevel() > 49 && pPlayer->GetBaseSkillValue(SKILL_BLACKSMITHING) >= 250)
    {
        switch (eCreature)
        {
            case NPC_LILITH:
                if (!HasWeaponSub(pPlayer))
                    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TEACH_HAMMER, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 1);
                break;
            case NPC_KILRAM:
                if (!HasWeaponSub(pPlayer))
                    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TEACH_AXE, GOSSIP_SENDER_LEARN, GOSSIP_ACTION_INFO_DEF + 2);
                break;
            case NPC_SERIL:
                if (!HasWeaponSub(pPlayer))
                    pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TEACH_SWORD,GOSSIP_SENDER_LEARN,GOSSIP_ACTION_INFO_DEF + 3);
                break;
        }
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

void SendActionMenu_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_TRADE:
            pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_TRAIN:
            pPlayer->SEND_TRAINERLIST(pCreature->GetObjectGuid());
            break;
            // Learn Hammer/Axe/Sword
        case GOSSIP_ACTION_INFO_DEF + 1:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_HAMMERSMITH, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_AXESMITH, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            pPlayer->CastSpell(pPlayer, SPELL_LEARN_SWORDSMITH, true);
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmLearn_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiAction)
{
    if (uiAction)
    {
        uint32 eCreature = pCreature->GetEntry();

        switch(eCreature)
        {
            case NPC_LILITH:
                pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TEACH_HAMMER, GOSSIP_SENDER_CHECK, uiAction);
                                                            //unknown textID (TALK_HAMMER_LEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
                break;
            case NPC_KILRAM:
                pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TEACH_AXE, GOSSIP_SENDER_CHECK, uiAction);
                                                            //unknown textID (TALK_AXE_LEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
                break;
            case NPC_SERIL:
                pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_TEACH_SWORD, GOSSIP_SENDER_CHECK, uiAction);
                                                            //unknown textID (TALK_SWORD_LEARN)
                pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
                break;
        }
    }
}

bool GossipSelect_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiSender)
    {
        case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
        case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_blacksmith(pPlayer, pCreature, uiAction); break;
    }
    return true;
}

bool QuestRewarded_npc_prof_blacksmith(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if ((pQuest->GetQuestId() == 5283) || (pQuest->GetQuestId() == 5301))             // Armorsmith
        pCreature->CastSpell(pPlayer, 17451, true);

    if ((pQuest->GetQuestId() == 5284) || (pQuest->GetQuestId() == 5302))             // Weaponsmith
        pCreature->CastSpell(pPlayer, 17452, true);

    return true;
}

/*###
# Engineering Trinkets
###*/

bool GossipHello_npc_engineering_tele_trinket(Player* pPlayer, Creature* pCreature)
{
    uint32 uiNpcTextID = 0;
    uint64 uiGossipItemID = 0;
    bool bCanLearn = false;

    if (pPlayer->HasSkill(SKILL_ENGINEERING))
    {
        switch(pCreature->GetEntry())
        {
            case NPC_ZAP:
                uiNpcTextID = 7249;
                if (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 260 && pPlayer->HasSpell(SPELL_GOBLIN_ENG))
                {
                    if (!pPlayer->HasSpell(SPELL_TO_EVERLOOK))
                    {
                        bCanLearn = true;
                        uiGossipItemID = GOSSIP_ITEM_ZAP;
                    }
                    else if (pPlayer->HasSpell(SPELL_TO_EVERLOOK))
                        uiNpcTextID = 7250;
                }
                break;
            case NPC_JHORDY:
                uiNpcTextID = 7251;
                if (pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 260 && pPlayer->HasSpell(SPELL_GNOMISH_ENG))
                {
                    if (!pPlayer->HasSpell(SPELL_TO_GADGET))
                    {
                        bCanLearn = true;
                        uiGossipItemID = GOSSIP_ITEM_JHORDY;
                    }
                    else if (pPlayer->HasSpell(SPELL_TO_GADGET))
                        uiNpcTextID = 7252;
                }
                break;
        }
    }

    if (bCanLearn)
    {
        if (pPlayer->HasItemCount(ITEM_GOBLIN_CARD, 1) || pPlayer->HasItemCount(ITEM_GNOMISH_CARD, 1))
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, uiGossipItemID, pCreature->GetEntry(), GOSSIP_ACTION_INFO_DEF+1);
    }

    pPlayer->SEND_GOSSIP_MENU(uiNpcTextID, pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_engineering_tele_trinket(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
        pPlayer->CLOSE_GOSSIP_MENU();

    if (uiSender != pCreature->GetEntry())
        return true;

    switch(uiSender)
    {
        case NPC_ZAP:
            pPlayer->CastSpell(pPlayer,SPELL_LEARN_TO_EVERLOOK,false);
            break;
        case NPC_JHORDY:
            pPlayer->CastSpell(pPlayer,SPELL_LEARN_TO_GADGET,false);
            break;
    }

    return true;
}

void AddSC_npc_professions()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_prof_blacksmith";
    pNewScript->pGossipHello = &GossipHello_npc_prof_blacksmith;
    pNewScript->pGossipSelect = &GossipSelect_npc_prof_blacksmith;
    pNewScript->pQuestRewardedNPC = &QuestRewarded_npc_prof_blacksmith;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_engineering_tele_trinket";
    pNewScript->pGossipHello = &GossipHello_npc_engineering_tele_trinket;
    pNewScript->pGossipSelect = &GossipSelect_npc_engineering_tele_trinket;
    pNewScript->RegisterSelf();
}
