-- cleaning waypoints for not existing creatures
DELETE FROM script_waypoint WHERE entry IN (15420,16295,16812,16993,17077,17312,17876,17969,18210,18731,18887,19685,20129,21027,22377,22458,22916,23002,24358,28070,28912);

-- kazzak   kazzak not have any speak sounds
UPDATE script_texts SET sound =  0  WHERE sound = 11332;
UPDATE script_texts SET sound =  0  WHERE sound = 11333;
UPDATE script_texts SET sound =  0  WHERE sound = 11334;
UPDATE script_texts SET sound =  0  WHERE sound = 11335;
UPDATE script_texts SET sound =  0  WHERE sound = 11336;
UPDATE script_texts SET sound =  0  WHERE sound = 11337;
UPDATE script_texts SET sound =  0  WHERE sound = 11338;
UPDATE script_texts SET sound =  0  WHERE sound = 11339;
UPDATE script_texts SET sound =  0  WHERE sound = 11340;

-- headless_horseman & doomwalker ( not in pre-bc)
DELETE FROM script_texts WHERE sound IN (11344,11345,11346,11347,11348,11349,11350,11351,11352,11961,11962,11963,11964,11969,12567,12569,12573 );

-- kel'thuzad
UPDATE script_texts SET sound = 8820  WHERE sound = 14463  ;
UPDATE script_texts SET sound = 8821  WHERE sound = 14464  ;
UPDATE script_texts SET sound = 8823  WHERE sound = 14465  ;
UPDATE script_texts SET sound = 8824  WHERE sound = 14466  ;
UPDATE script_texts SET sound = 8878  WHERE sound = 14467  ;
UPDATE script_texts SET sound = 8879  WHERE sound = 14468  ;
UPDATE script_texts SET sound = 8880  WHERE sound = 14469  ;
UPDATE script_texts SET sound = 8812  WHERE sound = 14472  ;
UPDATE script_texts SET sound = 8813  WHERE sound = 14473  ;
UPDATE script_texts SET sound = 8815  WHERE sound = 14474  ;
UPDATE script_texts SET sound = 8816  WHERE sound = 14470  ;
UPDATE script_texts SET sound = 8819  WHERE sound = 14471  ;
UPDATE script_texts SET sound = 8809  WHERE sound = 14475  ;
UPDATE script_texts SET sound = 8810  WHERE sound = 14476  ;
UPDATE script_texts SET sound = 8811  WHERE sound = 14477  ;
UPDATE script_texts SET sound = 8817  WHERE sound = 14478  ;
UPDATE script_texts SET sound = 8818  WHERE sound = 14479  ;
UPDATE script_texts SET sound = 8814  WHERE sound = 14480  ;
UPDATE script_texts SET sound = 9088  WHERE sound = 14481  ;
UPDATE script_texts SET sound = 9090  WHERE sound = 14483  ;
UPDATE script_texts SET sound = 9089  WHERE sound = 14482  ;
-- SPEC_CAT_DIE not exists in pre-bc[?]
UPDATE script_texts SET sound = 0 WHERE sound = 14484;
-- lich king answere missing sound
UPDATE script_texts SET sound = 8824 WHERE entry = -1533104;

-- rivendare
UPDATE script_texts SET sound = 8835 ,  comment = 'highlordmograine_naxx SAY_RIVE_AGGRO1' WHERE sound = 14571  ;
UPDATE script_texts SET sound = 8836 ,  comment = 'highlordmograine_naxx SAY_RIVE_AGGRO2' WHERE sound = 14572  ;
UPDATE script_texts SET sound = 8837 ,  comment = 'highlordmograine_naxx SAY_RIVE_AGGRO3' WHERE sound = 14573  ;
UPDATE script_texts SET sound = 8839 ,  comment = 'highlordmograine_naxx SAY_RIVE_SLAY1' WHERE sound = 14574  ;
UPDATE script_texts SET sound = 8840 ,  comment = 'highlordmograine_naxx SAY_RIVE_SLAY2' WHERE sound = 14575  ;
UPDATE script_texts SET sound = 8841 ,  comment = 'highlordmograine_naxx SAY_RIVE_SPECIAL' , content_default = ' Bow to the might of the HighLord!' WHERE sound = 14576  ;
UPDATE script_texts SET sound = 8842 ,  comment = 'highlordmograine_naxx SAY_RIVE_TAUNT1' WHERE sound = 14577  ;
UPDATE script_texts SET sound = 8843 ,  comment = 'highlordmograine_naxx SAY_RIVE_TAUNT2' WHERE sound = 14578  ;
UPDATE script_texts SET sound = 8844 ,  comment = 'highlordmograine_naxx SAY_RIVE_TAUNT3' WHERE sound = 14579  ;
UPDATE script_texts SET sound = 8838 ,  comment = 'highlordmograine_naxx SAY_RIVE_DEATH' , content_default = 'I... am... released! Perhaps it\'s not too late to - noo! I need... more time...'  WHERE sound = 14580 ;
