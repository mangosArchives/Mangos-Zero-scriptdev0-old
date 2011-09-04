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
SDName: Wetlands
SD%Complete: 100
SDComment: Quest support: 1249
SDCategory: Wetlands
EndScriptData */

/* ContentData
npc_mikhail
npc_tapoke_slim_jahn
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_tapoke_slim_jahn
######*/

enum
{
    QUEST_MISSING_DIPLO_PT11   = 1249,

    FACTION_HOSTILE            = 168,

    SPELL_STEALTH              = 1785,
    SPELL_CALL_FRIENDS         = 16457,    // Summons one friend

    SLIM_SAY_1                 = -1000676,
    SLIM_SAY_2                 = -1000677,
    MIKHAIL_SAY                = -1000678,

    NPC_SLIMS_FRIEND           = 4971,
    NPC_TAPOKE_SLIM_JAHN       = 4962,
    NPC_MIKHAIL                = 4963
};

struct MANGOS_DLL_DECL npc_tapoke_slim_jahnAI : public npc_escortAI
{
    npc_tapoke_slim_jahnAI(Creature* m_creature) : npc_escortAI(m_creature)
    {
        m_uiNormalFaction = m_creature->getFaction();
        Reset();
    }

    uint32 m_uiNormalFaction;
    uint32 m_uiTimer;
    uint32 m_uiPhase;

    bool m_bFriendSummoned, m_bIsBeaten;

    void Reset() {}

    void JustRespawned()
    {
        m_uiTimer = 0;
        m_uiPhase = -1;
        m_bIsBeaten = false;
        m_bFriendSummoned = false;
        // Weird style, but works
        Creature* pMikhail = GetClosestCreatureWithEntry(m_creature, NPC_MIKHAIL, 25.0f);
        if (pMikhail && !pMikhail->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
        {
            pMikhail->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            DoScriptText(MIKHAIL_SAY, pMikhail);
        }

        npc_escortAI::JustRespawned();
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 2:
                if (m_creature->HasStealthAura())
                    m_creature->RemoveSpellsCausingAura(SPELL_AURA_MOD_STEALTH);

                SetRun();
                m_creature->setFaction(FACTION_HOSTILE);
                break;
            case 5:
                Player* pPlayer = GetPlayerForEscort();

                if (pPlayer)
                {
                    if (Group* pGroup = pPlayer->GetGroup())
                    {
                        for(GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                        {
                            Player* pGroupie = itr->getSource();
                            if (pGroupie && pGroupie->GetQuestStatus(QUEST_MISSING_DIPLO_PT11) == QUEST_STATUS_INCOMPLETE)
                                pPlayer->SendQuestFailed(QUEST_MISSING_DIPLO_PT11);
                        }
                    }
                    else if (pPlayer->GetQuestStatus(QUEST_MISSING_DIPLO_PT11) == QUEST_STATUS_INCOMPLETE)
                        pPlayer->SendQuestFailed(QUEST_MISSING_DIPLO_PT11);
                }

                break;
        }
    }

    void Aggro(Unit* /*pWho*/)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (HasEscortState(STATE_ESCORT_ESCORTING) && !m_bFriendSummoned && pPlayer)
        {
            for(uint8 i = 0; i < 3; ++i)
                m_creature->CastSpell(m_creature, SPELL_CALL_FRIENDS, true);

            m_bFriendSummoned = true;
        }
    }

    void JustSummoned(Creature* pSummoned)
    {
        Player* pTarget = GetPlayerForEscort();

        if (pTarget && HasEscortState(STATE_ESCORT_ESCORTING))
        {
            pSummoned->AI()->AttackStart(pTarget);
            pSummoned->ForcedDespawn(150000);
        }
    }

    void DamageTaken(Unit* /*pDoneBy*/, uint32& uiDamage)
    {
        if (m_creature->getFaction() == m_uiNormalFaction)
            return;

        if (uiDamage > m_creature->GetHealth() || ((m_creature->GetHealth() - uiDamage) * 100 / m_creature->GetMaxHealth() <= 20))
        {
            uiDamage = 0;
            m_uiTimer = 3000;
            m_bIsBeaten = true;
            if (Player* pPlayer = GetPlayerForEscort())
            {
                uiDamage = 0;

                m_creature->setFaction(m_uiNormalFaction);

                SetRun(false);
                SetEscortPaused(true);
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        npc_escortAI::UpdateEscortAI(uiDiff);

        if (m_bIsBeaten)
        {
            if (m_uiPhase == -1)
            {
                m_uiPhase = 0;
                EnterEvadeMode();
            }

            if (m_uiTimer < uiDiff)
            {
                ++m_uiPhase;

                switch(m_uiPhase)
                {
                    case 1:
                        DoScriptText(SLIM_SAY_1, m_creature);
                        m_uiTimer = 4000;
                        break;
                    case 2:
                        DoScriptText(SLIM_SAY_2, m_creature);
                        m_uiTimer = 7000;
                        break;
                    case 3:
                        if (Player* pPlayer = GetPlayerForEscort())
                        {
                            if (Group* pGroup = pPlayer->GetGroup())
                            {
                                for(GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                                {
                                    Player* pGroupie = itr->getSource();
                                    if (pGroupie && pGroupie->GetQuestStatus(QUEST_MISSING_DIPLO_PT11) == QUEST_STATUS_INCOMPLETE)
                                        pGroupie->AreaExploredOrEventHappens(QUEST_MISSING_DIPLO_PT11);
                                }
                            }

                            else if (pPlayer->GetQuestStatus(QUEST_MISSING_DIPLO_PT11) == QUEST_STATUS_INCOMPLETE)
                                pPlayer->AreaExploredOrEventHappens(QUEST_MISSING_DIPLO_PT11);
                        }

                        m_creature->ForcedDespawn();
                        m_uiTimer = 0;
                        m_uiPhase = -1;
                        m_bIsBeaten = false;
                        break;
                }
            }
            else
                m_uiTimer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_tapoke_slim_jahn(Creature* pCreature)
{
    return new npc_tapoke_slim_jahnAI(pCreature);
}

/*######
## npc_mikhail
######*/

bool QuestAccept_npc_mikhail(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT11)
    {
        Creature* pSlim = GetClosestCreatureWithEntry(pCreature, NPC_TAPOKE_SLIM_JAHN, 25.0f);

        if (!pSlim)
            return false;

        if (npc_tapoke_slim_jahnAI* pEscortAI = dynamic_cast<npc_tapoke_slim_jahnAI*>(pSlim->AI()))
        {
            if (pEscortAI->HasEscortState(STATE_ESCORT_ESCORTING))
                return false;

            if (!pSlim->HasStealthAura())
                pSlim->CastSpell(pSlim, SPELL_STEALTH, true);

            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            pEscortAI->Start(false, pPlayer);
        }
    }

    return false;
}

void AddSC_wetlands()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_tapoke_slim_jahn";
    pNewScript->GetAI = &GetAI_npc_tapoke_slim_jahn;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_mikhail";
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_mikhail;
    pNewScript->RegisterSelf();
}
