/*
Compile: gcc -o mysql_test mysql_test.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
Run: ./mysql_test
*/

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h> //MySQL 연결을 위한 헤더파일

int main(void) {
   char* sql = "select now()"; //쿼리문
   int ret;

   MYSQL* conn; //MySQL 연결 변수
   MYSQL_RES* res; //MySQL 결과 핸들 변수
   MYSQL_ROW row; //MySQL 결과 저장 변수

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
   //쿼리 실행
   ret = mysql_query(conn, sql);
   res = mysql_store_result(conn);

   //결과값 가져오기 및 출력
   while((row = mysql_fetch_row(res)) != NULL) {
      printf("%s\n", row[0]);
   }   
   
   //할당된 메모리 해제
   mysql_free_result(res);

   //접속 해제
   mysql_close(conn);

   return(0);
}
