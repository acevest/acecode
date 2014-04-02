DROP DATABASE IF EXISTS webpy;
DROP USER 'webpy'@'localhost';

CREATE DATABASE webpy;
CREATE USER 'webpy'@'localhost' IDENTIFIED BY 'webpy';

GRANT ALL ON webpy.* TO 'webpy'@'localhost';

use webpy;

CREATE TABLE user (
	ID INT AUTO_INCREMENT NOT NULL,
	Pwd varchar(32) NOT NULL,
	NickName varchar(32) NOT NULL,
	PRIMARY KEY (ID)
) AUTO_INCREMENT=0 DEFAULT CHARSET=utf8;


INSERT INTO user VALUES(NULL, md5('root'), 'root');
INSERT INTO user VALUES(NULL, md5('user'), 'user');
INSERT INTO user VALUES(NULL, md5('webpy'), 'webpy');
INSERT INTO user VALUES(NULL, md5('admin'), 'admin');
