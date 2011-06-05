DELETE FROM script_texts WHERE entry BETWEEN -1000709 AND -1000696;
INSERT INTO script_texts (entry,content_default,sound,type,LANGUAGE,emote,comment) VALUES
(-1000696,'The Scourge are upon us! Run! Run for your lives!',0,1,0,0,'peasant YELL_PEASANT_SPAWN_1'),
(-1000697,'Please help us! The Prince has gone mad!',0,1,0,0,'peasant YELL_PEASANT_SPAWN_2'),
(-1000698,'Seek sanctuary in Hearthglen! It is our only hope!',0,1,0,0,'peasant YELL_PEASANT_SPAWN_3'),
(-1000699,'Should I live through this, I shall make it my life\'s sole ambition to destroy Arthas...',0,0,0,0,'peasant SAY_PEASANT_RANDOM_1'),
(-1000700,'I won\'t make it... go... go on without me...',0,0,0,0,'peasant SAY_PEASANT_RANDOM_2'),
(-1000701,'Death take me! I cannot go on! I have nothing left...',0,0,0,0,'peasant SAY_PEASANT_RANDOM_3'),
(-1000702,'The power of the light is truly great and merciful.',0,0,0,0,'peasant SAY_PEASANT_SAVE_1'),
(-1000703,'We shall be reunited once more, my love...',0,0,0,0,'peasant SAY_PEASANT_SAVE_2'),
(-1000704,'At last, it ends...',0,0,0,0,'peasant SAY_PEASANT_SAVE_3'),
(-1000705,'Stranger, find the fallen Prince Menethil and end his reign of terror. ',0,0,0,0,'peasant SAY_PEASANT_SAVE_4'),
(-1000706,'I have failed once more...',0,1,0,0,'eris YELL_ERIS_FAIL'),
(-1000707,'I now return to whence I came, only to find myself here once more to relive the same epic tragedy.',0,0,0,0,'eris SAY_ERIS_FAIL'),
(-1000708,'We are saved! The peasants have escaped the Scourge!',0,1,0,0,'eris YELL_ERIS_FINISH'),
(-1000709,'Be healed!',0,1,0,0,'eris YELL_ERIS_WAVE');
