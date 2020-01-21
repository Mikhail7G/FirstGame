#include "warpeff.h"

warpportal::warpportal(float _x,float _y,float _lifetime,int _sysid)
{
	x=_x;
	y=_y;
	lifetime=_lifetime;
	sysid=_sysid;
	state=0;
	timer1=lifetime;
	timer0=2;
	type=1;
	effdir=0;
	scale=1;

	init = new hgeAnim(animportal[0], hgeAnim::PLAY_ONCE);
	runing = new hgeAnim(animportal[1], hgeAnim::PLAY_LOOP);

};

warpportal::~warpportal()
{
	delete init;
	delete runing;
	hge->System_Log("WarpPort Killed");
};

void warpportal::Update()
{
	switch (state)
		{
		case 0:
			timer0-=1*dt;
			if(timer0<0)
			{
				state=1;
			};
		break;
		case 1:
			timer1-=1*dt;
			if(timer1<0)
			{
				kill=true;
			};
		break;
		};



};

void warpportal::Render()
{
	if(type==0)
	{
		eff->Update(dt);
		eff->Render();
	};
	if(type==1)
	{
		switch (state)
		{
		case 0:
			init->RenderEx(x, y, effdir+90.0f, scale, scale);
			init->Update();
			break;
		case 1:
			runing->RenderEx(x, y, effdir+90.0f, scale, scale);
			runing->Update();
			break;
		}
	};

};