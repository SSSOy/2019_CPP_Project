#include <iostream>
#include <string>
#include <my_global.h>
#include <mysql.h>
#pragma comment(lib, "libmysql.lib")

using namespace std;

int main() {
	MYSQL mysql;
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql, "localhost", "root", "mirim2", "turtlegame", 3306, NULL, 0))
		cout << "error";
	else
		cout << "success";
	mysql_close(&mysql);

	return 0;
}