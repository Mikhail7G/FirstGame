#include "damagetext.h"


dmgtext::dmgtext(float _dmg,float _x,float _y,int _sysid)
{
	vel=60;
	dmg=_dmg;
	x=_x+hge->Random_Float(-vel,vel);
	y=_y+hge->Random_Float(-vel,vel);
	lifetime=3;
	sysid=_sysid;
	timer1=lifetime;

};

dmgtext::~dmgtext()
{
	hge->System_Log("DMG_TXT Killed");
};

void dmgtext::Update()
{
	timer1-=1*dt;
	y-=25*dt;
	if(timer1<0)
	{
		kill=true;
	};


};

void dmgtext::Render()
{
	fnt1->printf(x, y, HGETEXT_LEFT,"%1.0f",dmg);

};