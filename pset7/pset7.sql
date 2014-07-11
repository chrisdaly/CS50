-- MySQL dump 10.14  Distrib 5.5.32-MariaDB, for Linux (i686)
--
-- Host: localhost    Database: pset7
-- ------------------------------------------------------
-- Server version	5.5.32-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `history`
--

DROP TABLE IF EXISTS `history`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `history` (
  `id` int(10) unsigned NOT NULL,
  `type` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `symbol` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `shares` int(11) NOT NULL,
  `price` double NOT NULL,
  `date` datetime NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `history`
--

LOCK TABLES `history` WRITE;
/*!40000 ALTER TABLE `history` DISABLE KEYS */;
INSERT INTO `history` VALUES (19,'sold','FB',0,0,'0000-00-00 00:00:00'),(19,'bought','FB',1,66.29,'2014-07-03 17:41:06'),(19,'bought','F',1,17.32,'2014-07-03 17:41:12'),(19,'bought','A',1,58.46,'2014-07-03 17:41:18'),(19,'sold','A',1,58.46,'2014-07-03 17:41:28'),(19,'sold','F',1,17.32,'2014-07-03 18:01:13'),(19,'sold','FB',1,66.29,'2014-07-03 18:01:44'),(19,'bought','FB',1,66.29,'2014-07-03 18:01:49'),(19,'sold','FB',1,66.29,'2014-07-03 18:03:30'),(19,'bought','FB',1000,66.29,'2014-07-03 18:03:38'),(19,'sold','FB',1000,66.29,'2014-07-03 18:09:20'),(19,'bought','FB',1,66.29,'2014-07-03 18:09:26'),(19,'bought','F',1000,17.32,'2014-07-03 18:09:44');
/*!40000 ALTER TABLE `history` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `stocks`
--

DROP TABLE IF EXISTS `stocks`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `stocks` (
  `id` int(10) unsigned NOT NULL,
  `symbol` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  `shares` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`,`symbol`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `stocks`
--

LOCK TABLES `stocks` WRITE;
/*!40000 ALTER TABLE `stocks` DISABLE KEYS */;
INSERT INTO `stocks` VALUES (6,'DVN.V','200'),(19,'F','1000'),(19,'FB','1');
/*!40000 ALTER TABLE `stocks` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `users`
--

DROP TABLE IF EXISTS `users`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `users` (
  `id` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `username` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `hash` varchar(255) COLLATE utf8_unicode_ci NOT NULL,
  `cash` decimal(65,4) unsigned NOT NULL DEFAULT '0.0000',
  `email` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE KEY `username` (`username`)
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `users`
--

LOCK TABLES `users` WRITE;
/*!40000 ALTER TABLE `users` DISABLE KEYS */;
INSERT INTO `users` VALUES (1,'caesar','$1$50$GHABNWBNE/o4VL7QjmQ6x0',10000.0000,''),(2,'hirschhorn','$1$50$lJS9HiGK6sphej8c4bnbX.',10000.0000,''),(3,'jharvard','$1$50$RX3wnAMNrGIbgzbRYrxM1/',10000.0000,''),(4,'malan','$1$HA$azTGIMVlmPi9W9Y12cYSj/',10000.0000,''),(5,'milo','$1$HA$6DHumQaK4GhpX8QE23C8V1',10000.0000,''),(6,'skroob','$1$50$euBi4ugiJmbpIbvTTfmfI.',10000.0000,''),(7,'zamyla','$1$50$uwfqB45ANW.9.6qaQ.DcF.',10000.0000,''),(8,'Chris','$1$5QmlUcXO$7wPJBPRUmM8V9AhMQ/z8W/',10000.0000,''),(10,'Maki','$1$XBnidtP8$.GtgEWDtFaWMLSzZBaRaE.',1846.3300,''),(12,'Sam','$1$FxAgn3I9$/POnom7vE9Ug7XaZ5kKDo/',10000.0000,''),(13,'Helen','$1$5EdThcJg$UFqzyfIgXQrNtYo.PCMkA/',10000.0000,''),(14,'Eoin','$1$HI9BLkg.$nqk9ekbBG9E6agTp0vIgr1',10000.0000,''),(16,'Eoin1','$1$pRTZvnH.$6VrQR5iOFZNg7dNHCV5Kl1',10000.0000,''),(17,'Jesse','$1$UME47BXK$ZzDsHwvECpcv9NUI2PG.h.',10000.0000,''),(19,'1','$1$Pk2ij9U2$GK4.Mt9xzj8URFA94WklF0',401651.3100,''),(20,'123','$1$xcJgKCV4$UGaho.UrOw3KGeQZmZPI9.',10000.0000,''),(21,'123123','$1$INSFnlVW$OBWRkpbqsQCGjVFfEdSsB/',10000.0000,'123@123.com'),(22,'asdasd','$1$TgALrHuh$YprulcIHslP8bXc3L5FkG0',10000.0000,'asd@asd.com'),(33,'C','$1$v9fbjWSv$AuvI8f59vlN7sjtDsqVLs0',10000.0000,'chrisdaly1988@gmail.com');
/*!40000 ALTER TABLE `users` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2014-07-04 14:25:30
