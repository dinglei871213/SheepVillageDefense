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
	string GetState();    //������״̬  
	string GetServerInfo();    //��������Ϣ  
	int GetProtocolInfo();    //Э����Ϣ  
	string GetHostInfo();    //������Ϣ  
	string GetClientInfo();    //�ͻ�����Ϣ  
	string GetFieldName(int FieldNum);
	bool IsEnd();    //�Ƿ����  
	void SeekData(int offset);    //����ָ������  
	unsigned int GetFieldNum();        //�õ��ֶ���  
	bool ConnectDB(Database_Param* p);    //�������ݿ�  
	MYSQL_ROW GetRecord();    //�õ������һ����¼��  
	my_ulonglong GetRowNum();    //�õ���¼��  
	bool SelectDB(Data_Param* para);    //ѡ�����ݿ�  
	bool UpdateRecord(Data_Param* para);    //���¼�¼  
	bool SelectRecord(Data_Param* para);    //ѡ���¼  
	bool InsertRecord(Data_Param* para);    //�����¼  
	bool DelRecord(Data_Param* para);        //ɾ����¼  
	bool SelectAll(Data_Param* para);        //ѡ�����м�¼  
	string OutErrors();        //���������Ϣ  
	bool MysqlEx(MYSQL* mysql, string str);
	HandleMysql();
	virtual ~HandleMysql();
private:
	bool FindSave(string str);    //���Ҳ���������  
private:
	MYSQL mysql;    //���ݿ����Ӿ��  
	MYSQL_FIELD* field;    //�ֶ���Ϣ���ṹ�壩  
public:
	MYSQL_RES* query;    //�����  
	MYSQL_ROW row;    //��¼��  
};

#endif  