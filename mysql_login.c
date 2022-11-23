/*
MySQL table create:
CREATE TABLE `user` (
  `no` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `id` varchar(20) DEFAULT NULL,
  `pw` varchar(20) DEFAULT NULL,
  `name` varchar(20) DEFAULT NULL,
  `insdt` datetime DEFAULT NULL,
  PRIMARY KEY (`no`),
  UNIQUE KEY `Index1` (`id`)
) ENGINE=MyISAM DEFAULT CHARSET=utf8;
INSERT INTO `user` (`id`, `pw`, `name`, `insdt`) VALUES ('test', '1234', 'test', NOW());

Compile: gcc -o mysql_login mysql_login.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

Run: ./mysql_login
*/

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h> //MySQL 연결을 위한 헤더파일

int main(void) {
   char sql[500]=""; //쿼리문
   char id[30]="";
   char pw[30]="";
   int ret;

   MYSQL* conn;    //MySQL 연결 변수
   MYSQL_RES* res; //MySQL 결과 핸들 변수
   MYSQL_ROW row;  //MySQL 결과 저장 변수

   conn = mysql_init(NULL); //초기화
   if(!conn) {
      printf("mysql_init failed!\n");
      return(1);
   }

   //MySQL 접속
   conn = mysql_real_connect(conn, "localhost", "id", "password", "dbname", 3306, (char*)NULL, 0);
   if(conn) printf("Connect success!\n");
   else {
      printf("Connect fail!\n");
      return(1);
   }

   printf("Input User ID: ");
   scanf("%s", id);
   printf("Input User PW: ");
   scanf("%s", pw);

   strcat(sql, "select * from user where id='");
   strcat(sql, id);
   strcat(sql, "' and pw='");
   strcat(sql, pw);
   strcat(sql, "'");

   //쿼리 실행
   ret = mysql_query(conn, sql);
   res = mysql_store_result(conn);

   //결과값 가져오기 및 출력
   if((row = mysql_fetch_row(res)) != NULL) {
      printf("\nUser Login OK: %s\n", row[0]);
   }

   //할당된 메모리 해제
   mysql_free_result(res);

   //접속 해제
   mysql_close(conn);

   return(0);
}