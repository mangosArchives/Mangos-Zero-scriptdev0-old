/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
    SDName: Boss_Four_Horsemen
    SD%Complete: 75
    SDComment: Lady Blaumeux, Thane Korthazz, Sir Zeliek
    SDCategory: Naxxramas
    EndScriptData */

    #include "precompiled.h"

    //all horsemen
    #define SPELL_SHIELDWALL            29061
    #define SPELL_BESERK                26662

    //lady blaumeux
    #define SAY_BLAU_AGGRO              -1533044
    #define SAY_BLAU_TAUNT1             -1533045
    #define SAY_BLAU_TAUNT2             -1533046
    #define SAY_BLAU_TAUNT3             -1533047
    #define SAY_BLAU_SPECIAL            -1533048
    #define SAY_BLAU_SLAY               -1533049
    #define SAY_BLAU_DEATH              -1533050

    #define SPELL_MARK_OF_BLAUMEUX      28833
    #define SPELL_UNYILDING_PAIN        57381
    #define SPELL_VOIDZONE              28863
    #define H_SPELL_VOIDZONE            57463
    #define SPELL_SHADOW_BOLT           57374
    #define H_SPELL_SHADOW_BOLT         57464

    #define C_SPIRIT_OF_BLAUMEUX        16776

    struct TRINITY_DLL_DECL boss_lady_blaumeuxAI : public ScriptedAI
    {
        boss_lady_blaumeuxAI(Creature *c) : ScriptedAI(c) {}

        uint32 Mark_Timer;
        uint32 VoidZone_Timer;
        bool ShieldWall1;
        bool ShieldWall2;

        void Reset()
        {
            Mark_Timer = 20000;                                 // First Horsemen Mark is applied at 20 sec.
            VoidZone_Timer = 12000;                             // right
            ShieldWall1 = true;
            ShieldWall2 = true;
        }

        void Aggro(Unit *who)
        {
            DoScriptText(SAY_BLAU_AGGRO, m_creature);
        }

        void KilledUnit(Unit* Victim)
        {
            DoScriptText(SAY_BLAU_SLAY, m_creature);
        }

        void JustDied(Unit* Killer)
        {
            DoScriptText(SAY_BLAU_DEATH, m_creature);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            // Mark of Blaumeux
            if (Mark_Timer < diff)
            {
                DoCast(m_creature->getVictim(),SPELL_MARK_OF_BLAUMEUX);
                Mark_Timer = 12000;
            }else Mark_Timer -= diff;

            // Shield Wall - All 4 horsemen will shield wall at 50% hp and 20% hp for 20 seconds
            if (ShieldWall1 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 50)
            {
                if(ShieldWall1)
                {
                    DoCast(m_creature,SPELL_SHIELDWALL);
                    ShieldWall1 = false;
                }
           }
           if (ShieldWall2 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 20)
           {
               if (ShieldWall2)
               {
                   DoCast(m_creature,SPELL_SHIELDWALL);
                   ShieldWall2 = false;
               }
           }

           // Void Zone
           if (VoidZone_Timer < diff)
           {
               DoCast(m_creature->getVictim(),SPELL_VOIDZONE);
               VoidZone_Timer = 12000;
           }else VoidZone_Timer -= diff;

           DoMeleeAttackIfReady();
       }
   };

   CreatureAI* GetAI_boss_lady_blaumeux(Creature *_Creature)
   {
       return new boss_lady_blaumeuxAI (_Creature);
   }

   //thane korthazz
   #define SAY_KORT_AGGRO              -1533051
   #define SAY_KORT_TAUNT1             -1533052
   #define SAY_KORT_TAUNT2             -1533053
   #define SAY_KORT_TAUNT3             -1533054
   #define SAY_KORT_SPECIAL            -1533055
   #define SAY_KORT_SLAY               -1533056
   #define SAY_KORT_DEATH              -1533057

   #define SPELL_MARK_OF_KORTHAZZ      28832
   #define SPELL_METEOR                26558                   // m_creature->getVictim() auto-area spell but with a core problem

   #define C_SPIRIT_OF_KORTHAZZ        16778

   struct TRINITY_DLL_DECL boss_thane_korthazzAI : public ScriptedAI
   {
       boss_thane_korthazzAI(Creature *c) : ScriptedAI(c) {}

       uint32 Mark_Timer;
       uint32 Meteor_Timer;
       bool ShieldWall1;
       bool ShieldWall2;

       void Reset()
       {
           Mark_Timer = 20000;                                 // First Horsemen Mark is applied at 20 sec.
           Meteor_Timer = 30000;                               // wrong
           ShieldWall1 = true;
           ShieldWall2 = true;
       }

       void Aggro(Unit *who)
       {
           DoScriptText(SAY_KORT_AGGRO, m_creature);
       }

       void KilledUnit(Unit* Victim)
       {
           DoScriptText(SAY_KORT_SLAY, m_creature);
       }

       void JustDied(Unit* Killer)
       {
           DoScriptText(SAY_KORT_DEATH, m_creature);
       }

       void UpdateAI(const uint32 diff)
       {
           if (!UpdateVictim())
               return;

           // Mark of Korthazz
           if (Mark_Timer < diff)
           {
               DoCast(m_creature->getVictim(),SPELL_MARK_OF_KORTHAZZ);
               Mark_Timer = 12000;
           }else Mark_Timer -= diff;

           // Shield Wall - All 4 horsemen will shield wall at 50% hp and 20% hp for 20 seconds
           if (ShieldWall1 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 50)
           {
               if (ShieldWall1)
               {
                   DoCast(m_creature,SPELL_SHIELDWALL);
                   ShieldWall1 = false;
               }
           }
           if (ShieldWall2 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 20)
           {
               if (ShieldWall2)
               {
                   DoCast(m_creature,SPELL_SHIELDWALL);
                  ShieldWall2 = false;
               }
           }

           // Meteor
           if (Meteor_Timer < diff)
           {
               DoCast(m_creature->getVictim(),SPELL_METEOR);
               Meteor_Timer = 20000;                           // wrong
          }else Meteor_Timer -= diff;

           DoMeleeAttackIfReady();
       }
   };

   CreatureAI* GetAI_boss_thane_korthazz(Creature *_Creature)
   {
       return new boss_thane_korthazzAI (_Creature);
   }

   //sir zeliek
   #define SAY_ZELI_AGGRO              -1533058
   #define SAY_ZELI_TAUNT1             -1533059
   #define SAY_ZELI_TAUNT2             -1533060
   #define SAY_ZELI_TAUNT3             -1533061
   #define SAY_ZELI_SPECIAL            -1533062
   #define SAY_ZELI_SLAY               -1533063
   #define SAY_ZELI_DEATH              -1533064

   #define SPELL_MARK_OF_ZELIEK        28835
   #define SPELL_HOLY_WRATH            28883
   #define H_SPELL_HOLY_WRATH          57466
   #define SPELL_HOLY_BOLT             57376
   #define H_SPELL_HOLY_BOLT           57465

   #define C_SPIRIT_OF_ZELIREK         16777

   struct TRINITY_DLL_DECL boss_sir_zeliekAI : public ScriptedAI
   {
       boss_sir_zeliekAI(Creature *c) : ScriptedAI(c) {}

       uint32 Mark_Timer;
       uint32 HolyWrath_Timer;
       bool ShieldWall1;
       bool ShieldWall2;

       void Reset()
       {
           Mark_Timer = 20000;                                 // First Horsemen Mark is applied at 20 sec.
           HolyWrath_Timer = 12000;                            // right
           ShieldWall1 = true;
           ShieldWall2 = true;
       }

       void Aggro(Unit *who)
       {
           DoScriptText(SAY_ZELI_AGGRO, m_creature);
       }

       void KilledUnit(Unit* Victim)
       {
           DoScriptText(SAY_ZELI_SLAY, m_creature);
       }

       void JustDied(Unit* Killer)
       {
           DoScriptText(SAY_ZELI_DEATH, m_creature);
       }

       void UpdateAI(const uint32 diff)
       {
           //Return since we have no target
           if (!UpdateVictim())
               return;

           // Mark of Zeliek
           if (Mark_Timer < diff)
           {
               DoCast(m_creature->getVictim(),SPELL_MARK_OF_ZELIEK);
               Mark_Timer = 12000;
           }else Mark_Timer -= diff;

           // Shield Wall - All 4 horsemen will shield wall at 50% hp and 20% hp for 20 seconds
           if (ShieldWall1 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 50)
           {
               if (ShieldWall1)
               {
                   DoCast(m_creature,SPELL_SHIELDWALL);
                   ShieldWall1 = false;
               }
         }
           if (ShieldWall2 && (m_creature->GetHealth()*100 / m_creature->GetMaxHealth()) < 20)
           {
               if (ShieldWall2)
               {
                   DoCast(m_creature,SPELL_SHIELDWALL);
                   ShieldWall2 = false;
               }
           }

           // Holy Wrath
           if (HolyWrath_Timer < diff)
           {
               DoCast(m_creature->getVictim(),SPELL_HOLY_WRATH);
               HolyWrath_Timer = 12000;
           }else HolyWrath_Timer -= diff;

           DoMeleeAttackIfReady();
       }
   };

   CreatureAI* GetAI_boss_sir_zeliek(Creature *_Creature)
   {
       return new boss_sir_zeliekAI (_Creature);
   }

   void AddSC_boss_four_horsemen()
   {
       Script *newscript;

       newscript = new Script;
       newscript->Name = "boss_lady_blaumeux";
       newscript->GetAI = &GetAI_boss_lady_blaumeux;
       newscript->RegisterSelf();

       newscript = new Script;
       newscript->Name = "boss_thane_korthazz";
       newscript->GetAI = &GetAI_boss_thane_korthazz;
       newscript->RegisterSelf();

       newscript = new Script;
       newscript->Name = "boss_sir_zeliek";
       newscript->GetAI = &GetAI_boss_sir_zeliek;
      newscript->RegisterSelf();
   }

