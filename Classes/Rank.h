#include<string>
#include<iostream>
#include<mysql.h>
#include<stdio.h>
#include "User.h"
#include "cocos2d.h"
#pragma  comment(lib,"libmysql.lib")
USING_NS_CC;
class Rank{
public:
	Rank(){};
	~Rank(){};
	void updateRank(User user);
	Vector<User*> getRecord();	//获得记录对象列表
	MYSQL* m_sqlCon;				//数据源指针

};