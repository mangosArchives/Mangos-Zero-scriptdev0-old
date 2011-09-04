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
SDName: Deeprun Tram
SD%Complete: 100
SDComment: Quest support: 6661
SDCategory: Deeprun Tram
EndScriptData */

/* ContentData
npc_deeprun_rat
EndContentData */

#include "precompiled.h"
#include "follower_ai.h"

/*####
# npc_deeprun_rat
####*/

enum
{
    SPELL_FLUTE         = 21050,
    SPELL_ENTHRALLED    = 21051,
    SPELL_BASH_RATS     = 21052,

    QUEST_ROUNDUP       = 6661,

    NPC_MONTY           = 12997,
    NPC_RAT             = 13016,
    NPC_RAT_F           = 13017
};

struct MANGOS_DLL_DECL npc_deeprun_ratAI : public FollowerAI
{
    npc_deeprun_ratAI(Creature* pCreature) : FollowerAI(pCreature) { Reset(); }

    uint32 m_uiTimer;

    void Reset()
    {
        m_uiTimer = 0;

        if (m_creature->GetEntry() == NPC_RAT_F)
        {
            if (!m_creature->HasSplineFlag(SPLINEFLAG_WALKMODE))
                m_creature->AddSplineFlag(SPLINEFLAG_WALKMODE);

            m_creature->UpdateEntry(NPC_RAT);
            m_creature->RemoveAurasDueToSpell(SPELL_ENTHRALLED);
        }
    }

    void MoveInLineOfSight(Unit *pWho)
    {
        if (m_creature->getVictim())
            return;

        if (pWho->GetEntry() == NPC_MONTY && m_creature->GetEntry() == NPC_RAT_F)
        {
            if (m_creature->IsWithinDistInMap(pWho, 10.0f) && !HasFollowState(STATE_FOLLOW_COMPLETE))
            {
                if (GetLeaderForFollower()->GetQuestStatus(QUEST_ROUNDUP) == QUEST_STATUS_COMPLETE)
                {
                    m_uiTimer = 30000;
                    SetFollowComplete(true);
                    m_creature->GetMotionMaster()->MovePoint(0, -20.5f, 34.7f, -4.3f);
                }
            }
        }
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell)
    {
        if (pSpell->Id == SPELL_FLUTE && pCaster->GetTypeId() == TYPEID_PLAYER && m_creature->GetEntry() == NPC_RAT)
        {
            if (((Player*)pCaster)->GetQuestStatus(QUEST_ROUNDUP) == QUEST_STATUS_INCOMPLETE ||
                ((Player*)pCaster)->GetQuestStatus(QUEST_ROUNDUP) == QUEST_STATUS_COMPLETE)
            {
                m_creature->UpdateEntry(NPC_RAT_F);
                m_creature->CastSpell(m_creature, SPELL_ENTHRALLED, false);

                StartFollow((Player*)pCaster);

                if (m_creature->HasSplineFlag(SPLINEFLAG_WALKMODE))
                    m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
            }

        }
        else if (pSpell->Id == SPELL_BASH_RATS && m_creature->GetEntry() == NPC_RAT_F)
            SetFollowComplete();
        else if (pSpell->Id == SPELL_ENTHRALLED && m_creature->getFaction() != FACTION_ESCORT_A_PASSIVE)
            m_creature->setFaction(FACTION_ESCORT_A_PASSIVE);
    }

    void UpdateFollowerAI(const uint32 uiDiff)
    {
        if (m_uiTimer && HasFollowState(STATE_FOLLOW_COMPLETE))
        {
            if (m_uiTimer < uiDiff)
                m_creature->ForcedDespawn();
            else
                m_uiTimer -= uiDiff;
        }
    }
};

CreatureAI* GetAI_npc_deeprun_rat(Creature* pCreature)
{
    return new npc_deeprun_ratAI(pCreature);
}

void AddSC_deeprun_tram()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_deeprun_rat";
    pNewScript->GetAI = &GetAI_npc_deeprun_rat;
    pNewScript->RegisterSelf();
}
