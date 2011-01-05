-- THIS FILE CONTAINS ALL EXTRA SCRIPTS CREATED FOR SCRIPTDEVZERO ONLY 
-- SOME OF THEM CAN BE VERY CUSTOM, OR NOT TESTED YET , USE THEM AT YOUR WISH

-- ### BLACKROCK SPIRE ###
INSERT INTO `script_texts` VALUES
('-1615000','Ha! Ha! Ha! Thank you for freeing me, fools. Now let me repay you by charring the flesh from your bones.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','Pyroguard_Emberseer SAY_AGGRO');

DELETE FROM `script_texts` WHERE `entry` IN ('-1615001','-1615002');
INSERT INTO `script_texts` VALUES
('-1615001','Enemy is destroing our laying! Stop it!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','Rookery_Hatcher SAY_BEGIN'),
('-1615002','And here I am! Now, arrogant worms, you\'ll pay for their invasion!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','Solakar_Flamewreath SAY_AGGRO');

DELETE FROM `script_texts` WHERE `entry` IN ('-1615003','-1615004','-1615005','-1615006','-1615007','-1615008','-1615009','-1615010','-1615011','-1615012','-1615013','-1615014','-1615015','-1615016','-1615017');
INSERT INTO `script_texts` VALUES
('-1615003','Sire, let me join the fray! I shall tear their spines out with my bare hands!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','REND_SAY_1'),
('-1615004','Defilers!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','REND_SAY_2'),
('-1615005','Impossible!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','REND_SAY_3'),
('-1615006','With pleasure...',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','REND_SAY_4'),
('-1615007','Excellent... it would appear as if the meddlesome insects have arrived just in time to feed my legion. Welcome, mortals!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_1'),
('-1615008','Let not even a drop of their blood remain upon the arena floor, my children. Feast on their souls!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_2'),
('-1615009','Foolsss... Kill the one in the dress!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_3'),
('-1615010','Concentrate your attacks upon the healer!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_4'),
('-1615011','Inconceivable!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_5'),
('-1615012','Do not force my hand, children! I shall use your hides to line my boots.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_6'),
('-1615013','Your efforts will prove fruitless. None shall stand in our way!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_7'),
('-1615014','THIS CANNOT BE!!! Rend, deal with these insects.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_8'),
('-1615015','The Warchief shall make quick work of you, mortals. Prepare yourselves!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_9'),
('-1615016','Taste in my power!',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_10'),
('-1615017','Your victory shall be short lived. The days of both the Alliance and Horde are coming to an end. The next time we meet shall be the last.',NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,'0','1','0','0','NEFARIUS_SAY_11');
