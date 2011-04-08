--Lord Kazzak Script Load.
UPDATE creature_template SET ScriptName='boss_lord_kazzak' WHERE entry=12397;

/* SUNKEN TEMPLE */
UPDATE instance_template SET script='instance_sunken_temple' WHERE map=109;
DELETE FROM areatrigger_scripts WHERE entry=4016;
INSERT INTO areatrigger_scripts VALUES (4016,'at_shade_of_eranikus');
UPDATE creature_template SET ScriptName='npc_malfurion_stormrage' WHERE entry=15362;

UPDATE instance_template SET script='instance_sunken_temple' WHERE map=109;
