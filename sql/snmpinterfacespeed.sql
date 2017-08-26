/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50549
Source Host           : localhost:3306
Source Database       : network

Target Server Type    : MYSQL
Target Server Version : 50549
File Encoding         : 65001

Date: 2017-08-22 16:13:32
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for snmpinterfacespeed
-- ----------------------------
DROP TABLE IF EXISTS `snmpinterfacespeed`;
CREATE TABLE `snmpinterfacespeed` (
  `id` int(32) unsigned NOT NULL,
  `lastifinoctets` bigint(64) DEFAULT NULL,
  `lastifinucastpkts` bigint(64) DEFAULT NULL,
  `lastifinnucastPkts` bigint(64) DEFAULT NULL,
  `lastifindiscards` bigint(64) DEFAULT NULL,
  `lastifinerrors` bigint(64) DEFAULT NULL,
  `lastifinunknownprotos` bigint(64) DEFAULT NULL,
  `lastifoutoctets` bigint(64) DEFAULT NULL,
  `lastifoutucastpkts` bigint(64) DEFAULT NULL,
  `lastifoutnucastPkts` bigint(64) DEFAULT NULL,
  `lastifoutdiscards` bigint(64) DEFAULT NULL,
  `lastifouterrors` bigint(64) DEFAULT NULL,
  `lasttimestamp` datetime DEFAULT NULL,
  `ifinoctetsps` bigint(64) DEFAULT NULL,
  `ifinucastpps` bigint(64) DEFAULT NULL,
  `ifinnucastpps` bigint(64) DEFAULT NULL,
  `ifindiscardpps` bigint(64) DEFAULT NULL,
  `ifinerrorpps` bigint(64) DEFAULT NULL,
  `ifinunknownprotospps` bigint(64) DEFAULT NULL,
  `ifoutoctetsps` bigint(64) DEFAULT NULL,
  `ifoutucastpps` bigint(64) DEFAULT NULL,
  `ifoutnucastpps` bigint(64) DEFAULT NULL,
  `ifoutdiscardpps` bigint(64) DEFAULT NULL,
  `ifouterrorpps` bigint(64) DEFAULT NULL,
  PRIMARY KEY (`id`),
  CONSTRAINT `snmpinterfacespeed_ibfk_1` FOREIGN KEY (`id`) REFERENCES `snmpinterfaceinfo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DELIMITER $$
DROP PROCEDURE IF EXISTS speed_update;
CREATE PROCEDURE speed_update()
BEGIN
    DECLARE oid INT unsigned DEFAULT 0;
    DECLARE newifinoctets, newifinucastpkts, newifinnucastpkts, newifindiscardpkts, newifinerrorpkts, newifinunknownprotospkts, newifoutoctets, newifoutucastpkts, newifoutnucastpkts, newifoutdiscardpkts, newifouterrorpkts BIGINT DEFAULT 0;
    DECLARE oldifinoctets, oldifinucastpkts, oldifinnucastpkts, oldifindiscardpkts, oldifinerrorpkts, oldifinunknownprotospkts, oldifoutoctets, oldifoutucastpkts, oldifoutnucastpkts, oldifoutdiscardpkts, oldifouterrorpkts BIGINT DEFAULT 0;
	DECLARE time_stamp datetime DEFAULT NULL;
	
    DECLARE done TINYINT DEFAULT 0;
    DECLARE cur1 CURSOR FOR
        SELECT id, ifinoctets, ifinucastpkts, ifinnucastPkts, ifindiscards, ifinerrors, ifinunknownprotos, ifoutoctets, ifoutucastpkts, ifoutnucastPkts, ifoutdiscards, ifouterrors, timestamp FROM snmpinterfaceinfo;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;

    OPEN cur1;
	read_loop: LOOP
	    FETCH cur1 INTO oid, newifinoctets, newifinucastpkts, newifinnucastpkts, newifindiscardpkts, newifinerrorpkts, newifinunknownprotospkts, newifoutoctets, newifoutucastpkts, newifoutnucastpkts, newifoutdiscardpkts, newifouterrorpkts, time_stamp;
		IF done THEN 
		    LEAVE read_loop;
		END IF;
		
        SELECT lastifinoctets, lastifinucastpkts, lastifinnucastPkts, lastifindiscards, lastifinerrors, lastifinunknownprotos, lastifoutoctets, lastifoutucastpkts, lastifoutnucastPkts, lastifoutdiscards, lastifouterrors
            INTO oldifinoctets, oldifinucastpkts, oldifinnucastpkts, oldifindiscardpkts, oldifinerrorpkts, oldifinunknownprotospkts, oldifoutoctets, oldifoutucastpkts, oldifoutnucastpkts, oldifoutdiscardpkts, oldifouterrorpkts 
			FROM snmpinterfacespeed WHERE id = oid;
			
	    REPLACE snmpinterfacespeed 
		    SET id = oid,
			    ifinoctetsps = newifinoctets - oldifinoctets,
			    ifinucastpps = newifinucastpkts - oldifinucastpkts,
				ifinnucastpps = newifinnucastpkts - oldifinnucastpkts,
				ifindiscardpps = newifindiscardpkts - oldifindiscardpkts,
				ifinerrorpps = newifinerrorpkts - oldifinerrorpkts,
				ifinunknownprotospps = newifinunknownprotospkts - oldifinunknownprotospkts,
				ifoutoctetsps = newifoutoctets - oldifoutoctets,
				ifoutucastpps = newifoutucastpkts - oldifoutucastpkts,
				ifoutnucastpps = newifoutnucastpkts - oldifoutnucastpkts,
				ifoutdiscardpps = newifoutdiscardpkts - oldifoutdiscardpkts,
				ifouterrorpps = newifouterrorpkts - oldifouterrorpkts,
				lastifinoctets = newifinoctets,
			    lastifinucastpkts = newifinucastpkts,
				lastifinnucastPkts = newifinnucastpkts,
				lastifindiscards = newifindiscardpkts,
				lastifinerrors = newifinerrorpkts,
				lastifinunknownprotos = newifinunknownprotospkts,
				lastifoutoctets = newifoutoctets,
				lastifoutucastpkts = newifoutucastpkts,
				lastifoutnucastPkts = newifoutnucastpkts,
				lastifoutdiscards = newifoutdiscardpkts,
				lastifouterrors = newifouterrorpkts,
				lasttimestamp = time_stamp;
			
	END LOOP;
	CLOSE cur1;
	
END$$
DELIMITER ;

SET GLOBAL event_scheduler = ON;

# Create this event just for test, need to comment out.
DELIMITER $$
DROP EVENT IF EXISTS add_count_test;
CREATE EVENT add_count_test ON SCHEDULE EVERY 1 SECOND
DO
	BEGIN
		UPDATE snmpinterfaceinfo 
			SET ifinoctets = ifinoctets + 10,
				ifinucastpkts = ifinucastpkts + 10
			WHERE id = 1;
		UPDATE snmpinterfaceinfo 
			SET ifinoctets = ifinoctets + 20,
				ifinucastpkts = ifinucastpkts + 20
			WHERE id = 2;
		UPDATE snmpinterfaceinfo 
			SET ifinoctets = ifinoctets + 30,
				ifinucastpkts = ifinucastpkts + 30
			WHERE id = 3;
	END $$
DELIMITER ;

			
DROP EVENT IF EXISTS update_speed;
CREATE EVENT update_speed ON SCHEDULE EVERY 5 SECOND
DO
    CALL speed_update;