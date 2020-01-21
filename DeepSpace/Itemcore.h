#ifndef ITEMCORE_H
#define ITEMCORE_H


// Этот класс отвечает за хранение вещей в игре, представляет собой контейнер, в корый хранит все виды вещей. Такие как: модули корабля, снаряды, руду и прочее.

#include <hge.h>
#include "cmath"
#include <hgesprite.h>
#include <memory>

#include "dsanim.h"
#include "dsanimate.h"

#include "effect.h"
#include "explosion.h"

//#include "shuphull.h"
//#include "weapon.h"
//#include "bullets.h"
//#include "shipengine.h"
//#include "shipengine.h"

using namespace std;
extern HGE *hge;
extern float dt;
extern int PlayerSys;
extern int ItemCount;

extern float syspozx[];//координаты секторов в космосу
extern float syspozy[];

extern HANIM    *cargobox;
extern HANIM    *animeffects[];
extern vector<effect*> eff;



static int coreid=0;


class cargo
{
public:
	bool moving;//флаг, отвечающий за движение контейнера после выброса из грузового отсека
	bool kill;//уничтожен ли объект?
	bool hidekill;//при сборе стакающихся вещей уничтожаем без вызрыва
	bool canstak;//можно ли сложить в кучу?

	int count;//сколько вещей в куче
	int sysid;//сектор
	int fraction;//1-люди

	int slotid;// в каком слоте лежит данный объект(чисто для игрока)

	float x;//координаты в космосе
	float y;
	float dx;
	float dy;

	float mass;

	float ItemDispread;//разброс базовых параметров

	int type;//0-корпус,1-двигатель,2-орудие,3-снаряд,4-руда
	int state;//0-космос,1-на корабле или в магазине


	HANIM    *crgbox;
	hgeAnim *box;//ссылка на то что загруженно, создается,удаляется при необходимости
	hgeSprite *ico;//картинка вещи

	char *name;//название объекта
	char *description;//описание объекта
	
	cargo();// координаты Х и У устанавливаются в локальных координатах системы!
    virtual	~cargo();

	virtual void Render();
	void Update();
	void MoveCrg();//после сброса с грузового отсека контейнер немного летит в случайном направлении
	void Install();//установить модуль на корабль

	void CreateAnim();//создаем анимацию после копирования т.к. копируется 1 созданная анимация
	void InitializeSpace(int sysid,float x,float y);//создать предмет в космосе
	void InitializeInside();//создать предмет в грузовом отсеке или на станции
	void ShipDrop(int sysid,float x,float y);//сбросить груз с корабля
	void TractorBeam(float x,float y);//таговый луч

	//старые функции
	void SetPoz(int sysid,float x,float y);//установить позицию относительно глобальной системы координат
	void SetFixedPoz(int sysid,float x,float y);//установить позицию относительно локальных координат системы

protected:
	float timer1;
	float speed;
	float dispread;
	int zz;




};



//class cargo
//{
//public:
//
//	bool moving;//флаг, отвечающий за движение контейнера после выброса из грузового отсека
//
//	int sysid;//сектор
//
//	float x;//координаты в космосе
//	float y;
//	float dx;
//	float dy;
//
//	int type;//0-корпус,1-двигатель,2-орудие,3-снаряд
//	int state;//0-космос,1-на корабле или в магазине
//
//	hgeAnim *img;//ссылка на то что загруженно, создается,удаляется при необходимости
//	hgeSprite *ico;//картинка вещи
//
//	char *name;
//	
//	hull *shiphull;//корпус корабля
//	engine *shipengine;//двигатель корабля
//	turret *weapon;//орудие
//	std::shared_ptr<bullet> bull;
//
//	cargo(int sysid,float x,float y);// координаты Х и У устанавливаются в локальных координатах системы!
//	~cargo();
//	cargo(int sysid,float x,float y,hull *shiphull);//помещаем корпус в контейнер
//	cargo(int sysid,float x,float y,engine *shipengine);//помещаем двигатель в контейнер
//	cargo(int sysid,float x,float y,turret *weapon);//помещаем орудие в контейнер
//	cargo(int sysid,float x,float y,std::shared_ptr<bullet> bull);//помещаем снаряд в контейнер
//
//	void Render();
//	void SetPoz(float x,float y);//установить позицию относительно глобальной системы координат
//	void MoveCrg();//после сброса с грузового отсека контейнер немного летит в случайном направлении
//
//protected:
//	float timer1;
//	float speed;
//	float dispread;
//
//
//
//
//
//
//
//};





#endif