#include "pradar.h"


radar::radar(player *_plr)
{
	plr=_plr;
	path=false;

	x=0;
	y=0;
    transform=0;
	tesval1=0;
	borderx=0;
	bordery=0;
	dx=0;
	dy=0;
	dx1=0;
	dy1=0;
	scalefactor=0.0136f;
	sysrad=10000;
	spr=new hgeSprite(*hradar);
 
};

void radar::Render()
{
	x=xview+850;//положение на экране
	y=yview+150;
	spr->Render(x,y);
	star->RenderEx(x,y,0,0.05,0.05);
	//дальше рисуем планеты

	for(int i=0;i<planetary.size();i++)
	{
		if(planetary.at(i)->sysid==PlayerSys)
		{
			float t;//перевод координат объекта в координаты радара
			float b;
			b=x-(syspozx[PlayerSys]-planetary.at(i)->x)*scalefactor;
			t=y-(syspozy[PlayerSys]-planetary.at(i)->y)*scalefactor; 
			planetary.at(i)->spr->RenderEx(b,t,0,0.03);

		};
	};

	//а тут рисуем корабли
	for(int i=0;i<dyn.size();i++)//все динамические объекты
	{
		if(dyn.at(i)->sysid==PlayerSys)
		{
			if((dyn.at(i)->visible==true)&&(dyn.at(i)->syndist<sysrad))
			{
				 float t;//перевод координат объекта в координаты радара
				 float b;
				 b=x-(syspozx[PlayerSys]-dyn.at(i)->x)*scalefactor;
				 t=y-(syspozy[PlayerSys]-dyn.at(i)->y)*scalefactor; 	

				 switch (dyn.at(i)->type) 
				 {
					 case -1:
							radarRED[0]->RenderEx(b,t,0,0.3f,0.3f);
					 break;
					 case 0:
							radarRED[0]->RenderEx(b,t,0,0.3f,0.3f);
					 break;
					 case 1:
							switch (dyn.at(i)->fraction)
							{
							case 1://люди
									radarRED[1]->RenderEx(b,t,0,0.5f,0.5f);
							break;
							}

					 break;
					 case 100:
							radarRED[4]->RenderEx(b,t,0,0.5f,0.5f);
					 break;
				 };
			};
		};
	};

	for(int i=0;i<cargoobjects.size();i++)//все динамические объекты
	{
		if((cargoobjects.at(i)->sysid==PlayerSys)&&(cargoobjects.at(i)->state==0))
		{
			float dist;
			dist=point_distanse(syspozx[PlayerSys],syspozy[PlayerSys],cargoobjects.at(i)->x,cargoobjects.at(i)->y);
			if(dist<sysrad)
			{
				float t;//перевод координат объекта в координаты радара
				float b;
				b=x-(syspozx[PlayerSys]-cargoobjects.at(i)->x)*scalefactor;
				t=y-(syspozy[PlayerSys]-cargoobjects.at(i)->y)*scalefactor; 	

				radarRED[3]->RenderEx(b,t,0,0.2f,0.2f);
			};
		};
	};



	//в самом конце рисуем рамку
	borderx=x-(syspozx[PlayerSys]-ScreenCenterX)*scalefactor;
	bordery=y-(syspozy[PlayerSys]-ScreenCenterY)*scalefactor; 	

	if(mouse_on(x,y,borderx,bordery,150,150))
	{
		border->RenderEx(borderx,bordery,0,0.3,0.3);
	};


	if(MouseOn())
	{
		hge->Input_GetMousePos(&mdx,&mdy);
		mdx=(x-MouseX)/scalefactor;
		mdy=(y-MouseY)/scalefactor;

		if(hge->Input_KeyDown(HGEK_LBUTTON))
		{
			plr->SetCamPos(syspozx[PlayerSys]-mdx+ScreenWidth/2,syspozy[PlayerSys]-mdy+ScreenHeight/2);
			plr->camlock=false;
		};
	};

};

void radar::ChangeMap()
{

};

bool radar::MouseOn()
{
	/*if(plr->PlayerRadar)
	{
		hgeRect *rr=new hgeRect();
		spr->GetBoundingBoxEx(x,y,0,1,1,rr);
		if(rr->TestPoint(MouseX,MouseY))
		{
			delete rr;
			return true;
		}
		else
		{
			delete rr;
			return false;
		};
	}
	else
	{
		return false;
	};*/
	return true;
};
