DROP TABLE IF EXISTS `sd2_db_version`;
DROP TABLE IF EXISTS `sd0_db_version`;
CREATE TABLE `sd0_db_version` (
  `version` varchar(255) NOT NULL default '' COMMENT 'Database version string'
) ENGINE=MyISAM DEFAULT CHARSET=utf8;

INSERT INTO sd0_db_version VALUES (' ScriptDevZero (for MangosZero rev. 0115+) ');
