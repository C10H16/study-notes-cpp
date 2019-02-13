#include <iostream>
#include <string>
#include <vector>
#include <mysql/mysql.h>
#include "MyDB.h"

MyDB::MyDB()
    :ErrorNum(0), ErrorInfo("ok")
{
    //mysql_library_init(0,Null,Null);
    mysql_init(&MysqlInstance);
}

MyDB::~MyDB()
{
    
}

//设置连接信息
void MyDB::SetMySQLConInfo(char *server, char* username, char* passwd, char* database, int port)
{
    MysqlConInfo.host = server;
    MysqlConInfo.user = username;
    MysqlConInfo.passwd = passwd;
    MysqlConInfo.dbname = database;
    MysqlConInfo.port = port;
}

//打开连接
bool MyDB::OpenDB()
{
    if(mysql_real_connect(&MysqlInstance, MysqlConInfo.host,
        MysqlConInfo.user, MysqlConInfo.passwd, MysqlConInfo.dbname,
        MysqlConInfo.port, 0, 0) != NULL)
    {
        return true;
    }
    else
    {
        ErrorIntoMySQL();
        return false;
    }
}

//断开连接
void MyDB::CloseDB()
{
    mysql_close(&MysqlInstance);
}

//读取数据
bool MyDB::Select(const std::string& Querystr, std::vector<std::vector<std::string> >& data)
{
    if(0 != mysql_query(&MysqlInstance, Querystr.c_str()))
    {
        ErrorIntoMySQL();
        return false;
    }

    Result = mysql_store_result(&MysqlInstance);

    //行列数
    int row = mysql_num_rows(Result);
    int field = mysql_num_fields(Result);

    MYSQL_ROW line = NULL;
    line = mysql_fetch_row(Result);

    int j = 0;
	std::string temp;
	std::vector<std::vector<std::string> > ().swap(data);
    while (NULL != line)
    {
		std::vector<std::string> linedata;
        for(int i = 0; i < field; i++)
        {
            if (line[i])
            {
                temp = line[i];
                linedata.push_back(temp);
            }
            else
            {
                temp = "";
                linedata.push_back(temp);
            }
        }
        line = mysql_fetch_row(Result);
        data.push_back(linedata);
    }
    return true;
}

//其他操作
bool MyDB::Query(const std::string& Querystr)
{
    if(0 == mysql_query(&MysqlInstance, Querystr.c_str()))
    {
        return true;
    }
    ErrorIntoMySQL();
    return false;
}

//错误信息
void MyDB::ErrorIntoMySQL()
{
    ErrorNum = atoi(mysql_error(&MysqlInstance));
    ErrorInfo = mysql_error(&MysqlInstance);
}

