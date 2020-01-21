#ifndef DEFENDERBOT_H
#define DEFENDERBOT_H

#include <hge.h>
#include "dyncore.h"
#include "warship.h"
#include <memory>
#include "pilot.h"
#include "Itemcore.h"
#include "planets.h"
#include "sector.h"
#include "bullcontainer.h"

extern int PlayerSys;
extern bool GPAUSED;

using namespace std;

extern vector<sector*> sectors;

extern hgeFont	*fnt;
extern HGE *hge;


static int PilotId = 0;//номер пилота


class defender : public pilotctr
{
public:
	int fraction;//кому принадлежит
	int state;//0-ничего 1-патруль
	int p_id;

	bool ready_to_fly;//флаг общей боеготовности

	float timer1;
	float t_timer1;

	std::weak_ptr<ship> Ship;//корабль 

	planet *homeplanet;//домашная планета


	defender();
	~defender();
	virtual void ScangeMap(int sysid);
	virtual void LogicUpdate();//обновление логики бота
	 void ShipLost();//уничтожение корабля

	 void CheckShip();//проверка корабля
	 void Patrol();
	 void SleepTimer();

	 void Alarm();
	 void WarActions();//боевые действия
	 void ReturnToBase();//возвращаемся на базу

	 void DebugDraw();//отладочная инфа

	 void GetBadTarget();//получаем все цели, которые агрессивны для этой планеты

	 void LoadAmmo();//заряжаем снарады в орудия

	 int GetId();



};



#endif