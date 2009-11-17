--Lord Kazzak Script Load.
UPDATE creature_template SET ScriptName='boss_lord_kazzak' WHERE entry=12397;

-- script Text
REPLACE INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES

(-1000147,'I remember well the sting of defeat at the conclusion of the Third War. I have waited far too long for my revenge. Now the shadow of the Legion falls over this world. It is only a matter of time until all of your failed creation... is undone.',11332,1,0,0,'kazzak SAY_INTRO'),
(-1000148,'The Legion will conquer all!',11333,1,0,0,'kazzak SAY_AGGRO1'),
(-1000149,'All mortals will perish!',11334,1,0,0,'kazzak SAY_AGGRO2'),
(-1000150,'All life must be eradicated!',11335,1,0,0,'kazzak SAY_SURPREME1'),
(-1000151,'I\'ll rip the flesh from your bones!',11336,1,0,0,'kazzak SAY_SURPREME2'),
(-1000152,'Kirel Narak!',11337,1,0,0,'kazzak SAY_KILL1'),
(-1000153,'Contemptible wretch!',11338,1,0,0,'kazzak SAY_KILL2'),
(-1000154,'The universe will be remade.',11339,1,0,0,'kazzak SAY_KILL3'),
(-1000155,'The Legion... will never... fall.',11340,1,0,0,'kazzak SAY_DEATH'),
(-1000156,'REUSE ME',0,0,0,0,'REUSE ME'),
(-1000157,'Invaders, you dangle upon the precipice of oblivion! The Burning Legion comes and with it comes your end.',0,1,0,0,'kazzak SAY_RAND1'),
(-1000158,'Impudent whelps, you only delay the inevitable. Where one has fallen, ten shall rise. Such is the will of Kazzak...',0,1,0,0,'kazzak SAY_RAND2');

