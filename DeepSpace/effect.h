#ifndef EFFECT_H
#define EFFECT_H

#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"

#include "dsanim.h"
#include "dsanimate.h"

extern HGE *hge;
extern int PlayerSys;
extern float dt;
extern float ScreenCenterX;
extern float ScreenCenterY;
extern bool GPAUSED;

using namespace std;

extern bool mouse_on(float x,float y,float mx,float my,float h,float w);

class effect
{
public:
		hgeParticleSystem *eff;

		hgeAnim *img;//ссылка на то что загруженно, создается,удаляется при необходимости
		HANIM *anim;//что загружаем в память при старте игры

		int sysid;
		float lifetime;//время жизни
		float x;//позиция эффекта
		float y;
		float scale;//маштаб

		bool kill;

		effect();
		virtual ~effect();
		virtual void Update();
		virtual void Render();






};



#endif