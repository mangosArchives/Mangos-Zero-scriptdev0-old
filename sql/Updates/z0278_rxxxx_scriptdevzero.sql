DELETE FROM gossip_texts WHERE entry BETWEEN -3001023 AND -3001019;
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3001019,'Please teach me how to become a hammersmith, Lilith.','lilith GOSSIP_TEACH_HAMMER'),
(-3001020,'Please teach me how to become an axesmith, Kilram.','kilram GOSSIP_TEACH_AXE'),
(-3001021,'Please teach me how to become a swordsmith, Seril.','eitrigg GOSSIP_TEACH_SWORD'),
(-3001022,'This Dimensional Imploder sounds dangerous! How can I make one?','zap GOSSIP_TEACH'),
(-3001023,'I must build a beacon for this marvelous device!','jhordy GOSSIP_TEACH');