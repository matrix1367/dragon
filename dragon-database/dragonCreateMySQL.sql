
DROP DATABASE IF EXISTS dragon;

CREATE DATABASE dragon;

USE dragon

/**
* 
*/
CREATE TABLE IF NOT EXISTS tb_city (
	cityid	INT PRIMARY KEY NOT NULL,
	name	varchar(80)	NOT NULL
);

/**
* key
*/
CREATE TABLE IF NOT EXISTS tb_location (
	locationid	INT	PRIMARY	KEY	NOT NULL,
	street	varchar(255),
	nrHome	varchar(10),
	nrLocal	varchar(10),
	zipCode	varchar(6),
	cityid	INT	references tb_city(cityid)
);
