DELETE FROM script_texts WHERE entry BETWEEN -1000693 AND -1000679;
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1000679,'By your command!',0,0,0,0,'SAY_QUEST_ACCEPT_ATTACK'),
(-1000680,'Wait here. Spybot will make Lescovar come out as soon as possible. Be ready! Attack only after you''ve overheard their conversation.',0,0,0,0,'SAY_TYRION_1'),
(-1000681,'Good day to you both. I would speak to Lord Lescovar.',0,0,0,0,'SAY_SPYBOT_1'),
(-1000682,'Of course. He awaits you in the library.',0,0,0,0,'SAY_GUARD_1'),
(-1000683,'Thank you. The Light be with you both.',0,0,0,0,'SAY_SPYBOT_2'),
(-1000684,'Milord, your guest has arrived. He awaits your presence.',0,0,0,0,'SAY_SPYBOT_3'),
(-1000685,'Ah, thank you kindly. I will leave you to the library while I tend to this small matter.',0,0,0,0,'SAY_LESCOVAR_1'),
(-1000686,'I shall use the time wisely, milord. Thank you.',0,0,0,0,'SAY_SPYBOT_4'),
(-1000687,'It''s time for my meditation, leave me.',0,0,0,0,'SAY_LESCOVAR_2'),
(-1000688,'Yes, sir!',0,0,0,0,'SAY_GUARD_2'),
(-1000689,'There you are. What news from Westfall?',0,0,0,0,'SAY_LESCOVAR_3'),
(-1000690,'VanCleef sends word that the plans are underway. But he''s hear rumors about someone snooping about.',0,0,0,0,'SAY_MARZON_1'),
(-1000691,'Hmm, it could be that meddle Shaw. I will see what I can discover. Be off with you. I''ll contact you again soon.',0,0,0,0,'SAY_LESCOVAR_4'),
(-1000692,'That\'s it! That\'s what you were waiting for! KILL THEM!',0,1,0,0,'SAY_TYRION_2'),
(-1000693,'The Defias shall succeed! No meek adventurer will stop us!',0,0,0,0,'SAY_MARZON_2');

DELETE FROM script_waypoint WHERE entry = 1754;
INSERT INTO script_waypoint VALUES
(1754, 1, -8334.89, 394.130, 122.274, 0, ''),
(1754, 2, -8335.58, 393.519, 122.275, 0, ''),
(1754, 3, -8352.99, 379.932, 122.275, 0, ''),
(1754, 4, -8356.65, 385.247, 122.275, 0, ''),
(1754, 5, -8364.29, 395.317, 122.275, 0, ''),
(1754, 6, -8361.75, 402.852, 122.275, 0, ''),
(1754, 7, -8359.94, 410.92, 122.275, 0, ''),
(1754, 8, -8362.84, 415.409, 122.275, 0, ''),
(1754, 9, -8370.42, 424.6, 122.275, 0, ''),
(1754, 10, -8380.45, 437.115, 122.275, 0, ''),
(1754, 11, -8386.37, 444.906, 122.275, 0, ''),
(1754, 12, -8388.5, 447.314, 123.275, 0, ''),
(1754, 13, -8390.25, 449.247, 124.275, 0, ''),
(1754, 14, -8392.84, 452.397, 123.761, 0, ''),
(1754, 15, -8397.52, 457.326, 123.761, 0, ''),
(1754, 16, -8402.42, 461.646, 123.761, 0, ''),
(1754, 17, -8409.52, 462.677, 123.761, 0, '');

DELETE FROM script_waypoint WHERE entry = 8856;
INSERT INTO script_waypoint VALUES
(8856, 1, -8409.34, 453.345, 123.761, 0, ''),
(8856, 2, -8409.52, 462.677, 123.761, 0, ''),
(8856, 3, -8402.42, 461.646, 123.761, 0, ''),
(8856, 4, -8397.52, 457.326, 123.761, 0, ''),
(8856, 5, -8392.84, 452.397, 123.761, 0, ''),
(8856, 6, -8390.25, 449.247, 124.275, 0, ''),
(8856, 7, -8388.5, 447.314, 123.275, 0, ''),
(8856, 8, -8386.37, 444.906, 122.275, 0, ''),
(8856, 9, -8380.45, 437.115, 122.275, 0, ''),
(8856, 10, -8370.42, 424.6, 122.275, 0, ''),
(8856, 11, -8362.84, 415.409, 122.275, 0, ''),
(8856, 12, -8359.94, 410.92, 122.275, 0, ''),
(8856, 13, -8361.75, 402.852, 122.275, 0, ''),
(8856, 14, -8364.29, 395.317, 122.275, 0, ''),
(8856, 15, -8356.65, 385.247, 122.275, 0, ''),
(8856, 16, -8352.99, 379.932, 122.275, 0, ''),
(8856, 17, -8335.58, 393.519, 122.275, 0, ''),
(8856, 18, -8334.89, 394.13, 122.274, 0, '');
