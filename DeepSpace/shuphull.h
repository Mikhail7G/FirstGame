#ifndef SHIPHULL_H
#define SHIPHULL_H

#include <hgeparticle.h>
#include <hge.h>
#include "dsanim.h"
#include <hgesprite.h>
#include "Itemcore.h"

extern enum WeaponSize;

static int ITEMID=0;

class hull :public cargo
{
public:
	int wslot;//слотов под орудия
	int itemlevel;
	float scale;//маштаб корпуса
	float engrad;//на сколько надо сместить след от двигателя для его правильного расположения
	float maxhp;//сколько максимум очков прочности
	float sensorrange;//дальность захвата цели
	///Сопротивления 4 видам урона: фугасное,кинетическое,тепловое,радиационное.
	float explres;
	float kinres;
	float termres;
	float radiores;
	float sigradius;//реальный радиус корпуса

	//char *name;

	WeaponSize enginesize;//размер двигателя
	WeaponSize wslotsize;//размер слотов орудий

	HANIM *anim;//анимация корпуса
	hgeParticleSystem *eng;//след от двигателя
	//hgeSprite *ico;//картинка корпуса

	hull(hgeParticleSystem *eng,HANIM *anim);
	~hull();
	void SetDefaultVar();//установить стандартные значения
	void SetDispreadVar(float dispread);//установить начальные параметры с разбросом
	void GenerateRandomVar(int level,float rand,float dispread);
	void LevelUp(int level);//поднять уровень вещи

	hull *clone_default() const//тут идет просто копирование данного предмета без изменения характеристик!
	{
		ItemCount++;
		return new hull(*this);
	};

protected:
	//стандартные переменные исп. для повышения уровня
	float d_scale;
	float d_maxhp;

	float d_explres;
	float d_kinres;
	float d_termres;
	float d_radiores;

	float d_sensorrange;
	float d_mass;
	float d_sigradius;

	int zz;

};


#endif