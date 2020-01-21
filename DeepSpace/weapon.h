#ifndef WEAPON_H
#define WEAPON_H

#include "cmath"
#include <memory>
#include <stdlib.h>
#include <stdio.h>

#include <hge.h>

#include "dsanim.h"
#include "dsanimate.h"
#include "dyncore.h"
#include "bullets.h"
#include "Itemcore.h"
#include "sector.h"


extern HGE *hge;

extern float dt;

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);
extern float point_direction(float x1,float y1,float x2,float y2);

extern vector<shared_ptr<dynamic>> dyn;
extern vector<sector*> sectors;

extern enum WeaponSize;


static int ITEMID1=0;

//класс turret - класс орудий, в каждую пушку можно будет зарядить снарады,ракеты и т.д.

class turret: public cargo
{
public:
	int itemlevel;//уровень вещи
	int ammoclip;//сколько патрон в обойме
	int ammo;//текущий снаряд в магазине

	float timer1;//таймер перезарядки обоймы
	float timer2;//таймер стреьбы внутри обоймы
	float reloadtimer;//таймер перезарядки
	float ammoreload;//задержка между выстрелами внутри обоймы.
	float fireradius;//радиус стрельбы
	float optimal;//рекомендуемый радиус стрельбы
	float tracking;//скорость поворота орудий
	float sigradius;//рекомендуемый радиус поражаемых целей


	//бонусы на урон:
	float damagemod;//модификатор урона для орудий
	float bonusdamage;//доп. урон, действует на все виды урона для каждой пушки- это в %

	float DPS;//урон в секунду
	float alphastrike;//урон с 1 снаряда

	float hitchance;//шанс поподания по цели



	bool autofire;//есть ли автострельба
	bool armed;//заряжено орудие?
	bool shoot;//нажат ли спусковой крючок

	//hgeSprite *ico;//картинка пушки

	std::weak_ptr<dynamic> target;//цель пушки
	std::weak_ptr<dynamic> parient;//к кому прикреплена пушка
	std::shared_ptr<bullet> bull;//заряжаем снаряд в пушку
	//std::weak_ptr<bullet> bull;//заряжаем снаряд в пушку

	WeaponSize Wsize;//размер модуля
	//char *name;//имя орудия

	
protected:
	float x;
	float y;
	float dir;
	//стандартные параметры для орудий, нужны для генерации рандомных вещей
	int d_mass;
	int d_ammoclip;
	float d_reloadtimer;
	float d_ammoreload;
	float d_fireradius;
	float d_optimal;
	float d_tracking;
	float d_sigradius;
	float d_damagemod;

	float zz;

	//это параметры после генерации вещи, но до влияния каких либо бонусов
	float s_fireradius;
	float s_optimal;
	float s_sigradius;
	float s_tracking;


public:
	turret(float reloadtimer,float ammoreload,float fireradius,float optimal,int ammoclip,float sigradius,float tracking);
	~turret();
	virtual void Update(float x,float y);//тут идет проверка на наличие цели и работа таймеров перезарядки.
	virtual void StartFiring();//начать автострельбу?
	virtual void Fire();//стреляем координаты места запуска
	virtual void Launch();//запускаем снаряд
	virtual void SetTarget(std::weak_ptr<dynamic> target);//устанавливаем цель для пушки
	virtual void DropTarget();//сброс цели
	virtual bool SetBullet(std::shared_ptr<bullet> bull);//заряжаем снаряд
	virtual void RemoveBullet();//разряжаем орудие и убираем бонусы от снаряда
	virtual void DestroyBullet();//выполняется при потере снаряда во время сброса в космос или при других усовиях, не требующих возвращение снаряда в магазин
	virtual void CalculateDPS();//расчитывем урон
	virtual void SetParient(std::weak_ptr<dynamic> parient);//кто стреляет из пушки

	virtual void SetDefaultVar();//устанавливает стадартные значения для этого типа орудия

	virtual void GenerateRandomVar(int level,float rand,float dispread);
	virtual void LevelUp(int level);//поднять уровень вещи
	virtual void SetBonusFromBullet();//утановить бонусы со снаряда

	virtual void GetClearVar();//установка параметров до влияния бонусов
	virtual void SetClearVar();//полсе разрядки снаряда возвращаям стандартные значения

	turret *clone_default() const//тут идет просто копирование данного предмета без изменения характеристик!
	{
		ItemCount++;
		return new turret(*this);
	};



protected:
	void ReloadTimer();
	bool Timer1();
	bool Timer2();



};


#endif