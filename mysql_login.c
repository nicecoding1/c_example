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
#include <mysql/mysql.h> //MySQL ������ ���� �������

int main(void) {
   char sql[500]=""; //������
   char id[30]="";
   char pw[30]="";
   int ret;

   MYSQL* conn;    //MySQL ���� ����
   MYSQL_RES* res; //MySQL ��� �ڵ� ����
   MYSQL_ROW row;  //MySQL ��� ���� ����

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

   printf("Input User ID: ");
   scanf("%s", id);
   printf("Input User PW: ");
   scanf("%s", pw);

   strcat(sql, "select * from user where id='");
   strcat(sql, id);
   strcat(sql, "' and pw='");
   strcat(sql, pw);
   strcat(sql, "'");

   //���� ����
   ret = mysql_query(conn, sql);
   res = mysql_store_result(conn);

   //����� �������� �� ���
   if((row = mysql_fetch_row(res)) != NULL) {
      printf("\nUser Login OK: %s\n", row[0]);
   }

   //�Ҵ�� �޸� ����
   mysql_free_result(res);

   //���� ����
   mysql_close(conn);

   return(0);
}