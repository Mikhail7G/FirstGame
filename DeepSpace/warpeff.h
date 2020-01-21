#ifndef WARPEFF_H
#define WARPEFF_H

#include "effect.h"

#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"

#include "dsanim.h"
#include "dsanimate.h"

extern HANIM    *animportal[];

class warpportal: public effect
{
public:

	float effdir;//направление эффекта


    warpportal(float x,float y,float lifetime,int sysid);//через анимации
	~warpportal();

	void Update();
	void Render();

protected:
	float timer0;//время активации эффекта
	float timer1;//время работы портала
	int type;// 0 -частицами, 1 - анимацией
	int state;//0-подготовка 1-циклично

	hgeAnim *init;
	hgeAnim *runing;

};



#endif