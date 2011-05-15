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
SDName: Razorfen_Downs
SD%Complete: 100
SDComment: Support for Henry Stern(2 recipes), Extinguishing the Idol Escort Event
SDCategory: Razorfen Downs
EndScriptData */

/* ContentData
npc_henry_stern
npc_belnistrasz
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*###
# npc_henry_stern
####*/

enum
{
    SPELL_GOLDTHORN_TEA                         = 13028,
    SPELL_TEACHING_GOLDTHORN_TEA                = 13029,
    SPELL_MIGHT_TROLLS_BLOOD_POTION             = 3451,
    SPELL_TEACHING_MIGHTY_TROLLS_BLOOD_POTION   = 13030,
    GOSSIP_TEXT_TEA_ANSWER                      = 2114,
    GOSSIP_TEXT_POTION_ANSWER                   = 2115,
};

#define GOSSIP_ITEM_TEA     "Teach me the cooking recipe"
#define GOSSIP_ITEM_POTION  "Teach me the alchemy recipe"

bool GossipHello_npc_henry_stern (Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetBaseSkillValue(SKILL_COOKING) >= 175 && !pPlayer->HasSpell(SPELL_GOLDTHORN_TEA))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_TEA, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    if (pPlayer->GetBaseSkillValue(SKILL_ALCHEMY) >= 180 && !pPlayer->HasSpell(SPELL_MIGHT_TROLLS_BLOOD_POTION))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_POTION, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_henry_stern (Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pCreature->CastSpell(pPlayer, SPELL_TEACHING_GOLDTHORN_TEA, true);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXT_TEA_ANSWER, pCreature->GetObjectGuid());
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXT_POTION_ANSWER, pCreature->GetObjectGuid());
        pCreature->CastSpell(pPlayer, SPELL_TEACHING_MIGHTY_TROLLS_BLOOD_POTION, true);
    }

    return true;
}

/*###
# npc_belnistrasz
####*/

enum
{
    QUEST_EXTINGUISHING_THE_IDOL  = 3525,

    SAY_BELNISTRASZ_READY         = -1129005,
    SAY_BELNISTRASZ_START_RIT     = -1129006,
    SAY_BELNISTRASZ_AGGRO         = -1129007,
    SAY_BELNISTRASZ_3_MIN         = -1129008,
    SAY_BELNISTRASZ_2_MIN         = -1129009,
    SAY_BELNISTRASZ_1_MIN         = -1129010,
    SAY_BELNISTRASZ_FINISH        = -1129011,

    NPC_WITHERED_BATTLE_BOAR      = 7333,
    NPC_WITHERED_QUILGUARD        = 7329,
    NPC_DEATHS_HEAD_GEOMANCER     = 7335,
    NPC_PLAGUEMAW_THE_ROTTING     = 7356,

    SPELL_FIREBALL                = 9053,
    SPELL_FROST_NOVA              = 11831,
    SPELL_IDOL_SHUTDOWN           = 12774
};


static float m_afFirstBoarCoord[4][4]=
{
    {2573.53f, 938.03f, 54.11f},
    {2576.56f, 942.42f, 53.65f},
    {2566.43f, 942.13f, 54.38f},
    {2571.94f, 944.73f, 53.41f}
};

static float m_afSecondBoarCoord[4][4]=
{
    {2583.82f, 950.08f, 52.85f},
    {2584.92f, 954.52f, 52.38f},
    {2590.59f, 952.58f, 53.61f},
    {2591.61f, 956.06f, 52.36f}
};

static float m_afThirdBoarCoord[4][4]=
{
    {2567.07f, 959.31f, 51.88f},
    {2569.77f, 963.93f, 51.50f},
    {2565.01f, 967.41f, 51.05f},
    {2561.66f, 964.06f, 51.33f}
};

static float m_fBossCoord[] = {2580.02f, 943.85f, 53.52f};

struct MANGOS_DLL_DECL npc_belnistraszAI : public npc_escortAI
{
    npc_belnistraszAI(Creature* m_creature) : npc_escortAI(m_creature)
    {
        m_uiRitualPhase = 0;
        m_uiRitualTimer = 0;
        m_uiWaypointID = 0;
        Reset();
    }

    uint8 m_uiRitualPhase;
    uint32 m_uiRitualTimer, m_uiWaypointID, m_uiFireballTimer, m_uiFrostNovaTimer;

    void Reset()
    {
        m_uiFireballTimer  = 1000;
        m_uiFrostNovaTimer = 6000;
    }

    void Aggro(Unit* pWho)
    {
        if (m_uiWaypointID <= 23)
            DoScriptText(SAY_BELNISTRASZ_AGGRO, m_creature, pWho);
    }

    void EnterEvadeMode()
    {
        if (m_uiWaypointID == 24)
        {
            m_creature->SetLootRecipient(NULL);
            m_creature->DeleteThreatList();
            m_creature->CombatStop(false);
        }
        else
            npc_escortAI::EnterEvadeMode();
    }

    void JustSummoned(Creature* pSummoned)
    {
        pSummoned->AI()->AttackStart(m_creature);
    }

    void DoSummonAdds(uint8 uiType)
    {
        switch(uiType)
        {
            case 1:
                m_creature->SummonCreature(NPC_WITHERED_BATTLE_BOAR, m_afFirstBoarCoord[0][0], m_afFirstBoarCoord[0][1], m_afFirstBoarCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_WITHERED_BATTLE_BOAR, m_afFirstBoarCoord[0][0], m_afFirstBoarCoord[0][1], m_afFirstBoarCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_WITHERED_QUILGUARD, m_afFirstBoarCoord[1][0], m_afFirstBoarCoord[1][1], m_afFirstBoarCoord[1][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_DEATHS_HEAD_GEOMANCER, m_afFirstBoarCoord[2][0], m_afFirstBoarCoord[2][1], m_afFirstBoarCoord[2][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                break;
            case 2:
                m_creature->SummonCreature(NPC_WITHERED_BATTLE_BOAR, m_afSecondBoarCoord[0][0], m_afSecondBoarCoord[0][1], m_afSecondBoarCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_WITHERED_BATTLE_BOAR, m_afSecondBoarCoord[0][0], m_afSecondBoarCoord[0][1], m_afSecondBoarCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_WITHERED_QUILGUARD, m_afSecondBoarCoord[1][0], m_afSecondBoarCoord[1][1], m_afSecondBoarCoord[1][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_DEATHS_HEAD_GEOMANCER, m_afSecondBoarCoord[2][0], m_afSecondBoarCoord[2][1], m_afSecondBoarCoord[2][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                break;
            case 3:
                m_creature->SummonCreature(NPC_WITHERED_BATTLE_BOAR, m_afThirdBoarCoord[0][0], m_afThirdBoarCoord[0][1], m_afThirdBoarCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_WITHERED_BATTLE_BOAR, m_afThirdBoarCoord[0][0], m_afThirdBoarCoord[0][1], m_afThirdBoarCoord[0][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_WITHERED_QUILGUARD, m_afThirdBoarCoord[1][0], m_afThirdBoarCoord[1][1], m_afThirdBoarCoord[1][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                m_creature->SummonCreature(NPC_DEATHS_HEAD_GEOMANCER, m_afThirdBoarCoord[2][0], m_afThirdBoarCoord[2][1], m_afThirdBoarCoord[2][2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                break;
            case 4:
                m_creature->SummonCreature(NPC_PLAGUEMAW_THE_ROTTING, m_fBossCoord[0], m_fBossCoord[1], m_fBossCoord[2], 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
                break;
        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        m_uiWaypointID = uiPointId;

        if (uiPointId == 24)
        {
            SetEscortPaused(true);
            m_uiRitualPhase = 1;
            m_uiRitualTimer = 1000;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        npc_escortAI::UpdateEscortAI(uiDiff);

        Player* pPlayer = GetPlayerForEscort();

        if (m_uiRitualTimer < uiDiff && pPlayer && HasEscortState(STATE_ESCORT_ESCORTING) && m_uiRitualPhase > 0)
        {
                switch(m_uiRitualPhase)
                {
                    case 1:
                        DoScriptText(SAY_BELNISTRASZ_START_RIT, m_creature);
                        DoCastSpellIfCan(m_creature, SPELL_IDOL_SHUTDOWN);
                        m_creature->addUnitState(UNIT_STAT_ROOT);
                        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                        m_uiRitualTimer = 1000;
                        break;
                    case 2:
                        DoSummonAdds(urand(1, 3));
                        m_uiRitualTimer = 39000;
                        break;
                    case 3:
                        DoSummonAdds(urand(1, 3));
                        m_uiRitualTimer = 20000;
                        break;
                    case 4:
                        DoScriptText(SAY_BELNISTRASZ_3_MIN, m_creature);
                        m_uiRitualTimer = 20000;
                        break;
                    case 5:
                        DoSummonAdds(urand(1, 3));
                        m_uiRitualTimer = 40000;
                        break;
                    case 6:
                        DoSummonAdds(urand(1, 3));
                        DoScriptText(SAY_BELNISTRASZ_2_MIN, m_creature);
                        m_uiRitualTimer = 40000;
                        break;
                    case 7:
                        DoSummonAdds(urand(1, 3));
                        m_uiRitualTimer = 20000;
                        break;
                    case 8:
                        DoScriptText(SAY_BELNISTRASZ_1_MIN, m_creature);
                        m_uiRitualTimer = 40000;
                        break;
                    case 9:
                        DoSummonAdds(4);
                        m_uiRitualTimer = 20000;
                        break;
                    case 10:
                        DoScriptText(SAY_BELNISTRASZ_FINISH, m_creature);
                        m_uiRitualTimer = 3000;
                        break;
                    case 11:
                        m_uiRitualPhase = 0;
                        m_uiRitualTimer = 0;
                        m_uiWaypointID = 0;
                        m_creature->SetVisibility(VISIBILITY_OFF);
                        if (Player* pPlayer = GetPlayerForEscort())
                        {
                            pPlayer->GroupEventHappens(QUEST_EXTINGUISHING_THE_IDOL, m_creature);

                            if (GameObject* pGo = GetClosestGameObjectWithEntry(m_creature, 152097, 30.0f))
                            {
                                pGo->SetRespawnTime(HOUR*IN_MILLISECONDS);
                                pGo->Refresh();
                            }
                        }

                        m_creature->clearUnitState(UNIT_STAT_ROOT);
                        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                        SetEscortPaused(false);
                        return;
                }

                if (m_uiRitualPhase < 11)
                    ++m_uiRitualPhase;

                return;
        }
        else
            m_uiRitualTimer -= uiDiff;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiFireballTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FIREBALL);
            m_uiFireballTimer  = urand(2000,3000);
        }
        else
            m_uiFireballTimer -= uiDiff;

        if (m_uiFrostNovaTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROST_NOVA);
            m_uiFrostNovaTimer = urand(10000,15000);
        }
        else
            m_uiFrostNovaTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_belnistrasz(Creature* pCreature)
{
    return new npc_belnistraszAI(pCreature);
}

bool QuestAccept_npc_belnistrasz(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_EXTINGUISHING_THE_IDOL)
    {
        if (npc_belnistraszAI* pEscortAI = dynamic_cast<npc_belnistraszAI*>(pCreature->AI()))
        {
            pEscortAI->Start(true, pPlayer, pQuest);
            DoScriptText(SAY_BELNISTRASZ_READY, pCreature, pPlayer);
            pCreature->setFaction(FACTION_ESCORT_N_NEUTRAL_PASSIVE);
        }
    }

    return true;
}

void AddSC_razorfen_downs()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_henry_stern";
    pNewScript->pGossipHello = &GossipHello_npc_henry_stern;
    pNewScript->pGossipSelect = &GossipSelect_npc_henry_stern;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_belnistrasz";
    pNewScript->GetAI = &GetAI_npc_belnistrasz;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_belnistrasz;
    pNewScript->RegisterSelf();
}