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
	int fare;
public :
	void setName(const char* name) {	this->name = name;	}
	const char* getName() { return this->name; }
	void setId(const char* id) { this->id = id; }
	const char* getId() { return this->id; }
	void setPw(const char* pw) { this->pw = pw; }
	const char* getPw() { return this->pw; }
	void setNum(int num) { this->num = num; }
	int getNum() { return this->num; }
	void setFare(int fare) { this->fare = fare; }
	int getFare() { return this->fare; }
};

void gotoxy(int x, int y) {
	COORD Pos = { x - 1, y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void paintIntro(int n) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}


void Menu() {
	while (1) {
	paintIntro(location);
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

		char s1[100], s2[100];
		char query[100];
		int query_stat;
		int check = 0;

		switch (location) {
		case 17:
			
			system("cls");
			cout << "<< 로그인 >>" << endl << endl;
			cout << "ID 입력 : ";
			cin >> s1;;
			cout << "PW 입력 : ";
			cin >> s2;

			sprintf_s(query, "select pw from readingroom where id = '%s';", s1);
			query_stat = mysql_query(connection, query);
			if (query_stat != 0) {
				cout << "존재하지 않는 회원입니다." << endl;
				Sleep(1000);
				break;
			}

			MYSQL_RES *sql_result;
			MYSQL_ROW sql_row;
			sql_result = mysql_store_result(connection);
			while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
				if (strcmp(sql_row[0], s2) == 0) {
					cout << "로그인 성공" << endl;
					Sleep(1000);
				}
			}
			mysql_free_result(sql_result);

			break;
		case 18:
			user u1;
			char s3[100], s4[100];
			char sql_T[100];

			system("cls");
			cout << "<< 회원가입>>" << endl << endl;
			cout << "이름 입력 : ";
			cin >> s1;
			u1.setName(s1);

			while (1) {
				
				cout << "ID입력 : ";
				cin >> s2;
				query_stat = mysql_query(connection, "select id from readingroom;");

				MYSQL_RES *sql_result;
				MYSQL_ROW sql_row;
				sql_result = mysql_store_result(connection);
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL) {
					if (strcmp(sql_row[0], s2) == 0) {
						cout << "아이디가 이미존재합니다." << endl;
						check = 1;
						break;
					}
					else
						check = 0;
				}
				if (!check) {
					mysql_free_result(sql_result);
					u1.setId(s2);
					break;
				}
			}
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
			system("cls");
			//┏ ┓┛┗ ━ ┃
			gotoxy(16, 5);
			cout << "┏";
			for (int i = 0; i < 56; i++)
				cout << "━";
			cout << "┓";
			for (int i = 0; i < 15; i++) {
				gotoxy(16, 6 + i);
				cout << "┃";
				for (int j = 0; j < 56; j++)
					cout << " ";
				cout << "┃";
			}
			gotoxy(16, 20);
			cout << "┗";
			for (int i = 0; i < 56; i++)
				cout << "━";
			cout << "┛";

			gotoxy(40, 7);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			cout << "미림독서실"; 
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			gotoxy(20, 11);
			cout << "요금은 일반석 하루 5000원, 1인실 하루 7000원입니다.";
			gotoxy(25, 13);
			cout << "다른 사람들을 위해 정숙유지 부탁드립니다.";
			gotoxy(27, 15);
			cout << "독서실 내에 음식물 반입 금지입니다.";
			gotoxy(21, 17);
			cout << "휴대전화는 무음모드, 혹은 전원 종료 부탁드립니다.";
			gotoxy(18, 21);
			cout << "메뉴화면으로 돌아가려면 아무키나 누르세요.";

			_getch();
			break;
		}
		location = 17;
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

	system("title 미림 독서실");
	Menu();

	mysql_close(&mysql);
	return 0;
}