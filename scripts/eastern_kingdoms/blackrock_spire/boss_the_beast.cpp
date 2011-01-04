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
SDName: Boss_The_Best
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_FLAMEBREAK       = 16785,
    SPELL_IMMOLATE         = 15570,
    SPELL_TERRIFYINGROAR   = 14100,
    SPELL_FIREBALL         = 16788,
    SPELL_FIRE_BLAST       = 16144,
    SPELL_BERSERKER_CHARGE = 16636,
    SPELL_SUMMON           = 20477
};

struct MANGOS_DLL_DECL boss_thebeastAI : public ScriptedAI
{
    boss_thebeastAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 m_uiFlamebreakTimer;
    uint32 m_uiImmolateTimer;
    uint32 m_uiTerrifyingRoarTimer;
    uint32 m_uiFireballTimer;
    uint32 m_uiFireBlastTimer;
    uint32 m_uiBerserkChargeTimer;
    uint32 m_uiSummonTimer;

    Unit* pTarget;

    void Reset()
    {
        m_uiSummonTimer         = 15000;
        m_uiFireballTimer       = urand(3000, 7000);
        m_uiFireBlastTimer      = urand(8000, 16000);
        m_uiBerserkChargeTimer  = 0;
        m_uiFlamebreakTimer     = urand(10000, 14000);
        m_uiImmolateTimer       = urand(1000, 5000);
        m_uiTerrifyingRoarTimer = urand(20000, 25000);
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

        // Charge
        if (m_uiBerserkChargeTimer < uiDiff)
        {
            for (uint8 i = 0; i < 10; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                {                            
                    i = 10;
                    m_uiBerserkChargeTimer = 10000;

                    DoCastSpellIfCan(pTarget, SPELL_BERSERKER_CHARGE);
                }
            }
        }
        else 
            m_uiBerserkChargeTimer -= uiDiff;

        // Fireball
        if (m_uiFireballTimer < uiDiff)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {                           
                DoCastSpellIfCan(pTarget, SPELL_FIREBALL);
                m_uiFireballTimer = urand(5000, 10000);
            }
        }
        else 
            m_uiFireballTimer -= uiDiff;

        // Fire Blast
        if (m_uiFireBlastTimer < uiDiff)
        {
            pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
            {                            
                DoCastSpellIfCan(pTarget, SPELL_FIRE_BLAST);
                m_uiFireBlastTimer = 9000;
            }
        }
        else 
            m_uiFireBlastTimer -= uiDiff;

        // Flamebreak
        if (m_uiFlamebreakTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FLAMEBREAK);
            m_uiFlamebreakTimer = urand(8000, 12000);
        }
        else
            m_uiFlamebreakTimer -= uiDiff;

        // Immolate
        if (m_uiImmolateTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_IMMOLATE);
            
            m_uiImmolateTimer = urand(6000, 10000);
        }
        else
            m_uiImmolateTimer -= uiDiff;

        // Terrifying Roar
        if (m_uiTerrifyingRoarTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_TERRIFYINGROAR);
            m_uiTerrifyingRoarTimer = urand(18000, 20000);
        }
        else
            m_uiTerrifyingRoarTimer -= uiDiff;

        // Summon
        if (m_uiSummonTimer < uiDiff)
        {
            for (uint8 i = 0; i < 10; i++)
            {
                pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1);

                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER && pTarget->GetDistance(m_creature) > 35.0f)
                {                            
                    i = 10;
                    m_uiSummonTimer = 15000;

                    DoCastSpellIfCan(pTarget, SPELL_SUMMON);
                }
            }
        }
        else 
            m_uiSummonTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_thebeast(Creature* pCreature)
{
    return new boss_thebeastAI(pCreature);
}

void AddSC_boss_thebeast()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_the_beast";
    newscript->GetAI = &GetAI_boss_thebeast;
    newscript->RegisterSelf();
}
