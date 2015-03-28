#include <Windows.h>
#include <winsock.h>  
#include <mysql.h>  
#include "GlobalData.h"  
#include <sstream>  
#include "HandleMysql.h"
using namespace  std;


HandleMysql::HandleMysql()
{
	mysql_init(&mysql);
}

HandleMysql::~HandleMysql()
{
	mysql_close(&mysql);
}

//Connect to the DB host  
bool HandleMysql::ConnectDB(Database_Param* p)
{
	if (!mysql_real_connect(&mysql, (p->host).c_str(), p->user.c_str(), p->password.c_str(), p->db.c_str(), p->port, p->unix_socket, p->client_flag))
	{
		return false;
	}
	return true;
}

//Select DB  
bool HandleMysql::SelectDB(Data_Param* para)
{
	if (mysql_select_db(&mysql, para->db_name.c_str()))
		return false;
	else
		return true;
}

//Get the record and store it int 'row'  
MYSQL_ROW HandleMysql::GetRecord()
{
	return (row = mysql_fetch_row(query));
}

//A utility to select all the records  
bool HandleMysql::SelectAll(Data_Param* para)
{
	unsigned int i = 0;
	ostringstream Ostr;
	Ostr << "select * from " << para->tab_name;
	if (!FindSave(Ostr.str()))
	{
		return false;
	}
	return true;
}

//Seek the row   
void HandleMysql::SeekData(int offset)
{
	mysql_data_seek(query, offset);
}

//Execute the query and store the results in 'query'  
bool HandleMysql::FindSave(string str)
{
	if (mysql_query(&mysql, str.c_str()))
		return false;
	query = mysql_store_result(&mysql);
	return true;
}

//A utility to delete the records  
bool HandleMysql::DelRecord(Data_Param* para)
{
	ostringstream Ostr;
	Ostr << "delete from " << para->tab_name << " where " << para->where_def;
	if (mysql_query(&mysql, Ostr.str().c_str()))
	{
		return false;
	}
	return true;
}

//A utility to insert records  
bool HandleMysql::InsertRecord(Data_Param* para)
{
	ostringstream Ostr;
	Ostr << "insert into " << para->tab_name << " values(" << para->insert_val << ")";
	if (mysql_query(&mysql, Ostr.str().c_str()))
	{
		return false;
	}
	return true;
}

//A utility to select records  
bool HandleMysql::SelectRecord(Data_Param* para)
{
	unsigned int i = 0;
	ostringstream Ostr;
	Ostr << "select " << para->select_exp << " from " << para->tab_name << " where " << para->where_def;
	if (!FindSave(Ostr.str()))
	{
		return false;
	}
	return true;
}

//A utility to update records  
bool HandleMysql::UpdateRecord(Data_Param* para)
{
	ostringstream Ostr;
	Ostr << "update " << para->tab_name << " set " << para->set_exp << " where " << para->where_def;
	if (mysql_query(&mysql, Ostr.str().c_str()))
	{
		return false;
	}
	return true;
}


bool HandleMysql::IsEnd()
{
	if (mysql_eof(query))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Get number of rows  
my_ulonglong HandleMysql::GetRowNum()
{
	return (mysql_num_fields(query));
}

//Get the name of the FieldNumth Field  
string HandleMysql::GetFieldName(int FieldNum)
{
	field = mysql_fetch_field_direct(query, FieldNum);
	return string(field->name);
}

string HandleMysql::GetClientInfo()
{
	return string(mysql_get_client_info());
}

string HandleMysql::GetServerInfo()
{
	return string(mysql_get_server_info(&mysql));
}

string HandleMysql::GetHostInfo()
{
	return string(mysql_get_host_info(&mysql));
}

int HandleMysql::GetProtocolInfo()
{
	return mysql_get_proto_info(&mysql);
}

string HandleMysql::GetState()
{
	string state(mysql_stat(&mysql));
	if (!state.empty())
		return string(OutErrors());
	return state;
}

/*void HandleMysql::FreeRecord()
{
mysql_free_result(query);
}*/

string HandleMysql::OutErrors()
{
	return string(mysql_error(&mysql));
}


bool HandleMysql::MysqlEx(MYSQL* mysql, string str)
{
	if (!FindSave(str))
	{
		return false;
	}
	return true;
}

unsigned int HandleMysql::GetFieldNum()
{
	return (mysql_num_fields(query));
}