#ifndef CARGOOPER_H
#define CARGOOPER_H

#include <hge.h>
#include "cmath"
#include <vector>
#include "Itemcore.h"
#include "sector.h"
#include <algorithm> 

using namespace std;
extern HGE *hge;
extern float dt;

extern vector<sector*> sectors;


class cargomanager
{
public:
	int maxslot;//максимум слотов в отсеке

	float totalmass;

	vector<cargo*> crg;//вещи, хранимые в отсеке корабля
	cargo *shipeng;//двигатель корабля
	cargo *shiphull;//корпус корабля
	vector<cargo*> shipwpn;//орудия корабля


	cargomanager();
	~cargomanager();

	bool GetItem(cargo *itm);//подбираем вещь с космоса
	void DropItem(int id,int sysid,float x,float y);//пока по id слота
	void DropItem(int id);//перенос в слоты на корабле
	void DropAll(int sysid, float x, float y);//сброс всех вещей
	void DropEngine(int sysid, float x, float y);//сброс двигателя(не вызывать до убийства корабля!)
	void DropHull(int sysid, float x, float y);//сброс корпуса при подбитии корабля
	void DropWeapon(int sysid, float x, float y);//сброс всего оружия

	void SortAllItems();//отсортировать все вещи в груз отсеке

protected:
	bool SortItem(cargo *itm);//


};


#endif