#ifndef _MYDB_H
#define _MYDB_H

#include <string>
#include <vector>
#include <mysql/mysql.h>

typedef struct
{
    char* host;
    char* user;
    char* passwd;
    char* dbname;
    int port;
}MySQLConInfo;
class MyDB
{
public:
    MyDB();
    virtual ~MyDB();
    void SetMySQLConInfo(char *server,char*username, char* passwd, char* database, int port = 0); //设置连接信息
    bool OpenDB(); //打开连接
    void CloseDB(); //关闭连接

    bool Select(const std::string& Querystr,std::vector<std::vector<std::string> >& data); //读取数据
    bool Query(const std::string& Querystr); //其他操作
    void ErrorIntoMySQL(); //错误消息

public:
    int ErrorNum; //错误代号
    const char* ErrorInfo; //错误提示
private:
    MySQLConInfo MysqlConInfo; //链接信息
    MYSQL MysqlInstance; //MySQL对象
    MYSQL_RES* Result; //用于存放结果
};

#endif
