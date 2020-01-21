#include "bgcore.h"


worldbg::worldbg()
{
  x=0;
  y=0;
  randomtimer=1.0f;
  timer1=randomtimer;

  suns[0]->FireAt(syspozx[PlayerSys], syspozy[PlayerSys]);
  suns[1]->FireAt(syspozx[PlayerSys], syspozy[PlayerSys]);
  suns[2]->FireAt(syspozx[PlayerSys], syspozy[PlayerSys]);
};

worldbg::~worldbg()
{

};

void worldbg::RenderBG()
{
	dx=syspozx[PlayerSys];//рисуем фон по координатам из массива систем
	dy=syspozy[PlayerSys];

	mainspace->Render(x,y);
	mainspace->SetBlendMode(BLEND_COLORMUL);
	//star->Render(syspozx[PlayerSys],syspozy[PlayerSys]);

	suns[0]->Update(dt);
	//suns[0]->MoveTo(syspozx[PlayerSys], syspozy[PlayerSys]);
	suns[0]->Render();
	suns[1]->Update(dt);
	//suns[1]->MoveTo(syspozx[PlayerSys], syspozy[PlayerSys]);
	suns[1]->Render();
	suns[2]->Update(dt);
	//suns[2]->MoveTo(syspozx[PlayerSys], syspozy[PlayerSys]);
	suns[2]->Render();

	SpawnRandom();
};

void worldbg::UpdateBG()
{
	x=dx-((dx-ScreenCenterX)/1.1);
	y=dy-((dy-ScreenCenterY)/1.1);


};

void worldbg::SpawnRandom()//спавнит рандомно вспышки на экране
{
	timer1-=1*dt;
	if(timer1<0)
	{
		timer1=randomtimer;

		float rx;
		float ry;

		rx=ScreenCenterX+hge->Random_Float(-1000,1000);
		ry=ScreenCenterY+hge->Random_Float(-1000,1000);

		 explosion *expl;
		 expl=new explosion(bganimeffects[hge->Random_Int(0,1)],rx,ry,5,PlayerSys);
		 eff.push_back(expl);

	};
};

void worldbg::RestartSun()
{
	suns[0]->Stop();
	suns[1]->Stop();
	suns[2]->Stop();

	suns[0]->FireAt(syspozx[PlayerSys], syspozy[PlayerSys]);
	suns[1]->FireAt(syspozx[PlayerSys], syspozy[PlayerSys]);
	suns[2]->FireAt(syspozx[PlayerSys], syspozy[PlayerSys]);

};