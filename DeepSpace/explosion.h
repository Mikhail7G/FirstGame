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

	explosion(hgeParticleSystem *eff,float x,float y,float lifetime,int sysid);//����� �������
	explosion(HANIM *anim,float x,float y,float lifetime,int sysid);//����� ��������
	~explosion();
	void Update();
	void Render();

protected:
	float timer1;
	int type;// 0 -���������, 1 - ���������

};



#endif