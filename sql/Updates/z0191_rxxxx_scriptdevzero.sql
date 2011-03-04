DELETE FROM script_texts WHERE entry BETWEEN -1189022 AND -1189000;
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1189000,'Ah, I have been waiting for a real challenge!',5830,1,0,0,'herod SAY_AGGRO'),
(-1189001,'Blades of Light!',5832,1,0,0,'herod SAY_WHIRLWIND'),
(-1189002,'Light, give me strength!',5833,1,0,0,'herod SAY_ENRAGE'),
(-1189003,'Hah, is that all?',5831,1,0,0,'herod SAY_KILL'),
(-1189004,'REUSE_ME',0,0,0,0,'REUSE_ME'),

(-1189005,'Infidels! They must be purified!',5835,1,0,0,'mograine SAY_MO_AGGRO'),
(-1189006,'Unworthy!',5836,1,0,0,'mograine SAY_MO_KILL'),
(-1189007,'At your side, milady!',5837,1,0,0,'mograine SAY_MO_RESSURECTED'),

(-1189008,'What, Mograine has fallen? You shall pay for this treachery!',5838,1,0,0,'whitemane SAY_WH_INTRO'),
(-1189009,'The Light has spoken!',5839,1,0,0,'whitemane SAY_WH_KILL'),
(-1189010,'Arise, my champion!',5840,1,0,0,'whitemane SAY_WH_RESSURECT'),

(-1189011,'Tell me... tell me everything!',5847,1,0,0,'vishas SAY_AGGRO'),
(-1189012,'Naughty secrets!',5849,1,0,0,'vishas SAY_HEALTH1'),
(-1189013,'I\'ll rip the secrets from your flesh!',5850,1,0,0,'vishas SAY_HEALTH2'),
(-1189014,'Purged by pain!',5848,1,0,0,'vishas SAY_KILL'),
(-1189015,'The monster got what he deserved.',0,0,1,0,'vishas SAY_TRIGGER_VORREL'),

(-1189016,'We hunger for vengeance.',5844,1,0,0,'thalnos SAY_AGGRO'),
(-1189017,'No rest, for the angry dead.',5846,1,0,0,'thalnos SAY_HEALTH'),
(-1189018,'More... More souls.',5845,1,0,0,'thalnos SAY_KILL'),

(-1189019,'You will not defile these mysteries!',5842,1,0,0,'doan SAY_AGGRO'),
(-1189020,'Burn in righteous fire!',5843,1,0,0,'doan SAY_SPECIALAE'),

(-1189021,'Release the hounds!',5841,1,0,0,'loksey SAY_AGGRO'),

(-1189022,'The master has fallen! Avenge him my brethren!',5834,1,0,0,'trainee SAY_TRAINEE_SPAWN');
