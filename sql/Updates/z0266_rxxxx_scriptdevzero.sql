DELETE FROM script_texts WHERE entry=-1469031;

DELETE FROM gossip_texts WHERE entry IN (-3469000, -3469001, -3469002);
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3469000,'I\'ve made no mistakes.','victor_nefarius GOSSIP_ITEM_NEFARIUS_1'),
(-3469001,'You have lost your mind, Nefarius. You speak in riddles.','victor_nefarius GOSSIP_ITEM_NEFARIUS_2'),
(-3469002,'Please do.','victor_nefarius GOSSIP_ITEM_NEFARIUS_3');

UPDATE script_texts SET comment='victor_nefarius SAY_NEFARIUS_CORRUPT' WHERE entry=-1469006;
