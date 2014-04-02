/* 在mysql中执行 source 本文件名 */
DROP DATABASE IF EXISTS venus;
CREATE DATABASE venus;
USE venus;

DROP TABLE IF EXISTS user;
CREATE TABLE user (
	ID INT AUTO_INCREMENT NOT NULL,
	Pwd varchar(32) NOT NULL,
	NickName varchar(24) NOT NULL,
	PRIMARY KEY (ID)
) AUTO_INCREMENT=10000 DEFAULT CHARSET=utf8;

INSERT INTO user VALUES(NULL, md5('root'), 'root');
INSERT INTO user VALUES(NULL, md5('puppy'), 'puppy');
