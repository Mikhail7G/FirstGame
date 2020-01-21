#ifndef SHIPENGINE_H
#define SHIPENGINE_H

#include <hge.h>
#include <hgesprite.h>
#include "Itemcore.h"

extern enum WeaponSize;//это не размер орудия а вообще размер любого устанавливаемого модуля

class engine :public cargo
{
public:
	int itemlevel;
	WeaponSize size;

	float speed;//скорость двигаетеля т.е. его предельная тяга
	float warptime;//время ухода в варп
	float warprange;//дальность прыжка
	float impulse;//Скорость разгона двигаетеля

	//char *name;

	//hgeSprite *ico;

	engine(float warptime,float speed,WeaponSize size);
	~engine();

	void SetDefaultVar();//установить стандартные значения
	void GenerateRandomVar(int level,float rand,float dispread);
	void LevelUp(int level);//поднять уровень вещи

	engine *clone_default() const//тут идет просто копирование данного предмета без изменения характеристик!
	{
		ItemCount++;
		return new engine(*this);
	};

protected:
	//стандартные значения
	float d_mass;//масса двигателя
	float d_speed;//скорость двигаетеля т.е. его предельная тяга
	float d_warptime;//время ухода в варп

};



#endif