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
SDName: Boss_Rend_Blackhand
SD%Complete: 100
SDComment: Script for UBRS boss Rend Blackhand (Entry 10429) and Stadium event
SDCategory: Blackrock Spire
EndScriptData */

#include "precompiled.h"
#include "blackrock_spire.h"

enum
{
    SPELL_CLEAVE        = 15284,
    SPELL_ENRAGE        = 8269,
    SPELL_MORTAL_STRIKE = 15708,
    SPELL_WHIRLWIND     = 13736
};

struct MANGOS_DLL_DECL boss_rend_blackhandAI : public ScriptedAI
{
    boss_rend_blackhandAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;

    uint32 m_uiWhirlWindTimer;
    uint32 m_uiCleaveTimer;
    uint32 m_uiMortalStrikeTimer;
    uint32 m_uiEnrageTimer;

    uint32 Nefarius_Say_2_Timer;
    uint32 DoorTimer;
    uint32 PhraseTimer;
    uint32 WaitTimer;

    uint8 t_phrase, phrase;
    uint8 introCounter;

    Unit* pNefarius;
    Creature* WaveMob[5];

    bool inCombat;
    bool isWait;
    bool isWaveMove;
    bool isWaveInCombat;
    bool Nefarius_Say_1;
    bool Nefarius_Say_2;

    void Reset()
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_STADIUM_EVENT) == DONE)
        {
            inCombat = true;
            m_uiWhirlWindTimer    = urand(15000, 19000);
            m_uiCleaveTimer       = urand(3000, 7000);
            m_uiMortalStrikeTimer = urand(6000, 10000);
            m_uiEnrageTimer       = 180000;
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_creature->SetVisibility(VISIBILITY_ON);
        }
        else
        {
            for (uint8 i = 0; i < 5; i++)
                WaveMob[i] = NULL;

            phrase = 0;
            t_phrase = 0;
            introCounter = 1;

            inCombat = false;
            isWait = false;
            isWaveMove = false;
            isWaveInCombat = false;
            Nefarius_Say_1 = false;
            Nefarius_Say_2 = false;
            Nefarius_Say_2_Timer = 8000;
            PhraseTimer = 40000;
            DoorTimer = 10000;
            WaitTimer = 10000;
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
            m_creature->SetVisibility(VISIBILITY_OFF);
        }

        m_pInstance->SetData(TYPE_REND_BLACKHAND, NOT_STARTED);
        m_pInstance->SetData(TYPE_STADIUM_WAVE, NOT_STARTED);
    }

    void Aggro(Unit* pWho)
    {
        m_creature->SetInCombatWithZone();
        m_creature->CallForHelp(20.0f);
    }

    void JustReachedHome()
    {
        m_pInstance->SetData(TYPE_STADIUM_EVENT, NOT_STARTED);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_REND_BLACKHAND, DONE);

        pNefarius = GetClosestCreatureWithEntry(m_creature, NPC_LORD_VICTOR_NEFARIUS, DEFAULT_VISIBILITY_INSTANCE);
        if (pNefarius)
        {
            DoScriptText(NEFARIUS_SAY_11, pNefarius);
            pNefarius->RemoveFromWorld();
        }
    }

    void SummonNefarius()
    {
        if (!m_pInstance)
            return;

        // Kill Nefarius before respawn
        pNefarius = GetClosestCreatureWithEntry(m_creature, NPC_LORD_VICTOR_NEFARIUS, DEFAULT_VISIBILITY_INSTANCE);
        if (pNefarius)
            pNefarius->RemoveFromWorld();

        pNefarius = NULL;
        pNefarius = m_creature->SummonCreature(NPC_LORD_VICTOR_NEFARIUS, 168.001f, -444.285f, 121.974f, 2.119f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);

        pNefarius->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        pNefarius->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE);
    }

    void SummonWave()
    {
        if (!m_pInstance)
            return;

        if (!WaveIsDead())
            return;

        if (m_pInstance->GetData(TYPE_STADIUM_EVENT) == DONE)
            return;

        for (uint8 i = 0; i < 5; i++)
            WaveMob[i] = NULL;

        if (isWait)
            return;

        switch (m_pInstance->GetData(TYPE_STADIUM_WAVE))
        {
            case 0:        // 1
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 1:        // 2
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 2:        // 3
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 3:        // 4
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 4:        // 5
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 212.943f, -420.077f, 110.949f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 5:        // 6
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -422.039f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[4] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -417.385f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            case 6:        // 7
                WaveMob[0] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -421.904f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[1] = m_creature->SummonCreature(NPC_CHROMATIC_DRAGONSPAWN, 210.500f, -418.040f, 110.935f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[2] = m_creature->SummonCreature(NPC_DRAGON_HANDLER, 205.868f, -420.077f, 110.919f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[3] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -422.039f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                WaveMob[4] = m_creature->SummonCreature(NPC_CHROMATIC_WHELP, 213.298f, -417.385f, 110.939f, 3.158f, TEMPSUMMON_DEAD_DESPAWN, 60 * 60 * 1000);
                break;
            default:
                break;
        }

        isWaveMove = false;
        isWaveInCombat = false;

        GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_STADIUM_COMBAT_DOOR));
        if (pDoor)
            pDoor->UseDoorOrButton(); // Открытие
    }

    bool WaveIsDead()
    {
        if (!m_pInstance)
            return false;

        if (m_pInstance->GetData(TYPE_STADIUM_WAVE) < 5)
        {
            for (uint8 i = 0; i < 4; i++)
                if (WaveMob[i] && WaveMob[i]->isAlive())
                    return false;

            // Если зануленые адды
            for (uint8 i = 0; i < 4; i++)
                if (!WaveMob[i])
                    return true;
        }
        else
        {
            for (uint8 i = 0; i < 5; i++)
                if (WaveMob[i] && WaveMob[i]->isAlive())
                    return false;

            // Если зануленые адды
            for (uint8 i = 0; i < 5; i++)
                if (!WaveMob[i])
                    return true;
        }

        isWait = true;
        m_pInstance->SetData(TYPE_STADIUM_WAVE, m_pInstance->GetData(TYPE_STADIUM_WAVE) + 1);
        return true;
    }

    void RandomPhrase()
    {
        phrase = urand(0,9);

        if (phrase == t_phrase)
            return;

        switch (phrase)
        {
            case 1:
                DoScriptText(NEFARIUS_SAY_3, pNefarius);
                break;
            case 2:
                DoScriptText(NEFARIUS_SAY_4, pNefarius);
                break;
            case 3:
                DoScriptText(NEFARIUS_SAY_5, pNefarius);
                break;
            case 4:
                DoScriptText(NEFARIUS_SAY_6, pNefarius);
                break;
            case 5:
                DoScriptText(NEFARIUS_SAY_7, pNefarius);
                break;
            case 6:
                DoScriptText(REND_SAY_1, m_creature);
                break;
            case 7:
                DoScriptText(REND_SAY_2, m_creature);
                break;
            case 8:
                DoScriptText(REND_SAY_3, m_creature);
                break;
            default:
                break;
        }
        t_phrase = phrase;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_REND_BLACKHAND) == SPECIAL)
        {
            Reset();
            return;
        }

        if (!inCombat)
        {
            if (m_pInstance->GetData(TYPE_STADIUM_EVENT) == IN_PROGRESS)
            {
                if (!Nefarius_Say_1)
                {
                    m_creature->SetVisibility(VISIBILITY_ON);
                    SummonNefarius();
                    if (pNefarius)
                    {
                        DoScriptText(NEFARIUS_SAY_1, pNefarius);
                        Nefarius_Say_1 = true;
                    }
                }
                
                if (!Nefarius_Say_2 && Nefarius_Say_1)
                {
                    if (Nefarius_Say_2_Timer < uiDiff)
                    {
                        DoScriptText(NEFARIUS_SAY_2, pNefarius);
                        Nefarius_Say_2 = true;
                    }
                    else Nefarius_Say_2_Timer -= uiDiff;
                }

                if (isWait)
                {
                    if (WaitTimer < uiDiff)
                    {
                        isWait = false;
                        WaitTimer = 10000;
                    }
                    else WaitTimer -= uiDiff;
                }

                if (Nefarius_Say_2 && !isWait)
                    SummonWave();

                if (!isWaveMove)
                {
                    isWaveMove = true;
                    if (m_pInstance->GetData(TYPE_STADIUM_WAVE) < 5)
                    {
                        for (uint8 i = 0; i < 4; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 4; i++)
                        {
                            WaveMob[i]->GetMotionMaster()->Clear();
                            WaveMob[i]->GetMotionMaster()->MovePoint(0, 153.763f, -419.833f, 110.472f);
                        }
                    }
                    else
                    {
                        for (uint8 i = 0; i < 5; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 5; i++)
                        {
                            WaveMob[i]->GetMotionMaster()->Clear();
                            WaveMob[i]->GetMotionMaster()->MovePoint(0, 153.763f, -419.833f, 110.472f);
                        }
                    }
                }

                if (!isWaveInCombat)
                {
                    isWaveInCombat = true;
                    if (m_pInstance->GetData(TYPE_STADIUM_WAVE) < 5)
                    {
                        for (uint8 i = 0; i < 4; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 4; i++)
                            if (WaveMob[i]->SelectHostileTarget() || WaveMob[i]->getVictim())
                                EnterCombat(WaveMob[i]->getVictim());
                    }
                    else
                    {
                        for (uint8 i = 0; i < 5; i++)
                            if (!WaveMob[i])
                                return;

                        for (uint8 i = 0; i < 5; i++)
                            if (WaveMob[i]->SelectHostileTarget() || WaveMob[i]->getVictim())
                                EnterCombat(WaveMob[i]->getVictim());
                    }
                }

                if (GameObject* pDoor = m_pInstance->instance->GetGameObject(m_pInstance->GetData64(GO_STADIUM_COMBAT_DOOR)))
                {
                    if (pDoor->GetGoState() == GO_STATE_ACTIVE)
                    {
                        if (DoorTimer < uiDiff)
                        {
                            pDoor->UseDoorOrButton();
                            DoorTimer = 10000;
                        }
                        else DoorTimer -= uiDiff;
                    }
                }
            }

            if (m_pInstance->GetData(TYPE_STADIUM_EVENT) != DONE)
            {
                if (PhraseTimer < uiDiff)
                {
                    if (isWaveInCombat)
                        RandomPhrase();
                    PhraseTimer = 40000;
                } else PhraseTimer -= uiDiff;
            }
            else
            {
                if (!introCounter)
                    return;

                switch (introCounter)
                {
                    case 1:
                        DoScriptText(NEFARIUS_SAY_8, pNefarius);
                        PhraseTimer = 3000;
                        introCounter++;
                        break;
                    case 2:
                        if (PhraseTimer < uiDiff)
                        {
                            DoScriptText(REND_SAY_4, m_creature);
                            PhraseTimer = 3000;
                            introCounter++;
                        }
                        else PhraseTimer -= uiDiff;
                        break;
                    case 3:
                        if (PhraseTimer < uiDiff)
                        {
                            DoScriptText(NEFARIUS_SAY_9, pNefarius);
                            m_creature->SetVisibility(VISIBILITY_OFF);
                            PhraseTimer = 35000;
                            introCounter++;
                        }
                        else PhraseTimer -= uiDiff;
                        break;
                    case 4:
                        if (PhraseTimer < uiDiff)
                        {
                            m_pInstance->SetData(TYPE_GYTH, IN_PROGRESS);
                            introCounter = 0;
                        }
                        else PhraseTimer -= uiDiff;
                        break;
                }
            }
            return;
        }

        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // WhirlWind
        if (m_uiWhirlWindTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_WHIRLWIND);
            m_uiWhirlWindTimer = urand(15000, 20000);
        }
        else
            m_uiWhirlWindTimer -= uiDiff;

        // Cleave
        if (m_uiCleaveTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_CLEAVE);
            m_uiCleaveTimer = urand(7000, 11000);
        }
        else
            m_uiCleaveTimer -= uiDiff;

        // Mortal Strike
        if (m_uiMortalStrikeTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_MORTAL_STRIKE);
            m_uiMortalStrikeTimer = urand(11000, 15000);
        }
        else
            m_uiMortalStrikeTimer -= uiDiff;

        // Enrage
        if (m_uiEnrageTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_ENRAGE);
            m_uiEnrageTimer = 180000;
        }
        else
            m_uiEnrageTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_rend_blackhand(Creature* pCreature)
{
    return new boss_rend_blackhandAI(pCreature);
}

void AddSC_boss_rend_blackhand()
{
    Script* newscript;
    newscript = new Script;
    newscript->Name = "boss_rend_blackhand";
    newscript->GetAI = &GetAI_boss_rend_blackhand;
    newscript->RegisterSelf();
}
