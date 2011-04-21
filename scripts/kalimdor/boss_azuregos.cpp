/*
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 * Copyright (C) 2010-2011 ScriptDev0 <http://github.com/scriptdev/scriptdevzero>
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
SDName: Boss_Azuregos
SD%Complete: 90
SDComment: Mark of Frost missing core support?
SDCategory: Azshara
EndScriptData */

#include "precompiled.h"

enum
{
    SAY_TELEPORT         = -1000100,

    //SPELL_MARKOFFROST    = 23182,
    SPELL_MANASTORM      = 21097,
    SPELL_CHILL          = 21098,
    SPELL_FROSTBREATH    = 21099,
    SPELL_REFLECTION     = 22067,
    SPELL_CLEAVE         = 19983,
    SPELL_ENRAGE         = 23537,
    //SPELL_ARCANE_VACUUM  = 21147
};

struct MANGOS_DLL_DECL boss_azuregosAI : public ScriptedAI
{
    boss_azuregosAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    uint32 m_uiMarkOfFrostTimer;
    uint32 m_uiManaStormTimer;
    uint32 m_uiChillTimer;
    uint32 m_uiBreathTimer;
    uint32 m_uiTeleportTimer;
    uint32 m_uiReflectTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiEnrageTimer;
    bool m_bEnraged;

    void Reset()
    {
        m_uiMarkOfFrostTimer = 35000;
        m_uiManaStormTimer = urand(5000, 17000);
        m_uiChillTimer = urand(10000, 30000);
        m_uiBreathTimer = urand(2000, 8000);
        m_uiTeleportTimer = 30000;
        m_uiReflectTimer = urand(15000, 30000);
        m_uiCleaveTimer = 7000;
        m_uiEnrageTimer = 0;
        m_bEnraged = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_uiTeleportTimer < uiDiff)
        {
            DoScriptText(SAY_TELEPORT, m_creature);

            ThreatList const& m_lThreatList = m_creature->getThreatManager().getThreatList();
            for (ThreatList::const_iterator itr = m_lThreatList.begin();itr != m_lThreatList.end(); ++itr)
            {
                Unit* pUnit = m_creature->GetMap()->GetUnit((*itr)->getUnitGuid());

                if (pUnit && (pUnit->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(pUnit, 30.0f)))
                {
                    DoTeleportPlayer(pUnit, m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ()+3, pUnit->GetOrientation());
                    (*itr)->removeReference(); // Reset threat for the current player?
                }
            }

            m_uiTeleportTimer = 30000;
        }
        else
            m_uiTeleportTimer -= uiDiff;

        //        //MarkOfFrostTimer
        //        if (MarkOfFrostTimer < uiDiff)
        //        {
        //            DoCastSpellIfCan(m_creature->getVictim(),SPELL_MARKOFFROST);
        //            MarkOfFrostTimer = 25000;
        //        }else MarkOfFrostTimer -= uiDiff;

        if (m_uiChillTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(),SPELL_CHILL) == CAST_OK)
                m_uiChillTimer = urand(13000, 25000);
        }
        else
            m_uiChillTimer -= uiDiff;

        if (m_uiBreathTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_FROSTBREATH) == CAST_OK)
                m_uiBreathTimer = urand(10000, 15000);
        }
        else
            m_uiBreathTimer -= uiDiff;

        if (m_uiManaStormTimer < uiDiff)
        {
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (DoCastSpellIfCan(target, SPELL_MANASTORM) == CAST_OK)
                    m_uiManaStormTimer = urand(7500, 12500);
            }
        }
        else
            m_uiManaStormTimer -= uiDiff;

        if (m_uiReflectTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_REFLECTION) == CAST_OK)
                m_uiReflectTimer = urand(20000, 35000);
        }
        else
            m_uiReflectTimer -= uiDiff;

        if (m_uiCleaveTimer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE) == CAST_OK)
                m_uiCleaveTimer = 7000;
        }
        else
            m_uiCleaveTimer -= uiDiff;

        if (m_creature->GetHealthPercent() < 26.0f && !m_bEnraged)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_ENRAGE) == CAST_OK)
                m_bEnraged = true;
        }

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_azuregos(Creature* pCreature)
{
    return new boss_azuregosAI(pCreature);
}

void AddSC_boss_azuregos()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_azuregos";
    pNewScript->GetAI = &GetAI_boss_azuregos;
    pNewScript->RegisterSelf();
}
