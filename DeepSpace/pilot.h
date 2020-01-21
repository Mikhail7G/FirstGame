#ifndef PILOT_H
#define PILOT_H
//тут хранятся все бонусы от навыков пилота от этого класса наследуюся игрок и боты
#include <hge.h>

extern HGE *hge;

class pilotctr
{
public:

	pilotctr();
	virtual ~pilotctr();
	virtual void ScangeMap(int sysid);
	virtual void ShipLost();//уничтожение корабля
	virtual void LigicUpdate();//обновление логики бота
	virtual void Alarm();//атака по кораблю

	virtual void NoAmmo();//сообщение от корабля о том, что кончились снаряды

	virtual int GetId()//id пилота
	{
		return 0;
	};


	virtual void DebugDraw()
	{

	};



};



#endif