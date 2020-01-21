#ifndef PLANETS_H
#define PLANETS_H
#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"
#include <memory>
#include "dyncore.h"


using namespace std;
extern HGE *hge;
extern float dt;

extern hgeSprite *shadow;

extern int PlayerSys;

extern float MouseX;
extern float MouseY;

//extern hgeSprite *PlanetsSpr[];

extern char *PLN_Spr[];

extern float syspozx[];//координаты секторов в космосу
extern float syspozy[];

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);
extern float slow_rotate(float speed,float dir,float newdir);

class planet
{
public:
	int sysid;

	float x;
	float y;
	float dx;
	float dy;
	float speed;//скорость врашения
	float alt;//орбита
	float scale;
	float border;//радиус планеты
	float dir;//угол поворота относительно центра

	char *name;
	int fraction;//кто живет на планете 0-никто, 1 - люди
	float population;//число жителей
	int type;//тип панеты 0 - нет, 1 - аграрная, 2-промышленная
	int resourse;//богатость планеты разлчиными ресурсами 0 - бедная 1 - умереная 2 - средная и тд


	vector<std::weak_ptr<dynamic>>attackers;//список всех, кто враг этой планете

	vector<std::weak_ptr<dynamic>>defense_ships;//список защитных кораблей планеты

	bool canland;

	hgeSprite *spr;
	HTEXTURE tex;
	int SpriteID;

	planet(int sysid,float alt,float speed,float scale,int SpriteID);
	planet(int sysid, int syspoz);
	~planet();
	void Update();
	void Render();
	void LoadTexture();//загрузка текстуры планеты
	void ChangeMap();//смена карты тут 
	void PeopleKill();//убивание жителей от астероидов и пр.
	void FastUpdate(float dt);//неточное обновление объекта

	bool MouseTest();//проверка наведения мышки

	void AddAggressiveToList(std::weak_ptr<dynamic> attacker);//добавляет атакующего врага в список

	void AddDefenceShip(weak_ptr<dynamic> ships);//при создании корабля на планете посещяем его в список

protected:
	bool reloaded;// сбрсили ли текстуры

	float poptimer;//таймер прироста популяции на планете
	float pt1;
	void Ptimer1();
	void Ptimer1_F(float dt);
	void UpdatePopulation();//прирост населения для планет


};


#endif