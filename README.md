


## 테이블은 두 개의 테이블이 존재합니다. ##

```SQL
CREATE TABLE tutorials_users
(
	user_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	user_name VARCHAR(32) NOT NULL,
	created DATETIME NOT NULL,
	channel_id INT UNSIGNED NOT NULL,
	current_stage VARCHAR(100),
	description TEXT NULL,
	PRIMARY KEY (user_id),
	
	CHECK(current_stage IN('All_Claer', 'Stage_One', 'Stage_Two', 'Stage_Three'))
);
```

```SQL	
CREATE TABLE tutorials_channels
(
	channel_id INT UNSIGNED NOT NULL AUTO_INCREMENT,
	user_count INT UNSIGNED DEFAULT 0,
	PRIMARY KEY (channel_id)
);
```



## 유저 테이블의 데이터 삽입은 채널 테이블에 영향을 줍니다. ##

(자동 증가 + 기본 값을 갖는 테이블에 데이터 삽입)

```SQL
INSERT INTO tutorials_channels VALUES();
INSERT INTO tutorials_channels VALUES();
INSERT INTO tutorials_channels VALUES();
```

```SQL
DELIMITER $$
CREATE TRIGGER trigger_after_update_users
AFTER INSERT ON tutorials_users
FOR EACH ROW
BEGIN
UPDATE tutorials_channels SET user_count = user_count + 1
WHERE tutorials_channels.channel_id = NEW.channel_id;
END $$ 
DELIMITER ;
```

(유저 정보를 갖는 테이블에 데이터 삽입)
```SQL
INSERT INTO tutorials_users
(user_name, created, channel_id, current_stage) VALUES('Lee', '2024-06-05 20:09:18', 1, 'All_Clear');

INSERT INTO tutorials_users
(user_name, created, channel_id, current_stage) VALUES('Kim', '2024-07-28 08:32:55', 1, 'Stage_One');

INSERT INTO tutorials_users
(user_name, created, channel_id, current_stage) VALUES('Park', '2024-08-08 17:17:17', 2, 'Stage_Two');

INSERT INTO tutorials_users
(user_name, created, channel_id, current_stage) VALUES('Dovahkiin', NOw(), 3, 'Stage_Three');
```



----------


```SQL
+---------+-----------+---------------------+------------+---------------+-------------+
| user_id | user_name | created             | channel_id | current_stage | description |
+---------+-----------+---------------------+------------+---------------+-------------+
|       1 | Lee       | 2024-06-05 20:09:18 |          1 | All_Clear     | NULL        |
|       2 | Kim       | 2024-07-28 08:32:55 |          1 | Stage_One     | NULL        |
|       3 | Park      | 2024-08-08 17:17:17 |          2 | Stage_Two     | NULL        |
|       4 | Dovahkiin | 2024-09-09 21:41:51 |          3 | Stage_Three   | NULL        |
+---------+-----------+---------------------+------------+---------------+-------------+

+------------+------------+
| channel_id | user_count |
+------------+------------+
|          1 |          2 |
|          2 |          1 |
|          3 |          1 |
+------------+------------+

SELECT user_id, user_name, created, current_stage, user_count
FROM tutorials_users LEFT JOIN tutorials_channels ON tutorials_users.channel_id = tutorials_channels.channel_id;

+---------+-----------+---------------------+---------------+------------+
| user_id | user_name | created             | current_stage | user_count |
+---------+-----------+---------------------+---------------+------------+
|       1 | Lee       | 2024-06-05 20:09:18 | All_Clear     |          2 |
|       2 | Kim       | 2024-07-28 08:32:55 | Stage_One     |          2 |
|       3 | Park      | 2024-08-08 17:17:17 | Stage_Two     |          1 |
|       4 | Dovahkiin | 2024-09-09 21:41:51 | Stage_Three   |          1 |
+---------+-----------+---------------------+---------------+------------+
```

----------


예제 C++ 코드에선 쿼리를 보내고 가져오는 실습을 위해
1) tutorials_users 테이블을 가져온 후 출력
2) user_id가 4인 데이터에 대해 description을 수정 
하는 코드가 작동합니다.


