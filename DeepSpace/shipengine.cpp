#include "shipengine.h"


engine::engine(float _warptime,float _speed,WeaponSize _size)
{
	mass=0;
	speed=_speed;
	warptime=1.0f;
	size=_size;
	warprange=1;
	name="нет";
	type=1;
	impulse = 10;

	if (impulse > speed)
	{
		impulse = speed / 2;
	};
};


engine::~engine()
{
	 hge->System_Log("Двиг:%s уничтожен в системе:%i",name,sysid);	
};

void engine::SetDefaultVar()
{
	d_mass=mass;
	d_speed=speed;
	d_warptime=warptime;
};

void engine::GenerateRandomVar(int _level,float _rand,float _dispread)
{
	int lvl=_level;//ур вещи
	itemlevel=lvl;
	float rand=_rand;//коэффициент понижения параметров вещей, дефолт 0,02f
	rand=0.02f;

	float rec;//коэффициент снижения характеристик
	rec=(rand*lvl)/(1+rand*lvl);
	//меняем скорость
	float s1=d_speed+d_speed*(0.1f*lvl);
	float s2=d_speed+d_speed*(0.1f*(lvl-1)*rec);
	speed=d_speed+((s1-s2)/7);
	//считаем время 
	float t1=d_warptime*0.1f*lvl;
	float t2=d_warptime*(0.1f*(lvl-1)*rec);
	//warptime=d_warptime-(d_warptime*0.5f*(t2/t1));

};

void engine::LevelUp(int _level)
{
	int level=_level;
	itemlevel+=level;
	GenerateRandomVar(itemlevel,0,0);

};
