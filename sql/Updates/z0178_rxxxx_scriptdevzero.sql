DELETE FROM script_texts WHERE entry BETWEEN -1409022 AND -1409000;
INSERT INTO script_texts (entry,content_default,sound,type,language,emote,comment) VALUES
(-1409000,'%s performs one last service for Ragnaros.',0,2,0,0,'geddon EMOTE_SERVICE'),
(-1409001,'REUSE ME',0,0,0,0,'REUSE ME'),
(-1409002,'%s refuses to die while its master is in trouble.',0,2,0,0,'core rager EMOTE_LOWHP'),

(-1409003,'Reckless mortals, none may challenge the sons of the living flame!',8035,1,0,0,'majordomo SAY_AGGRO'),
(-1409004,'The runes of warding have been destroyed! Hunt down the infedels my bretheren.',8039,6,0,0,'majordomo SAY_SPAWN'),
(-1409005,'Ashes to Ashes!',8037,1,0,0,'majordomo SAY_SLAY'),
(-1409006,'Burn mortals! Burn for this transgression!',8036,1,0,0,'majordomo SAY_SPECIAL'),
(-1409007,'Impossible! Stay your attack mortals! I submitt! I submitt!',8038,1,0,0,'majordomo SAY_DEFEAT_1'),

(-1409008,'Behold Ragnaros, the Firelord! He who was ancient when this world was young! Bow before him, mortals! Bow before your ending!',8040,1,0,0,'ragnaros SAY_SUMMON_MAJ'),
(-1409009,'TOO SOON! YOU HAVE AWAKENED ME TOO SOON, EXECUTUS! WHAT IS THE MEANING OF THIS INTRUSION?',8043,1,0,0,'ragnaros SAY_ARRIVAL1_RAG'),
(-1409010,'These mortal infidels, my lord! They have invaded your sanctum, and seek to steal your secrets!',8041,1,0,0,'ragnaros SAY_ARRIVAL2_MAJ'),
(-1409011,'FOOL! YOU ALLOWED THESE INSECTS TO RUN RAMPANT THROUGH THE HALLOWED CORE, AND NOW YOU LEAD THEM TO MY VERY LAIR? YOU HAVE FAILED ME, EXECUTUS! JUSTICE SHALL BE MET, INDEED!',8044,1,0,0,'ragnaros SAY_ARRIVAL3_RAG'),
(-1409012,'NOW FOR YOU, INSECTS. BOLDLY YOU SAUGHT THE POWER OF RAGNAROS NOW YOU SHALL SEE IT FIRST HAND.',8045,1,0,0,'ragnaros SAY_ARRIVAL5_RAG'),

(-1409013,'COME FORTH, MY SERVANTS! DEFEND YOUR MASTER!',8049,1,0,0,'ragnaros SAY_REINFORCEMENTS1'),
(-1409014,'YOU CANNOT DEFEAT THE LIVING FLAME! COME YOU MINIONS OF FIRE! COME FORTH YOU CREATURES OF HATE! YOUR MASTER CALLS!',8050,1,0,0,'ragnaros SAY_REINFORCEMENTS2'),
(-1409015,'BY FIRE BE PURGED!',8046,1,0,0,'ragnaros SAY_HAND'),
(-1409016,'TASTE THE FLAMES OF SULFURON!',8047,1,0,0,'ragnaros SAY_WRATH'),
(-1409017,'DIE INSECT!',8051,1,0,0,'ragnaros SAY_KILL'),
(-1409018,'MY PATIENCE IS DWINDILING! COME NATS TO YOUR DEATH!',8048,1,0,0,'ragnaros SAY_MAGMABURST'),

(-1409019,'You think you\'ve won already? Perhaps you\'ll need another lesson in pain!',0,1,0,0,'majordomo SAY_LAST_ADD'),
(-1409020,'Brashly you have come to rest the secrets of the living flame. You will soon regret the recklessness of your quest.',0,1,0,0,'majordomo SAY_DEFEAT_2'),
(-1409021,'I go now to summon the lord whos house this is. Should you seek an audiance with him your paltry lives will surly be forfit. Nevertheless seek out his lair if you dare!',0,1,0,0,'majordomo SAY_DEFEAT_3'),
(-1409022,'My flame! Please don\'t take away my flame... ',8042,1,0,0,'ragnaros SAY_ARRIVAL4_MAJ');
