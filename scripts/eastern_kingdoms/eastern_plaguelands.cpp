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
SDName: Eastern_Plaguelands
SD%Complete: 80
SDComment: Quest support: 5211, 5742, 7622. Special vendor Augustus the Touched
SDCategory: Eastern Plaguelands
EndScriptData */

/* ContentData
mobs_ghoul_flayer
npc_augustus_the_touched
npc_darrowshire_spirit
npc_tirion_fordring
npc_infected_peasant
npc_eris_havenfire
EndContentData */

#include "precompiled.h"

//id8530 - cannibal ghoul
//id8531 - gibbering ghoul
//id8532 - diseased flayer

struct MANGOS_DLL_DECL mobs_ghoul_flayerAI : public ScriptedAI
{
    mobs_ghoul_flayerAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset() { }

    void JustDied(Unit* Killer)
    {
        if (Killer->GetTypeId() == TYPEID_PLAYER)
            m_creature->SummonCreature(11064, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000);
    }

};

CreatureAI* GetAI_mobs_ghoul_flayer(Creature* pCreature)
{
    return new mobs_ghoul_flayerAI(pCreature);
}

/*######
## npc_augustus_the_touched
######*/

bool GossipHello_npc_augustus_the_touched(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pCreature->isVendor() && pPlayer->GetQuestRewardStatus(6164))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_VENDOR, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_augustus_the_touched(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_TRADE)
        pPlayer->SEND_VENDORLIST(pCreature->GetObjectGuid());
    return true;
}

/*######
## npc_darrowshire_spirit
######*/

#define SPELL_SPIRIT_SPAWNIN    17321

struct MANGOS_DLL_DECL npc_darrowshire_spiritAI : public ScriptedAI
{
    npc_darrowshire_spiritAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    void Reset()
    {
        DoCastSpellIfCan(m_creature,SPELL_SPIRIT_SPAWNIN);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }
};

CreatureAI* GetAI_npc_darrowshire_spirit(Creature* pCreature)
{
    return new npc_darrowshire_spiritAI(pCreature);
}

bool GossipHello_npc_darrowshire_spirit(Player* pPlayer, Creature* pCreature)
{
    pPlayer->SEND_GOSSIP_MENU(3873, pCreature->GetObjectGuid());
    pPlayer->TalkedToCreature(pCreature->GetEntry(), pCreature->GetObjectGuid());
    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    return true;
}

/*######
## npc_tirion_fordring
######*/

enum
{
    QUEST_REDEMPTION             = 5742,

    TIRION_GOSSIP_ITEM_1         = -3000106,
    TIRION_GOSSIP_ITEM_2         = -3000107,
    TIRION_GOSSIP_ITEM_3         = -3000108,
    TIRION_GOSSIP_ITEM_4         = -3000109,
};

bool GossipHello_npc_tirion_fordring(Player* pPlayer, Creature* pCreature)
{
    if (pPlayer->GetQuestStatus(QUEST_REDEMPTION) == QUEST_STATUS_INCOMPLETE && pPlayer->getStandState() == UNIT_STAND_STATE_SIT)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, TIRION_GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
    else
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_tirion_fordring(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, TIRION_GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            pPlayer->SEND_GOSSIP_MENU(4493, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, TIRION_GOSSIP_ITEM_3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            pPlayer->SEND_GOSSIP_MENU(4494, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, TIRION_GOSSIP_ITEM_4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            pPlayer->SEND_GOSSIP_MENU(4495, pCreature->GetObjectGuid());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            pPlayer->CLOSE_GOSSIP_MENU();
            pPlayer->AreaExploredOrEventHappens(QUEST_REDEMPTION);
            break;
    }
    return true;
}

/*######
## npc_taelan_fordring
######*/

enum
{
    QUEST_IN_DREAMS              = 5944,
};

/*######
## npc_infected_peasant
######*/

enum
{
    SPELL_DEATHS_DOOR           = 23127, // Green (weak)
    SPELL_SEETHING_PLAGUE       = 23072, // Purple (strong)

    NPC_INJURED_PEASANT         = 14484,
    NPC_PLAGUED_PEASANT         = 14485,

    SPELL_ENTER_THE_LIGHT_DND   = 23107
};

struct MANGOS_DLL_DECL npc_infected_peasantAI : public ScriptedAI
{
    npc_infected_peasantAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiDiseaseTimer;

    void Reset() {m_uiDiseaseTimer = 0;}

    void AttackStart(Unit* pVictim) {return;}

    // I still don't know from where I got these values
    void UpdateAI(const uint32 uiDiff)
    {
        // Holding this aura means that this NPC is saved
        if (m_creature->HasAura(SPELL_ENTER_THE_LIGHT_DND, EFFECT_INDEX_0))
            return;

        // And again... Messy, untidy, bullshit code ...for eyes :D
        if (m_uiDiseaseTimer <= uiDiff)
        {
            uint16 uiChance = urand(1,100);

            if (uiChance <= 10 && m_creature->GetEntry() == NPC_INJURED_PEASANT)
                m_creature->CastSpell(m_creature, SPELL_DEATHS_DOOR, false);
            else if (uiChance <= 25)
            {
                if (m_creature->GetEntry() == NPC_PLAGUED_PEASANT)
                    m_creature->CastSpell(m_creature, SPELL_SEETHING_PLAGUE, false);
                else
                    m_creature->CastSpell(m_creature, SPELL_DEATHS_DOOR, false);
            }
            else if (uiChance <= 40 && m_creature->GetEntry() == NPC_PLAGUED_PEASANT)
                m_creature->CastSpell(m_creature, SPELL_DEATHS_DOOR, false);

            m_uiDiseaseTimer = urand(8000,10000);
        }
        else
            m_uiDiseaseTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_infected_peasant(Creature* pCreature)
{
    return new npc_infected_peasantAI(pCreature);
}

/*######
## npc_eris_havenfire
######*/

// Get the right spawns for both aArcherSpawn and aPeasantSpawn
static const float aArcherSpawn[8][3] =
{
    {3327.42f, -3021.11f, 170.579f},
    {3335.4f, -3054.3f, 173.636f},
    {3314.3f, -3017.5f, 162.094f},
    {3351.3f, -3079.08f, 178.678f},
    {3358.93f, -3076.1f, 174.875f},
    {3371.58f, -3069.24f, 175.201f},
    {3377.78f, -3041.79f, 173.068f},
    {3369.46f, -3023.11f, 171.831f}
};

static const float aPeasantSpawn[15][3] =
{
    {3352.44f, -3048.32f, 164.833f},
    {3355.26f, -3052.93f, 165.72f},
    {3358.12f, -3050.71f, 165.307f},
    {3360.07f, -3052.31f, 165.3f},
    {3361.64f, -3055.29f, 165.295f},
    {3361.4f, -3052.17f, 165.261f},
    {3363.13f, -3056.21f, 165.285f},
    {3363.99f, -3054.49f, 165.342f},
    {3366.84f, -3053.95f, 165.541f},
    {3367.61f, -3056.84f, 165.88f},
    {3364.9f, -3052.68f, 165.321f},
    {3363.3f, -3051.2f, 165.266f},
    {3367.61f, -3051.14f, 165.517f},
    {3363.54f, -3049.64f, 165.238f},
    {3360.66f, -3049.14f, 165.261f}
};

static const uint32 aPeasantSpawnYell[] = {-1000696, -1000697, -1000698};
static const uint32 aPeasantRandomSay[] = {-1000699, -1000700, -1000701}; // TODO
static const uint32 aPeasantSaveSay[] = {-1000702, -1000703, -1000704, -1000705};

enum
{
    QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW    = 7622,

    NPC_SCOURGE_ARCHER                       = 14489,
    NPC_SCOURGE_FOOTSOLDIER                  = 14486,

    SPELL_BLESSING_OF_NORDRASSIL             = 23108
};

// Never show this code to your friends. It's Super-Duper!!
struct MANGOS_DLL_DECL npc_eris_havenfireAI : public ScriptedAI
{
    npc_eris_havenfireAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_bIsQuestInProgress = false;
        Reset();
    }

    bool m_bIsQuestInProgress;
    uint64 m_uiMainTimer;
    uint8 m_uiPhase, m_uiCurrentWave, m_uiKillCounter, m_uiSaveCounter, m_uiTotalSaved, m_uiTotalKilled;
    ObjectGuid m_playerGuid;
    GUIDList m_lSummonedGUIDList;

    void Reset()
    {
        // No need to continue while 'WE ARE IN'!!
        if (m_bIsQuestInProgress)
            return;

        m_bIsQuestInProgress = false;
        m_uiMainTimer = 5000;
        m_uiPhase = 1;
        m_uiCurrentWave = 0;
        m_uiKillCounter = 0;
        m_uiSaveCounter = 0;
        m_uiTotalSaved = 0;
        m_uiTotalKilled = 0;
        m_playerGuid.Clear();

        if (!m_creature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER))
            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);

        // Despawn when something is spawned
        if (!m_lSummonedGUIDList.empty())
        {
            for (GUIDList::const_iterator itr = m_lSummonedGUIDList.begin(); itr != m_lSummonedGUIDList.end(); ++itr)
                if (Creature* pSummoned = m_creature->GetMap()->GetCreature(*itr))
                    pSummoned->ForcedDespawn();
        }
        m_lSummonedGUIDList.clear();
    }

    void PhaseEnded(bool bFailed, bool bWave)
    {
        Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid);

        // Continue only when we have starting player
        if (!pPlayer)
            return;

        // Failed
        if (bFailed && !bWave)
        {
            DoScriptText(urand(0, 1) ? -1000706 : -1000707, m_creature);
            if (pPlayer->GetQuestStatus(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW) == QUEST_STATUS_INCOMPLETE)
                pPlayer->FailQuest(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW);

            m_bIsQuestInProgress = false;
            Reset();
            return;
        }

        // Wave completed
        if (!bFailed && bWave)
        {
            DoScriptText(-1000709, m_creature);
            m_creature->CastSpell(pPlayer, SPELL_BLESSING_OF_NORDRASSIL, false);
            // m_uiSaveCounter and m_uiKillCounter are only temporar values
            m_uiSaveCounter = 0;
            m_uiKillCounter = 0;
            return;
        }

        // Whole event completed
        if (!bFailed && !bWave)
        {
            DoScriptText(-1000708, m_creature);
            if (pPlayer->GetQuestStatus(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW) == QUEST_STATUS_INCOMPLETE)
                pPlayer->AreaExploredOrEventHappens(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW);

            m_bIsQuestInProgress = false;
            Reset();
            return; // Formal return?
        }
    }

    void DoNextWave(bool bInit)
    {
        if (bInit)
        {
            for(uint8 i = 0; i < 9; ++i)
            {
                if (Creature* pTemp = m_creature->SummonCreature(NPC_SCOURGE_ARCHER, aArcherSpawn[i][0], aArcherSpawn[i][1], aArcherSpawn[i][2], 0, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 360000))
                {
                    m_lSummonedGUIDList.push_back(pTemp->GetObjectGuid());
                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                }
            }
            return;
        }

        ++m_uiCurrentWave;

        uint8 uiShorter = 10 + m_uiCurrentWave;
        uint8 uiRandomPeasant = urand(0, uiShorter);

        for(uint8 i = 0; i < uiShorter; ++i)
        {
            // As I'm reading through the code now, I see that there is a 1:7 chance to spawn a NPC_PLAGUED_PEASANT instead NPC_INJURED_PEASANT.
            // The chance increases by each phase with 1 (Phase 1 - 1:7, Phase 2 - 2:7, etc...)
            if (Creature* pTemp = m_creature->SummonCreature(urand(0, 7 - m_uiCurrentWave) ? NPC_INJURED_PEASANT : NPC_PLAGUED_PEASANT, aPeasantSpawn[i][0], aPeasantSpawn[i][1], aPeasantSpawn[i][2], 0, TEMPSUMMON_DEAD_DESPAWN, 0))
            {
                float fX, fY, fZ;
                pTemp->GetRandomPoint(3332.767f, -2979.002f, 160.97f, 5.0f, fX, fY, fZ);
                pTemp->GetMotionMaster()->MovePoint(1, fX, fY, fZ);
                if (i == uiRandomPeasant)
                    DoScriptText(aPeasantSpawnYell[urand(0,2)], pTemp);
            }
        }
    }

    void SummonedMovementInform(Creature* pSummoned, uint32 /*uiMotionType*/, uint32 uiPointId)
    {
        if (uiPointId == 1)
        {
            if (m_uiSaveCounter >= 10 + m_uiCurrentWave) // When saved peasants exceed maximum peasants, something went wrong ^^
                debug_log("SD0: npc_eris_havenfire: Current wave %u was not reset properly in void WaveFinished().", m_uiCurrentWave);

            ++m_uiSaveCounter;
            ++m_uiTotalSaved;

            // When counted, force despawn. I don't know exactly when they should disappear
            pSummoned->GetMotionMaster()->Clear(false);

            if (pSummoned->HasAura(SPELL_DEATHS_DOOR, EFFECT_INDEX_0))
                pSummoned->RemoveAurasDueToSpell(SPELL_DEATHS_DOOR);

            if (pSummoned->HasAura(SPELL_SEETHING_PLAGUE, EFFECT_INDEX_0))
                pSummoned->RemoveAurasDueToSpell(SPELL_SEETHING_PLAGUE);

            uint8 uiRandomPeasant = urand(1,10);
            if (uiRandomPeasant == 5)
                DoScriptText(aPeasantSaveSay[urand(0,3)], pSummoned);

            pSummoned->CastSpell(pSummoned, SPELL_ENTER_THE_LIGHT_DND, false);
            pSummoned->ForcedDespawn(4000);
        }
    }

    void SummonedCreatureJustDied(Creature* pSummoned)
    {
       /* We do not want to count staying peasants.
        * It means that they are saved. Saved peasants are ForcedDespawn(),
        * which triggers SummonedCreatureJustDied.
        */
        if (pSummoned->GetMotionMaster()->GetCurrentMovementGeneratorType() != IDLE_MOTION_TYPE &&
           (pSummoned->GetEntry() == NPC_INJURED_PEASANT || pSummoned->GetEntry() == NPC_PLAGUED_PEASANT))
        {
            ++m_uiKillCounter;
            ++m_uiTotalKilled;
        }
        pSummoned->RemoveCorpse();
    }

    void DoSummonFootsoldier()
    {
        Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid);

        for(uint8 i = 0; i < 6 + 1; ++i)
        {
            float fX, fY, fZ;

            if (pPlayer)
            {
                pPlayer->GetRandomPoint(pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 15.0f, fX, fY, fZ);

                if (Creature* pTemp = m_creature->SummonCreature(NPC_SCOURGE_FOOTSOLDIER, fX, fY, fZ, 0, TEMPSUMMON_DEAD_DESPAWN, 0))
                    m_lSummonedGUIDList.push_back(pTemp->GetObjectGuid());
            }
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Nothing is needed to update when the event is not in progress
        if (!m_bIsQuestInProgress)
            return;

        if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
        {
            pPlayer->DeleteThreatList();
            if (pPlayer->GetQuestStatus(QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW) != QUEST_STATUS_INCOMPLETE || pPlayer->isDead())
            {
                m_bIsQuestInProgress = false;
                Reset();
                return;
            }
        }

        if (m_uiPhase)
        {
            // Reaching 15 dead peasants means fail for us
            if (m_uiTotalKilled >= 15)
            {
                PhaseEnded(true, false);
                return;
            }
            // Do next step
            else if (m_uiKillCounter + m_uiSaveCounter == 10 + m_uiCurrentWave)
            {
                // When we saved 50 peasants
                if (m_uiTotalSaved >= 50)
                    PhaseEnded(false, false);
                // When the wave completed, but still we are not done
                else
                    PhaseEnded(false, true);

                return;
            }

            // No more phases or no wave
            if (m_uiPhase >= 15 || !m_uiCurrentWave)
                return;

            // Force Archers to attack peasants
            if (!m_lSummonedGUIDList.empty())
            {
                for (GUIDList::const_iterator itr = m_lSummonedGUIDList.begin(); itr != m_lSummonedGUIDList.end(); ++itr)
                {
                    if (Creature* pArcher = m_creature->GetMap()->GetCreature(*itr))
                    {
                        // Archer is not an 'archer'
                        if (pArcher->GetEntry() != NPC_SCOURGE_ARCHER)
                            continue;

                        if (pArcher->getVictim())
                            if (((pArcher->getVictim()->GetEntry() == NPC_PLAGUED_PEASANT || pArcher->getVictim()->GetEntry() == NPC_INJURED_PEASANT)) &&
                                !pArcher->getVictim()->HasAura(SPELL_ENTER_THE_LIGHT_DND, EFFECT_INDEX_0))
                                continue;

                        float fRange = 59.9f; // Range above 60 yd is not valid, because ACID recognizes it as out of range

                       /* Make the chance of being a victim equal for each peasant.
                        * I mean that now NPC_INJURED_PEASANT has now a bigger chance to be a target,
                        * because it is checked in the first place. On the second is NPC_PLAGUED_PEASANT.
                        * So this is needed to be solved.
                        */

                        Creature* pPeasant = GetClosestCreatureWithEntry(pArcher, NPC_INJURED_PEASANT, fRange);
                        if (!pPeasant)
                            pPeasant = GetClosestCreatureWithEntry(pArcher, NPC_PLAGUED_PEASANT, fRange);

                        if (pPeasant && !pPeasant->HasAura(SPELL_ENTER_THE_LIGHT_DND, EFFECT_INDEX_0))
                            pArcher->AI()->AttackStart(pPeasant);
                        else if (pArcher->getVictim())
                            pArcher->AI()->EnterEvadeMode();
                    }
                }
            }


            if (m_uiMainTimer < uiDiff)
            {
                switch(m_uiPhase)
                {
                    case 1: // Spawn Archers
                        DoNextWave(true);
                        m_uiMainTimer = 2000;
                        break;
                    case 2: // Wave 1
                        DoNextWave(false);
                        m_uiMainTimer = 60000;
                        break;
                    case 3: // Wave 2
                        DoNextWave(false);
                        m_uiMainTimer = 20000;
                        break;
                    case 4: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 5: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 6: // Wave 3 + Summon Scourge Footsoldiers
                        DoNextWave(false);
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 7: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 8: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 9: // Wave 4 + Summon Scourge Footsoldiers
                        DoNextWave(false);
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 10: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 11: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 12: // Wave 5 + Summon Scourge Footsoldiers
                        DoNextWave(false);
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 13: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 20000;
                        break;
                    case 14: // Summon Scourge Footsoldiers
                        DoSummonFootsoldier();
                        m_uiMainTimer = 0;
                        break;
                }

               /* Just a note:
                * Phase is NOT Wave. Phase means a part of this event in this script.
                * Wave means a wave of peasants. We have maximum of 5 waves. You never can be clear enough :P
                */
                ++m_uiPhase;
            }
            else
                m_uiMainTimer -= uiDiff;
        }
        else // Impossible to have m_bIsQuestInProgress and !m_uiPhase
            debug_log("SD0: npc_eris_havenfire: No phase detected!");

    }
};

bool QuestAccept_npc_eris_havenfire(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_THE_BALANCE_OF_LIGHT_AND_SHADOW)
    {
        // Everybody loves dynamic casts <3
        if (npc_eris_havenfireAI* pEris = dynamic_cast<npc_eris_havenfireAI*>(pCreature->AI()))
        {
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            pEris->m_bIsQuestInProgress = true;
            pEris->m_uiCurrentWave = 1;
            pEris->m_playerGuid = pPlayer->GetObjectGuid();
        }
    }

    return true;
}

CreatureAI* GetAI_npc_eris_havenfire(Creature* pCreature)
{
    return new npc_eris_havenfireAI(pCreature);
}

void AddSC_eastern_plaguelands()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "mobs_ghoul_flayer";
    pNewScript->GetAI = &GetAI_mobs_ghoul_flayer;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_augustus_the_touched";
    pNewScript->pGossipHello = &GossipHello_npc_augustus_the_touched;
    pNewScript->pGossipSelect = &GossipSelect_npc_augustus_the_touched;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_darrowshire_spirit";
    pNewScript->GetAI = &GetAI_npc_darrowshire_spirit;
    pNewScript->pGossipHello = &GossipHello_npc_darrowshire_spirit;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_tirion_fordring";
    pNewScript->pGossipHello = &GossipHello_npc_tirion_fordring;
    pNewScript->pGossipSelect = &GossipSelect_npc_tirion_fordring;
    pNewScript->RegisterSelf();

    /*pNewScript = new Script;
    pNewScript->Name = "npc_taelan_fordring";
    pNewScript->RegisterSelf();*/

    pNewScript = new Script;
    pNewScript->Name = "npc_infected_peasant";
    pNewScript->GetAI = &GetAI_npc_infected_peasant;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_eris_havenfire";
    pNewScript->GetAI = &GetAI_npc_eris_havenfire;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_eris_havenfire;
    pNewScript->RegisterSelf();
}
