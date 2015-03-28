#ifndef HANDLEMYSQL_H  
#define HANDLEMYSQL_H  

#include <winsock.h>  
#include <mysql.h>  
#include "GlobalData.h"  
#include <sstream>  
using namespace  std;
class HandleMysql
{
public:
	string GetState();    //服务器状态  
	string GetServerInfo();    //服务器信息  
	int GetProtocolInfo();    //协议信息  
	string GetHostInfo();    //主机信息  
	string GetClientInfo();    //客户机信息  
	string GetFieldName(int FieldNum);
	bool IsEnd();    //是否最后  
	void SeekData(int offset);    //查找指定数据  
	unsigned int GetFieldNum();        //得到字段数  
	bool ConnectDB(Database_Param* p);    //连接数据库  
	MYSQL_ROW GetRecord();    //得到结果（一个记录）  
	my_ulonglong GetRowNum();    //得到记录数  
	bool SelectDB(Data_Param* para);    //选择数据库  
	bool UpdateRecord(Data_Param* para);    //更新记录  
	bool SelectRecord(Data_Param* para);    //选择记录  
	bool InsertRecord(Data_Param* para);    //插入记录  
	bool DelRecord(Data_Param* para);        //删除记录  
	bool SelectAll(Data_Param* para);        //选择所有记录  
	string OutErrors();        //输出错误信息  
	bool MysqlEx(MYSQL* mysql, string str);
	HandleMysql();
	virtual ~HandleMysql();
private:
	bool FindSave(string str);    //查找并保存结果集  
private:
	MYSQL mysql;    //数据库链接句柄  
	MYSQL_FIELD* field;    //字段信息（结构体）  
public:
	MYSQL_RES* query;    //结果集  
	MYSQL_ROW row;    //记录集  
};

#endif  