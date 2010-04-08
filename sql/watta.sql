DROP TABLE IF EXISTS `logs`;
CREATE TABLE `logs` (
  `date`          TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `severity`      INT(1) NOT NULL DEFAULT 5,
  `message`       TEXT NULL DEFAULT NULL,
  INDEX `logs_date` (`date` ASC)
) ENGINE=InnoDB DEFAULT CHARACTER SET=utf8;

DROP TABLE IF EXISTS `workdays`;
CREATE TABLE `workdays` (
  `date`          DATE NOT NULL,
  `activities`    varchar(1024),
  PRIMARY KEY (`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

DROP TABLE IF EXISTS `sessions`;
CREATE TABLE `sessions` (
  `date`           DATE NOT NULL,
  `startTime`     TIME NOT NULL,
  `endTime`       TIME NOT NULL,
  INDEX sessions_date (`date`),
  FOREIGN KEY (`date`) REFERENCES `workdays`(`date`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
