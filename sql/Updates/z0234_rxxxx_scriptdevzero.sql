DELETE FROM script_texts WHERE entry BETWEEN -1109011 AND -1109005;
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1109005,'The shield be down! Rise up Atal\'ai! Rise up!',5861,1,0,0,'jammalan SAY_JAMMALAN_INTRO'),
(-1109006,'HAKKAR LIVES!',5870,1,0,0,'avatar SAY_AVATAR_BRAZIER_1'),
(-1109007,'I TASTE THE BLOOD OF LIFE!',5868,1,0,0,'avatar SAY_AVATAR_BRAZIER_2'),
(-1109008,'I DRAW CLOSER TO YOUR WORLD!',5867,1,0,0,'avatar SAY_AVATAR_BRAZIER_3'),
(-1109009,'I AM NEAR!',5869,1,0,0,'avatar SAY_AVATAR_BRAZIER_4'),
(-1109010,'DIE, MORTALS!',5871,1,0,0,'avatar SAY_AVATAR_AGGRO'),
(-1109011,'No! You must no do this!',0,1,0,0,'suppressor SAY_SUPPRESSOR_WARN');
