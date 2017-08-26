/*
Navicat MySQL Data Transfer

Source Server         : mysql
Source Server Version : 50549
Source Host           : localhost:3306
Source Database       : network

Target Server Type    : MYSQL
Target Server Version : 50549
File Encoding         : 65001

Date: 2017-08-21 09:21:33
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for snmpinterfaceinfo
-- ----------------------------
DROP TABLE IF EXISTS `snmpinterfaceinfo`;
CREATE TABLE `snmpinterfaceinfo` (
  `id` int(32) unsigned NOT NULL AUTO_INCREMENT,
  `deviceid` int(32) DEFAULT NULL,
  `devicename` varchar(64) DEFAULT NULL,
  `manageip` varchar(32) DEFAULT NULL,
  `portid` varchar(16) DEFAULT NULL,
  `ifindex` int(32) DEFAULT NULL,
  `ifdescr` varchar(100) DEFAULT NULL,
  `ifadminstatus` int(2) DEFAULT NULL,
  `ifoperstatus` int(2) DEFAULT NULL,
  `ifspeed` bigint(64) DEFAULT NULL,
  `ifinoctets` bigint(64) DEFAULT NULL,
  `ifinucastpkts` bigint(64) DEFAULT NULL,
  `ifinnucastPkts` bigint(64) DEFAULT NULL,
  `ifindiscards` bigint(64) DEFAULT NULL,
  `ifinerrors` bigint(64) DEFAULT NULL,
  `ifinunknownprotos` bigint(64) DEFAULT NULL,
  `ifoutoctets` bigint(64) DEFAULT NULL,
  `ifoutucastpkts` bigint(64) DEFAULT NULL,
  `ifoutnucastPkts` bigint(64) DEFAULT NULL,
  `ifoutdiscards` bigint(64) DEFAULT NULL,
  `ifouterrors` bigint(64) DEFAULT NULL,
  `timestamp` datetime DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
