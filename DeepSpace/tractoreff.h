#ifndef TRACTOREFF_H
#define TRACTOREFF_H


#include "effect.h"

#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"

#include "dsanim.h"
#include "dsanimate.h"

#include "dyncore.h"
#include "Itemcore.h"



extern hgeSprite *tractorspr;

extern vector<cargo*> cargoobjects;
extern vector<shared_ptr<dynamic>> dyn;

extern float point_dir2(float x1,float y1,float x2,float y2);
extern float point_distanse(float x1,float y1,float x2,float y2);

class tractor:public effect
{
public:
	int alpha;
	float dx;
	float dy;
	shared_ptr<dynamic> shp;//кто запустил
	cargo *trg;// куда полетел

	hgeSprite *spr;

	tractor(float dx,float dy,cargo *trg,int sysid);
	tractor(shared_ptr<dynamic> shp,cargo *trg,int sysid);
	~tractor();

	void Update();
	void Render();

protected:
	float timer1;
};

#endif