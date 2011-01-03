/*
 * Scripted for --> Mangos-Zero Special Thanks for VladimirMangos, Yehonal, Theluda, Drkotas, Shin, Wrath Team.
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
SDName: Wailing Caverns
SD%Complete: 
SDComment: 
SDCategory: Wailing Caverns
EndScriptData */

/* ContentData
npc_disciple_of_naralex
EndContentData */

#include "precompiled.h"
#include "def_wailing_caverns.h"
#include "escort_ai.h"

/*######
##npc_disciple_of_naralex
######*/

enum
{
    SPELL_MARK              = 5232,
    SPELL_SLEEP             = 1090,
    SPELL_POTION            = 8141,
    SPELL_CLEANSING         = 6270,
    SPELL_AWAKENING         = 6271,
    SPELL_SHAPESHIFT        = 8153,

    YELL_AFTER_GOSSIP       = -1614999,
    SAY_CAST_MARK           = -1614998,
    SAY_1ST_WP              = -1614997,
    SAY_AFTER_1ST_TRASH     = -1614996,
    SAY_BEFORE_CIRCLE       = -1614995,
    SAY_AFTER_CIRCLE        = -1614994,
    SAY_BEFORE_CHAMBER      = -1614993,
    SAY_BEFORE_RITUAL       = -1614992,
    EMOTE_DISCIPLE_1        = -1614991,
    EMOTE_NARALEX_1         = -1614990,
    SAY_ATTACKED           = -1614989,
    EMOTE_NARALEX_2         = -1614987,
    SAY_BEFORE_MUTANOUS     = -1614986,
    SAY_NARALEX_AWAKEN      = -1614985,
    SAY_DISCIPLE_FINAL      = -1614984,
    SAY_NARALEX_FINAL1      = -1614983,
    SAY_NARALEX_FINAL2      = -1614982,

    MOB_DEVIATE_VIPER       = 5755,
    MOB_DEVIATE_MOCCASIN    = 5762,
    MOB_NIGHTMARE_ECTOPLASM = 5763,
    MOB_MUTANOUS_DEVOURER   = 3654
};

#define GOSSIP_ITEM_BEGIN   "Let the event begin!"

float Position [10][3] =
{
    {-33.5f, 243.3f, -93.6f},
    {-61.5f, 296.6f, -89.8f},
    {-70.3f, 259.7f, -91.8f},
    {142.7f, 254.0f, -102.2f},
    {140.5f, 219.8f, -102.4f},
    {92.2f, 261.9f, -101.5f},
    {100.3f, 268.6f, -102.2f},
    {123.8f, 271.9f, -102.4f},
    {141.3f, 255.1f, -102.2f},
    {142.4f, 199.7f, -93.2f}
};

struct MANGOS_DLL_DECL npc_disciple_of_naralexAI : public npc_escortAI
{
	npc_disciple_of_naralexAI(Creature* pCreature) : npc_escortAI(pCreature)
	{
		m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
		Reset();
	}

	ScriptedInstance* m_pInstance;
    Unit* EventStarter;

    uint32 Event_Timer;
    uint32 Sleep_Timer;
    uint32 Potion_Timer;
    uint32 Cleansing_Timer;

    int32 Point;
    int8 Subevent_Phase;

    bool Yelled;

    void Reset() 
    {
        Sleep_Timer = 5000;
        Potion_Timer = 5000;
        Cleansing_Timer = 0;
        Yelled = false;
    }
    
    void EnterEvadeMode() 
    {
        if (Point == 15 || Point == 30)
        {
            m_creature->DeleteThreatList();
            m_creature->CombatStop(true);
            Reset();
        }
        else
        {
            npc_escortAI::EnterEvadeMode();
        }
    }
    void Debug (uint32 Point)
    {
        error_log("Debug: Wailing Caverns escort event point %u ", Point, EventStarter->GetName());
    }

	void WaypointReached(uint32 i) 
    {
        switch (i)
        {
        case 0:
            DoScriptText(SAY_CAST_MARK,m_creature);
            SetEscortPaused(true);
            Event_Timer = 5000;
            Point = i;
            break;
        case 1:
            DoScriptText(SAY_1ST_WP,m_creature);
            Event_Timer = 5000;
            Point = i;
            SetEscortPaused(true);
            break;
        case 6:
            DoScriptText(SAY_AFTER_1ST_TRASH,m_creature);
            break;
        case 15:
            Subevent_Phase = 0;
            Event_Timer = 2000;
            Point = i;
            SetEscortPaused(true);
            break;
        case 26:
            DoScriptText(SAY_BEFORE_CHAMBER,m_creature);
            break;
        case 30:
            m_pInstance->SetData(TYPE_DISCIPLE, IN_PROGRESS);
            Event_Timer = 1000;
            Subevent_Phase = 0;
            Point = i;
            SetEscortPaused(true);
        default: break;
        }
    }

   	void SummonAttacker(uint32 entry, float x, float y, float z)
	{
		Creature* Summoned = m_creature->SummonCreature(entry, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 20000);
        if (Summoned && EventStarter)
            ((CreatureAI*)Summoned->AI())->AttackStart(EventStarter);
    }

    void UpdateEscortAI(const uint32 diff)
    {
        if (!m_pInstance)
            return;
        
        Unit* pPlayer = GetPlayerForEscort();
        if (!pPlayer)
            return;
        EventStarter = pPlayer;

        Unit* Naralex = m_creature->GetMap()->GetUnit( m_pInstance->GetData64(DATA_NARALEX));
        if (!Naralex)
            return;

        if (Event_Timer && Event_Timer <= diff)
        {
            switch (Point)
            {
            case 0:
                {
                Debug(Point);
                Map *map = m_creature->GetMap();
                if (map && map->IsDungeon())
                {
                    Map::PlayerList const &PlayerList = map->GetPlayers();
                    if (!PlayerList.isEmpty())
                    {
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        {
                            if (i->getSource()->isAlive() && (i->getSource()->GetDistance(m_creature)<30))
                                m_creature->CastSpell(i->getSource(),SPELL_MARK,false);
                        }
                    }
                }
                SetEscortPaused(false);
                Event_Timer = 0;
                break;
                }

            case 1:
                Debug(Point);
                SetEscortPaused(false);
                Event_Timer = 0;
                break;

            case 15:
                Debug(Point);
                switch (Subevent_Phase)
                {
                case 0:
                    DoScriptText(SAY_BEFORE_CIRCLE,m_creature);
                    Subevent_Phase = 1;
                    Event_Timer = 2000;
                    break;
                case 1:
                    m_creature->CastSpell(m_creature,SPELL_CLEANSING,false);
                    Subevent_Phase = 2;
                    Event_Timer = 30000;
                    break;
                case 2:
                    for (int i=0; i <3; ++i)
                    {
                        SummonAttacker(MOB_DEVIATE_VIPER,Position[i][0],Position[i][1],Position[i][2]);
                    }
                    Subevent_Phase = 3;
                    Event_Timer = 2000;
                    break;
                case 3:
                    if (!m_creature->isInCombat() && !pPlayer->isInCombat())
                    {
                        DoScriptText(SAY_AFTER_CIRCLE,m_creature);
                        Point = 16;
                        Event_Timer = 2000;
                        SetEscortPaused(false);
                        break;
                    }
                    else
                    {
                        Event_Timer = 2000;
                        Subevent_Phase = 3;
                        break;
                    }
                }
                break;
            case 30:
                Debug(Point);
                SetEscortPaused(true);
                switch (Subevent_Phase)
                {
                case 0:
                    DoScriptText(SAY_BEFORE_RITUAL,m_creature);
                    Subevent_Phase = 1;
                    Event_Timer = 2000;
                    break;
                case 1:
                    m_creature->CastSpell(m_creature,SPELL_AWAKENING,false);
                    DoScriptText(EMOTE_DISCIPLE_1,m_creature);
                    Subevent_Phase = 2;
                    Event_Timer = 4000;
                    break;
                case 2:
                    DoScriptText(EMOTE_NARALEX_1, Naralex);
                    Subevent_Phase = 3;
                    Event_Timer = 5000;
                    break;
                case 3:
                    for (int i = 3; i <6; ++i)
                    {
                        SummonAttacker(MOB_DEVIATE_MOCCASIN, Position[i][0],Position[i][1],Position[i][2]);
                    }
                    Event_Timer = 40000;
                    Subevent_Phase = 4;
                    break;
                case 4:
                    for (int i = 3; i <10; ++i)
                    {
                        SummonAttacker(MOB_NIGHTMARE_ECTOPLASM, Position[i][0],Position[i][1],Position[i][2]);
                    }
                    Event_Timer = 40000;
                    Subevent_Phase = 5;
                    break;
                case 5:
                     Subevent_Phase = 6;
                     Event_Timer = 10000;
                     DoScriptText(EMOTE_NARALEX_2,Naralex);
                     DoScriptText(SAY_BEFORE_MUTANOUS,m_creature);
                     break;
                case 6:
                    SummonAttacker(MOB_MUTANOUS_DEVOURER, Position[4][0],Position[4][1],Position[4][2]);
                    Subevent_Phase = 7;
                    Event_Timer = 2000;
                    break;
                case 7:
                    if (m_pInstance->GetData(TYPE_MUTANOUS) == DONE)
                    {
                    Naralex->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_SIT);
                    DoScriptText(SAY_NARALEX_AWAKEN,Naralex);
                    m_creature->InterruptNonMeleeSpells(false,SPELL_AWAKENING);
                    m_creature->RemoveAurasDueToSpell(SPELL_AWAKENING);
                    m_pInstance->SetData(TYPE_DISCIPLE,DONE);
                    Event_Timer = 2000;
                    Subevent_Phase = 8;
                    break;
                    }else
                    {
                    Event_Timer = 2000;
                    Subevent_Phase = 7;
                    break;
                    }
                case 8:
                    DoScriptText(SAY_DISCIPLE_FINAL,m_creature);
                    Subevent_Phase = 9;
                    Event_Timer = 5000;
                    break;
                case 9:
                    DoScriptText(SAY_NARALEX_FINAL1,Naralex);
                    Naralex->SetByteValue(UNIT_FIELD_BYTES_1,0,UNIT_STAND_STATE_STAND);
                    Event_Timer = 5000;
                    Subevent_Phase = 10;
                    break;
                case 10:
                    DoScriptText(SAY_NARALEX_FINAL2,Naralex);
                    m_creature->CastSpell(m_creature,SPELL_SHAPESHIFT,false);
                    Naralex->CastSpell(Naralex,SPELL_SHAPESHIFT,false);
                    Event_Timer = 10000;
                    Subevent_Phase = 11;
                    break;
                case 11:
                    m_creature->SendMonsterMove(Position[9][0],Position[9][1],Position[9][2],SPLINETYPE_NORMAL,SPLINEFLAG_UNKNOWN7,5000); 
                    Naralex->SendMonsterMove(Position[9][0],Position[9][1],Position[9][2],SPLINETYPE_NORMAL,SPLINEFLAG_UNKNOWN7,5000);
                    Event_Timer = 5000;
                    Subevent_Phase = 12;
                    break;
                case 12:
                    m_creature->SetVisibility(VISIBILITY_OFF);
                    Naralex->SetVisibility(VISIBILITY_OFF);
                    break;
                }
                break;
            default: break;
            }
        }else Event_Timer -= diff;

        if (Potion_Timer < diff)
        {
            if ((m_creature->GetHealth()/m_creature->GetMaxHealth())<0.8)
                m_creature->CastSpell(m_creature, SPELL_POTION, false);
            Potion_Timer = 45000;
        } else Potion_Timer -= diff;

        if (m_creature->isInCombat() && m_creature->isInCombat() && m_creature->getVictim())
        {
            if (!Yelled)
            {
                DoScriptText(SAY_ATTACKED,m_creature,m_creature->getVictim());
                Yelled = true;
            }

            if (Sleep_Timer < diff)
            {
                if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM,1))
                    m_creature->CastSpell(target,SPELL_SLEEP,false);
                Sleep_Timer = 30000;
            } else Sleep_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    }
};

bool GossipHello_npc_disciple_of_naralex(Player* pPlayer, Creature* pCreature)
{
	ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
	
	if (pCreature->isQuestGiver())
		pPlayer->PrepareQuestMenu(pCreature->GetGUID());
	if (m_pInstance && m_pInstance->GetData(TYPE_DISCIPLE) == SPECIAL)
    {
		pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BEGIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(699, pCreature->GetGUID());
    } else
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
	return true;
}

bool GossipSelect_npc_disciple_of_naralex(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance* m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    
    if (!m_pInstance)
        return false;

	if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
	{
		if (npc_disciple_of_naralexAI* pEscortAI = dynamic_cast<npc_disciple_of_naralexAI*>(pCreature->AI()))
		{   
            pEscortAI->Start(true,false,pPlayer->GetGUID());
            pCreature->setFaction(FACTION_ESCORT_N_ACTIVE);
            DoScriptText(YELL_AFTER_GOSSIP,pCreature);
		}
		pPlayer->CLOSE_GOSSIP_MENU();
	}
	return true;
}

CreatureAI* GetAI_npc_disciple_of_naralex(Creature* pCreature)
{
	return new npc_disciple_of_naralexAI(pCreature);
}

void AddSC_wailing_caverns()
{
	Script *newscript;
	
	newscript = new Script;
	newscript->Name = "npc_disciple_of_naralex";
	newscript->GetAI = &GetAI_npc_disciple_of_naralex;
	newscript->pGossipHello =  &GossipHello_npc_disciple_of_naralex;
	newscript->pGossipSelect = &GossipSelect_npc_disciple_of_naralex;
	newscript->RegisterSelf();
}
