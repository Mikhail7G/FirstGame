#ifndef WARSHIP_H
#define WARSHIP_H

#include <vector>
#include <hge.h>
#include <hgevector.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"
#include <memory>

#include "dyncore.h"
#include "dsanim.h"
#include "dsanimate.h"

#include "damagetext.h"
#include "effect.h"
#include "explosion.h"


#include "shuphull.h"
#include "weapon.h"
#include "pilot.h"
#include "sector.h"
#include "warpeff.h"
#include "shipengine.h"
#include "Itemcore.h"
#include "cargooper.h"
#include "tractoreff.h"



using namespace std;
extern HGE *hge;
extern float dt;

extern int GlobalShipObj;

extern float syspozx[];//координаты секторов в космосе
extern float syspozy[];
extern const float lighting;
extern bool GPAUSED;

extern hgeParticleSystem  *effects[];

extern float point_distanse(float x1, float y1, float x2, float y2);
extern float point_dir2(float x1, float y1, float x2, float y2);
extern float slow_rotate(float speed, float dir, float newdir);
extern float point_direction(float x1, float y1, float x2, float y2);
extern float point_direction2(float x1, float y1, float x2, float y2);
extern float slerp(float var1, float var2, float delta);
extern bool mouse_on(float x, float y, float mx, float my, float h, float w);

extern vector<effect*> eff;
extern vector<sector*> sectors;
extern vector<cargo*> cargoobjects;

extern float CollRad;

extern HANIM    *animeffects[];

extern HSHADER             shad1;


enum states
{
	STOP = 0,
	FLY = 1,
	WARP = 2
};

enum warpstatus
{
	OFF = 0,
	ON = 1,
	RUN = 2
};


class ship : public dynamic
{
public:
	hgeAnim *img;//ссылка на то что загруженно, создается,удаляется при необходимости
	HANIM *anim;//что загружаем в память при старте игры

	hgeParticleSystem *eng;//эффект от двигателя

	hull *shiphull;//корпус корабля
	engine *shipengine;//двигатель корабля

	std::weak_ptr<dynamic> target;

	vector<std::weak_ptr<dynamic>>attackers;//список всех, кто атакует корабль 


	cargomanager *crgmgr;//менеджер грузового отсека

	///слоты под орудия 
	int wslot;//сколько слотов под орудия
	vector<turret*>weapons;
	// turret *weapons[10];
	turret *weapon;//временная переменная

	float totalDPS;
	float totalVolley;//сумма урона от всех пушек


	int autopilot;//в каком режиме автопилот
	vector<int> a_systems;//системы для автопилота

	//int state;//что делает корабль 0-стоит,1-летит
	states state;

	warpstatus warpengine;//в каком режиме двигатели

	//float scale;//маштаб кораблика(зависит от корпуса)
	float alpha;//при посадке альфа постепенно уменьшается
	float newdir;
	float testval1;
	float testval2;
	float testval3;
	float engrad;//отвечает за положение эффекта от двигателя

	float sensorrange;//дальность захвата цели

	float attackradius;//радиус орбиты для автопилота
	float maxattackradius;//радиус орбиты для автопилота максимальный

	bool prmlock;//сбрасывет скорость при повороте
	bool smoke;//рисовать ли след от двигателя

	float warptime;
	float wrpt1;
	bool warponse;

	float itempuckuprad;//радиус подбора вещей
	float tractorradius;//радиус тягового луча
	float tractorpower;//мощность тягового луча в кг

	//bool underAttack;//находится ли корабль под огнём. перенёс в dyn
	float attackTimer;//время флага агрессии, пока будет 30 сек.
	float attacktim1;//

	//bool firstAttack;//флаг, отвечает за нанесение урона кораблю, если на нём самом нет флага+ если нет флага underAttack на цели игрока.
	float firstAttackTim;//время невозможности посадки составляет 15 сек
	float firstAttacktim1;

	float acc;//коф ускорения(зависит от двигателя, но меньше maxspeed)

	pilotctr *pilot;//кто управляет кораблем

	shared_ptr<dynamic > obj;//кораблик



	ship(int sysid, hull *shiphull);
	~ship();
	void Update();
	void Render();
	void FlyTo(float x, float y);//куда полететь кораблю
	void DropTarget();//освобождает цель
	void Fire();//дать команду на стрельбу
	void TargetOperations();//действия с целью
	void WeaponUpdate();//обновляем орудия
	void SetTrgToWeap();//передать цель всеморудиям
	void SetOneTrgToWeap(int weaponid);//передать цель орудиям
	void GetWeaponDPS();//посчитать увс от пушкек
	void RecalculateVariables();//пересчет всех бонусов для корабля

	bool SetTarget(std::weak_ptr<dynamic> target);

	void Damage(float e, float k, float t, float r);

	void WarpOn(int nextsys);//запуск двигателя для перемещения в другую систему
	void WarpRun();//запуск двигателя для перемещения в другую систему

	bool InstallEngine(engine *shipengine);
	bool InstallWeapon(turret *weapon);
	bool RemoveWeapon(int id);//убираем орудие по индексу слота
	bool RemoveEngine();//убираем двигатель

	void UpgradeHull();//пересчет значений корпуса
	void CheckMass();//пересчет веса корабля при обновлении корпуса и операций с грузовым отсеком

	void FirstAttack();//функция проверки и активации таймера аттаки на неагресивную цель

	void FullLevelUp(int lvl);//повышаем уровень всего корабля и установленных модулей

	bool PickItem(cargo *itm);//поднять вещь на борт
	void SetItem(cargo *itm);//принудительная загрузка в груз отсек
	void DropItem(int id);//сброс вещи
	void ScanForItems();//забирает ближайшие к кораблю вещи

	void AddAggressiveToList(std::weak_ptr<dynamic> attacker);//добавляет атакующего врага в список



	//упрощенные расчеты
	void FastUpdate(float dt);//приблизительное обновление движения при отсутствии игрока в секторе
	void F_MoveTo(float dt);


	//коллизии
	void CalculaceCollision();
	void PozTest();//проверка пересечения корабля с другими кораблями в тек. координате.
	void PatchCorr();//корректироква орбиты

	//комманды для бота
	bool GetNearlestTarget();//получаем ближайшую цель из списка agressive
	bool MoveToNearlestAggr();//двигаться к ближайшей агрессивной цели


protected:



	void MoveTo();//для облегчения поиска кода перенес каждое действие в отдельную функцию


	void AggressiveActive();//функция активации агрессивного флага военных действий
	void AggressiveTimer();

	void FirstAttackTimer();


	void ResetSpeed();//установить нормальную скорость


	float centerx;//центр корабля по оси Х, используется для перемещения точек крепления на корабле
	float centery;//центр по оси У

	float dist;

	float acceleration;//ускорение корабля

	//стандартные переменные исп. для повышения уровня
	float d_scale;
	float d_maxhp;

	float d_explres;
	float d_kinres;
	float d_termres;
	float d_radiores;

	float d_sensorrange;
	float d_mass;

	bool autoflight;//автополет
	bool go_to_next_sys;
	int startsys;
	int sys_ind;



};



#endif