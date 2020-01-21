#include "Itemcore.h"


cargo::cargo()
{
	moving=false;
	timer1=5;
	canstak=false;
	count=0;
	slotid=0;

	sysid=-1;
	x=0;
	y=0;
	name="Ќет";
	description="«десь могла бы быть ваша реклама\0";
	state=0;
	kill=false;
	mass=0;
	hidekill=false;

	coreid+=1;
	zz=coreid;
	fraction=0;
	ItemDispread = 1;

	crgbox=cargobox;

};

void cargo::CreateAnim()
{
	box=new hgeAnim(crgbox,hgeAnim::PLAY_LOOP);//крутитс€ посто€нно
	box->RandomStart();
	box->renderspeed=7;
};

cargo::~cargo()
{
  hge->System_Log(" онтейнер уничтожен в системе:%i",sysid);	
  if(!hidekill)
  {
	  explosion *expl;//тут только пока анимицией, сделать возможность мен€ть на частицы
	  expl=new explosion(animeffects[2],x,y,5,sysid);
	  eff.push_back(expl);
	  delete box;
  }
  else
  {
	  delete box;
  };
  // delete box;

  ItemCount--;
};

void cargo::SetPoz(int _sysid,float _x,float _y)
{
	sysid=_sysid;
	x=_x;
	y=_y;
	dispread=150;
	speed=20;
	dx=x+hge->Random_Float(-dispread,dispread);
	dy=y+hge->Random_Float(-dispread,dispread);
	moving=true;
	timer1=5;
	state=0;
};

void cargo::SetFixedPoz(int _sysid,float _x,float _y)
{
	sysid=_sysid;
	x=syspozx[sysid]+_x;
	y=syspozy[sysid]+_y;
	state=0;
};

void Update()
{
};

void cargo::Render()
{
	box->RenderEx(x,y,0,1,1);
	box->Update();

	if(moving)
	{
		MoveCrg();
	};

};

void cargo::MoveCrg()
{
	if(sysid==PlayerSys)
	{
		if(timer1>0)
		{
			timer1-=1*dt;
			float cx,cy;
			cx=(x-dx)/10;
			cy=(y-dy)/10;
			x-=cx*dt*speed;
			y-=cy*dt*speed;
		}
		else
		{
			moving=false;
		};

	}
	else
	{
		x=x+hge->Random_Float(-dispread,dispread);
		y=y+hge->Random_Float(-dispread,dispread);
		moving=false;
	};

};

void cargo::Install()
{
	state=1;
	InitializeInside();
};

void cargo::InitializeSpace(int _sysid,float _x,float _y)
{
	CreateAnim();

	sysid=_sysid;
	x=syspozx[sysid]+_x;
	y=syspozy[sysid]+_y;


};

void cargo::InitializeInside()
{
	CreateAnim();

	state=1;
};

void cargo::ShipDrop(int _sysid,float _x,float _y)
{
	sysid=_sysid;
	x=_x;
	y=_y;
	dispread=150;
	speed=20;
	dx=x+hge->Random_Float(-dispread,dispread);
	dy=y+hge->Random_Float(-dispread,dispread);
	moving=true;
	timer1=5;
	state=0;

};

void cargo::TractorBeam(float _x,float _y)
{
	dx=_x+hge->Random_Float(-50,50);
	dy=_y+hge->Random_Float(-50,50);
	timer1=10;
	speed=10;
	moving=true;
};