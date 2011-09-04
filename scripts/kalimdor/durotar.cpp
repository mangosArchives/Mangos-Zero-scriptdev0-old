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
SDName: Durotar
SD%Complete: 95
SDComment: Quest support: 5441
SDCategory: Durotar
EndScriptData */

/* ContentData
npc_lazy_peon
EndContentData */

#include "precompiled.h"

/*######
##npc_lazy_peon
######*/

/* This is what happens:
 *  1. Peon gets hit on the head and wakes up
 *  2. Peon runs to lumber pile
 *  3. Peon walks to the tree and starts chopping
 *  4. Peon walks back to the lumber pile
 *  5. Peon repeats steps 3 and 4 a few times, then goes back to sleep
 * Timers and emotes might be incorrect since the event has changed after 1.12
 */

enum
{
    SAY_SPELL_HIT       = -1000639, //Ow! Ok, I'll get back to work, $N!

    SPELL_BUFF_SLEEP    = 17743,
    SPELL_AWAKEN_PEON   = 19938,

    QUEST_LAZY_PEONS    = 5441,

    GO_LUMBERPILE       = 175784
};

struct MANGOS_DLL_DECL npc_lazy_peonAI : public ScriptedAI
{
    npc_lazy_peonAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    bool m_bWork;
    float m_fStartX, m_fStartY, m_fStartZ, m_fLumberX, m_fLumberY, m_fLumberZ;

    uint32 m_uiTimeToWork, m_uiTimeToChop, m_uiTimeToWait,
           m_uiWorkTimer, m_uiChopTimer, m_uiWaitTimer;

    void Reset ()
    {
        m_uiTimeToWork = 300000;
        m_uiTimeToChop = 10000;
        m_uiTimeToWait = 2000;
        m_bWork = false;
        m_uiWorkTimer = 0;
        m_uiChopTimer = 0;
        m_uiWaitTimer = m_uiTimeToWait;
    }

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        m_creature->GetRespawnCoord(m_fStartX,m_fStartY,m_fStartZ);

        if (GameObject* pLumber = GetClosestGameObjectWithEntry(m_creature,GO_LUMBERPILE,20))
            pLumber->GetPosition(m_fLumberX,m_fLumberY,m_fLumberZ);

        if (spell->Id == SPELL_AWAKEN_PEON && caster->GetTypeId() == TYPEID_PLAYER
            && ((Player*)caster)->GetQuestStatus(QUEST_LAZY_PEONS) == QUEST_STATUS_INCOMPLETE && !m_bWork)
        {
            ((Player*)caster)->KilledMonsterCredit(m_creature->GetEntry(),m_creature->GetObjectGuid());
            DoScriptText(SAY_SPELL_HIT, m_creature, caster);
            m_creature->RemoveAllAuras();
            m_creature->HandleEmoteState(EMOTE_STATE_STAND);
            m_uiWorkTimer = m_uiTimeToWork;
            m_bWork = true;
        }
    }

    void MovementInform(uint32 uiMoveType, uint32 uiWpId)
    {
        if (uiMoveType != POINT_MOTION_TYPE || !m_bWork)
            return;
        switch (uiWpId)
        {
            case 1:
                m_creature->HandleEmoteState(EMOTE_STATE_WORK_CHOPWOOD);
                m_uiChopTimer = m_uiTimeToChop;
                break;
            case 2:
                m_creature->SetOrientation(m_creature->GetAngle(m_fLumberX,m_fLumberY));
                m_creature->StopMoving();
                m_creature->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
                m_uiWaitTimer = m_uiTimeToWait;
                break;
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (m_bWork == true)
        {
            if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType()==IDLE_MOTION_TYPE)
            {
                if (m_uiWaitTimer <= uiDiff)
                {
                    if (m_creature->IsWithinDist3d(m_fStartX,m_fStartY,m_fStartZ,1) && m_uiChopTimer <= uiDiff)
                    {
                        m_creature->HandleEmoteState(EMOTE_STATE_NONE);

                        if (m_uiChopTimer == 0)
                        {
                            m_creature->RemoveSplineFlag(SPLINEFLAG_WALKMODE);
                            m_creature->GetMotionMaster()->MovePoint(2,m_fLumberX-1,m_fLumberY,m_fLumberZ);
                            m_creature->SetSplineFlags(SPLINEFLAG_WALKMODE);
                        }
                        else
                            m_creature->GetMotionMaster()->MovePoint(2,m_fLumberX-1,m_fLumberY,m_fLumberZ);
                    }
                    else if (m_creature->IsWithinDist3d(m_fLumberX-1,m_fLumberY,m_fLumberZ,2))
                        m_creature->GetMotionMaster()->MovePoint(1,m_fStartX,m_fStartY,m_fStartZ);
                }

                if (m_uiWorkTimer > uiDiff)
                    m_uiWorkTimer -= uiDiff;

                if (m_uiChopTimer > uiDiff)
                    m_uiChopTimer -= uiDiff;

                if (m_uiWaitTimer > uiDiff)
                    m_uiWaitTimer -= uiDiff;
            }

            if (m_uiWorkTimer <= uiDiff)
            {
                m_creature->StopMoving();
                m_creature->HandleEmoteState(EMOTE_STATE_NONE);
                DoCastSpellIfCan(m_creature, SPELL_BUFF_SLEEP);
                Reset();
            }
        }
    }
};

CreatureAI* GetAI_npc_lazy_peon(Creature* pCreature)
{
    return new npc_lazy_peonAI(pCreature);
}

void AddSC_durotar()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_lazy_peon";
    pNewScript->GetAI = &GetAI_npc_lazy_peon;
    pNewScript->RegisterSelf();
}
