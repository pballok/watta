DROP TABLE IF EXISTS `sessions`;
DROP TABLE IF EXISTS `workdays`;
DROP TABLE IF EXISTS `logs`;

CREATE TABLE `logs` (
  `date`           TIMESTAMP           NOT NULL DEFAULT CURRENT_TIMESTAMP,
  `severity`       INT(1)              NOT NULL DEFAULT 5,
  `message`        TEXT                         DEFAULT NULL,
  INDEX `in_logs_date` (`date` ASC)
) ENGINE=InnoDB;

CREATE TABLE `workdays` (
  `date`           DATE                NOT NULL,
  `activities`     VARCHAR(1024)                DEFAULT NULL,
  PRIMARY KEY `pk_workdays_date` (`date`)
) ENGINE=InnoDB;

CREATE TABLE `sessions` (
  `date`           DATE                NOT NULL,
  `startTime`      TIME                         DEFAULT NULL,
  `endTime`        TIME                         DEFAULT NULL,
  INDEX `in_sessions_date` (`date` ASC),
  FOREIGN KEY `fk_sessions_workdays` (`date`) REFERENCES `workdays`(`date`) ON DELETE RESTRICT ON UPDATE CASCADE
) ENGINE=InnoDB;
