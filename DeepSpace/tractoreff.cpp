#include "tractoreff.h"


tractor::tractor(float _dx,float _dy,cargo *_trg,int _sysid)
{
	dx=_dx;
	dy=_dy;
	trg=_trg;
	sysid=_sysid;
	lifetime=1.5f;
	timer1=lifetime;
	spr=new hgeSprite(*tractorspr);
	alpha=255;
};

tractor::tractor(shared_ptr<dynamic> _shp,cargo *_trg,int _sysid)
{
	shp=_shp;
	trg=_trg;
	sysid=_sysid;
	lifetime=1.5f;
	timer1=lifetime;
	spr=new hgeSprite(*tractorspr);
	alpha=255;
};

tractor::~tractor()
{
	hge->System_Log("Tractor_eff_free");
	delete spr;
};

void tractor::Render()
{
	float dir;
	dir=point_dir2(trg->x,trg->y,dx,dy);
	float dist;
	dist=point_distanse(dx,dy,trg->x,trg->y);

	//float dir;
	//dir=point_dir2(trg->x,trg->y,shp->x,shp->y);
	//float dist;
	//dist=point_distanse(shp->x,shp->y,trg->x,trg->y);

	spr->RenderEx(dx,dy,dir,1,0.1f);
	spr->SetTextureRect(0, 0, dist, 64);
	spr->SetColor(ARGB(alpha,255,255,255));
	alpha-=10*dt;

};

void tractor::Update()
{
	timer1-=1*dt;
	if(timer1<0)
	{
		kill=true;
	};

};