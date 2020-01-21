#include "explosion.h"


explosion::explosion(hgeParticleSystem *_eff,float _x,float _y,float _lifetime,int _sysid)
{
	eff=new hgeParticleSystem(*_eff);
	x=_x;
	y=_y;
	lifetime=_lifetime;
	sysid=_sysid;
	eff->FireAt(x,y);
	timer1=lifetime;
	type=0;
};

explosion::explosion(HANIM *_anim,float _x,float _y,float _lifetime,int _sysid)
{
	anim = _anim;
	img = new hgeAnim(anim,hgeAnim::PLAY_ONCE);

	x = _x;
	y = _y;
	lifetime = _lifetime;
	sysid = _sysid;
	timer1 = lifetime;
	type = 1;
};

explosion::~explosion()
{
	
	hge->System_Log("EXPL Killed");
	if(type==0)
	{
	delete eff;
	};
	if(type==1)
	{
		delete img;
	};
};

void explosion::Update()
{
	timer1 -= 1 * dt;
	if(timer1<0)
	{
		kill = true;
	};

};

void explosion::Render()
{
	if(type==0)
	{
		eff->Update(dt);
		eff->Render();
	};
	if(type==1)
	{
		img->RenderEx(x, y, 0, 1, 1);
		img->Update();
	};

};