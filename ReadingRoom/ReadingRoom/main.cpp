#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <mysql.h>
#include <time.h>
#pragma comment(lib, "libmysql.lib")
using namespace std;

int location = 17;
MYSQL *connection, mysql;

class user {
private :
	const char* name;
	const char* id;
	const char* pw;
	int num;
	int studingTime;
public :
	void setName(const char* name) {	this->name = name;	}
	const char* getName() { return this->name; }
	void setId(const char* id) { this->id = id; }
	const char* getId() { return this->id; }
	void setPw(const char* pw) { this->pw = pw; }
	const char* getPw() { return this->pw; }
	void setNum(int num) { this->num = num; }
	int getNum() { return this->num; }
	void setStudingTime(int studingTime) { this->studingTime = studingTime; }
	int getStudingTime() { return this->studingTime; }
};

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void paintIntro(int n) {
	system("cls");
	gotoxy(2, 2);			cout << "위, 아래 방향키와 엔터 키로 메뉴를 선택해주세요!";
	gotoxy(12, 7);		cout << "         ■  ■■■■ ■    ■■■■           ■    ■   ■";
	gotoxy(12, 8);		cout << "■■■■ ■        ■ ■    ■            ■   ■  ■  ■ ■";
	gotoxy(12, 9);		cout << "■    ■ ■  ■■■■ ■    ■■■■     ■■■■     ■■■";
	gotoxy(12, 10);		cout << "■■■■ ■  ■       ■       ■       ■  ■ ■         ■";
	gotoxy(12, 11);		cout << "         ■  ■■■■ ■  ■■■■■■         ■     ■■■";
	gotoxy(12, 12);		cout << "         ■     ■■■■    ■■■■           ■     ■";
	gotoxy(12, 13);		cout << "         ■     ■■■■          ■           ■     ■■■";

	gotoxy(36, n);		cout << "▶";

	gotoxy(40, 17);		cout << "로그인";
	gotoxy(39, 18);		cout << "회원가입";
	gotoxy(39, 19);		cout << "이용안내" << endl;
}


void Menu() {
	while (1) {
	paintIntro(17);
	int c = 0;
		while (c != 13) { //enter key
			c = _getch();
			if (c == 224) // 방향키
				c = _getch();

			if (c == 72) { //위 방향키
				if (location > 17) 
					paintIntro(--location);
			}
			else if (c == 80) { //아래 방향키
				if (location < 19) 
					paintIntro(++location);
			}
		}

		switch (location) {
		case 17:
			break;
		case 18:
			user u1;
			char s1[100], s2[100], s3[100], s4[100];
			char query[100];
			int query_stat;

			system("cls");
			cout << "이름 입력 : ";
			cin >> s1;
			u1.setName(s1);
			cout << "ID입력 : ";
			cin >> s2;
			u1.setId(s2);
			while (1) {
				cout << "password 입력 : ";
				cin >> s3;
				cout << "password 확인 : ";
				cin >> s4;
				if (strcmp(s3, s4) == 0) {
					u1.setPw(s3);
					break;
				}
				else
					cout << "비밀번호가 일치하지 않습니다.\n";
			}

			sprintf_s(query, "INSERT INTO readingroom (name, id, pw) VALUES ('%s', '%s', '%s'); ", u1.getName(), u1.getId(), u1.getPw());
			query_stat = mysql_query(connection, query);

			if (query_stat != 0) {
				fprintf(stderr, "Mysql query error : %s", mysql_error(&mysql));
				Sleep(1000);
			}
			else {
				cout << "등록이 완료되었습니다.";
				Sleep(1000);
			}
			break;
		case 19:
			break;
		}
	}
}


int main() {

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "utf8");
	mysql_options(&mysql, MYSQL_INIT_COMMAND, "SET NAMES utf8");
	connection = mysql_real_connect(&mysql, "localhost", "root", "mirim2", "readingroom", 3306, NULL, 0);
	if (connection == NULL)
		return 0;

	//한글사용을위해추가.
	mysql_query(connection, "set session character_set_connection=euckr;");
	mysql_query(connection, "set session character_set_results=euckr;");
	mysql_query(connection, "set session character_set_client=euckr;");

	/*
	// 셀렉트
	int query_stat = mysql_query(connection, "select * from readingroom;");
	if (query_stat != 0) 
		fprintf(stderr, "Mysql query error : %s", mysql_error(&mysql));

	// 결과출력
	MYSQL_RES *sql_result;
	MYSQL_ROW sql_row;
	sql_result = mysql_store_result(connection);
	while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
		printf("%2s %2s %s\n", sql_row[0], sql_row[1], sql_row[2]);
	}
	mysql_free_result(sql_result);
	*/

	Menu();

	mysql_close(&mysql);
	return 0;
}