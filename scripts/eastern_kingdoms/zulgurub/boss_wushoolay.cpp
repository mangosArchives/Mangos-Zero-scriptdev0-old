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
SDName: Boss_Wushoolay
SD%Complete: 95
SDComment: TODO: Get correct timers. Move to ACID when possible.
SDCategory: Zul'Gurub
EndScriptData */

#include "precompiled.h"
#include "zulgurub.h"

enum
{
    SPELL_LIGHTNING_CLOUD        = 24683,
    SPELL_FORKED_LIGHTNING       = 24682,
    SPELL_CHAIN_LIGHTNING        = 24680
};

struct MANGOS_DLL_DECL boss_wushoolayAI : public ScriptedAI
{
    boss_wushoolayAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiLightningCloudTimer;
    uint32 m_uiForkedLightningTimer;
    uint32 m_uiChainLightningTimer;

    void Reset()
    {
        m_uiLightningCloudTimer = urand(5000,10000);
        m_uiForkedLightningTimer = urand(8000,16000);
        m_uiChainLightningTimer = urand(7000,18000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Lightning Cloud
        if (m_uiLightningCloudTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_LIGHTNING_CLOUD);
            m_uiLightningCloudTimer = urand(15000,20000);
        }
        else m_uiLightningCloudTimer -= uiDiff;

        // Forked Lightning
        if (m_uiForkedLightningTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_FORKED_LIGHTNING);

            m_uiForkedLightningTimer = urand(12000,16000);
        }
        else m_uiForkedLightningTimer -= uiDiff;

        // Chain Lightning
        if (m_uiChainLightningTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,0), SPELL_CHAIN_LIGHTNING);

            m_uiChainLightningTimer = urand(12000,16000);
        }
        else m_uiChainLightningTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_wushoolay(Creature* pCreature)
{
    return new boss_wushoolayAI(pCreature);
}

void AddSC_boss_wushoolay()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_wushoolay";
    pNewScript->GetAI = &GetAI_boss_wushoolay;
    pNewScript->RegisterSelf();
}
