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
SDName: Boss_Mor_Grayhoof
SD%Complete: 100
SDComment:
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    //Druid spell
    SPELL_HURRICANE              =    27530,
    SPELL_MOONFIRE               =    27737,
    SPELL_SHOCK                  =    15605,
    
    //Healing spell
    SPELL_HEALING_TOUCH          =    27527,
    SPELL_REJUVENATION           =    27532,
    
    //Bear spell
    SPELL_BEAR_FORM              =    27543,
    SPELL_DEMORALIZING_ROAR      =    27551,
    SPELL_MAUL                   =    27553,
    SPELL_SWIPE                  =    27554,
    
    //Cat spell
    SPELL_CAT_FORM               =    27545,
    SPELL_SHRED                  =    27555,
    SPELL_RAKE                   =    27556,
    SPELL_FEROCIOUS_BITE         =    27557,

    //Dragon form
    SPELL_FAERIE_DRAGON_FORM     =    27546,
    SPELL_ARCANE_EXPLOSION       =    22271,
    SPELL_REFLECTION             =    27564,
    SPELL_CHAIN_LIGHTING         =    27567
};

struct MANGOS_DLL_DECL boss_mor_grayhoofAI : public ScriptedAI
{
    boss_mor_grayhoofAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 roll;
    uint32 spell;
    
    uint32 AOE_Timer;
    uint32 Shock_Timer;
    uint32 Healing_Timer;

    uint32 BearAbilities_Timer;
    uint32 CatAbilities_Timer;
    uint32 DragonSpells_Timer;

    uint32 BearForm_Timer;
    uint32 CatForm_Timer;
    uint32 DemoralizingRoar_Timer;
    
    bool BearForm_Used;
    bool CatForm_Used;

    bool m_druidForm;
    bool m_bearForm;
    bool m_catForm;
    bool m_dragonForm;

    void Reset()
    {
        roll = 0;
        spell = 0;
        AOE_Timer = urand(5000,15000);
        Healing_Timer= urand(5000,15000);
        Shock_Timer = urand(5000,10000);
        
        BearAbilities_Timer = 2500;
        CatAbilities_Timer = 2500;
        DragonSpells_Timer = urand(5000,10000);
        
        BearForm_Timer = 10000;
        CatForm_Timer = 10000;
        DemoralizingRoar_Timer = 500;
        
        BearForm_Used = false;
        CatForm_Used = false;
        
        m_druidForm = true;
        m_bearForm = false;
        m_catForm = false;
        m_dragonForm = false;
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(30.0f);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        
        if (m_druidForm)
        {
            if (AOE_Timer < diff)
            {
                roll = urand(1,2);
                if (roll == 1) spell = SPELL_HURRICANE;
                else spell = SPELL_MOONFIRE;
                DoCastSpellIfCan(m_creature->getVictim(),spell);
                AOE_Timer = urand(5000,15000);
            }else AOE_Timer -= diff;
            
            if (Shock_Timer < diff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_SHOCK);
                Shock_Timer = urand(5000,10000);
            }else Shock_Timer -= diff;
            
            if (Healing_Timer < diff)
            {
                roll = urand(1,2);
                if (roll == 1) spell = SPELL_HEALING_TOUCH;
                else spell = SPELL_REJUVENATION;
                DoCastSpellIfCan(m_creature,spell);
                Healing_Timer = urand(5000,15000);
            }else Healing_Timer -= diff;
        }
        else if (m_bearForm)
        {
            if (DemoralizingRoar_Timer < diff)
            {
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_DEMORALIZING_ROAR);
                DemoralizingRoar_Timer = 30000;
            }else DemoralizingRoar_Timer -= diff;
            
            if (BearAbilities_Timer < diff)
            {
                roll = urand(1,2);
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_MAUL-1+roll); //small hack
                BearAbilities_Timer = urand(2500,5000);
            }else BearAbilities_Timer -= diff;
        }
        else if (m_catForm)
        {
            if (CatAbilities_Timer < diff)
            {
                roll = urand(1,3);
                DoCastSpellIfCan(m_creature->getVictim(),SPELL_SHRED-1+roll); // small hack
                CatAbilities_Timer = urand(2500,5000);
            }else CatAbilities_Timer -= diff;
        }
        else if (m_dragonForm)
        {
            if (DragonSpells_Timer < diff)
            {
                roll = urand(1,3);
                if (roll == 1) spell = SPELL_ARCANE_EXPLOSION;
                else if (roll == 2) spell = SPELL_CHAIN_LIGHTING;
                else DoCastSpellIfCan(m_creature,SPELL_REFLECTION);
                if (roll != 3) DoCastSpellIfCan(m_creature->getVictim(),spell);
                DragonSpells_Timer = urand(5000,10000);
            }else DragonSpells_Timer -= diff;
        }
        
        if ((m_creature->GetHealthPercent() < 80) && !BearForm_Used && m_druidForm)
        {
            m_creature->CastStop();
            m_creature->InterruptNonMeleeSpells(false);
            DoCastSpellIfCan(m_creature,SPELL_BEAR_FORM);
            BearForm_Used = true;
            m_bearForm = true;
            m_druidForm = false;
        }
        
        if ((m_creature->GetHealthPercent() < 60) && !CatForm_Used && m_druidForm)
        {
            m_creature->CastStop();
            m_creature->InterruptNonMeleeSpells(false);
            DoCastSpellIfCan(m_creature,SPELL_CAT_FORM);
            CatForm_Used = true;
            m_catForm = true;
            m_druidForm = false;
        }
        
        if ((m_creature->GetHealthPercent() < 35) && CatForm_Used && m_druidForm)
        {
            m_creature->CastStop();
            m_creature->InterruptNonMeleeSpells(false);
            DoCastSpellIfCan(m_creature,SPELL_FAERIE_DRAGON_FORM);
            m_dragonForm = true;
            m_druidForm = false;
        }
        
        if (m_bearForm && (BearForm_Timer < diff)) {m_bearForm = false; m_druidForm = true;}
        else if (m_bearForm) BearForm_Timer -= diff;
        
        if (m_catForm && (CatForm_Timer < diff)) {m_catForm = false; m_druidForm = true;}
        else if (m_catForm) CatForm_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_mor_grayhoof(Creature* pCreature)
{
    return new boss_mor_grayhoofAI(pCreature);
}

void AddSC_boss_mor_grayhoof()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_mor_grayhoof";
    newscript->GetAI = &GetAI_boss_mor_grayhoof;
    newscript->RegisterSelf();
}