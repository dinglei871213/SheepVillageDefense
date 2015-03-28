#ifndef __SheepVillageDefense__Bullet1__
#define __SheepVillageDefense__Bullet1__

#include <iostream>
#include "BulletBase.h"
#include "cocos2d.h"

USING_NS_CC;
//子弹1类
class Bullet1 : public BulletBase
{
public:
	bool init();

	CREATE_FUNC(Bullet1);

};


//子弹2类
class Bullet2 : public BulletBase
{
public:
	 bool init() ;

	 CREATE_FUNC(Bullet2);

};

//子弹3类
class Bullet3 : public BulletBase
{
public:
	 bool init() ;

	 CREATE_FUNC(Bullet3);

};

//子弹4类
class Bullet4 : public BulletBase
{
public:
	bool init();

	CREATE_FUNC(Bullet4);

};


#endif /* defined(__SheepVillageDefense__Bullet1__) */
