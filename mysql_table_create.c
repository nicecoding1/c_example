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

Compile: gcc -o mysql_table_create mysql_table_create.c -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient

Run: ./mysql_login
*/

#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h> //MySQL ������ ���� �������

int main(void) {
   char sql[500]="";  //������
   char sql2[200]=""; //������
   int ret;

   MYSQL* conn;    //MySQL ���� ����

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

   strcat(sql, "CREATE TABLE `user` ( ");
   strcat(sql, "`no` int(10) unsigned NOT NULL AUTO_INCREMENT,");
   strcat(sql, "`id` varchar(20) DEFAULT NULL,");
   strcat(sql, "`pw` varchar(20) DEFAULT NULL,");
   strcat(sql, "`name` varchar(20) DEFAULT NULL,");
   strcat(sql, "`insdt` datetime DEFAULT NULL,");
   strcat(sql, "PRIMARY KEY (`no`),");
   strcat(sql, "UNIQUE KEY `Index1` (`id`)");
   strcat(sql, ") ENGINE=MyISAM DEFAULT CHARSET=utf8");

   strcat(sql2, "INSERT INTO `user` (`id`, `pw`, `name`, `insdt`) VALUES ('test', '1234', 'test', NOW());");

   //���̺� ����
   mysql_query(conn, sql);

   //������ �Է�
   mysql_query(conn, sql2);

   //���� ����
   mysql_close(conn);

   return(0);
}