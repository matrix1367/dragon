
DROP DATABASE IF EXISTS dragon;

CREATE DATABASE dragon 
	DEFAULT CHARACTER SET utf8
	DEFAULT COLLATE utf8_general_ci;

USE dragon

/**
* 
*/
CREATE TABLE IF NOT EXISTS tb_city (
	cityid	INT PRIMARY KEY NOT NULL,
	name	varchar(80)	NOT NULL
)
DEFAULT CHARACTER SET = utf8
COLLATE = utf8_bin;

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


CREATE TABLE IF NOT EXISTS tb_shop (
	shopid	INT	PRIMARY	KEY	NOT	NULL,
	name varchar(255) NOT NULL,
	nip varchar(10)	NOT NULL,
	locationid	INT	REFERENCES	tb_location(locationid)
);







/*
* insert simple data
*/

INSERT INTO tb_city (cityid, name) VALUES (1, 'Poznań');
INSERT INTO tb_location (locationid, street, nrHome, nrLocal, zipCode, cityid) VALUES (1, 'Katowicka', '53', 'A', '61-131', 1);






