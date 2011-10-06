/*  */

/* AREATRIGGER */
DELETE FROM scripted_areatrigger WHERE entry=3066;
INSERT INTO scripted_areatrigger VALUES (3066,'at_ravenholdt');
DELETE FROM scripted_areatrigger WHERE entry IN (4112, 4113);
INSERT INTO scripted_areatrigger VALUES
(4112,'at_naxxramas'),
(4113,'at_naxxramas');
DELETE FROM scripted_areatrigger WHERE entry IN (3546, 3547, 3548, 3549, 3550, 3552);
INSERT INTO scripted_areatrigger VALUES
(3546, 'at_childrens_week_spot'), -- Darnassian bank
(3547, 'at_childrens_week_spot'), -- Undercity - thone room
(3548, 'at_childrens_week_spot'), -- Stonewrought Dam
(3549, 'at_childrens_week_spot'), -- The Mor'shan Rampart
(3550, 'at_childrens_week_spot'), -- Ratchet Docks
(3552, 'at_childrens_week_spot'); -- Westfall Lighthouse
DELETE FROM scripted_areatrigger WHERE entry IN (2026, 2046);
INSERT INTO scripted_areatrigger VALUES
(2026, 'at_blackrock_spire'),
(2046, 'at_blackrock_spire');
DELETE FROM scripted_areatrigger WHERE entry IN (3958, 3960);
INSERT INTO scripted_areatrigger VALUES
(3958, 'at_zulgurub'),
(3960, 'at_zulgurub');
DELETE FROM scripted_areatrigger WHERE entry IN (1726, 1727, 1728, 1729, 1730, 1731, 1732, 1733, 1734, 1735, 1736, 1737, 1738, 1739, 1740);
INSERT INTO scripted_areatrigger VALUES
(1726, 'at_scent_larkorwi'),
(1727, 'at_scent_larkorwi'),
(1728, 'at_scent_larkorwi'),
(1729, 'at_scent_larkorwi'),
(1730, 'at_scent_larkorwi'),
(1731, 'at_scent_larkorwi'),
(1732, 'at_scent_larkorwi'),
(1733, 'at_scent_larkorwi'),
(1734, 'at_scent_larkorwi'),
(1735, 'at_scent_larkorwi'),
(1736, 'at_scent_larkorwi'),
(1737, 'at_scent_larkorwi'),
(1738, 'at_scent_larkorwi'),
(1739, 'at_scent_larkorwi'),
(1740, 'at_scent_larkorwi');
DELETE FROM scripted_areatrigger WHERE entry=3626;
INSERT INTO scripted_areatrigger VALUES 
(3626, 'at_vaelastrasz');

/* BATTLEGROUNDS */
UPDATE creature_template SET ScriptName='npc_spirit_guide' WHERE entry IN (13116, 13117);

/* WORLD BOSS */
UPDATE creature_template SET ScriptName='boss_ysondre' WHERE entry=14887;
UPDATE creature_template SET ScriptName='boss_emeriss' WHERE entry=14889;
UPDATE creature_template SET ScriptName='boss_lord_kazzak' WHERE entry=12397;
UPDATE creature_template SET ScriptName='boss_taerar' WHERE entry=14890;
UPDATE creature_template SET ScriptName='boss_shade_of_taerar' WHERE entry=15302;
UPDATE creature_template SET ScriptName='boss_azuregos' WHERE entry=6109;
UPDATE creature_template SET ScriptName='mob_dementeddruids' WHERE entry=15260;
UPDATE creature_template SET ScriptName='boss_lethon' WHERE entry=14888;

/* GO */
UPDATE gameobject_template SET ScriptName='go_cat_figurine' WHERE entry=13873;
UPDATE gameobject_template SET ScriptName='go_northern_crystal_pylon' WHERE entry=164955;
UPDATE gameobject_template SET ScriptName='go_western_crystal_pylon' WHERE entry=164956;
UPDATE gameobject_template SET ScriptName='go_eastern_crystal_pylon' WHERE entry=164957;
UPDATE gameobject_template SET ScriptName='go_barov_journal' WHERE entry=180794;
UPDATE gameobject_template SET ScriptName='go_field_repair_bot_74A' where entry=179552;
UPDATE gameobject_template SET ScriptName='go_gilded_brazier' WHERE entry=181956;
UPDATE gameobject_template SET ScriptName='go_orb_of_command' WHERE entry=179879;
UPDATE gameobject_template SET ScriptName='go_resonite_cask' WHERE entry=178145;
UPDATE gameobject_template SET ScriptName='go_sacred_fire_of_life' WHERE entry=175944;
UPDATE gameobject_template SET ScriptName='go_tablet_of_madness' WHERE entry=180368;
UPDATE gameobject_template SET ScriptName='go_tablet_of_the_seven' WHERE entry=169294;
UPDATE gameobject_template SET ScriptName='go_andorhal_tower' WHERE entry IN (176094,176095,176096,176097);
UPDATE gameobject_template SET ScriptName='go_hand_of_iruxos_crystal' WHERE entry=176581;
UPDATE gameobject_template SET ScriptName='go_demon_portal' WHERE entry IN (177243,177365,177369,177397,177398,177399,177400,177366,177367,177368);
UPDATE gameobject_template SET ScriptName='go_wind_stones' WHERE entry IN (180456,180518,180529,180544,180549,180564,180461,180534,180554,180466,180539,180559);
UPDATE gameobject_template SET ScriptName='go_hiveashi_pod' WHERE entry=178553;
UPDATE gameobject_template SET ScriptName='go_panther_cage' WHERE entry=176195;

/* GUARD */
UPDATE creature_template SET ScriptName='guard_orgrimmar' WHERE entry=3296;
UPDATE creature_template SET ScriptName='guard_stormwind' WHERE entry IN (68,1976);
UPDATE creature_template SET ScriptName='guard_contested' WHERE entry IN (9460,4624,3502,11190,15184);
UPDATE creature_template SET ScriptName='guard_elwynnforest' WHERE entry=1423;
UPDATE creature_template SET ScriptName='guard_darnassus' WHERE entry=4262;
UPDATE creature_template SET ScriptName='guard_teldrassil' WHERE entry=3571;
UPDATE creature_template SET ScriptName='guard_ironforge' WHERE entry=5595;
UPDATE creature_template SET ScriptName='guard_dunmorogh' WHERE entry IN (727,13076);
UPDATE creature_template SET ScriptName='guard_undercity' WHERE entry=5624;
UPDATE creature_template SET ScriptName='guard_bluffwatcher' WHERE entry=3084;
UPDATE creature_template SET ScriptName='guard_durotar' WHERE entry=5953;
UPDATE creature_template SET ScriptName='guard_mulgore' WHERE entry IN (3212,3215,3217,3218,3219,3220,3221,3222,3223,3224);
UPDATE creature_template SET ScriptName='guard_dunmorogh' WHERE entry IN (727,13076);
UPDATE creature_template SET ScriptName='guard_tirisfal' WHERE entry IN (1735,1738,2210,1744,1745,5725,1743,2209,1746,1742);

/* NPC (usually creatures to be found in more than one specific zone) */
UPDATE creature_template SET ScriptName='npc_chicken_cluck' WHERE entry=620;
UPDATE creature_template SET ScriptName='npc_garments_of_quests' WHERE entry IN (12429,12423,12427,12430,12428);
UPDATE creature_template SET ScriptName='npc_guardian' WHERE entry=5764;
UPDATE creature_template SET ScriptName='npc_lunaclaw_spirit' WHERE entry=12144;
UPDATE creature_template SET ScriptName='npc_mount_vendor' WHERE entry IN (384,1261,1460,2357,3362,3685,4730,4731,4885,7952,7955,16264,17584);
UPDATE creature_template SET ScriptName='npc_doctor' WHERE entry IN (12939,12920);
UPDATE creature_template SET ScriptName='npc_injured_patient' WHERE entry IN (12936,12937,12938,12923,12924,12925);
UPDATE creature_template SET ScriptName='' WHERE npcflag!=npcflag|65536 AND ScriptName='npc_innkeeper';
UPDATE creature_template SET ScriptName='npc_innkeeper' WHERE npcflag=npcflag|65536;
UPDATE creature_template SET ScriptName='npc_prof_blacksmith' WHERE entry IN (5164,11145,11146,11176,11177,11178,11191,11192,11193);
UPDATE creature_template SET ScriptName='npc_engineering_tele_trinket' WHERE entry IN (14742,14743);
UPDATE creature_template SET ScriptName='npc_rogue_trainer' WHERE entry IN (918,4163,3328,4583,5165,5167,13283,16684);
UPDATE creature_template SET ScriptName='npc_sayge' WHERE entry=14822;
UPDATE creature_template SET ScriptName='npc_shahram' WHERE entry=10718;

/* SPELL */
UPDATE creature_template SET ScriptName='spell_dummy_npc' WHERE entry IN (
-- eastern kingdoms
-- kalimdor
12296,12298);

/* WORLD MAP SCRIPTS */
DELETE FROM world_template WHERE map IN (0, 1);
INSERT INTO world_template VALUES
(0, 'world_map_eastern_kingdoms'),
(1, 'world_map_kalimdor');

/* */
/* ZONE */
/* */

/* ALTERAC MOUNTAINS */

/* ALTERAC VALLEY */

/* ARATHI HIGHLANDS */
UPDATE creature_template SET ScriptName='npc_professor_phizzlethorpe' WHERE entry=2768;

/* ASHENVALE */
UPDATE creature_template SET ScriptName='npc_muglash' WHERE entry=12717;
UPDATE gameobject_template SET ScriptName='go_naga_brazier' WHERE entry=178247;
UPDATE creature_template SET ScriptName='npc_ruul_snowhoof' WHERE entry=12818;
UPDATE creature_template SET ScriptName='npc_torek' WHERE entry=12858;

/* AZSHARA */
UPDATE creature_template SET ScriptName='mobs_spitelashes' WHERE entry IN (6190,6193,6194,6195,6196,7885,7886,12204,12205);
UPDATE creature_template SET ScriptName='npc_loramus_thalipedes' WHERE entry=7783;

/* BADLANDS */

/* BARRENS */
UPDATE creature_template SET ScriptName='npc_beaten_corpse' WHERE entry=10668;
UPDATE creature_template SET ScriptName='npc_gilthares' WHERE entry=3465;
UPDATE creature_template SET ScriptName='npc_sputtervalve' WHERE entry=3442;
UPDATE creature_template SET ScriptName='npc_taskmaster_fizzule' WHERE entry=7233;
UPDATE creature_template SET ScriptName='npc_twiggy_flathead' WHERE entry=6248;
DELETE FROM scripted_areatrigger WHERE entry=522;
INSERT INTO scripted_areatrigger VALUES (522,'at_twiggy_flathead');
UPDATE creature_template SET ScriptName='npc_wizzlecranks_shredder' WHERE entry=3439;

/* BLACKFATHOM DEPTHS */
UPDATE instance_template SET ScriptName='instance_blackfathom_deeps' WHERE map=48;
UPDATE gameobject_template SET ScriptName='go_fire_of_akumai' WHERE entry IN (21118,21119,21120,21121);

/* BLACKROCK DEPTHS */
DELETE FROM scripted_areatrigger WHERE entry=1526;
INSERT INTO scripted_areatrigger VALUES (1526,'at_ring_of_law');
UPDATE instance_template SET ScriptName='instance_blackrock_depths' WHERE map =230;
UPDATE creature_template SET ScriptName='boss_emperor_dagran_thaurissan' WHERE entry=9019;
UPDATE creature_template SET ScriptName='boss_moira_bronzebeard' WHERE entry=8929;
UPDATE creature_template SET ScriptName='boss_ambassador_flamelash' WHERE entry=9156;
UPDATE creature_template SET ScriptName='boss_anubshiah' WHERE entry=9031;
UPDATE creature_template SET ScriptName='boss_doomrel' WHERE entry=9039;
UPDATE creature_template SET ScriptName='boss_gloomrel' WHERE entry=9037;
UPDATE creature_template SET ScriptName='boss_general_angerforge' WHERE entry=9033;
UPDATE creature_template SET ScriptName='boss_gorosh_the_dervish' WHERE entry=9027;
UPDATE creature_template SET ScriptName='boss_grizzle' WHERE entry=9028;
UPDATE creature_template SET ScriptName='boss_high_interrogator_gerstahn' WHERE entry=9018;
UPDATE creature_template SET ScriptName='boss_magmus' WHERE entry=9938;
UPDATE creature_template SET ScriptName='mob_phalanx' WHERE entry=9502;
UPDATE creature_template SET ScriptName='npc_grimstone' WHERE entry=10096;
UPDATE creature_template SET ScriptName='npc_lokhtos_darkbargainer' WHERE entry=12944;
UPDATE creature_template SET ScriptName='npc_kharan_mighthammer' WHERE entry=9021;
UPDATE creature_template SET ScriptName='npc_rocknot' WHERE entry=9503;
UPDATE gameobject_template SET ScriptName='go_shadowforge_brazier' WHERE entry IN (174744, 174745);
UPDATE creature_template SET ScriptName='npc_theldren_trigger' WHERE entry=16079;
UPDATE creature_template SET ScriptName ='npc_dughal_stormwing' WHERE entry=9022;
UPDATE creature_template SET ScriptName ='npc_marshal_windsor' WHERE entry=9023;
UPDATE creature_template SET ScriptName ='npc_marshal_reginald_windsor' WHERE entry=9682;
UPDATE creature_template SET ScriptName ='npc_tobias_seecher' WHERE entry=9679;
UPDATE gameobject_template SET ScriptName ='go_cell_door' WHERE entry IN (170561, 170562, 170566, 170567, 170568, 170569);
UPDATE gameobject_template SET ScriptName='go_relic_coffer_door' WHERE entry IN (174554, 174555, 174556, 174557, 174558, 174559, 174560, 174561, 174562, 174563, 174564, 174566);

/* BLACKROCK SPIRE */
UPDATE instance_template SET ScriptName='instance_blackrock_spire' WHERE map=229;
/* BLACKROCK SPIRE Lower bosses */
UPDATE creature_template SET ScriptName='boss_highlord_omokk' WHERE entry=9196;
UPDATE creature_template SET ScriptName='boss_shadow_hunter_voshgajin' WHERE entry=9236;
UPDATE creature_template SET ScriptName='boss_warmaster_voone' WHERE entry=9237;
UPDATE creature_template SET ScriptName='boss_mother_smolderweb' WHERE entry=10596;
UPDATE creature_template SET ScriptName='quartermaster_zigris' WHERE entry=9736;
UPDATE creature_template SET ScriptName='boss_halycon' WHERE entry=10220;
UPDATE creature_template SET ScriptName='boss_overlord_wyrmthalak' WHERE entry=9568;
/* BLACKROCK SPIRE Upper bosses */
UPDATE creature_template SET ScriptName='boss_the_beast' WHERE entry=10430;
UPDATE creature_template SET ScriptName='boss_drakkisath' WHERE entry=10363;
UPDATE creature_template SET ScriptName='boss_gyth' WHERE entry=10339;
UPDATE creature_template SET ScriptName='boss_rend_blackhand' WHERE entry=10429;
UPDATE creature_template SET ScriptName='boss_pyroguard_emberseer' WHERE entry=9816;
DELETE FROM scripted_event_id WHERE id=4884;
INSERT INTO scripted_event_id VALUES
(4884,'event_spell_altar_emberseer');

/* BLACKWING LAIR */
UPDATE instance_template SET ScriptName='instance_blackwing_lair' WHERE map=469;
UPDATE creature_template SET ScriptName='boss_razorgore' WHERE entry=12435;
UPDATE creature_template SET ScriptName='boss_vaelastrasz' WHERE entry=13020;
UPDATE creature_template SET ScriptName='boss_broodlord' WHERE entry=12017;
UPDATE creature_template SET ScriptName='boss_firemaw' WHERE entry=11983;
UPDATE creature_template SET ScriptName='boss_ebonroc' WHERE entry=14601;
UPDATE creature_template SET ScriptName='boss_flamegor' WHERE entry=11981;
UPDATE creature_template SET ScriptName='boss_chromaggus' WHERE entry=14020;
UPDATE creature_template SET ScriptName='boss_victor_nefarius' WHERE entry=10162;
UPDATE creature_template SET ScriptName='boss_nefarian' WHERE entry=11583;

/* BLASTED LANDS */
UPDATE creature_template SET ScriptName='npc_deathly_usher' WHERE entry=8816;
UPDATE creature_template SET ScriptName='npc_fallen_hero_of_horde' WHERE entry=7572;
UPDATE creature_template SET ScriptName='boss_lord_kazzak' WHERE entry=12397;

/* BURNING STEPPES */
UPDATE creature_template SET ScriptName='npc_ragged_john' WHERE entry=9563;

/* DARKSHORE */
UPDATE creature_template SET ScriptName='npc_rabid_bear' WHERE entry=2164;
UPDATE creature_template SET ScriptName='npc_kerlonian' WHERE entry=11218;
UPDATE creature_template SET ScriptName='npc_prospector_remtravel' WHERE entry=2917;
UPDATE creature_template SET ScriptName='npc_threshwackonator' WHERE entry=6669;

/* DARNASSUS */

/* DEADMINES */
UPDATE creature_template SET ScriptName='boss_mr_smite' WHERE entry=646;
UPDATE instance_template SET ScriptName='instance_deadmines' WHERE map=36;
UPDATE gameobject_template SET ScriptName='go_defias_cannon' WHERE entry=16398;

/* DEADWIND PASS */

/* DEEPRUN TRAM */
UPDATE creature_template SET ScriptName='npc_deeprun_rat' WHERE entry=13016;

/* DESOLACE */
UPDATE creature_template SET ScriptName='npc_aged_dying_ancient_kodo' WHERE entry IN (4700, 4701, 4702, 11627);
UPDATE creature_template SET ScriptName='npc_dalinda_malem' WHERE entry=5644;
UPDATE creature_template SET ScriptName='npc_melizza_brimbuzzle' WHERE entry=12277;

/* DIRE MAUL */
UPDATE instance_template SET ScriptName='instance_dire_maul' WHERE map=429;

/* DUN MOROGH */
UPDATE creature_template SET ScriptName='npc_narm_faulk' WHERE entry=6177;

/* DUROTAR */
UPDATE creature_template SET ScriptName='npc_lazy_peon' WHERE entry=10556;

/* DUSKWOOD */

/* DUSTWALLOW MARSH */
UPDATE creature_template SET ScriptName='npc_lady_jaina_proudmoore' WHERE entry=4968;
UPDATE creature_template SET ScriptName='npc_ogron' WHERE entry=4983;
UPDATE creature_template SET ScriptName='npc_morokk' WHERE entry=4500;
UPDATE creature_template SET ScriptName='npc_nat_pagle' WHERE entry=12919;
UPDATE creature_template SET ScriptName='npc_private_hendel' WHERE entry=4966;

/* EASTERN PLAGUELANDS */
UPDATE creature_template SET ScriptName='mobs_ghoul_flayer' WHERE entry IN (8530,8531,8532);
UPDATE creature_template SET ScriptName='npc_augustus_the_touched' WHERE entry=12384;
UPDATE creature_template SET ScriptName='npc_darrowshire_spirit' WHERE entry=11064;
UPDATE creature_template SET ScriptName='npc_tirion_fordring' WHERE entry=1855;
UPDATE creature_template SET ScriptName='npc_infected_peasant' WHERE entry IN (14484,14485);
UPDATE creature_template SET ScriptName='npc_eris_havenfire' WHERE entry=14494;

/* ELWYNN FOREST */
UPDATE creature_template SET ScriptName='npc_henze_faulk' WHERE entry=6172;

/* FELWOOD */
DELETE FROM scripted_event_id WHERE id=8328;
INSERT INTO scripted_event_id VALUES
(8328, 'npc_kroshius');
UPDATE creature_template SET ScriptName='npc_kitten' WHERE entry=9937;
UPDATE creature_template SET ScriptName='npc_corrupt_saber' WHERE entry=10042;
UPDATE creature_template SET ScriptName='npcs_riverbreeze_and_silversky' WHERE entry IN (9528,9529);
UPDATE creature_template SET ScriptName='npc_niby_the_almighty' WHERE entry=14469;
UPDATE creature_template SET ScriptName='npc_kroshius' WHERE entry=14467;

/* FERALAS */
UPDATE creature_template SET ScriptName='npc_gregan_brewspewer' WHERE entry=7775;
UPDATE creature_template SET ScriptName='npc_oox22fe' WHERE entry=7807;
UPDATE creature_template SET ScriptName='npc_screecher_spirit' WHERE entry=8612;

/* GNOMEREGAN */
UPDATE creature_template SET ScriptName='boss_thermaplugg' WHERE entry=7800;
UPDATE gameobject_template SET ScriptName='go_gnomeface_button' WHERE entry BETWEEN 142214 AND 142219;
UPDATE creature_template SET ScriptName='npc_blastmaster_emi_shortfuse' WHERE entry=7998;
UPDATE instance_template SET ScriptName='instance_gnomeregan' WHERE map=90;

/* HILLSBRAD FOOTHILLS */

/* HINTERLANDS */
UPDATE creature_template SET ScriptName='npc_00x09hl' WHERE entry=7806;
UPDATE creature_template SET ScriptName='npc_rinji' WHERE entry=7780;

/* IRONFORGE */
UPDATE creature_template SET ScriptName='npc_royal_historian_archesonus' WHERE entry=8879;

/* LOCH MODAN */
UPDATE creature_template SET ScriptName='npc_mountaineer_pebblebitty' WHERE entry=3836;
UPDATE creature_template SET ScriptName='npc_miran' WHERE entry=1379;

/* MARAUDON */
UPDATE creature_template SET ScriptName='boss_princess_theradras' WHERE entry=12201;
UPDATE creature_template SET ScriptName='boss_noxxion' WHERE entry=13282;
UPDATE creature_template SET ScriptName='boss_landslide' WHERE entry=12203;
UPDATE creature_template SET ScriptName='celebras_the_cursed' WHERE entry=12225;

/* MOLTEN CORE */
UPDATE instance_template SET ScriptName='instance_molten_core' WHERE map=409;
UPDATE creature_template SET ScriptName='boss_lucifron' WHERE entry=12118;
UPDATE creature_template SET ScriptName='boss_magmadar' WHERE entry=11982;
UPDATE creature_template SET ScriptName='boss_gehennas' WHERE entry=12259;
UPDATE creature_template SET ScriptName='boss_garr' WHERE entry=12057;
UPDATE creature_template SET ScriptName='boss_baron_geddon' WHERE entry=12056;
UPDATE creature_template SET ScriptName='boss_shazzrah' WHERE entry=12264;
UPDATE creature_template SET ScriptName='boss_golemagg' WHERE entry=11988;
UPDATE creature_template SET ScriptName='boss_sulfuron' WHERE entry=12098;
UPDATE creature_template SET ScriptName='boss_majordomo' WHERE entry=12018;
UPDATE creature_template SET ScriptName='boss_ragnaros' WHERE entry=11502;
UPDATE creature_template SET ScriptName='mob_firesworn' WHERE entry=12099;
UPDATE creature_template SET ScriptName='mob_core_rager' WHERE entry=11672;
UPDATE creature_template SET ScriptName='mob_flamewaker_priest' WHERE entry=11662;
UPDATE gameobject_template SET ScriptName='go_molten_core_rune' WHERE entry IN (176951, 176952, 176953, 176954, 176955, 176956, 176957);

/* MOONGLADE */
UPDATE creature_template SET ScriptName='npc_bunthen_plainswind' WHERE entry=11798;
UPDATE creature_template SET ScriptName='npc_great_bear_spirit' WHERE entry=11956;
UPDATE creature_template SET ScriptName='npc_silva_filnaveth' WHERE entry=11800;
UPDATE creature_template SET ScriptName='npc_keeper_remulos' WHERE entry=11832;
UPDATE creature_template SET ScriptName='boss_eranikus' WHERE entry=15491;

/* MULGORE */
UPDATE creature_template SET ScriptName='npc_skorn_whitecloud' WHERE entry=3052;
UPDATE creature_template SET ScriptName='npc_plains_vision' WHERE entry=2983;

/* NAXXRAMAS */
UPDATE instance_template SET ScriptName='instance_naxxramas' WHERE map=533;
UPDATE creature_template SET ScriptName='boss_anubrekhan' WHERE entry=15956;
UPDATE creature_template SET ScriptName='boss_faerlina' WHERE entry=15953;
UPDATE creature_template SET ScriptName='boss_maexxna' WHERE entry=15952;
UPDATE creature_template SET ScriptName='npc_web_wrap' WHERE entry=16486;
UPDATE creature_template SET ScriptName='boss_noth' WHERE entry=15954;
UPDATE creature_template SET ScriptName='boss_heigan' WHERE entry=15936;
UPDATE creature_template SET ScriptName='boss_loatheb' WHERE entry=16011;
UPDATE creature_template SET ScriptName='boss_razuvious' WHERE entry=16061;
UPDATE creature_template SET ScriptName='boss_gothik' WHERE entry=16060;
UPDATE creature_template SET ScriptName='spell_anchor' WHERE entry=16137;
UPDATE creature_template SET ScriptName='boss_thane_korthazz' WHERE entry=16064;
UPDATE creature_template SET ScriptName='boss_sir_zeliek' WHERE entry=16063;
UPDATE creature_template SET ScriptName='boss_lady_blaumeux' WHERE entry=16065;
UPDATE creature_template SET ScriptName='boss_mograine_naxx' WHERE entry=16062;
UPDATE creature_template SET ScriptName='boss_patchwerk' WHERE entry=16028;
UPDATE creature_template SET ScriptName='boss_grobbulus' WHERE entry=15931;
UPDATE creature_template SET ScriptName='boss_gluth' WHERE entry=15932;
UPDATE creature_template SET ScriptName='boss_thaddius' WHERE entry=15928;
UPDATE creature_template SET ScriptName='boss_stalagg' WHERE entry=15929;
UPDATE creature_template SET ScriptName='boss_feugen' WHERE entry=15930;
UPDATE creature_template SET ScriptName='npc_tesla_coil' WHERE entry=16218;
UPDATE creature_template SET ScriptName='boss_sapphiron' WHERE entry=15989;
UPDATE creature_template SET ScriptName='boss_kelthuzad' WHERE entry=15990;

/* ONYXIA'S LAIR */
UPDATE creature_template SET ScriptName='boss_onyxia' WHERE entry=10184;
UPDATE instance_template SET ScriptName='instance_onyxias_lair' WHERE map=249;

/* ORGRIMMAR */
UPDATE creature_template SET ScriptName='npc_neeru_fireblade' WHERE entry=3216;
UPDATE creature_template SET ScriptName='npc_shenthul' WHERE entry=3401;
UPDATE creature_template SET ScriptName='npc_thrall_warchief' WHERE entry=4949;
UPDATE creature_template SET ScriptName='npc_eitrigg' WHERE entry=3144;

/* RAGEFIRE CHASM */

/* RAZORFEN DOWNS */
UPDATE creature_template SET ScriptName='boss_amnennar_the_coldbringer' WHERE entry=7358;
UPDATE creature_template SET ScriptName='npc_henry_stern' WHERE entry=8696;
UPDATE creature_template SET ScriptName='npc_belnistrasz' WHERE entry=8516;

/* RAZORFEN KRAUL */
UPDATE instance_template SET ScriptName='instance_razorfen_kraul' WHERE map=47;
UPDATE creature_template SET ScriptName='npc_willix_the_importer' WHERE entry=4508;

/* REDRIDGE MOUNTAINS */
UPDATE creature_template SET ScriptName='npc_corporal_keeshan' WHERE entry=349;

/* RUINS OF AHN'QIRAJ */
UPDATE instance_template SET ScriptName='instance_ruins_of_ahnqiraj' WHERE map=509;
UPDATE creature_template SET ScriptName='mob_anubisath_guardian' WHERE entry=15355;
UPDATE creature_template SET ScriptName='boss_kurinnaxx' WHERE entry=15348;
UPDATE creature_template SET ScriptName='boss_ayamiss' WHERE entry=15369;
UPDATE creature_template SET ScriptName='boss_moam' WHERE entry=15340;

/* SCARLET MONASTERY */
UPDATE instance_template SET ScriptName='instance_scarlet_monastery' WHERE map=189;
UPDATE creature_template SET ScriptName='boss_arcanist_doan' WHERE entry=6487;
UPDATE creature_template SET ScriptName='boss_azshir_the_sleepless' WHERE entry=6490;
UPDATE creature_template SET ScriptName='boss_bloodmage_thalnos' WHERE entry=4543;
UPDATE creature_template SET ScriptName='boss_herod' WHERE entry=3975;
UPDATE creature_template SET ScriptName='boss_high_inquisitor_fairbanks' WHERE entry=4542;
UPDATE creature_template SET ScriptName='boss_high_inquisitor_whitemane' WHERE entry=3977;
UPDATE creature_template SET ScriptName='boss_houndmaster_loksey' WHERE entry=3974;
UPDATE creature_template SET ScriptName='boss_interrogator_vishas' WHERE entry=3983;
UPDATE creature_template SET ScriptName='boss_scarlet_commander_mograine' WHERE entry=3976;
UPDATE creature_template SET ScriptName='boss_scorn' WHERE entry=14693;
UPDATE creature_template SET ScriptName='mob_scarlet_trainee' WHERE entry=6575;

/* SCHOLOMANCE */
UPDATE instance_template SET ScriptName='instance_scholomance' WHERE map=289;
UPDATE creature_template SET ScriptName='boss_darkmaster_gandling' WHERE entry=1853;
UPDATE creature_template SET ScriptName='boss_death_knight_darkreaver' WHERE entry=14516;
UPDATE creature_template SET ScriptName='boss_vectus' WHERE entry=10432;
UPDATE creature_template SET ScriptName='boss_jandice_barov' WHERE entry=10503;
UPDATE creature_template SET ScriptName='boss_kormok' WHERE entry=16118;
UPDATE creature_template SET ScriptName='mob_illusionofjandicebarov' WHERE entry=11439;
DELETE FROM scripted_event_id WHERE id IN (5618,5619,5620,5621,5622,5623);
INSERT INTO scripted_event_id VALUES
(5618,'event_spell_gandling_shadow_portal'),
(5619,'event_spell_gandling_shadow_portal'),
(5620,'event_spell_gandling_shadow_portal'),
(5621,'event_spell_gandling_shadow_portal'),
(5622,'event_spell_gandling_shadow_portal'),
(5623,'event_spell_gandling_shadow_portal');

/* SEARING GORGE */
UPDATE creature_template SET ScriptName='npc_kalaran_windblade' WHERE entry=8479;
UPDATE creature_template SET ScriptName='npc_zamael_lunthistle' WHERE entry=8436;
UPDATE creature_template SET ScriptName='npc_lothos_riftwaker' WHERE entry=14387;

/* SHADOWFANG KEEP */
UPDATE instance_template SET ScriptName='instance_shadowfang_keep' WHERE map=33;
UPDATE creature_template SET ScriptName='npc_shadowfang_prisoner' WHERE entry IN (3849,3850);
UPDATE creature_template SET ScriptName='npc_arugal' WHERE entry=10000;
UPDATE creature_template SET ScriptName='npc_deathstalker_vincent' WHERE entry=4444;
UPDATE creature_template SET ScriptName='mob_arugal_voidwalker' WHERE entry=4627;
UPDATE creature_template SET ScriptName='boss_arugal' WHERE entry=4275;

/* SILITHUS */
UPDATE creature_template SET ScriptName='npc_highlord_demitrian' WHERE entry=14347;
UPDATE creature_template SET ScriptName='npcs_rutgar_and_frankal' WHERE entry IN (15170,15171);
UPDATE creature_template SET ScriptName='npc_anachronos_the_ancient' WHERE entry=15381;
UPDATE gameobject_template SET ScriptName='go_crystalline_tear' WHERE entry=180633;

/* SILVERPINE FOREST */
UPDATE creature_template SET ScriptName='npc_deathstalker_erland' WHERE entry=1978;
UPDATE creature_template SET ScriptName='npc_deathstalker_faerleia' WHERE entry=2058;

/* STONETALON MOUNTAINS */
UPDATE creature_template SET ScriptName='npc_braug_dimspirit' WHERE entry=4489;
UPDATE creature_template SET ScriptName='npc_kaya' WHERE entry=11856;

/* STORMWIND CITY */
UPDATE creature_template SET ScriptName='npc_bartleby' WHERE entry=6090;
UPDATE creature_template SET ScriptName='npc_dashel_stonefist' WHERE entry=4961;
UPDATE creature_template SET ScriptName='npc_lady_katrana_prestor' WHERE entry=1749;
UPDATE creature_template SET ScriptName='npc_squire_rowe' WHERE entry =17804;
UPDATE creature_template SET ScriptName='npc_reginald_windsor' WHERE entry =12580;
UPDATE creature_template SET ScriptName='npc_tyrion' WHERE entry=7766;
UPDATE creature_template SET ScriptName='npc_tyrion_spybot' WHERE entry=8856;
UPDATE creature_template SET ScriptName='npc_lord_gregor_lescovar' WHERE entry=1754;
UPDATE creature_template SET ScriptName='npc_marzon_silent_blade' WHERE entry=1755;

/* STRANGLETHORN VALE */
UPDATE creature_template SET ScriptName='mob_yenniku' WHERE entry=2530;

/* STRATHOLME */
UPDATE instance_template SET ScriptName='instance_stratholme' WHERE map=329;
UPDATE creature_template SET ScriptName='boss_dathrohan_balnazzar' WHERE entry=10812;
UPDATE creature_template SET ScriptName='boss_magistrate_barthilas' WHERE entry=10435;
UPDATE creature_template SET ScriptName='boss_maleki_the_pallid' WHERE entry=10438;
UPDATE creature_template SET ScriptName='boss_nerubenkan' WHERE entry=10437;
UPDATE creature_template SET ScriptName='boss_cannon_master_willey' WHERE entry=10997;
UPDATE creature_template SET ScriptName='boss_baroness_anastari' WHERE entry=10436;
UPDATE creature_template SET ScriptName='boss_ramstein_the_gorger' WHERE entry=10439;
UPDATE creature_template SET ScriptName='boss_timmy_the_cruel' WHERE entry=10808;
UPDATE creature_template SET ScriptName='boss_postmaster_malown' WHERE entry=11143;
UPDATE creature_template SET ScriptName='boss_baron_rivendare' WHERE entry=10440;
UPDATE creature_template SET ScriptName='mobs_spectral_ghostly_citizen' WHERE entry IN (10384,10385);
UPDATE creature_template SET ScriptName='mob_restless_soul' WHERE entry=11122;
UPDATE creature_template SET ScriptName='mob_freed_soul' WHERE entry=11136;
UPDATE gameobject_template SET ScriptName='go_gauntlet_gate' WHERE entry=175357;
UPDATE gameobject_template SET ScriptName='go_service_gate' WHERE entry=175368;

/* SUNKEN TEMPLE */
UPDATE instance_template SET ScriptName='instance_sunken_temple' WHERE map=109;
DELETE FROM scripted_areatrigger WHERE entry=4016;
INSERT INTO scripted_areatrigger VALUES (4016,'at_shade_of_eranikus');
UPDATE creature_template SET ScriptName='npc_malfurion_stormrage' WHERE entry=15362;
DELETE FROM scripted_event_id WHERE id IN (3094,3095,3097,3098,3099,3100);
INSERT INTO scripted_event_id VALUES
(3094,'event_antalarion_statue_activation'),
(3095,'event_antalarion_statue_activation'),
(3097,'event_antalarion_statue_activation'),
(3098,'event_antalarion_statue_activation'),
(3099,'event_antalarion_statue_activation'),
(3100,'event_antalarion_statue_activation');
UPDATE creature_template SET ScriptName='npc_shade_of_hakkar' WHERE entry=8440;
UPDATE gameobject_template SET ScriptName='go_eternal_flame' WHERE entry IN (148418,148419,148420,148421);
DELETE FROM scripted_event_id WHERE id=8502;
INSERT INTO scripted_event_id VALUES
(8502,'event_avatar_of_hakkar');

/* SWAMP OF SORROWS */
UPDATE creature_template SET ScriptName='npc_galen_goodward' WHERE entry=5391;

-- Added support for quest 1393. Patch by przemratajczak.

/* TANARIS */
UPDATE creature_template SET ScriptName='mob_aquementas' WHERE entry=9453;
UPDATE creature_template SET ScriptName='npc_marin_noggenfogger' WHERE entry=7564;
UPDATE creature_template SET ScriptName='npc_oox17tn' WHERE entry=7784;
UPDATE creature_template SET ScriptName='npc_stone_watcher_of_norgannon' WHERE entry=7918;
UPDATE creature_template SET ScriptName='npc_tooga' WHERE entry=5955;
UPDATE creature_template SET ScriptName='npc_mux_manascrambler' WHERE entry=16014;

/* TELDRASSIL */
UPDATE creature_template SET ScriptName='npc_mist' WHERE entry=3568;

/* TEMPLE OF AHN'QIRAJ */
UPDATE instance_template SET ScriptName='instance_temple_of_ahnqiraj' WHERE map=531;
UPDATE creature_template SET ScriptName='boss_cthun' WHERE entry=15727;
UPDATE creature_template SET ScriptName='boss_skeram' WHERE entry=15263;
UPDATE creature_template SET ScriptName='boss_vem' WHERE entry=15544;
UPDATE creature_template SET ScriptName='boss_yauj' WHERE entry=15543;
UPDATE creature_template SET ScriptName='boss_kri' WHERE entry=15511;
UPDATE creature_template SET ScriptName='boss_sartura' WHERE entry=15516;
UPDATE creature_template SET ScriptName='boss_fankriss' WHERE entry=15510;
-- UPDATE creature_template SET ScriptName='boss_viscidus' WHERE entry=15299;
-- UPDATE creature_template SET ScriptName='boss_glob_of_viscidus' WHERE entry=15667;
UPDATE creature_template SET ScriptName='boss_huhuran' WHERE entry=15509;
UPDATE creature_template SET ScriptName='boss_veklor' WHERE entry=15276;
UPDATE creature_template SET ScriptName='boss_veknilash' WHERE entry=15275;
UPDATE creature_template SET ScriptName='boss_ouro' WHERE entry=15517;
UPDATE creature_template SET ScriptName='boss_eye_of_cthun' WHERE entry=15589;
UPDATE creature_template SET ScriptName='mob_sartura_royal_guard' WHERE entry=15984;
UPDATE creature_template SET ScriptName='mob_claw_tentacle' WHERE entry=15725;
UPDATE creature_template SET ScriptName='mob_eye_tentacle' WHERE entry=15726;
UPDATE creature_template SET ScriptName='mob_giant_claw_tentacle' WHERE entry=15728;
UPDATE creature_template SET ScriptName='mob_giant_eye_tentacle' WHERE entry=15334;
UPDATE creature_template SET ScriptName='mob_giant_flesh_tentacle' WHERE entry=15802;
UPDATE creature_template SET ScriptName='mob_anubisath_sentinel' WHERE entry=15264;

/* THOUSAND NEEDLES */
UPDATE creature_template SET ScriptName='npc_kanati' WHERE entry=10638;
UPDATE creature_template SET ScriptName='npc_plucky_johnson' WHERE entry=6626;
UPDATE creature_template SET ScriptName='npc_paoka_swiftmountain' WHERE entry=10427;
UPDATE creature_template SET ScriptName='npc_lakota_windsong' WHERE entry=10646;

/* THUNDER BLUFF */
UPDATE creature_template SET ScriptName='npc_cairne_bloodhoof' WHERE entry=3057;

/* TIRISFAL GLADES */
UPDATE gameobject_template SET ScriptName='go_mausoleum_trigger' WHERE entry=104593;
UPDATE gameobject_template SET ScriptName='go_mausoleum_door' WHERE entry=176594;
UPDATE creature_template SET ScriptName='npc_calvin_montague' WHERE entry=6784;

/* ULDAMAN */
DELETE FROM scripted_event_id WHERE id IN (2228,2268);
INSERT INTO scripted_event_id VALUES
(2228,'event_spell_altar_boss_aggro'),
(2268,'event_spell_altar_boss_aggro');
UPDATE creature_template SET ScriptName='boss_archaedas' WHERE entry=2748;
UPDATE creature_template SET ScriptName='mob_archaeras_add' WHERE entry IN (7309,7076,7077,10120);
UPDATE creature_template SET ScriptName='npc_lore_keeper_of_norgannon' WHERE entry=7172;
UPDATE instance_template SET ScriptName='instance_uldaman' WHERE map=70;

/* UN'GORO CRATER */
UPDATE creature_template SET ScriptName='npc_ame01' WHERE entry=9623;
UPDATE creature_template SET ScriptName='npc_ringo' WHERE entry=9999;

/* UNDERCITY */
UPDATE creature_template SET ScriptName='npc_parqual_fintallas' WHERE entry=4488;

/* WAILING CAVERNS */
UPDATE instance_template SET ScriptName='instance_wailing_caverns' WHERE map=43;
UPDATE creature_template SET ScriptName='npc_disciple_of_naralex' WHERE entry=3678;

/* WESTERN PLAGUELANDS  */
UPDATE creature_template SET ScriptName='npcs_dithers_and_arbington' WHERE entry IN (11056,11057);
UPDATE creature_template SET ScriptName='npc_myranda_the_hag' WHERE entry=11872;
UPDATE creature_template SET ScriptName='npc_the_scourge_cauldron' WHERE entry=11152;

/* WESTFALL */
UPDATE creature_template SET ScriptName='npc_daphne_stilwell' WHERE entry=6182;
UPDATE creature_template SET ScriptName='npc_defias_traitor' WHERE entry=467;

/* WETLANDS */
UPDATE creature_template SET ScriptName='npc_tapoke_slim_jahn' WHERE entry=4962;
UPDATE creature_template SET ScriptName='npc_mikhail' WHERE entry=4963;

/* WINTERSPRING */
UPDATE creature_template SET ScriptName='npc_lorax' WHERE entry=10918;
UPDATE creature_template SET ScriptName='npc_rivern_frostwind' WHERE entry=10618;
UPDATE creature_template SET ScriptName='npc_witch_doctor_mauari' WHERE entry=10307;

/* ZUL'FARRAK */
UPDATE instance_template SET ScriptName='instance_zulfarrak' WHERE map=209;
DELETE FROM scripted_event_id WHERE id=2488;
INSERT INTO scripted_event_id VALUES (2488,'event_go_zulfarrak_gong');
DELETE FROM scripted_areatrigger WHERE entry=1447;
INSERT INTO scripted_areatrigger VALUES (1447,'at_zulfarrak');
UPDATE creature_template SET ScriptName='npc_sergeant_bly' WHERE entry=7604;
UPDATE creature_template SET ScriptName='npc_weegli_blastfuse' WHERE entry=7607;

/* ZUL'GURUB */
UPDATE instance_template SET ScriptName='instance_zulgurub' WHERE map=309;
UPDATE creature_template SET ScriptName='boss_jeklik' WHERE entry=14517;
UPDATE creature_template SET ScriptName='boss_venoxis' WHERE entry=14507;
UPDATE creature_template SET ScriptName='boss_marli' WHERE entry=14510;
UPDATE creature_template SET ScriptName='boss_mandokir' WHERE entry=11382;
UPDATE creature_template SET ScriptName='mob_ohgan' WHERE entry=14988;
UPDATE creature_template SET ScriptName='boss_gahzranka' WHERE entry=15114;
UPDATE creature_template SET ScriptName='boss_jindo' WHERE entry=11380;
UPDATE creature_template SET ScriptName='boss_hakkar' WHERE entry=14834;
UPDATE creature_template SET ScriptName='boss_thekal' WHERE entry=14509;
UPDATE creature_template SET ScriptName='boss_arlokk' WHERE entry=14515;
UPDATE gameobject_template SET ScriptName='go_gong_of_bethekk' WHERE entry=180526;
UPDATE creature_template SET ScriptName='boss_grilek' WHERE entry=15082;
UPDATE creature_template SET ScriptName='boss_hazzarah' WHERE entry=15083;
UPDATE creature_template SET ScriptName='boss_renataki' WHERE entry=15084;
UPDATE creature_template SET ScriptName='boss_wushoolay' WHERE entry=15085;
UPDATE creature_template SET ScriptName='mob_zealot_lorkhan' WHERE entry=11347;
UPDATE creature_template SET ScriptName='mob_zealot_zath' WHERE entry=11348;
UPDATE creature_template SET ScriptName='mob_healing_ward' WHERE entry=14987;
UPDATE creature_template SET ScriptName='mob_spawn_of_marli' WHERE entry=15041;
UPDATE creature_template SET ScriptName='mob_batrider' WHERE entry=14965;
UPDATE creature_template SET ScriptName='mob_shade_of_jindo' WHERE entry=14986;

/* EOF */
