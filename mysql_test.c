/*
Compile: gcc -o mysql_test mysql_test.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient
Run: ./mysql_test
*/

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h> //MySQL ������ ���� �������

int main(void) {
   char* sql = "select now()"; //������
   int ret;

   MYSQL* conn; //MySQL ���� ����
   MYSQL_RES* res; //MySQL ��� �ڵ� ����
   MYSQL_ROW row; //MySQL ��� ���� ����

   conn = mysql_init(NULL); //�ʱ�ȭ
   if(!conn) {
      printf("mysql_init failed!\n");
      return(1);
   }
   
   //MySQL ����
   conn = mysql_real_connect(conn, "localhost", "id", "password", "dbname", 3306, (char*)NULL, 0); 
   if(conn) printf("Connect success!\n");
   else {
      printf("Connect fail!\n");
      return(1);
   }
   //���� ����
   ret = mysql_query(conn, sql);
   res = mysql_store_result(conn);

   //����� �������� �� ���
   while((row = mysql_fetch_row(res)) != NULL) {
      printf("%s\n", row[0]);
   }   
   
   //�Ҵ�� �޸� ����
   mysql_free_result(res);

   //���� ����
   mysql_close(conn);

   return(0);
}
