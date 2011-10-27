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

#include "precompiled.h"
#include "Config/Config.h"
#include "config.h"
#include "Database/DatabaseEnv.h"
#include "DBCStores.h"
#include "ObjectMgr.h"
#include "ProgressBar.h"
#include "../system/ScriptLoader.h"
#include "../system/system.h"
#include "../../game/ScriptMgr.h"

typedef std::vector<Script*> SDScriptVec;
int num_sc_scripts;
SDScriptVec m_scripts;

Config SD0Config;

void FillSpellSummary();

void LoadDatabase()
{
    std::string strSD0DBinfo = SD0Config.GetStringDefault("ScriptDevZeroDatabaseInfo", "");

    if (strSD0DBinfo.empty())
    {
        error_log("SD0: Missing ScriptDevZero database info from configuration file. Load database aborted.");
        return;
    }

    //Initialize connection to DB
    if (SD0Database.Initialize(strSD0DBinfo.c_str()))
    {
        outstring_log("SD0: ScriptDevZero database at %s initialized.", strSD0DBinfo.c_str());
        outstring_log("");

        pSystemMgr.LoadVersion();
        pSystemMgr.LoadScriptTexts();
        pSystemMgr.LoadScriptTextsCustom();
        pSystemMgr.LoadScriptGossipTexts();
        pSystemMgr.LoadScriptWaypoints();
    }
    else
    {
        error_log("SD0: Unable to connect to Database. Load database aborted.");
        return;
    }

    SD0Database.HaltDelayThread();

}

struct TSpellSummary {
    uint8 Targets;                                          // set of enum SelectTarget
    uint8 Effects;                                          // set of enum SelectEffect
}extern *SpellSummary;

MANGOS_DLL_EXPORT
void FreeScriptLibrary()
{
    // Free Spell Summary
    delete []SpellSummary;

    // Free resources before library unload
    for (SDScriptVec::const_iterator itr = m_scripts.begin(); itr != m_scripts.end(); ++itr)
        delete *itr;

    m_scripts.clear();

    num_sc_scripts = 0;
}

MANGOS_DLL_EXPORT
void InitScriptLibrary()
{
    //ScriptDevZero startup
    outstring_log("");
    outstring_log("ScriptDevZero http://github.com/scriptdev/scriptdevzero/");
    outstring_log("");
    outstring_log("Fork of: ");
    outstring_log(" MMM  MMM    MM");
    outstring_log("M  MM M  M  M  M");
    outstring_log("MM    M   M   M");
    outstring_log(" MMM  M   M  M");
    outstring_log("   MM M   M MMMM");
    outstring_log("MM  M M  M ");
    outstring_log(" MMM  MMM  http://www.scriptdev2.com");
    outstring_log("");

    //Get configuration file
    if (!SD0Config.SetSource(_SCRIPTDEVZERO_CONFIG))
        error_log("SD0: Unable to open configuration file. Database will be unaccessible. Configuration values will use default.");
    else
        outstring_log("SD0: Using configuration file %s",_SCRIPTDEVZERO_CONFIG);

    //Check config file version
    if (SD0Config.GetIntDefault("ConfVersion", 0) != SD0_CONF_VERSION)
        error_log("SD0: Configuration file version doesn't match expected version. Some config variables may be wrong or missing.");

    outstring_log("");

    //Load database (must be called after SD0Config.SetSource).
    LoadDatabase();

    outstring_log("SD0: Loading C++ scripts");
    BarGoLink bar(1);
    bar.step();
    outstring_log("");

    // Resize script ids to needed ammount of assigned ScriptNames (from core)
    m_scripts.resize(GetScriptIdsCount(), NULL);

    FillSpellSummary();

    AddScripts();

    // Check existance scripts for all registered by core script names
    for (uint32 i = 1; i < GetScriptIdsCount(); ++i)
    {
        if (!m_scripts[i])
            error_log("SD0: No script found for ScriptName '%s'.", GetScriptName(i));
    }

    outstring_log(">> Loaded %i C++ Scripts.", num_sc_scripts);
}

//*********************************
//*** Functions used globally ***

/**
 * Function that does script text
 *
 * @param iTextEntry Entry of the text, stored in SD0-database
 * @param pSource Source of the text
 * @param pTarget Can be NULL (depending on CHAT_TYPE of iTextEntry). Possible target for the text
 */
void DoScriptText(int32 iTextEntry, WorldObject* pSource, Unit* pTarget)
{
    if (!pSource)
    {
        error_log("SD0: DoScriptText entry %i, invalid Source pointer.", iTextEntry);
        return;
    }

    if (iTextEntry >= 0)
    {
        error_log("SD0: DoScriptText with source entry %u (TypeId=%u, guid=%u) attempts to process text entry %i, but text entry must be negative.",
            pSource->GetEntry(), pSource->GetTypeId(), pSource->GetGUIDLow(), iTextEntry);

        return;
    }

    const StringTextData* pData = pSystemMgr.GetTextData(iTextEntry);
    if (!pData)
    {
        error_log("SD0: DoScriptText with source entry %u (TypeId=%u, guid=%u) could not find text entry %i.",
            pSource->GetEntry(), pSource->GetTypeId(), pSource->GetGUIDLow(), iTextEntry);

        return;
    }

    debug_log("SD0: DoScriptText: text entry=%i, Sound=%u, Type=%u, Language=%u, Emote=%u",
        iTextEntry, pData->uiSoundId, pData->uiType, pData->uiLanguage, pData->uiEmote);

    if (pData->uiSoundId)
    {
        if (GetSoundEntriesStore()->LookupEntry(pData->uiSoundId))
        {
            if (pData->uiType == CHAT_TYPE_ZONE_YELL)
                pSource->GetMap()->PlayDirectSoundToMap(pData->uiSoundId);
            else if (pData->uiType == CHAT_TYPE_WHISPER || pData->uiType == CHAT_TYPE_BOSS_WHISPER)
            {
                // An error will be displayed for the text
                if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                    pSource->PlayDirectSound(pData->uiSoundId, (Player*)pTarget);
            }
            else
                pSource->PlayDirectSound(pData->uiSoundId);
        }
        else
            error_log("SD0: DoScriptText entry %i tried to process invalid sound id %u.", iTextEntry, pData->uiSoundId);
    }

    if (pData->uiEmote)
    {
        if (pSource->GetTypeId() == TYPEID_UNIT || pSource->GetTypeId() == TYPEID_PLAYER)
            ((Unit*)pSource)->HandleEmoteCommand(pData->uiEmote);
        else
            error_log("SD0: DoScriptText entry %i tried to process emote for invalid TypeId (%u).", iTextEntry, pSource->GetTypeId());
    }

    switch(pData->uiType)
    {
        case CHAT_TYPE_SAY:
            pSource->MonsterSay(iTextEntry, pData->uiLanguage, pTarget);
            break;
        case CHAT_TYPE_YELL:
            pSource->MonsterYell(iTextEntry, pData->uiLanguage, pTarget);
            break;
        case CHAT_TYPE_TEXT_EMOTE:
            pSource->MonsterTextEmote(iTextEntry, pTarget);
            break;
        case CHAT_TYPE_BOSS_EMOTE:
            pSource->MonsterTextEmote(iTextEntry, pTarget, true);
            break;
        case CHAT_TYPE_WHISPER:
        {
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                pSource->MonsterWhisper(iTextEntry, pTarget);
            else
                error_log("SD0: DoScriptText entry %i cannot whisper without target unit (TYPEID_PLAYER).", iTextEntry);

            break;
        }
        case CHAT_TYPE_BOSS_WHISPER:
        {
            if (pTarget && pTarget->GetTypeId() == TYPEID_PLAYER)
                pSource->MonsterWhisper(iTextEntry, pTarget, true);
            else
                error_log("SD0: DoScriptText entry %i cannot whisper without target unit (TYPEID_PLAYER).", iTextEntry);

            break;
        }
        case CHAT_TYPE_ZONE_YELL:
            pSource->MonsterYellToZone(iTextEntry, pData->uiLanguage, pTarget);
            break;
    }
}

/**
 * Function that either simulates or does script text for a map
 *
 * @param iTextEntry Entry of the text, stored in SD0-database, only type CHAT_TYPE_ZONE_YELL supported
 * @param uiCreatureEntry Id of the creature of whom saying will be simulated
 * @param pMap Given Map on which the map-wide text is displayed
 * @param pCreatureSource Can be NULL. If pointer to Creature is given, then the creature does the map-wide text
 * @param pTarget Can be NULL. Possible target for the text
 */
void DoOrSimulateScriptTextForMap(int32 iTextEntry, uint32 uiCreatureEntry, Map* pMap, Creature* pCreatureSource /*=NULL*/, Unit* pTarget /*=NULL*/)
{
    if (!pMap)
    {
        error_log("SD0: DoOrSimulateScriptTextForMap entry %i, invalid Map pointer.", iTextEntry);
        return;
    }

    if (iTextEntry >= 0)
    {
        error_log("SD0: DoOrSimulateScriptTextForMap with source entry %u for map %u attempts to process text entry %i, but text entry must be negative.", uiCreatureEntry, pMap->GetId(), iTextEntry);
        return;
    }

    CreatureInfo const* pInfo = GetCreatureTemplateStore(uiCreatureEntry);
    if (!pInfo)
    {
         error_log("SD0: DoOrSimulateScriptTextForMap has invalid source entry %u for map %u.", uiCreatureEntry, pMap->GetId());
        return;
    }

    const StringTextData* pData = pSystemMgr.GetTextData(iTextEntry);
    if (!pData)
    {
        error_log("SD0: DoOrSimulateScriptTextForMap with source entry %u for map %u could not find text entry %i.", uiCreatureEntry, pMap->GetId(), iTextEntry);
        return;
    }

    debug_log("SD0: DoOrSimulateScriptTextForMap: text entry=%i, Sound=%u, Type=%u, Language=%u, Emote=%u",
        iTextEntry, pData->uiSoundId, pData->uiType, pData->uiLanguage, pData->uiEmote);

    if (pData->uiType != CHAT_TYPE_ZONE_YELL)
    {
        error_log("SD0: DoSimulateScriptTextForMap entry %i has not supported chat type %u.", iTextEntry, pData->uiType);
        return;
    }

    if (pData->uiSoundId)
    {
        if (GetSoundEntriesStore()->LookupEntry(pData->uiSoundId))
            pMap->PlayDirectSoundToMap(pData->uiSoundId);
        else
            error_log("SD0: DoOrSimulateScriptTextForMap entry %i tried to process invalid sound id %u.", iTextEntry, pData->uiSoundId);
    }

    if (pCreatureSource)                                // If provided pointer for sayer, use direct version
        pMap->MonsterYellToMap(pCreatureSource->GetObjectGuid(), iTextEntry, pData->uiLanguage, pTarget);
    else                                                // Simulate yell
        pMap->MonsterYellToMap(pInfo, iTextEntry, pData->uiLanguage, pTarget);
}

//*********************************
//*** Functions used internally ***

void Script::RegisterSelf(bool bReportError)
{
    if (uint32 id = GetScriptId(Name.c_str()))
    {
        m_scripts[id] = this;
        ++num_sc_scripts;
    }
    else
    {
        if (bReportError)
            error_log("SD0: Script registering but ScriptName %s is not assigned in database. Script will not be used.", Name.c_str());

        delete this;
    }
}

//********************************
//*** Functions to be Exported ***

MANGOS_DLL_EXPORT
char const* GetScriptLibraryVersion()
{
    if (!strSD0Version.empty())
    {
        strSD0Version.append(_FULLVERSION);
        return strSD0Version.c_str();
    }

    return _FULLVERSION;
}

MANGOS_DLL_EXPORT
bool GossipHello(Player* pPlayer, Creature* pCreature)
{
    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->pGossipHello)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pGossipHello(pPlayer, pCreature);
}

MANGOS_DLL_EXPORT
bool GOGossipHello(Player *pPlayer, GameObject *pGo)
{
    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pGossipHelloGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pGossipHelloGO(pPlayer, pGo);
}

MANGOS_DLL_EXPORT
bool GossipSelect(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    debug_log("SD0: Gossip selection, sender: %u, action: %u", uiSender, uiAction);

    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->pGossipSelect)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pGossipSelect(pPlayer, pCreature, uiSender, uiAction);
}

MANGOS_DLL_EXPORT
bool GOGossipSelect(Player *pPlayer, GameObject *pGo, uint32 sender, uint32 action)
{
    debug_log("SD0: GO Gossip selection, sender: %u, action: %u", sender, action);

    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pGossipSelectGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pGossipSelectGO(pPlayer, pGo, sender, action);
}

MANGOS_DLL_EXPORT
bool GossipSelectWithCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* sCode)
{
    debug_log("SD0: Gossip selection with code, sender: %u, action: %u", uiSender, uiAction);

    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->pGossipSelectWithCode)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pGossipSelectWithCode(pPlayer, pCreature, uiSender, uiAction, sCode);
}

MANGOS_DLL_EXPORT
bool GOGossipSelectWithCode(Player *pPlayer, GameObject *pGo, uint32 sender, uint32 action, const char* sCode)
{
    debug_log("SD0: GO Gossip selection with code, sender: %u, action: %u", sender, action);

    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pGossipSelectGOWithCode)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pGossipSelectGOWithCode(pPlayer, pGo, sender, action, sCode);
}

MANGOS_DLL_EXPORT
bool QuestAccept(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->pQuestAcceptNPC)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pQuestAcceptNPC(pPlayer, pCreature, pQuest);
}

MANGOS_DLL_EXPORT
bool QuestRewarded(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->pQuestRewardedNPC)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pQuestRewardedNPC(pPlayer, pCreature, pQuest);
}

MANGOS_DLL_EXPORT
uint32 GetNPCDialogStatus(Player* pPlayer, Creature* pCreature)
{
    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->pDialogStatusNPC)
        return 100;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pDialogStatusNPC(pPlayer, pCreature);
}

MANGOS_DLL_EXPORT
uint32 GetGODialogStatus(Player* pPlayer, GameObject* pGo)
{
    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pDialogStatusGO)
        return 100;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pDialogStatusGO(pPlayer, pGo);
}

MANGOS_DLL_EXPORT
bool ItemQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
{
    Script *tmpscript = m_scripts[pItem->GetProto()->ScriptId];

    if (!tmpscript || !tmpscript->pQuestAcceptItem)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pQuestAcceptItem(pPlayer, pItem, pQuest);
}

MANGOS_DLL_EXPORT
bool GOUse(Player* pPlayer, GameObject* pGo)
{
    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pGOUse)
        return false;

    return tmpscript->pGOUse(pPlayer, pGo);
}

MANGOS_DLL_EXPORT
bool GOQuestAccept(Player* pPlayer, GameObject* pGo, const Quest* pQuest)
{
    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pQuestAcceptGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pQuestAcceptGO(pPlayer, pGo, pQuest);
}

MANGOS_DLL_EXPORT
bool GOQuestRewarded(Player* pPlayer, GameObject* pGo, Quest const* pQuest)
{
    Script *tmpscript = m_scripts[pGo->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pQuestRewardedGO)
        return false;

    pPlayer->PlayerTalkClass->ClearMenus();

    return tmpscript->pQuestRewardedGO(pPlayer, pGo, pQuest);
}

MANGOS_DLL_EXPORT
bool AreaTrigger(Player* pPlayer, AreaTriggerEntry const* atEntry)
{
    Script *tmpscript = m_scripts[GetAreaTriggerScriptId(atEntry->id)];

    if (!tmpscript || !tmpscript->pAreaTrigger)
        return false;

    return tmpscript->pAreaTrigger(pPlayer, atEntry);
}

MANGOS_DLL_EXPORT
bool ProcessEvent(uint32 uiEventId, Object* pSource, Object* pTarget, bool bIsStart)
{
    Script *tmpscript = m_scripts[GetEventIdScriptId(uiEventId)];

    if (!tmpscript || !tmpscript->pProcessEventId)
        return false;

    // bIsStart may be false, when event is from taxi node events (arrival=false, departure=true)
    return tmpscript->pProcessEventId(uiEventId, pSource, pTarget, bIsStart);
}

MANGOS_DLL_EXPORT
CreatureAI* GetCreatureAI(Creature* pCreature)
{
    Script *tmpscript = m_scripts[pCreature->GetScriptId()];

    if (!tmpscript || !tmpscript->GetAI)
        return NULL;

    return tmpscript->GetAI(pCreature);
}

MANGOS_DLL_EXPORT
bool ItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    Script *tmpscript = m_scripts[pItem->GetProto()->ScriptId];

    if (!tmpscript || !tmpscript->pItemUse)
        return false;

    return tmpscript->pItemUse(pPlayer, pItem, targets);
}

MANGOS_DLL_EXPORT
bool EffectDummyCreature(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget)
{
    Script *tmpscript = m_scripts[pTarget->GetScriptId()];

    if (!tmpscript || !tmpscript->pEffectDummyNPC)
        return false;

    return tmpscript->pEffectDummyNPC(pCaster, spellId, effIndex, pTarget);
}

MANGOS_DLL_EXPORT
bool EffectDummyGameObject(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget)
{
    Script *tmpscript = m_scripts[pTarget->GetGOInfo()->ScriptId];

    if (!tmpscript || !tmpscript->pEffectDummyGO)
        return false;

    return tmpscript->pEffectDummyGO(pCaster, spellId, effIndex, pTarget);
}

MANGOS_DLL_EXPORT
bool EffectDummyItem(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget)
{
    Script *tmpscript = m_scripts[pTarget->GetProto()->ScriptId];

    if (!tmpscript || !tmpscript->pEffectDummyItem)
        return false;

    return tmpscript->pEffectDummyItem(pCaster, spellId, effIndex, pTarget);
}

MANGOS_DLL_EXPORT
bool AuraDummy(Aura const* pAura, bool apply)
{
    Script *tmpscript = m_scripts[((Creature*)pAura->GetTarget())->GetScriptId()];

    if (!tmpscript || !tmpscript->pEffectAuraDummy)
        return false;

    return tmpscript->pEffectAuraDummy(pAura, apply);
}

MANGOS_DLL_EXPORT
InstanceData* CreateInstanceData(Map* pMap)
{
    Script *tmpscript = m_scripts[pMap->GetScriptId()];

    if (!tmpscript || !tmpscript->GetInstanceData)
        return NULL;

    return tmpscript->GetInstanceData(pMap);
}
