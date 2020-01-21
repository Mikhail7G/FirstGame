#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <vector>
#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"
#include <memory>
#include "rudacore.h"
#include "Itemcore.h"

#include "dsanim.h"
#include "dsanimate.h"

#include "dyncore.h"
#include "planets.h"
#include "sector.h"


#include "effect.h"
#include "explosion.h"

using namespace std;
extern HGE *hge;
extern float dt;

extern hgeFont	*fnt;

extern float syspozx[];//координаты секторов в космосу
extern float syspozy[];
extern const float lighting;
extern int AsteroidCount;
extern bool GPAUSED;

extern HANIM    *animeffects[];
extern HANIM    *animitem[];

extern vector<planet*> planetary;
extern vector<sector*> sectors;
extern vector<effect*> eff;
extern vector<shared_ptr<dynamic>> dyn;
extern vector<cargo*> cargoobjects;

extern float CollRad;

extern bool mouse_on(float x,float y,float mx,float my,float h,float w);
extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);
extern float slow_rotate(float speed,float dir,float newdir);

class asteroid: public dynamic
{	
	public:
	hgeSprite *spr;//картинка астероида, потом тут будет анимированный об

	hgeAnim *img;//ссылка на то что загруженно, создается,удаляется при необходимости
	HANIM *anim;//что загружаем в память при старте игры

	int drawtupe;// тип картинки 0-статичная 1-анимированная
	//float scale;//при приближении к солнцу атсероид уменьшается в размере, типо падает

	asteroid(float x,float y,int sysid);//рандомная картинка
	asteroid(float x,float y,int sysid,hgeSprite *spr);//создаем по координатам, индекс системы и его спрайтик
	asteroid(float x,float y,int sysid,HANIM *anim);//создаем по координатам, индекс системы и его анимированную картинку
	~asteroid();
	void Update();
	void Render();
	void Damage(float e,float k,float t,float r);
	void ShipCollision();//столкновение с кораблями
	void FastUpdate(float dt);//приблизительное обновление движения при отсутствии игрока в секторе

	//коллизии
	void CalculaceCollision();

	void FullLevelUp(int lvl)
	{
	};

	float cor_x;//значения для быстрых просчетов(рандомная точка возле солнца)
	float cor_y;
	bool go_around=true;//флаг, отыечает за однократный расчет координат улета

};


#endif