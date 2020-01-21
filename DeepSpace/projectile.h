#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <vector>
#include "dyncore.h"
#include <hge.h>
#include "cmath"
#include <memory>
#include "dsanim.h"
#include "dsanimate.h"
#include "bullets.h"
#include "warship.h"


extern HGE *hge;
extern float dt;

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);
extern bool mouse_on(float x,float y,float mx,float my,float h,float w);



class projectile: public bullet
{
public:
	projectile(hgeSprite *spr,float Edmg,float Kdmg,float Tdmg,float Rdmg);
	~projectile();

	void Update();
	void Render();
	void SetTarget(std::weak_ptr<dynamic> target,float x,float y);//задает цель и запускает снаряд
	//void SetParient(std::weak_ptr<dynamic> parient);//устанавливаем хозяина снаряда
	
		virtual projectile* clone() const
		   {
			  return new projectile(*this);
		   }

		void FullLevelUp(int lvl)
		{
		};
		

};


#endif
