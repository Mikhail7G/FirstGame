#include "radiushelp.h"

radiusrenderer::radiusrenderer(int _sysid,float _x,float _y,float _rad,shared_ptr<dynamic> _shp1)
{
	sysid=_sysid;
	dx=_x;
	dy=_y;
	rad=_rad;
	timer1=1.5f;
	alpha=255;
	shp1=_shp1;
	spr=new hgeSprite(*fail1spr);
};

radiusrenderer::radiusrenderer(int _sysid,float _rad,shared_ptr<dynamic> _shp0,shared_ptr<dynamic> _shp1)
{
	sysid=_sysid;
	rad=_rad;
	shp0=_shp0;
	shp1=_shp1;
	timer1=1.5f;
	alpha=255;
	spr=new hgeSprite(*fail1spr);
};

radiusrenderer::~radiusrenderer()
{
	hge->System_Log("RADIO Eff_free");
	delete spr;
};

void radiusrenderer::Render()
{
	dx=shp0->x;
	dy=shp0->y;

	float dir;
	dir=point_dir2(shp1->x,shp1->y,dx,dy);
	float dist;
	dist=point_distanse(dx,dy,shp1->x,shp1->y);

	spr->RenderEx(dx,dy,dir,1,0.1f);
	spr->SetTextureRect(0,0,dist,64);
	spr->SetColor(ARGB(alpha,255,255,255));
	alpha-=10*dt;

	fnt->printf(shp1->x,shp1->y-50, HGETEXT_LEFT,"%1.0f",dist/10);

	hgeTools->RenderCircumference(dx,dy,rad,100,ARGB(255,255,0,0),0,M_PI*2);


};

void radiusrenderer::Update()
{
	timer1-=1*dt;
	if(timer1<0)
	{
		kill=true;
	};


};