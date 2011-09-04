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
SDName: Stormwind_City
SD%Complete: 100
SDComment: Quest support: 434, 1640, 1447, 4185, 6402, 6403
SDCategory: Stormwind City
EndScriptData */

/* ContentData
npc_bartleby
npc_dashel_stonefist
npc_lady_katrana_prestor
quest_the_great_masquerade
quest_stormwind_rendezvous
npc_reginald_windsor
npc_squire_rowe
npc_lord_gregor_lescovar
npc_marzon_silent_blade
npc_tyrion_spybot
npc_tyrion
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_bartleby
######*/

enum
{
    FACTION_ENEMY   = 168,
    QUEST_BEAT      = 1640
};

struct MANGOS_DLL_DECL npc_bartlebyAI : public ScriptedAI
{
    npc_bartlebyAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        Reset();
    }

    uint32 m_uiNormalFaction;

    void Reset()
    {
        if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void AttackedBy(Unit* pAttacker)
    {
        if (m_creature->getVictim())
            return;

        if (m_creature->IsFriendlyTo(pAttacker))
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (uiDamage > m_creature->GetHealth() || ((m_creature->GetHealth() - uiDamage)*100 / m_creature->GetMaxHealth() < 15))
        {
            uiDamage = 0;

            if (pDoneBy->GetTypeId() == TYPEID_PLAYER)
                ((Player*)pDoneBy)->AreaExploredOrEventHappens(QUEST_BEAT);

            EnterEvadeMode();
        }
    }
};

bool QuestAccept_npc_bartleby(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_BEAT)
    {
        pCreature->setFaction(FACTION_ENEMY);
        ((npc_bartlebyAI*)pCreature->AI())->AttackStart(pPlayer);
    }
    return true;
}

CreatureAI* GetAI_npc_bartleby(Creature* pCreature)
{
    return new npc_bartlebyAI(pCreature);
}

/*######
## npc_dashel_stonefist
######*/

enum
{
    QUEST_MISSING_DIPLO_PT8   = 1447,

    FACTION_HOSTILE           = 168,
    FACTION_FRIENDLY_ADDS     = 35,    // Wrong, only guesswork

    NPC_OLD_TOWN_THUG         = 4969,
    DASHEL_SAY_BEATEN         = -1000675
};

struct MANGOS_DLL_DECL npc_dashel_stonefistAI : public ScriptedAI
{
    npc_dashel_stonefistAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        m_uiTimer = 0;
        m_uiPhase = -1;
        m_uiPlayerGUID = 0;
        m_bIsBeaten = false;
        Reset();
    }

    uint32 m_uiNormalFaction;
    uint32 m_uiTimer;
    uint32 m_uiPhase;
    uint64 m_uiPlayerGUID;

    bool m_bIsBeaten;

    void Reset()
    {
        if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void DamageTaken(Unit* pDoneBy, uint32 &uiDamage)
    {
        if (m_creature->getFaction() == m_uiNormalFaction)
            return;

        if (uiDamage > m_creature->GetHealth() || ((m_creature->GetHealth() - uiDamage) * 100 / m_creature->GetMaxHealth() <= 20))
        {
            uiDamage = 0;
            m_uiTimer = 5000;
            m_bIsBeaten = true;

            std::list<Creature*> m_lGuardList;
            GetCreatureListWithEntryInGrid(m_lGuardList, m_creature, NPC_OLD_TOWN_THUG, 30.0f);

            for (std::list<Creature*>::const_iterator itr = m_lGuardList.begin(); itr != m_lGuardList.end(); ++itr)
            {
                Creature* pAdd = *itr;
                if (pAdd && pAdd->isAlive())
                {
                    pAdd->setFaction(m_uiNormalFaction);
                    pAdd->AI()->EnterEvadeMode();
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
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
                        DoScriptText(DASHEL_SAY_BEATEN, m_creature);
                        m_uiTimer = 4000;
                        break;
                    case 2:
                        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                            pPlayer->AreaExploredOrEventHappens(QUEST_MISSING_DIPLO_PT8);

                        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        m_uiTimer = 0;
                        m_uiPhase = -1;
                        m_uiPlayerGUID = 0;
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

bool QuestAccept_npc_dashel_stonefist(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_MISSING_DIPLO_PT8)
    {
        if (npc_dashel_stonefistAI* pDashel = dynamic_cast<npc_dashel_stonefistAI*>(pCreature->AI()))
        {
            pCreature->setFaction(FACTION_HOSTILE);
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            pDashel->AttackStart(pPlayer);
            pDashel->m_uiPlayerGUID = pPlayer->GetObjectGuid();
        }
    }
    return true;
}

CreatureAI* GetAI_npc_dashel_stonefist(Creature* pCreature)
{
    return new npc_dashel_stonefistAI(pCreature);
}

/*######
## npc_lady_katrana_prestor
######*/

enum
{
    GOSSIP_ITEM_KAT_1     = -3000100,
    GOSSIP_ITEM_KAT_2     = -3000101,
    GOSSIP_ITEM_KAT_3     = -3000102,
    GOSSIP_ITEM_KAT_4     = -3000103
};

bool GossipHello_npc_lady_katrana_prestor(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(4185) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(2693, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_lady_katrana_prestor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            pPlayer->SEND_GOSSIP_MENU(2694, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(2695, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_KAT_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(2696, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(4185);
            break;
    }
    return true;
}

/*######
## quest_the_great_masquerade
## quest_stormwind_rendezvous
######*/

/* Notes about this event:
 * - Event timers, waypoints, spawn locations are mainly guesswork from videos, etc...
 * - Need to check for other, more blizz-like possibilities related to spawned / used creatures in this event:
 *    Anduin Wrynn, Highlord Bolvar Fordragon, Lady Katrana Prestor, General Marcus Jonathan and his guards.
 *   This is currently done by spawning the same creatures and making the original ones invisible ("overwriting").
 */

static const float aSpawnPos[10][4] =
{
    {-9145.680f, 373.795f, 90.648f, 0.671f},                // Windsor Spawn
    {-9049.960f, 446.152f, 93.056f, 0.365f},                // Windsor's mount - Mercutio spawn
    {-8967.960f, 510.008f, 96.351f, 3.770f},                // Jonathan Spawn
    {-8968.510f, 512.556f, 96.352f, 3.849f},                // Guard Right - Left
    {-8969.780f, 515.012f, 96.593f, 3.955f},                // Guard Right - Middle
    {-8972.410f, 518.228f, 96.594f, 4.281f},                // Guard Right - Right
    {-8965.170f, 508.565f, 96.352f, 3.825f},                // Guard Left - Right
    {-8962.960f, 506.583f, 96.593f, 3.802f},                // Guard Left - Middle
    {-8961.080f, 503.828f, 96.593f, 3.465f},                // Guard Left - Left
    {-9020.490f, 467.768f, 73.935f, 0.365f}                 // Prestor Invisible Spawn
};

static const float aMovePoint[9][3] =
 {
    {-9050.390f, 443.556f, 93.056f},                        // Windsor first move
    {-8959.440f, 505.424f, 96.595f},                        // Guard Left - Middle kneel
    {-8957.670f, 507.056f, 96.595f},                        // Guard Left - Right kneel
    {-8970.680f, 519.252f, 96.595f},                        // Guard Right - Middle kneel
    {-8969.100f, 520.395f, 96.595f},                        // Guard Right - Left kneel
    {-8974.590f, 516.213f, 96.590f},                        // Jonathan kneel
    {-8505.770f, 338.312f, 120.886f},                       // Wrynn safe
    {-8448.690f, 337.074f, 121.330f},                       // Bolvar help
    {-8449.310f, 337.559f, 121.330f}                        // Bolvar kneel
};

// Always the code selects one of from these
static const uint32 aGuardSay[] = {-1000608, -1000609, -1000610, -1000611, -1000612, -1000613, -1000614};

enum
{
    GOSSIP_ITEM_ROWE           = -3000104,
    GOSSIP_ITEM_REGINALD       = -3000105,

    NPC_WINDSOR                = 12580,
    NPC_WINDSOR_MOUNT          = 12581,
    NPC_JONATHAN               = 466,
    NPC_PRESTOR                = 1749,
    NPC_BOLVAR                 = 1748,
    NPC_WRYNN                  = 1747,

    NPC_GUARD_ROYAL            = 1756,
    NPC_GUARD_CITY             = 68,
    NPC_GUARD_PATROLLER        = 1976,
    NPC_GUARD_ONYXIA           = 12739,

    QUEST_STORMWIND_RENDEZVOUS = 6402,
    QUEST_THE_GREAT_MASQUERADE = 6403,

    SPELL_PRESTOR_TRANSFORM    = 17136,
    SPELL_WINDSOR_READ         = 20358,
    SPELL_WINDSOR_DEATH        = 20465,
    SPELL_ONYXIA_DESPAWN       = 20466
};

/*######
## npc_reginald_windsor
######*/

struct MANGOS_DLL_DECL npc_reginald_windsorAI : public npc_escortAI
{
    npc_reginald_windsorAI(Creature* m_creature) : npc_escortAI(m_creature)
    {
        Reset();
    }

    uint8 TOTAL_EVENT_PHASE;
    uint32 m_uiEventTimer;
    uint8 m_uiEventPhase;
    uint8 m_uiMobDeadCount;

    bool m_bGuardCanSalute;
    bool m_bPreloaded;

    ObjectGuid m_PrestorGuid;
    ObjectGuid m_JonathanOrigGuid;
    ObjectGuid m_WrynnOrigGuid;
    ObjectGuid m_BolvarOrigGuid;

    // For phase 3
    GUIDList m_lGuardsAlreadySalutedList;
    ObjectGuid m_JonathanGuid;
    ObjectGuid m_GuardGuid[6];

    // For phase 6
    std::list<Creature*> m_lRoyalGuardList;
    GUIDList m_lDragonkinGuardList;
    ObjectGuid m_WrynnGuid;
    ObjectGuid m_BolvarGuid;

    bool m_bWrynnOK, m_bBolvarOK, m_bPrestorOK;

    void Reset()
    {
        TOTAL_EVENT_PHASE = 0;
        m_uiEventTimer = 1;
        m_uiEventPhase = 0;
        m_uiMobDeadCount = 0;

        m_bGuardCanSalute = false;
        m_bPreloaded = false;

        m_PrestorGuid.Clear();
        m_JonathanOrigGuid.Clear();
        m_WrynnOrigGuid.Clear();
        m_BolvarOrigGuid.Clear();
        m_JonathanGuid.Clear();
        m_WrynnGuid.Clear();
        m_BolvarGuid.Clear();

        for(uint8 i = 0; i < 6; ++i)
            m_GuardGuid[i].Clear();

        m_bWrynnOK = false;
        m_bBolvarOK = false;
        m_bPrestorOK = false;
    }

    void SetTotalEventPhase(uint8 uiPhase) {TOTAL_EVENT_PHASE = uiPhase;}

    uint8 GetTotalEventPhase() {return TOTAL_EVENT_PHASE;}

    void ResetTimers(uint32 uiEventTimer)
    {
        m_uiEventTimer = uiEventTimer;
        m_uiEventPhase = 0;
    }

    void WaypointReached(uint32 uiPointId)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch(uiPointId)
        {
            case 0: // Phase 2 ends here, set next...
                debug_log("SD0: npc_reginald_windsor: phase 2 done");
                ResetTimers(1000);
                SetTotalEventPhase(3);
                SetEscortPaused(true);
                break;
            case 5: // We are far enough from Jonathan, so we can reset him
            {
                for(uint8 i = 3; i < 9; ++i)
                    if (Creature* pTemp = m_creature->GetMap()->GetCreature(m_GuardGuid[i-3]))
                        pTemp->ForcedDespawn();

                if (Creature* pJonathanOrig = m_creature->GetMap()->GetCreature(m_JonathanOrigGuid))
                {
                    pJonathanOrig->SetVisibility(VISIBILITY_ON);
                    pJonathanOrig->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }

                if (Creature* pJonathan = m_creature->GetMap()->GetCreature(m_JonathanGuid))
                    pJonathan->ForcedDespawn();

                m_bGuardCanSalute = true; // Allow guards to salute at Windosr
                break;
            }
            case 19: // Phase 3 ends here, set next...
                debug_log("SD0: npc_reginald_windsor: phase 3 done");
                ResetTimers(1000);
                SetTotalEventPhase(4);
                SetEscortPaused(true);
                break;
            case 22: // Phase 5 ends here, set next...
                debug_log("SD0: npc_reginald_windsor: phase 5 done");
                ResetTimers(3000);
                SetTotalEventPhase(6);
                SetEscortPaused(true);
                m_bGuardCanSalute = false;
                m_lGuardsAlreadySalutedList.clear();
                break;
        }
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_GUARD_ONYXIA)
            ++m_uiMobDeadCount;

        if (m_uiMobDeadCount == m_lDragonkinGuardList.size())
        {
            for (std::list<Creature*>::const_iterator itr = m_lRoyalGuardList.begin(); itr != m_lRoyalGuardList.end(); ++itr)
                if (Creature* pGuard = *itr)
                    pGuard->ForcedDespawn();

            m_lRoyalGuardList.clear();
            m_lDragonkinGuardList.clear();

            // Forward Bolvar to Windsor's corpse
            if (Creature* pBolvar = m_creature->GetMap()->GetCreature(m_BolvarGuid))
            {
                pBolvar->AddSplineFlag(SPLINEFLAG_WALKMODE);
                pBolvar->GetMotionMaster()->MovePoint(8, aMovePoint[8][0], aMovePoint[8][1], aMovePoint[8][2]);
            }

            // Force Wrynn to return from the safe hall
            if (Creature* pWrynn = m_creature->GetMap()->GetCreature(m_WrynnGuid))
            {
                float fRetX, fRetY, fRetZ;
                pWrynn->GetRespawnCoord(fRetX, fRetY, fRetZ);
                pWrynn->SetVisibility(VISIBILITY_ON);
                pWrynn->GetMotionMaster()->MovePoint(10, fRetX, fRetY, fRetZ);
            }
        }
    }

    void MoveInLineOfSight(Unit* pWho)
    {
        // Notice Wrynn, Bolvar and Prestor about Windsor's visit
        if (!m_bPreloaded && GetTotalEventPhase() == 5)
        {
            if (pWho->GetEntry() == NPC_WRYNN || pWho->GetEntry() == NPC_BOLVAR || pWho->GetEntry() == NPC_PRESTOR)
                PreloadPhase(6);
        }
    }

    void DoGuardSalute(float fRange)    // TODO: Moving guard does not stop. Need to make them stop and then continue movement after few seconds.
    {                                   // Also missing facing reset.
        std::list<Creature*> m_lTempGuardList;
        std::list<Creature*> m_lTempGuardToSaluteList;

        Creature* pGuard = NULL;
        bool m_bGuardOK = true;

        GetCreatureListWithEntryInGrid(m_lTempGuardList, m_creature, NPC_GUARD_ROYAL, fRange);
        if (m_lTempGuardList.empty())
            GetCreatureListWithEntryInGrid(m_lTempGuardList, m_creature, NPC_GUARD_CITY, fRange);

        if (m_lTempGuardList.empty())
            GetCreatureListWithEntryInGrid(m_lTempGuardList, m_creature, NPC_GUARD_PATROLLER, fRange);

        // Return when list empty
        if (m_lTempGuardList.empty())
            return;

        // Only if at least one guard is on the list
        if (!m_lTempGuardList.empty())
        {
            // Check function to prevent the same guard to salute more than once
            for (std::list<Creature*>::const_iterator itr = m_lTempGuardList.begin(); itr != m_lTempGuardList.end(); ++itr)
            {
                Creature* pTemp = *itr;
                for (GUIDList::const_iterator itrGUID = m_lGuardsAlreadySalutedList.begin(); itrGUID != m_lGuardsAlreadySalutedList.end(); ++itrGUID)
                {
                    Creature* pTempGuard = m_creature->GetMap()->GetCreature(*itrGUID);
                    if (!pTemp || ! pTempGuard)
                        continue;

                    if (pTemp == pTempGuard)
                        m_bGuardOK = false;
                }
                if (m_bGuardOK)
                    m_lTempGuardToSaluteList.push_back(pTemp);
            }

            // Return if no guard is available to salute
            if (m_lTempGuardToSaluteList.empty())
                return;

            // Causes guards on the list to salute Windsor
            for (std::list<Creature*>::const_iterator itr = m_lTempGuardToSaluteList.begin(); itr != m_lTempGuardToSaluteList.end(); ++itr)
            {
                pGuard = *itr;
                m_lGuardsAlreadySalutedList.push_back(pGuard->GetObjectGuid());
                pGuard->SetFacingToObject(m_creature);
                DoScriptText(aGuardSay[urand(0, 6)], pGuard);
            }

            m_lTempGuardToSaluteList.clear();
            m_lTempGuardList.clear();
        }
    }

    /* TODO PreloadPhase(): Need to re-done this in the proper way to avoid summoning creatures
     *     and then make the creatures to properly reset. Hacky solution for now.
     *     Also needed to know what should happen when one or more (original) NPCs
     *     below is/are dead. Currently quest cannot be completed when this occurs.
     *     So basically the whole function PreloadPhase() should be rewritted in proper way.
     */

    void PreloadPhase(uint8 uiPhaseID)
    {
        if (uiPhaseID == 3)
        {
            // Guards
            for(uint8 i = 3; i < 9; ++i)
            {
                if (Creature* pTemp = m_creature->SummonCreature(NPC_GUARD_CITY, aSpawnPos[i][0], aSpawnPos[i][1], aSpawnPos[i][2], aSpawnPos[i][3], TEMPSUMMON_DEAD_DESPAWN, 0))
                {
                    m_GuardGuid[i-3] = pTemp->GetObjectGuid();
                    pTemp->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                }
            }

            // Jonathan
            if (Creature* pJonathanOrig = GetClosestCreatureWithEntry(m_creature->GetMap()->GetCreature(m_GuardGuid[3]), NPC_JONATHAN, 50.0f))
            {
                pJonathanOrig->SetVisibility(VISIBILITY_OFF);
                pJonathanOrig->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_JonathanOrigGuid = pJonathanOrig->GetObjectGuid();
            }
            if (Creature* pJonathan = m_creature->SummonCreature(NPC_JONATHAN, aSpawnPos[2][0], aSpawnPos[2][1], aSpawnPos[2][2], aSpawnPos[2][3], TEMPSUMMON_DEAD_DESPAWN, 0))
            {
                pJonathan->Unmount();
                pJonathan->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pJonathan->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                m_JonathanGuid = pJonathan->GetObjectGuid();
            }
        }

        else if (uiPhaseID == 6 && !m_bPreloaded) // Every NPC below must be alive!
        {
            Creature* pWrynnOrig = GetClosestCreatureWithEntry(m_creature, NPC_WRYNN, 85.0f);
            if (pWrynnOrig && !m_bWrynnOK)
            {
                pWrynnOrig->SetVisibility(VISIBILITY_OFF);
                pWrynnOrig->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_WrynnOrigGuid = pWrynnOrig->GetObjectGuid();

                if (Creature* pWrynn = m_creature->SummonCreature(NPC_WRYNN, pWrynnOrig->GetPositionX(), pWrynnOrig->GetPositionY(), pWrynnOrig->GetPositionZ(), pWrynnOrig->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
                    m_WrynnGuid = pWrynn->GetObjectGuid();

                m_bWrynnOK = true;
            }

            Creature* pBolvarOrig = GetClosestCreatureWithEntry(m_creature, NPC_BOLVAR, 85.0f);
            if (pBolvarOrig && !m_bBolvarOK)
            {
                pBolvarOrig->SetVisibility(VISIBILITY_OFF);
                pBolvarOrig->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_BolvarOrigGuid = pBolvarOrig->GetObjectGuid();

                if (Creature* pBolvar = m_creature->SummonCreature(NPC_BOLVAR, pBolvarOrig->GetPositionX(), pBolvarOrig->GetPositionY(), pBolvarOrig->GetPositionZ(), pBolvarOrig->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
                {
                    pBolvar->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    pBolvar->setFaction(11);
                    m_BolvarGuid = pBolvar->GetObjectGuid();
                }

                m_bBolvarOK = true;
            }

            Creature* pPrestor = GetClosestCreatureWithEntry(m_creature, NPC_PRESTOR, 85.0f);
            if (pPrestor && !m_bPrestorOK) // If pPrestor is wrong, event cannot be continued
            {
                pPrestor->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                pPrestor->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                m_PrestorGuid = pPrestor->GetObjectGuid();
                m_bPrestorOK = true;
            }

            // PreloadPhase(6) is called until everything is right
            if (m_bWrynnOK && m_bBolvarOK && m_bPrestorOK)
                m_bPreloaded = true;
        }
    }

    void SummonedMovementInform(Creature* pSummoned, uint32 /*uiMotionType*/, uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 1:
            case 2:
                pSummoned->SetFacingTo(2.234f);
                pSummoned->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case 3:
            case 4:
            case 5:
                pSummoned->SetFacingTo(5.375f);
                pSummoned->SetStandState(UNIT_STAND_STATE_KNEEL);
                break;
            case 6:
                pSummoned->SetVisibility(VISIBILITY_OFF);
                break;
            case 7:
                if (Creature* pPrestor = m_creature->GetMap()->GetCreature(m_PrestorGuid))
                    pSummoned->SetFacingToObject(pPrestor);
                break;
            case 8:
                pSummoned->SetFacingToObject(m_creature);
                pSummoned->SetStandState(UNIT_STAND_STATE_KNEEL);
                DoScriptText(-1000635, pSummoned);
                ResetTimers(250);
                SetTotalEventPhase(7);
                break;
            case 9: // Escort finished
                pSummoned->SetFacingTo(2.293f);
                pSummoned->ForcedDespawn();

                if (Creature* pBolvarOrig = m_creature->GetMap()->GetCreature(m_BolvarOrigGuid))
                {
                    pBolvarOrig->SetVisibility(VISIBILITY_ON);
                    pBolvarOrig->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    for (std::list<Creature*>::const_iterator itr = m_lRoyalGuardList.begin(); itr != m_lRoyalGuardList.end(); ++itr)
                        if (Creature* pGuard = *itr)
                            pGuard->ForcedDespawn();

                    // Kill Windsor definitly
                    pBolvarOrig->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                    break;
                }

                debug_log("SD0: npc_reginald_windsor: escort finished");
            case 10:
                pSummoned->SetFacingTo(2.343f);
                pSummoned->ForcedDespawn();
                if (Creature* pWrynnOrig = m_creature->GetMap()->GetCreature(m_WrynnOrigGuid))
                {
                    pWrynnOrig->SetVisibility(VISIBILITY_ON);
                    pWrynnOrig->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        Player* pPlayer = GetPlayerForEscort();
        if (!HasEscortState(STATE_ESCORT_ESCORTING) || !pPlayer)
            return;

        // Causes guards within 15y(?) to salute Windsor
        if (m_bGuardCanSalute)
            DoGuardSalute(15.0f);

        // Phase 1 == When Windsor arrives to Stormwind on his mount... (npc_squire_roweAI)

        // Phase 2 == When player accepts quest QUEST_THE_GREAT_MASQUERADE
        if (GetTotalEventPhase() == 2 && m_uiEventPhase < 6)
        {
            if (m_uiEventTimer < uiDiff)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        SetEscortPaused(true);
                        m_creature->SetFacingToObject(pPlayer);
                        DoScriptText(-1000592, m_creature);
                        m_uiEventTimer = 6000;
                        break;
                    case 2:
                        PreloadPhase(3);
                        m_creature->SetFacingTo(0.673f);
                        m_uiEventTimer = 2000;
                        break;
                    case 3:
                        DoScriptText(-1000593, m_creature);
                        m_uiEventTimer = 4500;
                        break;
                    case 4: // Had no other idea regarding this... Could be hacky
                        // Summon her in Stormwind texture, so player cannot see her.
                        if (Creature* pPrestor = m_creature->SummonCreature(NPC_PRESTOR, aSpawnPos[9][0], aSpawnPos[9][1], aSpawnPos[9][2], aSpawnPos[9][3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 7000))
                        {
                            pPrestor->SetVisibility(VISIBILITY_OFF);
                            pPrestor->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                            DoScriptText(-1000594, pPrestor);
                        }

                        m_uiEventTimer = 1000;
                        break;
                    case 5:
                        SetEscortPaused(false);
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        // Phase 3 == Dialog between Windsor and Jonathan
        if (GetTotalEventPhase() == 3 && m_uiEventPhase < 21)
        {
            Creature* pJonathan = m_creature->GetMap()->GetCreature(m_JonathanGuid);

            if (m_uiEventTimer < uiDiff && pJonathan)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        DoScriptText(-1000595, pJonathan);
                        m_uiEventTimer = 5000;
                        break;
                    case 2:
                        DoScriptText(-1000596, m_creature);
                        m_uiEventTimer = 5000;
                        break;
                    case 3:
                        DoScriptText(-1000597, m_creature);
                        m_uiEventTimer = 8000;
                        break;
                    case 4:
                        DoScriptText(-1000598, pJonathan);
                        m_uiEventTimer = 6000;
                        break;
                    case 5:
                        DoScriptText(-1000599, pJonathan);
                        m_uiEventTimer = 9500;
                        break;
                    case 6:
                        DoScriptText(-1000600, m_creature);
                        m_uiEventTimer = 8000;
                        break;
                    case 7:
                        DoScriptText(-1000601, m_creature);
                        m_uiEventTimer = 6000;
                        break;
                    case 8:
                        pJonathan->SetFacingTo(5.375f);
                        DoScriptText(-1000602, pJonathan);

                        if (Creature* pGuardLeftL = m_creature->GetMap()->GetCreature(m_GuardGuid[5]))
                        {
                            pGuardLeftL->SetFacingTo(2.234f);
                            pGuardLeftL->SetStandState(UNIT_STAND_STATE_KNEEL);
                        }

                        m_uiEventTimer = 1000;
                        break;
                    case 9:
                        if (Creature* pGuardLeftM = m_creature->GetMap()->GetCreature(m_GuardGuid[4]))
                            pGuardLeftM->GetMotionMaster()->MovePoint(1, aMovePoint[1][0], aMovePoint[1][1], aMovePoint[1][2]);

                        if (Creature* pGuardLeftR = m_creature->GetMap()->GetCreature(m_GuardGuid[3]))
                            pGuardLeftR->GetMotionMaster()->MovePoint(2, aMovePoint[2][0], aMovePoint[2][1], aMovePoint[2][2]);

                        m_uiEventTimer = 5000;
                        break;
                    case 10:
                        pJonathan->SetFacingTo(2.234f);
                        DoScriptText(-1000603, pJonathan);

                        if (Creature* pGuardRightR = m_creature->GetMap()->GetCreature(m_GuardGuid[2]))
                        {
                            pGuardRightR->SetFacingTo(5.375f);
                            pGuardRightR->SetStandState(UNIT_STAND_STATE_KNEEL);
                        }

                        m_uiEventTimer = 500;
                        break;
                    case 11:
                        if (Creature* pGuardRightM = m_creature->GetMap()->GetCreature(m_GuardGuid[1]))
                            pGuardRightM->GetMotionMaster()->MovePoint(3, aMovePoint[3][0], aMovePoint[3][1], aMovePoint[3][2]);

                        if (Creature* pGuardRightL = m_creature->GetMap()->GetCreature(m_GuardGuid[0]))
                            pGuardRightL->GetMotionMaster()->MovePoint(4, aMovePoint[4][0], aMovePoint[4][1], aMovePoint[4][2]);

                        m_uiEventTimer = 5500;
                        break;
                    case 12:
                        pJonathan->SetFacingToObject(m_creature);
                        DoScriptText(-1000604, pJonathan);
                        m_uiEventTimer = 5000;
                        break;
                    case 13:
                        pJonathan->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
                        m_uiEventTimer = 4000;
                        break;
                    case 14:
                        DoScriptText(-1000605, pJonathan);
                        m_uiEventTimer = 3000;
                        break;
                    case 15:
                        pJonathan->GetMotionMaster()->MovePoint(5, aMovePoint[5][0], aMovePoint[5][1], aMovePoint[5][2]);
                        m_uiEventTimer = 7000;
                        break;
                    case 16:
                        m_creature->SetFacingToObject(pJonathan);
                        DoScriptText(-1000606, m_creature);
                        m_uiEventTimer = 5000;
                        break;
                    case 17:
                        m_creature->SetFacingTo(6.112f);
                        m_uiEventTimer = 500;
                        break;
                    case 18:
                        DoScriptText(-1000607, m_creature);
                        m_uiEventTimer = 2500;
                        break;
                    case 19:
                        m_creature->HandleEmoteCommand(EMOTE_STATE_POINT);
                        m_uiEventTimer = 2500;
                        break;
                    case 20:
                        SetEscortPaused(false);
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        // Phase 4 == Reginald stands before Stormwind Keep
        if (GetTotalEventPhase() == 4 && m_uiEventPhase < 3)
        {
            if (m_uiEventTimer < uiDiff)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        m_creature->SetFacingTo(5.398f);
                        m_uiEventTimer = 4000;
                        break;
                    case 2:
                        DoScriptText(-1000615, m_creature);
                        m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        m_creature->HandleEmoteCommand(EMOTE_STATE_POINT);
                        m_uiEventTimer = 3000;
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        // Phase 5 == Player selects gossip option
        if (GetTotalEventPhase() == 5 && m_uiEventPhase < 2)
        {
            if (m_uiEventTimer < uiDiff)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        SetEscortPaused(false);
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        // Phase 6 == Windsor's dialog with Prestor
        if (GetTotalEventPhase() == 6 && m_uiEventPhase < 22)
        {
            Creature* pWrynn = m_creature->GetMap()->GetCreature(m_WrynnGuid);
            Creature* pBolvar = m_creature->GetMap()->GetCreature(m_BolvarGuid);
            Creature* pPrestor = m_creature->GetMap()->GetCreature(m_PrestorGuid);

            if (m_uiEventTimer < uiDiff && pWrynn && pBolvar && pPrestor)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        DoScriptText(-1000617, m_creature);
                        m_uiEventTimer = 3500;
                        break;
                    case 2:
                        DoScriptText(-1000618, pBolvar);
                        pWrynn->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pWrynn->GetMotionMaster()->MovePoint(6, aMovePoint[6][0], aMovePoint[6][1], aMovePoint[6][2]);
                        m_uiEventTimer = 2500;
                        break;
                    case 3:
                        DoScriptText(-1000619, m_creature);
                        m_uiEventTimer = 4000;
                        break;
                    case 4:
                        DoScriptText(-1000620, pPrestor);
                        m_uiEventTimer = 3000;
                        break;
                    case 5:
                        DoScriptText(-1000621, pPrestor);
                        m_uiEventTimer = 8000;
                        break;
                    case 6:
                        DoScriptText(-1000622, pPrestor);
                        m_uiEventTimer = 8000;
                        break;
                    case 7:
                        DoScriptText(-1000623, m_creature);
                        m_uiEventTimer = 7000;
                        break;
                    case 8:
                        DoScriptText(-1000624, m_creature);
                        m_uiEventTimer = 4000;
                        break;
                    case 9:
                        DoScriptText(-1000625, m_creature);
                        m_uiEventTimer = 5000;
                        break;
                    case 10:
                        DoScriptText(-1000626, m_creature);
                        m_uiEventTimer = 4000;
                        break;
                    case 11:
                        DoScriptText(-1000627, m_creature);
                        m_uiEventTimer = 3500;
                        break;
                    case 12:
                        DoCastSpellIfCan(pPrestor, SPELL_WINDSOR_READ);
                        m_uiEventTimer = 10000;
                        break;
                    case 13:
                        pPrestor->UpdateEntry(12756);
                        pPrestor->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        DoScriptText(-1000628, pBolvar);
                        pBolvar->SetFacingToObject(pPrestor);
                        pPrestor->CastSpell(pPrestor, SPELL_PRESTOR_TRANSFORM, false); // Has small delay while trying to apply the correct model
                        m_uiEventTimer = 3000;
                        break;
                    case 14:
                        DoScriptText(-1000629, pPrestor);
                        pBolvar->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                        pBolvar->GetMotionMaster()->MovePoint(7, aMovePoint[7][0], aMovePoint[7][1], aMovePoint[7][2]);
                        m_uiEventTimer = 3000;
                        break;
                    case 15:
                        DoScriptText(-1000630, pBolvar);
                        pBolvar->AddSplineFlag(SPLINEFLAG_WALKMODE);
                        m_uiEventTimer = 1000;
                        break;
                    case 16:
                        DoScriptText(-1000620, pPrestor);
                        m_uiEventTimer = 2000;
                        break;
                    case 17:
                        DoScriptText(-1000631, pPrestor);
                        GetCreatureListWithEntryInGrid(m_lRoyalGuardList, m_creature->GetMap()->GetCreature(m_WrynnOrigGuid), NPC_GUARD_ROYAL, 25.0f);

                        for (std::list<Creature*>::const_iterator itr = m_lRoyalGuardList.begin(); itr != m_lRoyalGuardList.end(); ++itr)
                        {
                            if (Creature* pGuard = *itr)
                            {
                                pGuard->SetVisibility(VISIBILITY_OFF);
                                pGuard->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                if (Creature* pGuardDragonkin = m_creature->SummonCreature(NPC_GUARD_ONYXIA, pGuard->GetPositionX(), pGuard->GetPositionY(), pGuard->GetPositionZ(), pGuard->GetOrientation(), TEMPSUMMON_DEAD_DESPAWN, 0))
                                {
                                    pGuardDragonkin->SetFacingToObject(pPrestor);
                                    pGuardDragonkin->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                    m_lDragonkinGuardList.push_back(pGuardDragonkin->GetObjectGuid());
                                }
                            }
                        }

                        m_uiEventTimer = 5000;
                        break;
                    case 18:
                        pPrestor->CastSpell(m_creature, SPELL_WINDSOR_DEATH, false);
                        m_uiEventTimer = 1500;
                        break;
                    case 19: // Reginald's death
                        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
                        m_creature->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                        m_creature->addUnitState(UNIT_STAT_DIED);
                        DoScriptText(-1000632, m_creature);

                        for (GUIDList::const_iterator itr = m_lDragonkinGuardList.begin(); itr != m_lDragonkinGuardList.end(); ++itr)
                        {
                            if (Creature* pGuardDragonkin = m_creature->GetMap()->GetCreature(*itr))
                            {
                                pGuardDragonkin->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                pGuardDragonkin->AI()->AttackStart(pBolvar);
                            }
                        }

                        m_uiEventTimer = 500;
                        break;
                    case 20:
                        DoScriptText(-1000633, pPrestor);
                        m_uiEventTimer = 3500;
                        break;
                    case 21:
                        //DoScriptText(-1000634, pPrestor, pPlayer); Does not work, also causes LUA error for unknown reason
                        pPrestor->CastSpell(pPrestor, SPELL_ONYXIA_DESPAWN, false);
                        pPrestor->SetRespawnTime(30000);
                        pPrestor->ForcedDespawn(1000);
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

        // Phase 7 == When Bolvar reaches Windsor after the fight ended
        if (GetTotalEventPhase() == 7 && m_uiEventPhase < 4)
        {
            Creature* pBolvar = m_creature->GetMap()->GetCreature(m_BolvarGuid);

            if (m_uiEventTimer < uiDiff && pBolvar)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        DoScriptText(-1000636, m_creature);
                        DoScriptText(-1000637, m_creature);
                        m_uiEventTimer = 250;
                        break;
                    case 2:
                        pBolvar->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

                        if (Group* pGroup = pPlayer->GetGroup())
                        {
                            for(GroupReference* itr = pGroup->GetFirstMember(); itr != NULL; itr = itr->next())
                            {
                                Player* pGroupie = itr->getSource();
                                if (pGroupie && pGroupie->GetQuestStatus(QUEST_THE_GREAT_MASQUERADE) == QUEST_STATUS_INCOMPLETE)
                                    pGroupie->AreaExploredOrEventHappens(QUEST_THE_GREAT_MASQUERADE);
                            }
                        }

                        else if (pPlayer->GetQuestStatus(QUEST_THE_GREAT_MASQUERADE) == QUEST_STATUS_INCOMPLETE)
                            pPlayer->AreaExploredOrEventHappens(QUEST_THE_GREAT_MASQUERADE);

                        m_uiEventTimer = 8000;
                        break;
                    case 3:
                        float fRetX, fRetY, fRetZ;
                        pBolvar->GetRespawnCoord(fRetX, fRetY, fRetZ);
                        pBolvar->SetStandState(UNIT_STAND_STATE_STAND);
                        pBolvar->GetMotionMaster()->MovePoint(9, fRetX, fRetY, fRetZ);
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }

    }
};

bool QuestAccept_npc_reginald_windsor(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    npc_reginald_windsorAI* pReginald = dynamic_cast<npc_reginald_windsorAI*>(pCreature->AI());

    if (pQuest->GetQuestId() == QUEST_THE_GREAT_MASQUERADE && pReginald)
    {
        pReginald->SetTotalEventPhase(2);
        pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
        pReginald->Start(false, pPlayer, pQuest);
    }

    return true;
}

bool GossipHello_npc_reginald_windsor(Player* pPlayer, Creature* pCreature)
{
    npc_reginald_windsorAI* pReginald = dynamic_cast<npc_reginald_windsorAI*>(pCreature->AI());

    if (pCreature->isQuestGiver() && pReginald && pReginald->GetTotalEventPhase() == 0)
    {
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE,pCreature->GetObjectGuid());
    }

    else if (pReginald && pReginald->GetTotalEventPhase() == 4)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_REGINALD, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
        pPlayer->SEND_GOSSIP_MENU(5633, pCreature->GetObjectGuid());
    }

    return true;
}

bool GossipSelect_npc_reginald_windsor(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 /*uiAction*/)
{
    pPlayer->CLOSE_GOSSIP_MENU();
    pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
    DoScriptText(-1000616, pCreature);

    if (npc_reginald_windsorAI* pReginald = dynamic_cast<npc_reginald_windsorAI*>(pCreature->AI()))
    {
        debug_log("SD0: npc_reginald_windsor: phase 4 done");
        pReginald->SetTotalEventPhase(5); // Phase 4 ends here, set next...
        pReginald->ResetTimers(3000);
    }

    return true;
}

CreatureAI* GetAI_npc_reginald_windsor(Creature* pCreature)
{
    return new npc_reginald_windsorAI(pCreature);
}

/*######
## npc_squire_rowe
######*/

struct MANGOS_DLL_DECL npc_squire_roweAI : public npc_escortAI
{
    npc_squire_roweAI(Creature* m_creature) : npc_escortAI(m_creature)
    {
        m_MarshalGuid.Clear();
        m_bMarshalArrived = false;
        m_uiEventTimer = 0;
        m_uiEventPhase = -1;
    }

    ObjectGuid m_MarshalGuid;
    bool m_bMarshalArrived;
    uint32 m_uiEventTimer;
    uint8 m_uiEventPhase;

    void Reset() {} // Not Used

    void SummonedMovementInform(Creature* pSummoned, uint32 /*uiMotionType*/, uint32 uiPointId)
    {
        if (uiPointId == 1 && pSummoned->GetEntry() == NPC_WINDSOR && !m_bMarshalArrived)
        {
            m_bMarshalArrived = true;
            pSummoned->GetMotionMaster()->Clear(false);
            m_creature->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
        }
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
        if (pSummoned->GetEntry() == NPC_WINDSOR)
            m_MarshalGuid.Clear();
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 3:
                m_creature->SetFacingTo(3.799f);

                // Summon Marshal Windsor
                if (Creature* pMarshal = m_creature->SummonCreature(NPC_WINDSOR, aSpawnPos[0][0], aSpawnPos[0][1], aSpawnPos[0][2], aSpawnPos[0][3], TEMPSUMMON_DEAD_DESPAWN, 0))
                {
                    m_MarshalGuid = pMarshal->GetObjectGuid();
                    m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                    pMarshal->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                    pMarshal->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    pMarshal->Mount(2410);
                    pMarshal->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                    pMarshal->GetMotionMaster()->MovePoint(1, aMovePoint[0][0], aMovePoint[0][1], aMovePoint[0][2]);
                }
                break;
            case 4:
                m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                break;
            case 7:
                m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                DoScriptText(-1000638, m_creature);
                m_creature->SetFacingTo(2.234f);
                SetEscortPaused(true);
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        Creature* pMarshal = m_creature->GetMap()->GetCreature(m_MarshalGuid);
        Player* pPlayer = GetPlayerForEscort();

        // Return cases
        if (m_uiEventPhase == -1 || !pMarshal || !pPlayer)
            return;

        // Phase 1 == When Windsor arrives to Stormwind on his mount...
        if (m_bMarshalArrived && m_uiEventPhase < 6)
        {
            if (m_uiEventTimer < uiDiff)
            {
                ++m_uiEventPhase;

                switch(m_uiEventPhase)
                {
                    case 1:
                        pMarshal->Unmount();
                        pMarshal->AddSplineFlag(SPLINEFLAG_WALKMODE);
                        m_uiEventTimer = 1500;
                        break;
                    case 2:
                        // Using TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, if something goes wrong :/
                        if (Creature* pMount = m_creature->SummonCreature(NPC_WINDSOR_MOUNT, aSpawnPos[1][0], aSpawnPos[1][1], aSpawnPos[1][2], aSpawnPos[1][3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300000))
                            pMount->RemoveSplineFlag(SPLINEFLAG_WALKMODE);

                        m_uiEventTimer = 1500;
                        break;
                    case 3:
                        DoScriptText(-1000590, pMarshal);
                        pMarshal->HandleEmoteCommand(EMOTE_ONESHOT_ATTACKUNARMED);
                        m_uiEventTimer = 1000;
                        break;
                    case 4:
                        pMarshal->SetFacingToObject(pPlayer);
                        m_uiEventTimer = 3000;
                        break;
                    case 5:
                        DoScriptText(-1000591, pMarshal, pPlayer);
                        pMarshal->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                        debug_log("SD0: npc_reginald_windsor: phase 1 done");
                        // Reseting Rowe makes him avaliable to further players
                        npc_escortAI::JustRespawned(); // Phase 1 ends here, set next...
                        m_uiEventTimer = 0;
                        m_uiEventPhase = -1;
                        m_bMarshalArrived = false;
                        break;
                }
            }
            else
                m_uiEventTimer -= uiDiff;
        }
    }
};

bool GossipHello_npc_squire_rowe(Player* pPlayer, Creature* pCreature)
{
    uint32 m_uiGossipMenu = 0;
    npc_squire_roweAI* pRowe = dynamic_cast<npc_squire_roweAI*>(pCreature->AI());

    if (pPlayer->IsActiveQuest(QUEST_STORMWIND_RENDEZVOUS) && pRowe && (!pPlayer->GetQuestRewardStatus(QUEST_STORMWIND_RENDEZVOUS) ||
       !pPlayer->GetQuestRewardStatus(QUEST_THE_GREAT_MASQUERADE) && pPlayer->GetQuestRewardStatus(QUEST_STORMWIND_RENDEZVOUS)))
    {
        // When event in progress and quest checks are true
        if (Creature* pMarshal = pCreature->GetMap()->GetCreature(pRowe->m_MarshalGuid))
            m_uiGossipMenu = 9064;

        // When event not in progress and quest checks are true
        else
        {
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ROWE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
            pRowe->m_uiEventPhase = 0;
            m_uiGossipMenu = 9065;
        }
    }

     // When quest checks are false
    else
        m_uiGossipMenu = 9063;

    // Send gossip menu
    pPlayer->SEND_GOSSIP_MENU(m_uiGossipMenu, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_squire_rowe(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    pPlayer->CLOSE_GOSSIP_MENU();

    if (npc_squire_roweAI* pRowe = dynamic_cast<npc_squire_roweAI*>(pCreature->AI()))
    {
        pRowe->Start(true, pPlayer);
        pRowe->m_uiEventTimer = 3000;
        pRowe->m_uiEventPhase = 0;
    }
    return true;
}

CreatureAI* GetAI_npc_squire_rowe(Creature* pCreature)
{
    return new npc_squire_roweAI(pCreature);
}

/*######
## npc_lord_gregor_lescovar
######*/

enum
{
    SAY_LESCOVAR_2 = -1000687,
    SAY_GUARD_2    = -1000688,
    SAY_LESCOVAR_3 = -1000689,
    SAY_MARZON_1   = -1000690,
    SAY_LESCOVAR_4 = -1000691,
    SAY_TYRION_2   = -1000692,
    SAY_MARZON_2   = -1000693,

    NPC_STORMWIND_ROYAL = 1756,
    NPC_MARZON_BLADE    = 1755,
    NPC_TYRION          = 7766,
    NPC_LORD_GREGOR_LESCOVAR = 1754,
    QUEST_THE_ATTACK    = 434
};

struct MANGOS_DLL_DECL npc_lord_gregor_lescovarAI : public npc_escortAI
{
    npc_lord_gregor_lescovarAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        Reset();
    }

    uint32 m_uiNormalFaction;
    uint32 m_uiTimer;
    uint32 m_uiPhase;

    void Reset()
    {
        m_uiTimer = 0;
        m_uiPhase = 0;

        if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn(10);

        if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature, NPC_MARZON_BLADE, 150.0f))
        {
            if (pMarzon->isAlive())
                pMarzon->ForcedDespawn(10);
        }
    }

    void EnterCombat(Unit* pWho)
    {
        if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature, NPC_MARZON_BLADE, 150.0f))
        {
            if (pMarzon->isAlive() && !pMarzon->isInCombat())
                pMarzon->AI()->AttackStart(pWho);

        }
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 14:
                SetEscortPaused(true);
                DoScriptText(SAY_LESCOVAR_2, m_creature);
                m_uiTimer = 3000;
                m_uiPhase = 1;
                break;
            case 16:
                SetEscortPaused(true);
                if (Creature *pMarzon = m_creature->SummonCreature(NPC_MARZON_BLADE,-8411.360352f, 480.069733f, 123.760895f, 4.941504f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000))
                    pMarzon->GetMotionMaster()->MovePoint(0,-8408.000977f, 468.611450f, 123.759903f);

                m_uiTimer = 2000;
                m_uiPhase = 4;
                break;
        }
    }

    void DoGuardsDisappearAndDie()
    {
        std::list<Creature*> lGuardList;
        GetCreatureListWithEntryInGrid(lGuardList,m_creature,NPC_STORMWIND_ROYAL,8.0f);
        if (!lGuardList.empty())
        {
            for (std::list<Creature*>::const_iterator itr = lGuardList.begin(); itr != lGuardList.end(); ++itr)
            {
                if (Creature* pGuard = *itr)
                    pGuard->ForcedDespawn(10);
            }
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (m_uiPhase)
        {
            if (m_uiTimer <= uiDiff)
            {
                switch(m_uiPhase)
                {
                    case 1:
                        if (Creature* pGuard = GetClosestCreatureWithEntry(m_creature,NPC_STORMWIND_ROYAL, 8.0f))
                            DoScriptText(SAY_GUARD_2, pGuard);
                        m_uiTimer = 3000;
                        m_uiPhase = 2;
                        break;
                    case 2:
                        DoGuardsDisappearAndDie();
                        m_uiTimer = 2000;
                        m_uiPhase = 3;
                        break;
                    case 3:
                        SetEscortPaused(false);
                        m_uiTimer = 0;
                        m_uiPhase = 0;
                        break;
                    case 4:
                        DoScriptText(SAY_LESCOVAR_3, m_creature);
                        m_uiTimer = 0;
                        m_uiPhase = 0;
                        break;
                    case 5:
                        if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature,NPC_MARZON_BLADE, 150.0f))
                            DoScriptText(SAY_MARZON_1, pMarzon);
                        m_uiTimer = 3000;
                        m_uiPhase = 6;
                        break;
                    case 6:
                        DoScriptText(SAY_LESCOVAR_4, m_creature);
                        if (Player* pPlayer = GetPlayerForEscort())
                            pPlayer->AreaExploredOrEventHappens(QUEST_THE_ATTACK);
                        m_uiTimer = 2000;
                        m_uiPhase = 7;
                        break;
                    case 7:
                        if (Creature* pTyrion = GetClosestCreatureWithEntry(m_creature,NPC_TYRION, 20.0f))
                            DoScriptText(SAY_TYRION_2, pTyrion);
                        if (Creature *pMarzon = GetClosestCreatureWithEntry(m_creature,NPC_MARZON_BLADE, 150.0f))
                            pMarzon->setFaction(14);
                        m_creature->setFaction(14);
                        m_uiTimer = 0;
                        m_uiPhase = 0;
                        break;
                }
            }
            else
                m_uiTimer -= uiDiff;
        }
    }

};

CreatureAI* GetAI_npc_lord_gregor_lescovarAI(Creature* pCreature)
{
    return new npc_lord_gregor_lescovarAI(pCreature);
}

/*######
## npc_marzon_silent_blade
######*/

struct MANGOS_DLL_DECL npc_marzon_silent_bladeAI : public ScriptedAI
{
    npc_marzon_silent_bladeAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNormalFaction = pCreature->getFaction();
        Reset();
    }

    uint32 m_uiNormalFaction;

    void Reset()
    {
        if (m_creature->getFaction() != m_uiNormalFaction)
            m_creature->setFaction(m_uiNormalFaction);
    }

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_MARZON_2, m_creature);
    }

    void EnterEvadeMode()
    {
        m_creature->ForcedDespawn(10);
    }

    void MovementInform(uint32 uiType, uint32)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;


        if (Creature *pLescovar = GetClosestCreatureWithEntry(m_creature,NPC_LORD_GREGOR_LESCOVAR, 30.0f))
        {
            ((npc_lord_gregor_lescovarAI*)pLescovar->AI())->m_uiTimer = 2000;
            ((npc_lord_gregor_lescovarAI*)pLescovar->AI())->m_uiPhase = 5;

        }

    }

    void UpdateAI(const uint32)
    {
        if (!m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_marzon_silent_bladeAI(Creature* pCreature)
{
    return new npc_marzon_silent_bladeAI(pCreature);
}

/*######
## npc_tyrion_spybot
######*/

enum
{
    SAY_QUEST_ACCEPT_ATTACK  = -1000679,
    SAY_TYRION_1             = -1000680,
    SAY_SPYBOT_1             = -1000681,
    SAY_GUARD_1              = -1000682,
    SAY_SPYBOT_2             = -1000683,
    SAY_SPYBOT_3             = -1000684,
    SAY_LESCOVAR_1           = -1000685,
    SAY_SPYBOT_4             = -1000686,

    NPC_PRIESTESS_TYRIONA    = 7779

};

struct MANGOS_DLL_DECL npc_tyrion_spybotAI : public npc_escortAI
{
    npc_tyrion_spybotAI(Creature* pCreature) : npc_escortAI(pCreature) {Reset();}

    uint32 m_uiTimer;
    uint32 m_uiPhase;

    void Reset()
    {
        m_uiTimer = 0;
        m_uiPhase = 0;
    }

    void WaypointReached(uint32 uiPointId)
    {
        switch(uiPointId)
        {
            case 1:
                SetEscortPaused(true);
                m_uiTimer = 2000;
                m_uiPhase = 1;
                break;
            case 5:
                SetEscortPaused(true);
                DoScriptText(SAY_SPYBOT_1, m_creature);
                m_uiTimer = 2000;
                m_uiPhase = 5;
                break;
            case 17:
                SetEscortPaused(true);
                DoScriptText(SAY_SPYBOT_3, m_creature);
                m_uiTimer = 3000;
                m_uiPhase = 8;
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff)
    {
        if (m_uiPhase)
        {
            if (m_uiTimer <= uiDiff)
            {
                switch(m_uiPhase)
                {
                    case 1:
                        DoScriptText(SAY_QUEST_ACCEPT_ATTACK, m_creature);
                        m_uiTimer = 3000;
                        m_uiPhase = 2;
                        break;
                    case 2:
                        if (Creature* pTyrion =GetClosestCreatureWithEntry(m_creature, NPC_TYRION, 30.0f))
                            DoScriptText(SAY_TYRION_1, pTyrion);
                        m_uiTimer = 3000;
                        m_uiPhase = 3;
                        break;
                    case 3:
                        m_creature->UpdateEntry(NPC_PRIESTESS_TYRIONA, ALLIANCE);
                        m_uiTimer = 2000;
                        m_uiPhase = 4;
                        break;
                    case 4:
                        SetEscortPaused(false);
                        m_uiPhase = 0;
                        m_uiTimer = 0;
                        break;
                    case 5:
                        if (Creature* pGuard = GetClosestCreatureWithEntry(m_creature, NPC_STORMWIND_ROYAL, 10.0f))
                            DoScriptText(SAY_GUARD_1, pGuard);
                        m_uiTimer = 3000;
                        m_uiPhase = 6;
                        break;
                    case 6:
                        DoScriptText(SAY_SPYBOT_2, m_creature);
                        m_uiTimer = 3000;
                        m_uiPhase = 7;
                        break;
                    case 7:
                        SetEscortPaused(false);
                        m_uiTimer = 0;
                        m_uiPhase = 0;
                        break;
                    case 8:
                        if (Creature* pLescovar = GetClosestCreatureWithEntry(m_creature, NPC_LORD_GREGOR_LESCOVAR, 10.0f))
                            DoScriptText(SAY_LESCOVAR_1, pLescovar);
                        m_uiTimer = 3000;
                        m_uiPhase = 9;
                        break;
                    case 9:
                        DoScriptText(SAY_SPYBOT_4, m_creature);
                        m_uiTimer = 3000;
                        m_uiPhase = 10;
                        break;
                    case 10:
                        if (Creature* pLescovar = GetClosestCreatureWithEntry(m_creature, NPC_LORD_GREGOR_LESCOVAR, 10.0f))
                        {
                            if (Player* pPlayer = GetPlayerForEscort())
                            {
                                if (npc_lord_gregor_lescovarAI* pEscortAI = dynamic_cast<npc_lord_gregor_lescovarAI*>(pLescovar->AI()))
                                    pEscortAI->Start(true, pPlayer);

                            }
                        }
                        m_creature->ForcedDespawn(10);
                        m_uiTimer = 0;
                        m_uiPhase = 0;
                        break;
                }
            }
            else
                m_uiTimer -= uiDiff;
        }
    }

};

CreatureAI* GetAI_npc_tyrion_spybotAI(Creature* pCreature)
{
    return new npc_tyrion_spybotAI(pCreature);
}

/*######
## npc_tyrion
######*/

enum
{
    NPC_TYRION_SPYBOT = 8856
};

bool QuestAccept_npc_tyrion(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_THE_ATTACK)
    {
        if (Creature* pTyrionSpybot = GetClosestCreatureWithEntry(pCreature, NPC_TYRION_SPYBOT, 10.0f))
        {
            if (npc_tyrion_spybotAI* pEscortAI = dynamic_cast<npc_tyrion_spybotAI*>(pTyrionSpybot->AI()))
            {
                pEscortAI->Start(false, pPlayer, pQuest);
            }
            return true;
        }
    }
    return true;
};

void AddSC_stormwind_city()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_bartleby";
    pNewScript->GetAI = &GetAI_npc_bartleby;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_bartleby;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_dashel_stonefist";
    pNewScript->GetAI = &GetAI_npc_dashel_stonefist;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_dashel_stonefist;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_lady_katrana_prestor";
    pNewScript->pGossipHello = &GossipHello_npc_lady_katrana_prestor;
    pNewScript->pGossipSelect = &GossipSelect_npc_lady_katrana_prestor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_squire_rowe";
    pNewScript->GetAI = &GetAI_npc_squire_rowe;
    pNewScript->pGossipHello =  &GossipHello_npc_squire_rowe;
    pNewScript->pGossipSelect = &GossipSelect_npc_squire_rowe;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_reginald_windsor";
    pNewScript->GetAI = &GetAI_npc_reginald_windsor;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_reginald_windsor;
    pNewScript->pGossipHello =  &GossipHello_npc_reginald_windsor;
    pNewScript->pGossipSelect = &GossipSelect_npc_reginald_windsor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_lord_gregor_lescovar";
    pNewScript->GetAI = &GetAI_npc_lord_gregor_lescovarAI;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_marzon_silent_blade";
    pNewScript->GetAI = &GetAI_npc_marzon_silent_bladeAI;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_tyrion_spybot";
    pNewScript->GetAI = &GetAI_npc_tyrion_spybotAI;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_tyrion";
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_tyrion;
    pNewScript->RegisterSelf();
}
