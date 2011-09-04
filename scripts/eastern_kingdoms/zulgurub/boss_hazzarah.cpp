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
SDName: Boss_Hazzarah
SD%Complete: 95
SDComment: TODO: Get correct timers. Move to ACID when possible.
SDCategory: Zul'Gurub
EndScriptData */

#include "precompiled.h"
#include "zulgurub.h"

enum
{
    SPELL_SLEEP           = 24664,
    SPELL_ILLUSIONS       = 24728,
    SPELL_CHAIN_BURN      = 24684
};

struct MANGOS_DLL_DECL boss_hazzarahAI : public ScriptedAI
{
    boss_hazzarahAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiSleepTimer;
    uint32 m_uiIllusionsTimer;
    uint32 m_uiChainBurnTimer;

    void Reset()
    {
        m_uiSleepTimer = urand(14000,23000);
        m_uiIllusionsTimer = urand(10000,18000);
        m_uiChainBurnTimer = urand(4000,10000);
    }

    void JustSummoned(Creature* pSummoned)
    {
        if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            pSummoned->AI()->AttackStart(pTarget);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Chain Burn
        if (m_uiChainBurnTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0), SPELL_CHAIN_BURN);
            m_uiChainBurnTimer = urand(8000,16000);
        }
        else m_uiChainBurnTimer -= uiDiff;

        // Sleep
        if (m_uiSleepTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SLEEP);
            m_uiSleepTimer = urand(12000,20000);
        }
        else m_uiSleepTimer -= uiDiff;

        // Illusions
        if (m_uiIllusionsTimer < uiDiff)
        {
            //We will summon 3 illusions which attacks rangom players
            for(int i = 0; i < 3; ++i)
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_ILLUSIONS);

            m_uiIllusionsTimer = urand(15000,25000);
        }
        else m_uiIllusionsTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_hazzarah(Creature* pCreature)
{
    return new boss_hazzarahAI(pCreature);
}

void AddSC_boss_hazzarah()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_hazzarah";
    pNewScript->GetAI = &GetAI_boss_hazzarah;
    pNewScript->RegisterSelf();
}
