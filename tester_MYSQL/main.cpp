
#include <iostream>

#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")


int main()
{
	MYSQL* pConnect = NULL;
	MYSQL myCon;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;
	int query_stat;

	mysql_init(&myCon);
	pConnect = mysql_real_connect(&myCon, "localhost", "root", "1111", "tutorials", 3306, (char*)NULL, 0);
	if (NULL == pConnect)
	{
		std::cout << "MySQL connection error: " << mysql_error(&myCon);
		return 1;
	}


	// 쿼리 보내기 - mysql_query(..., "mySQL 명령어");
	query_stat = mysql_query(pConnect, "SELECT * FROM tutorials_users");
	if (NULL != query_stat)
	{
		std::cout << "MySQL query error: " << mysql_error(&myCon);
		return 1;
	}

	// 쿼리 가져오기 - mysql_store_result(...);
	sql_result = mysql_store_result(pConnect);

	std::cout << "userID\tuserName\tcurrentStage\tdescription" << std::endl;
	while (NULL != (sql_row = mysql_fetch_row(sql_result)))
	{
		std::cout << sql_row[0] << "\t";
		std::cout << sql_row[1] << "\t\t";
		std::cout << sql_row[4] << "\t";

		if (NULL != sql_row[5])
			std::cout << sql_row[5];

		std::cout << std::endl;
	}

	query_stat = mysql_query(pConnect, "UPDATE tutorials_users SET description = 'hacker' WHERE user_id = 6");
	if (NULL != query_stat)
	{
		std::cout << "MySQL query error: " << mysql_error(&myCon);
		return 1;
	}

	mysql_close(pConnect);
	return 0;
}