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
SDName: Boss_Renataki
SD%Complete: 100
SDComment:
SDCategory: Zul'Gurub
EndScriptData */

#include "precompiled.h"
#include "zulgurub.h"

enum
{
    SPELL_AMBUSH           = 24337,
    SPELL_THOUSAND_BLADES  = 24649,
    SPELL_VANISH           = 24699,
    SPELL_GOUGE            = 24698,
    SPELL_THRASH           = 3391
};

struct MANGOS_DLL_DECL boss_renatakiAI : public ScriptedAI
{
    boss_renatakiAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiAmbushTimer;
    uint32 m_uiThousandBladesTimer;
    uint32 m_uiVanishTimer;
    uint32 m_uiGougeTimer;
    uint32 m_uiThrash_Timer;
    uint32 m_uiAggro_Timer;

    bool m_bVanished;

    void Reset()
    {
        m_uiAmbushTimer = urand(3000,7000);
        m_uiVanishTimer = urand(30000,45000);
        m_uiGougeTimer = 10000;
        m_uiThrash_Timer = 5000;
        m_uiAggro_Timer = urand(15000,25000);
        m_uiThousandBladesTimer = urand(4000,8000);

        DoRemoveVanishIfPresent();
    }

    void DoRemoveVanishIfPresent()
    {
        if (m_creature->HasAura(SPELL_VANISH, EFFECT_INDEX_1))
            m_creature->RemoveAurasDueToSpell(SPELL_VANISH);

        m_bVanished = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Vanish
        if (m_uiVanishTimer < uiDiff)
        {
            m_creature->InterruptSpell(CURRENT_GENERIC_SPELL);
            DoCastSpellIfCan(m_creature, SPELL_VANISH);
            m_bVanished = true;
            m_uiVanishTimer = urand(30000,45000);
        }
        else
            m_uiVanishTimer -= uiDiff;

        // Gouge
        if (m_uiThrash_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_GOUGE);
            m_uiThrash_Timer = urand(10000,15000);
        }
        else
            m_uiThrash_Timer -= uiDiff;

        // Ambush
        if (m_bVanished)
        {
            if (m_uiAmbushTimer < uiDiff)
            {
                if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                {
                    DoRemoveVanishIfPresent();
                    m_creature->NearTeleportTo(pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0.0f);
                    DoCastSpellIfCan(pTarget, SPELL_AMBUSH);
                    m_uiAmbushTimer = urand(3000,7000);
                    AttackStart(pTarget);
                }
            }
            else
                m_uiAmbushTimer -= uiDiff;
        }

        // Following code only in visible from
        if (m_bVanished)
            return;

        // Reset some aggro to make attacks on random players possible
        if (m_uiAggro_Timer < uiDiff)
        {
            if (m_creature->getThreatManager().getThreat(m_creature->getVictim()))
                m_creature->getThreatManager().modifyThreatPercent(m_creature->getVictim(),-50);

            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
                AttackStart(pTarget);

            m_uiAggro_Timer = urand(7000,20000);
        }
        else
            m_uiAggro_Timer -= uiDiff;

        if (m_uiThousandBladesTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_THOUSAND_BLADES);
            m_uiThousandBladesTimer = urand(7000,12000);
        }
        else
            m_uiThousandBladesTimer -= uiDiff;

        // Thrash
        if (m_uiThrash_Timer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_THRASH);
            m_uiThrash_Timer = urand(10000,20000);
        }
        else
            m_uiThrash_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_renataki(Creature* pCreature)
{
    return new boss_renatakiAI(pCreature);
}

void AddSC_boss_renataki()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_renataki";
    newscript->GetAI = &GetAI_boss_renataki;
    newscript->RegisterSelf();
}
