#ifndef RADIUSHELP_H
#define RADIUSHELP_H


#include <vector>
#include <memory>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"
#include "hgeDTool.h"
#include "effect.h"
#include "dyncore.h"
#include <hgefont.h>



using namespace std;

extern hgeDTool *hgeTools;
extern hgeSprite *tractorspr;
extern hgeSprite *fail1spr;

extern hgeFont	*fnt;


extern float point_dir2(float x1,float y1,float x2,float y2);
extern float point_distanse(float x1,float y1,float x2,float y2);


class radiusrenderer: public effect
{
public:
	int alpha;
	float dx;
	float dy;
	float rad;

	hgeSprite *spr;

	shared_ptr<dynamic> shp0;
	shared_ptr<dynamic> shp1;

	radiusrenderer(int sysid,float x,float y,float rad,shared_ptr<dynamic> shp1);//неспользуется
	radiusrenderer(int sysid,float rad,shared_ptr<dynamic> shp0,shared_ptr<dynamic> shp1);
	~radiusrenderer();
	void Update();
	void Render();

protected:
	float timer1;




};


#endif