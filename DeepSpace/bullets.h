#ifndef BULLETS_H
#define BULLETS_H
//базовый класс дл€ всех выпускаемых снар€дов

#include "dyncore.h"
#include <hge.h>
#include "cmath"
#include <memory>
#include "dsanim.h"
#include "dsanimate.h"
#include "effect.h"
#include "explosion.h"
#include "Itemcore.h"



extern HGE *hge;
extern float dt;

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);

extern vector<effect*> eff;


extern enum WeaponSize;

static int BULLID=0;


class bullet:  public dynamic
{
public:
		int totalCount;//количество снар€дов
		float dir;//направление полета
		float lifetime;//врем€ жизни

		int efftype;//тип эффекта 0-частицы, 1 -анимаци€

		float Edmg;//повреждени€ от 4 видов урона
		float Kdmg;
		float Tdmg;
		float Rdmg;

		float damagemod;//модификатор урона, передаетс€ от оруди€
		//как считаетс€ урон, урон=стандарт*дамагмод+бонус от модулей
		float critdamage;//урон, который зависит от крита(рандом)


		float hitchance;//
		float critchance;//шанс крита(у арты чаще критует)
		bool doublecrit;//дл€ арты увеличенный шанс крита
		bool oncourse;//попадет ли снар€д в цель, зависит от многих параметров оруди€ и самой пули

		char *name;//название снар€да
		char *description;//описание объекта

		///бонусы, вли€ющие на параметры орудий, все бонусы »ƒ”“ ¬ % !!!!!!!!!
		float fireradius_b;//бонус дальности стрельбы
		float optimal_b;//бонус оптимального рассто€ни€ стрельбы
		float sigradius_b;//бонус сигнатуры
		float tracking_b;//бонус скорости слежени€

		hgeAnim *img;//ссылка на то что загруженно, создаетс€,удал€етс€ при необходимости
		HANIM *anim;//что загружаем в пам€ть при старте игры
		hgeSprite *spr;//если не анимировнный снар€д
		hgeSprite *ico;//иконка снар€да
		hgeParticleSystem *effect;//эффект при попадании
		HANIM *animeff;//анимированный эффект, не частицы


		std::weak_ptr<dynamic> target;//цель снар€да
		std::weak_ptr<dynamic> parient;//кто стрельнул

		WeaponSize BSize;


		bullet();
		virtual ~bullet();
		virtual void SetTarget(std::weak_ptr<dynamic> target,float x,float y);//задает цель и запускает снар€д
		virtual void SetParient(std::weak_ptr<dynamic> parient);//устанавливаем хоз€ина снар€да

		 virtual bullet* clone() const//клонироване снар€да дл€ стрельбы из пушки
		   {
			  return new bullet(*this);
		   };

		void FullLevelUp(int lvl)
		{
		};
		

protected:
	int zz;




};



#endif