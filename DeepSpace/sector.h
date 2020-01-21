#ifndef SECTOR_H
#define SECTOR_H


//Это касс отвечающий за системы в космосе, хранит координаты сектора,тут создаются планеты, контроль за БГ и пр.


#include <hge.h>
#include <hgefont.h>
#include <vector>
#include <memory>
#include "Itemcore.h"

#include "dsanim.h"
#include "dsanimate.h"
#include "dyncore.h"

#include "planets.h"

using namespace std;

extern double Call_Time;

extern HGE *hge;
extern float dt;

extern HANIM    *mapeffects[];//анимированные эффекты

extern vector<shared_ptr<dynamic>> dyn;

extern float CollRad;

extern int PlayerSys;
extern float syspozx[];//координаты секторов в космосу
extern float syspozy[];

extern enum Fraction;//кому принадлежит система определен в gamecore

static int Count=0;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);

class sector
{
public:
	int id;

    int raiting;//уровень развития системы, от 0 до 100. - скорость производства зависит от него
	int level;//уровень системы

	float x;//положение сектора в пространстве
	float y;

	bool hide;//скрыта ли система от кораблей

	hgeSprite *ico;//картинка системы
	HANIM *ani;
	hgeAnim  *aico;//анимированная каринка системы

	Fraction frac;

	char *name;//имя

	vector<planet*> planetlist;//список планет, которые входят в сектор

	vector<shared_ptr<dynamic>> objects;//все динамические объеткы в данном секторе

	vector<cargo*> cargoobjects;//вещи в текущей системе

	sector(float x,float y,hgeSprite *ico);
	sector(float x, float y, HANIM *ani);
	~sector();
	void Render(float x,float y);
	void AddToList(shared_ptr<dynamic> obj);//добавляем объект в список, при инициализации или при переходе в сектор
	void RemoveFromList(shared_ptr<dynamic> obj);//удаляем объект из листа

	void Update();//обновление объектов в данном секторе
	void Render();//рисуем объекты в сеторе игрока

	void PreInit();//запускаем систему в Update();

	void FastUpdate();//приблизительные расчеты в неактивных системах

	float call_time;
	float last_time;

	void AddItemToList(cargo* item);//добавляем объект в список

	int cur_col_obj;




};


#endif