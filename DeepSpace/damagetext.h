#ifndef DAMAGETEXT_H
#define DAMAGETEXT_H

#include "effect.h"

#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include <hgefont.h>
#include "cmath"

extern hgeFont	*fnt;
extern hgeFont *mainf;
extern hgeFont *fnt1;


class dmgtext: public effect
{
public:
	float dmg;//сколько урона нанес

	dmgtext(float dmg,float x,float y,int sysid);
	~dmgtext();
	void Update();
	void Render();

protected:
	float timer1;
	float vel;
};


#endif