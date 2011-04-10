DELETE FROM gossip_texts WHERE entry BETWEEN -3000109 AND -3000106;
INSERT INTO gossip_texts (entry,content_default,comment) VALUES
(-3000106,'I am ready to hear your tale, Tirion.','tirion GOSSIP_ITEM_1'),
(-3000107,'Thank you, Tirion. What of your identity?','tirion GOSSIP_ITEM_2'),
(-3000108,'That is terrible.','tirion GOSSIP_ITEM_3'),
(-3000109,'I will, Tirion.','tirion GOSSIP_ITEM_4');
