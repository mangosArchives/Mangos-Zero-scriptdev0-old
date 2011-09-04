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
SDName: Boss_Grilek
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "precompiled.h"
#include "zulgurub.h"

enum
{
    SPELL_AVARTAR                = 24646,
    SPELL_GROUND_TREMOR          = 6524,
    SPELL_ENTAGLING_ROOTS        = 24648,
    SPELL_STUN                   = 24647 // ???
};

struct MANGOS_DLL_DECL boss_grilekAI : public ScriptedAI
{
    boss_grilekAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiAvartarTimer;
    uint32 m_uiGroundTremorTimer;
    uint32 m_uiEntanglingRootsTimer;

    void Reset()
    {
        m_uiAvartarTimer = 20000;
        m_uiGroundTremorTimer = 40000;
        m_uiEntanglingRootsTimer = urand(10000,14000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Avartar Timer
        if (m_uiAvartarTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_AVARTAR);
            DoResetThreat();
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
                AttackStart(pTarget);

            m_uiAvartarTimer = urand(40000,50000);
        }
        else m_uiAvartarTimer -= uiDiff;

        // Ground Tremor
        if (m_uiGroundTremorTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_GROUND_TREMOR);
            m_uiGroundTremorTimer = urand(12000,16000);
        }
        else m_uiGroundTremorTimer -= uiDiff;

        // Entangling Roots
        if (m_uiEntanglingRootsTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0), SPELL_ENTAGLING_ROOTS);
            m_uiEntanglingRootsTimer = urand(10000,12000);
        }
        else m_uiEntanglingRootsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_grilek(Creature* pCreature)
{
    return new boss_grilekAI(pCreature);
}

void AddSC_boss_grilek()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_grilek";
    pNewScript->GetAI = &GetAI_boss_grilek;
    pNewScript->RegisterSelf();
}
