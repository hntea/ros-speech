DROP DATABASE IF EXISTS Music;
CREATE DATABASE IF NOT EXISTS MusicDB;
USE MusicDB;
CREATE TABLE IF NOT EXISTS `music` (
  `musicID` int(10) NOT NULL AUTO_INCREMENT COMMENT '歌曲编号',
  `musicName` varchar(50) DEFAULT NULL COMMENT '歌曲名字',
  `musicPath` varchar(100) DEFAULT NULL COMMENT '歌曲路径',
  `musician` varchar(50) DEFAULT NULL COMMENT '歌手',
  PRIMARY KEY (`musicID`),
  KEY `musicMusicianID` (`musician`)
)CHARSET=utf8;

INSERT INTO `music` (`musicID`, `musicName`, `musicPath`, `musician`) VALUES
(1, '爱情第一课', 'ad880483cb0c3df04ed10a0f8ce53fe3.mp3', '弦子'),
(2, '配角', 'f14665fcf4325b550f2a135630cd4616.mp3', 'Sara'),
(3, '中国人', 'f14665fcf4325b550f2a135630cd4616.mp3', '刘德华');
