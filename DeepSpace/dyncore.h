#ifndef DYNCORE_H
#define DYNCORE_H
#include <vector>
#include "dsanim.h"
#include "dsanimate.h"
#include <memory>

using namespace std;

extern int GlobalDynObj;


extern bool DrawCollisionData;

static int Total=0;//всего динамических объектов



class dynamic
{
public:
	 float x;//координаты объекта, для всех общие.
	 float y;
	 float dx;
	 float dy;//куда полетит объект
	 float dir;//направление объекта
	 int id;
	 int itemlevel;//уровень вещи
	 bool kill;
	 bool visible;//видим ли объект в мире
	 char *name;//имя объекта
	 int sysid;//в какой системе объект
	 int nextsys;//куда полетит объект
     int type;//тип объекта, 0-астероид,1-корабль(игрок 100) >0-не колизионные объекты!
	 int fraction;//кому принадлежит 0-мусор,1-люди,2-агрессивные роботы
	 float radius;//радиус объекта(для выделения и столкновений)
	 float sigradius;//реальный радиус объекта
	 float hp;//очки жизни
	 float maxhp;//максимально брони
	 float speed;//скорость объекта
	 float maxspeed;//максимально возможная
	 float syndist;//расстояние до центра сектора
	 float mass;//масса объекта
	 float cargomass;//масса установленных вещей и масса груз отсека

	 float scale;//маштаб объекта

	 float rotatespeed;//скорость поворота

	 /////Параметры брони корабля
	 float explres;
	 float kinres;
	 float termres;
	 float radiores;
	 float EXParmor;//потенциальная броня с учетом сопротивлений

	 bool underAttack;//находится ли корабль под огнём.
	 bool firstAttack;//флаг, отвечает за нанесение урона кораблю, если на нём самом нет флага+ если нет флага underAttack на цели игрока.
	

	 vector<std::weak_ptr<dynamic>>collisions;//проверка столкновения с ближайшими объектами


	 ///для отладки
	 bool scharge_flag1 = true; //для бота, показывает все ли орудия заряженны


	dynamic();
	virtual ~dynamic();
	virtual void Update();
	virtual void Render();
	virtual void Damage(float e,float k,float t,float r);
	virtual void FirstAttack();//функция проверки и активации таймера аттаки на неагресивную цель ДЛЯ кораблей
	virtual void FullLevelUp(int lvl);//повышаем уровень объекта
	virtual void FastUpdate(float dt);//функция обновления объектов за пределами системы игрока
	int GetTotal();

	//обработка столкновений
	void AddCollisionTest(std::weak_ptr<dynamic> col);//добавляем объект проверки столкновений
	virtual void CalculaceCollision();//расчет столкновений


};



#endif