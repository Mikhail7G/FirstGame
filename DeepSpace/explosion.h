#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "effect.h"

#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"

#include "dsanim.h"
#include "dsanimate.h"


class explosion: public effect
{
public:

	explosion(hgeParticleSystem *eff,float x,float y,float lifetime,int sysid);//через частицы
	explosion(HANIM *anim,float x,float y,float lifetime,int sysid);//через анимации
	~explosion();
	void Update();
	void Render();

protected:
	float timer1;
	int type;// 0 -частицами, 1 - анимацией

};



#endif