/* Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Gyth
SD%Complete: 100
SDComment: Event completed!
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_CORROSIVEACID     = 16359,
    SPELL_FREEZE            = 16350,                        // ID was wrong!
    SPELL_FLAMEBREATH       = 16390,
    SPELL_KNOCK_AWAY        = 10101,
    SPELL_CHROMATIC_CHAOS   = 16337,

    MODEL_ID_GYTH_MOUNTED   = 9723,
    MODEL_ID_GYTH           = 9806
};

struct MANGOS_DLL_DECL boss_gythAI : public ScriptedAI
{
    boss_gythAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 uiCorrosiveAcidTimer;
    uint32 uiFreezeTimer;
    uint32 uiFlamebreathTimer;
    uint32 uiKnockAwayTimer;
    uint32 DoorTimer;

    bool inCombat;
    bool isMove;
    bool m_bSummonedRend;
    bool m_bBuffed;

    Creature* pRend;
    Creature* pNefarius;

    void Reset()
    {
        if (!m_pInstance)
            return;

        uiCorrosiveAcidTimer = 8000;
        uiFreezeTimer = 11000;
        uiFlamebreathTimer = 4000;
        uiKnockAwayTimer = 15000;
        DoorTimer = 10000;
        inCombat = false;
        m_bSummonedRend = false;
        m_bBuffed = false;
        isMove = false;
        pRend = NULL;
        pNefarius = NULL;
        inCombat = false;
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetVisibility(VISIBILITY_OFF);
        m_creature->SetDisplayId(MODEL_ID_GYTH_MOUNTED);
        m_pInstance->SetData(TYPE_GYTH, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        if (!m_pInstance)
            return;

        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_GYTH, DONE);
            if (m_pInstance->GetData(TYPE_GYTH_LOOTED) == DONE)
                m_creature->RemoveFromWorld();

            if (m_pInstance->GetData(TYPE_GYTH_LOOTED) != DONE)
                m_pInstance->SetData(TYPE_GYTH_LOOTED, DONE);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (!inCombat)
        {
            if (m_pInstance->GetData(TYPE_GYTH) == IN_PROGRESS)
            {
                inCombat = true;
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                m_creature->SetVisibility(VISIBILITY_ON);
                return;
            }
            return;
        }

        if (!isMove)
        {
            isMove = true;
            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MovePoint(0, 153.763f, -419.833f, 110.472f);
        }

        if (GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_STADIUM_COMBAT_DOOR)))
        {
            if (pDoor->GetGoState() == GO_STATE_ACTIVE)
            {
                if (DoorTimer < uiDiff)
                    pDoor->UseDoorOrButton();
                else DoorTimer -= uiDiff;
            }
        }

        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        else EnterCombat(m_creature->getVictim());

        // Corrosive Acid
        if (uiCorrosiveAcidTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_CORROSIVEACID);
            uiCorrosiveAcidTimer = 7000;
        }
        else
            uiCorrosiveAcidTimer -= uiDiff;

        // Freeze_Timer
        if (uiFreezeTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FREEZE) == CAST_OK)
            uiFreezeTimer = 16000;
        }
        else
            uiFreezeTimer -= uiDiff;

        // Flamebreath
        if (uiFlamebreathTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FLAMEBREATH);
            uiFlamebreathTimer = 10500;
        }
        else
            uiFlamebreathTimer -= uiDiff;

        // Knock Away
        if (uiKnockAwayTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_KNOCK_AWAY);
            uiKnockAwayTimer = 9000;
        }
        else
            uiKnockAwayTimer -= uiDiff;

        // Summon Rend
        if (!m_bSummonedRend && m_creature->GetHealthPercent() < 15.0f)
        {
            pRend = GetClosestCreatureWithEntry(m_creature, NPC_REND_BLACKHAND, DEFAULT_VISIBILITY_INSTANCE);
            if (pRend)
                pRend->Relocate(m_creature->GetPositionX() + 5.0f, m_creature->GetPositionY() + 5.0f, m_creature->GetPositionZ());

            m_pInstance->SetData(TYPE_REND_BLACKHAND, SPECIAL);

            // summon Rend and Change model to normal Gyth
            // Inturrupt any spell casting
            m_creature->InterruptNonMeleeSpells(false);
            // Gyth model
            m_creature->SetDisplayId(MODEL_ID_GYTH);
            m_bSummonedRend = true;
        }


        // Chromatic Chaos
        if (!m_bBuffed && m_creature->GetHealthPercent() < 50.0f)
        {
            pNefarius = GetClosestCreatureWithEntry(m_creature, NPC_LORD_VICTOR_NEFARIUS, DEFAULT_VISIBILITY_INSTANCE);
            if (pNefarius)
            {
                DoScriptText(NEFARIUS_SAY_10, pNefarius);
                DoCastSpellIfCan(m_creature, SPELL_CHROMATIC_CHAOS);
                m_bBuffed = true;
            }
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_gyth(Creature* pCreature)
{
    return new boss_gythAI(pCreature);
}

void AddSC_boss_gyth()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_gyth";
    pNewScript->GetAI = &GetAI_boss_gyth;
    pNewScript->RegisterSelf();
}