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
SDName: Boss_Theldren
SD%Complete: 0
SDComment: TODO: Correct timers needed
SDCategory: Blackrock Depths
EndScriptData */

#include "precompiled.h"

enum
{
    SPELL_DRINK_HEALING_POTION       = 15503,

    //Theldren
    SPELL_BATTLE_SHOUT               = 27578,
    SPELL_DEMORALIZING_SHOUT         = 27579,
    SPELL_DISARM                     = 27581,
    SPELL_FRIGHTENING_SHOUT          = 19134,
    SPELL_HAMSTRING                  = 27584,
    SPELL_INTERCEPT                  = 27577,
    SPELL_MORTAL_STRIKE              = 27580,

    THELDREN_SAY_AGGRO_1             = -1230010,
    THELDREN_SAY_AGGRO_2             = -1230011,
    THELDREN_SAY_AGGRO_3             = -1230012,
    //Va'jashni

    //Volida
    SPELL_BLINK                      = 14514,
    SPELL_CONE_OF_COLD               = 20828,
    SPELL_FROST_NOVA                 = 15063,
    SPELL_FROSTBOLT                  = 20822,
    SPELL_ICE_BLOCK                  = 27619
};

struct MANGOS_DLL_DECL boss_theldrenAI : public ScriptedAI
{
    boss_theldrenAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    uint32 BattleShout_Timer;
    uint32 DemoralizingShout_Timer;
    uint32 Disarm_Timer;
    uint32 HealingPotion_Timer;
    uint32 FrighteningShout_Timer;
    uint32 Hamstring_Timer;
    uint32 Intercept_Timer;
    uint32 MortalStrike_Timer;

    void Reset()
    {
        BattleShout_Timer       = 0;
        DemoralizingShout_Timer = 12000;
        Disarm_Timer            = 15000;
        HealingPotion_Timer     = 20000;
        FrighteningShout_Timer  = 25000;
        Hamstring_Timer         = 5000;
        Intercept_Timer         = 0;
        MortalStrike_Timer      = 10000;
    }

    void Aggro(Unit* pWho)
    {
        if (DoCastSpellIfCan(pWho, SPELL_INTERCEPT) == CAST_OK)
            Intercept_Timer = 30000;

        switch(urand(0, 2))
        {
            case 0:
                DoScriptText(THELDREN_SAY_AGGRO_1, m_creature);
                break;
            case 1:
                DoScriptText(THELDREN_SAY_AGGRO_2, m_creature);
                break;
            case 2:
                DoScriptText(THELDREN_SAY_AGGRO_3, m_creature);
                break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_theldren(Creature* m_creature)
{
    return new boss_theldrenAI(m_creature);
}

struct MANGOS_DLL_DECL npc_volidaAI : public ScriptedAI
{
    npc_volidaAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    uint32 Blink_Timer;
    uint32 ConeOfCold_Timer;
    uint32 FrostNova_Timer;
    uint32 HealingPotion_Timer;
    uint32 Frostbolt_Timer;
    uint32 IceBlock_Timer;

    void Reset()
    {
        Blink_Timer             = 0;
        ConeOfCold_Timer        = 0;
        FrostNova_Timer         = 0;
        HealingPotion_Timer     = 0;
        Frostbolt_Timer         = 0;
        IceBlock_Timer          = 0;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_volida(Creature* m_creature)
{
    return new npc_volidaAI(m_creature);
}

struct MANGOS_DLL_DECL npc_vajashniAI : public ScriptedAI
{
    npc_vajashniAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_vajashni(Creature* m_creature)
{
    return new npc_vajashniAI(m_creature);
}

struct MANGOS_DLL_DECL npc_rezznikAI : public ScriptedAI
{
    npc_rezznikAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_rezznik(Creature* m_creature)
{
    return new npc_rezznikAI(m_creature);
}

struct MANGOS_DLL_DECL npc_korvAI : public ScriptedAI
{
    npc_korvAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_korv(Creature* m_creature)
{
    return new npc_korvAI(m_creature);
}

struct MANGOS_DLL_DECL npc_malgen_longspearAI : public ScriptedAI
{
    npc_malgen_longspearAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_malgen_longspear(Creature* m_creature)
{
    return new npc_malgen_longspearAI(m_creature);
}

struct MANGOS_DLL_DECL npc_snokh_blackspineAI : public ScriptedAI
{
    npc_snokh_blackspineAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_snokh_blackspine(Creature* m_creature)
{
    return new npc_snokh_blackspineAI(m_creature);
}

struct MANGOS_DLL_DECL npc_rotfangAI : public ScriptedAI
{
    npc_rotfangAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_rotfang(Creature* m_creature)
{
    return new npc_rotfangAI(m_creature);
}

struct MANGOS_DLL_DECL npc_leftyAI : public ScriptedAI
{
    npc_leftyAI(Creature* m_creature) : ScriptedAI(m_creature) {Reset();}

    void Reset()
    {

    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_lefty(Creature* m_creature)
{
    return new npc_leftyAI(m_creature);
}

void AddSC_boss_theldren()
{
    Script *pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_theldren";
    pNewScript->GetAI = &GetAI_boss_theldren;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_volida";
    pNewScript->GetAI = &GetAI_npc_volida;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_vajashni";
    pNewScript->GetAI = &GetAI_npc_vajashni;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_rezznik";
    pNewScript->GetAI = &GetAI_npc_rezznik;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_korv";
    pNewScript->GetAI = &GetAI_npc_korv;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_malgen_longspear";
    pNewScript->GetAI = &GetAI_npc_malgen_longspear;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_snokh_blackspine";
    pNewScript->GetAI = &GetAI_npc_snokh_blackspine;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_rotfang";
    pNewScript->GetAI = &GetAI_npc_rotfang;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_lefty";
    pNewScript->GetAI = &GetAI_npc_lefty;
    pNewScript->RegisterSelf();
}
