DROP TABLE IF EXISTS `logs`;
CREATE TABLE `logs` (
  `date` TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP ,
  `severity` INT(1) NOT NULL DEFAULT 5 ,
  `message` TEXT NULL DEFAULT NULL ,
  INDEX `logs_date` (`date` ASC)
) ENGINE=InnoDB DEFAULT CHARACTER SET=utf8;

DROP TABLE IF EXISTS `sessions`;
CREATE TABLE `sessions` (
  `startTime`     timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `endTime`       timestamp,
  `activities`    varchar(1024),
  PRIMARY KEY     (`startTime`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;
