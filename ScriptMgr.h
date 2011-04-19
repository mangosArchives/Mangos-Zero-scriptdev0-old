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

#ifndef SC_SCRIPTMGR_H
#define SC_SCRIPTMGR_H

#include "Common.h"
#include "DBCStructure.h"

class Player;
class Creature;
class CreatureAI;
class InstanceData;
class Quest;
class Item;
class GameObject;
class SpellCastTargets;
class Map;
class Unit;
class WorldObject;
class Aura;
class Object;

#define MAX_SCRIPTS         5000                            //72 bytes each (approx 351kb)
#define VISIBLE_RANGE       (166.0f)                        //MAX visible range (size of grid)
#define DEFAULT_TEXT        "<ScriptDev2 Text Entry Missing!>"

struct Script
{
    Script() :
        pGossipHello(NULL), pGossipHelloGO(NULL), pGossipSelect(NULL), pGossipSelectGO(NULL),
        pGossipSelectWithCode(NULL), pGossipSelectGOWithCode(NULL),
        pDialogStatusNPC(NULL), pDialogStatusGO(NULL),
        pQuestAcceptNPC(NULL), pQuestAcceptGO(NULL), pQuestAcceptItem(NULL),
        pQuestRewardedNPC(NULL), pQuestRewardedGO(NULL),
        pGOUse(NULL), pItemUse(NULL), pAreaTrigger(NULL), pProcessEventId(NULL),
        pEffectDummyNPC(NULL), pEffectDummyGO(NULL), pEffectDummyItem(NULL), pEffectAuraDummy(NULL),
        GetAI(NULL), GetInstanceData(NULL)
    {}

    std::string Name;

    bool (*pGossipHello             )(Player*, Creature*);
    bool (*pGossipHelloGO           )(Player*, GameObject*);
    bool (*pGossipSelect            )(Player*, Creature*, uint32, uint32);
    bool (*pGossipSelectGO          )(Player*, GameObject*, uint32, uint32);
    bool (*pGossipSelectWithCode    )(Player*, Creature*, uint32, uint32, const char*);
    bool (*pGossipSelectGOWithCode  )(Player*, GameObject*, uint32, uint32, const char*);
    uint32 (*pDialogStatusNPC       )(Player*, Creature*);
    uint32 (*pDialogStatusGO        )(Player*, GameObject*);
    bool (*pQuestAcceptNPC          )(Player*, Creature*, Quest const*);
    bool (*pQuestAcceptGO           )(Player*, GameObject*, Quest const*);
    bool (*pQuestAcceptItem         )(Player*, Item*, Quest const*);
    bool (*pQuestRewardedNPC        )(Player*, Creature*, Quest const*);
    bool (*pQuestRewardedGO         )(Player*, GameObject*, Quest const*);
    bool (*pGOUse                   )(Player*, GameObject*);
    bool (*pItemUse                 )(Player*, Item*, SpellCastTargets const&);
    bool (*pAreaTrigger             )(Player*, AreaTriggerEntry const*);
    bool (*pProcessEventId          )(uint32, Object*, Object*, bool);
    bool (*pEffectDummyNPC          )(Unit*, uint32, SpellEffectIndex, Creature*);
    bool (*pEffectDummyGO           )(Unit*, uint32, SpellEffectIndex, GameObject*);
    bool (*pEffectDummyItem         )(Unit*, uint32, SpellEffectIndex, Item*);
    bool (*pEffectAuraDummy         )(const Aura*, bool);

    CreatureAI* (*GetAI             )(Creature*);
    InstanceData* (*GetInstanceData )(Map*);

    void RegisterSelf(bool bReportError = true);
};

//Generic scripting text function
void DoScriptText(int32 textEntry, WorldObject* pSource, Unit* target = NULL);

#if COMPILER == COMPILER_GNU
#define FUNC_PTR(name,callconvention,returntype,parameters)    typedef returntype(*name)parameters __attribute__ ((callconvention));
#else
#define FUNC_PTR(name, callconvention, returntype, parameters)    typedef returntype(callconvention *name)parameters;
#endif

#endif
