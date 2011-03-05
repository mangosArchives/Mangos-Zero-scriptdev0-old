/* Special Thanks the Mangos-Zero, and Scriptdev2, and ScriptDev-Zero team!
 * Copyright (C) 2006 - 2011 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Lord_Kazzak
SD%Complete: 70
SDComment:
SDCategory: Dark-Portal
EndScriptData */

#include "precompiled.h"

enum
{
   SAY_INTRO                 = -1000147,
   SAY_AGGRO1                = -1000148,
   SAY_AGGRO2                = -1000149,
   SAY_SURPREME1             = -1000150,
   SAY_SURPREME2             = -1000151,
   SAY_KILL1                 = -1000152,
   SAY_KILL2                 = -1000153,
   SAY_KILL3                 = -1000154,
   SAY_DEATH                 = -1000155,
   EMOTE_FRENZY              = -1000156,
   SAY_RAND1                 = -1000157,
   SAY_RAND2                 = -1000158,

   SPELL_SHADOWVOLLEY        = 28599,
   SPELL_CLEAVE              = 27794,
   SPELL_THUNDERCLAP         = 26554,
   SPELL_VOIDBOLT            = 22709,
   SPELL_MARKOFKAZZAK        = 21056,
   SPELL_ENRAGE              = 28747,
   SPELL_CAPTURESOUL         = 21054,
   SPELL_TWISTEDREFLECTION   = 21063
};

/*
Melee
Shadowbolt Volley
Cleave
Thunderclap
Twisted Reflection
Mark of Kazzak
Void Bolt
Capture Soul
*/
struct MANGOS_DLL_DECL boss_lordkazzakAI : public ScriptedAI
{
    boss_lordkazzakAI(Creature *c) : ScriptedAI(c) {Reset();}

    uint32 ShadowVolley_Timer;
    uint32 Cleave_Timer;
    uint32 ThunderClap_Timer;
    uint32 VoidBolt_Timer;
    uint32 MarkOfKazzak_Timer;
    uint32 Enrage_Timer;
    uint32 Twisted_Reflection_Timer;

    void Reset()
    {
        ShadowVolley_Timer = 8000 + rand()%4000;
        Cleave_Timer = 7000;
        ThunderClap_Timer = 16000 + rand()%4000;
        VoidBolt_Timer = 30000;
        MarkOfKazzak_Timer = 25000;
        Enrage_Timer = 60000;
        Twisted_Reflection_Timer = 33000;
    }

    void JustRespawned()
    {
        DoScriptText(SAY_INTRO, m_creature);
    }

    void Aggro(Unit *who)
    {
        switch(rand()%2)
        {
            case 0: DoScriptText(SAY_AGGRO1, m_creature); break;
            case 1: DoScriptText(SAY_AGGRO2, m_creature); break;
        }
    }

    void KilledUnit(Unit* victim)
    {

        if (victim->GetTypeId() != TYPEID_PLAYER)
            return;

        DoCastSpellIfCan(m_creature,SPELL_CAPTURESOUL);

        switch(rand()%3)
        {
            case 0: DoScriptText(SAY_KILL1, m_creature); break;
            case 1: DoScriptText(SAY_KILL2, m_creature); break;
            case 2: DoScriptText(SAY_KILL3, m_creature); break;
        }
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_DEATH, m_creature);
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim() )
            return;

        //ShadowVolley_Timer
        if (ShadowVolley_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SHADOWVOLLEY);
            ShadowVolley_Timer = 4000 + rand()%2000;
        }else ShadowVolley_Timer -= diff;

        //Cleave_Timer
        if (Cleave_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_CLEAVE);
            Cleave_Timer = 8000 + rand()%4000;
        }else Cleave_Timer -= diff;

        //ThunderClap_Timer
        if (ThunderClap_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_THUNDERCLAP);
            ThunderClap_Timer = 10000 + rand()%4000;
        }else ThunderClap_Timer -= diff;

        //VoidBolt_Timer
        if (VoidBolt_Timer < diff)
        {
            DoCastSpellIfCan(m_creature->getVictim(),SPELL_VOIDBOLT);
            VoidBolt_Timer = 15000 + rand()%3000;
        }else VoidBolt_Timer -= diff;

        //MarkOfKazzak_Timer
        if (MarkOfKazzak_Timer < diff)
        {
            Unit* victim = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
            if (victim->GetPower(POWER_MANA))
            {
                DoCastSpellIfCan(victim, SPELL_MARKOFKAZZAK);
                MarkOfKazzak_Timer = 20000;
            }
        }else MarkOfKazzak_Timer -= diff;

        //Enrage_Timer
        if (Enrage_Timer < diff)
        {
            DoScriptText(EMOTE_FRENZY, m_creature);
            DoCastSpellIfCan(m_creature,SPELL_ENRAGE);
            Enrage_Timer = 30000;
        }else Enrage_Timer -= diff;

        if (Twisted_Reflection_Timer < diff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_TWISTEDREFLECTION);

            Twisted_Reflection_Timer = 15000;
        }else Twisted_Reflection_Timer -= diff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_boss_lordkazzak(Creature *_Creature)
{
    return new boss_lordkazzakAI (_Creature);
}

void AddSC_boss_lord_kazzak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_lord_kazzak";
    pNewScript->GetAI = &GetAI_boss_lordkazzak;
    pNewScript->RegisterSelf();
}

