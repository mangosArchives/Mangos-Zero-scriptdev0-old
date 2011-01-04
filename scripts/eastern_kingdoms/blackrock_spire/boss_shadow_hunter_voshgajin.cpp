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
SDName: Boss_Shadow_Hunter_Voshgajin
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_CURSEOFBLOOD = 24673,
    SPELL_HEX          = 16708,
    SPELL_CLEAVE       = 20691
};

struct MANGOS_DLL_DECL boss_shadowvoshAI : public ScriptedAI
{
    boss_shadowvoshAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 m_uiCurseOfBloodTimer;
    uint32 m_uiHexTimer;
    uint32 m_uiCleaveTimer;

    void Reset()
    {
        m_uiCurseOfBloodTimer = urand(1000, 4000);
        m_uiHexTimer          = urand(6000, 10000);
        m_uiCleaveTimer       = urand(12000, 18000);

        //m_creature->CastSpell(m_creature,SPELL_ICEARMOR,true);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Curse Of Blood
        if (m_uiCurseOfBloodTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_CURSEOFBLOOD);
            m_uiCurseOfBloodTimer = urand(40000, 45000);
        }
        else
            m_uiCurseOfBloodTimer -= uiDiff;

        // Hex
        if (m_uiHexTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_HEX);
            m_uiHexTimer = urand(12000, 18000);
        }
        else
            m_uiHexTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
            m_uiCleaveTimer = urand(5000, 10000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_shadowvosh(Creature* pCreature)
{
    return new boss_shadowvoshAI(pCreature);
}

void AddSC_boss_shadowvosh()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_shadow_hunter_voshgajin";
    newscript->GetAI = &GetAI_boss_shadowvosh;
    newscript->RegisterSelf();
}