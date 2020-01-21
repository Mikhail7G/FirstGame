#include "playerradar.h"


dsradar::dsradar(player *_plr)
{
	plr = _plr;

	path = false;

	x = 0;
	y = 0;
	transform = 0;
	tesval1 = 0;
	borderx = 0;
	bordery = 0;
	dx = 0;
	dy = 0;
	dx1 = 0;
	dy1 = 0;
	scalefactor = 0.0136f;
	sysrad = 10000;
	back = hradar;
	sec_start = 0;
	sec_end = 0;


};

dsradar::~dsradar()
{

};

void dsradar::Show()
{
	render = !render;
};

void dsradar::Render()
{
	auto sec = sectors.at(PlayerSys)->objects;
	auto pln = sectors.at(PlayerSys)->planetlist;

	x = xview + 850;//положение на экране
	y = yview + 150;
	back->Render(x, y);
	star->RenderEx(x, y, 0, 0.05, 0.05);
	//дальше рисуем планеты

	for (int i = 0; i<pln.size(); i++)
	{
		
			float t;//перевод координат объекта в координаты радара
			float b;
			b = x - (syspozx[PlayerSys] - pln.at(i)->x)*scalefactor;
			t = y - (syspozy[PlayerSys] - pln.at(i)->y)*scalefactor;
			pln.at(i)->spr->RenderEx(b, t, 0, 0.02);
	};

	//а тут рисуем корабли
	for (int i = 0; i<sec.size(); i++)//все динамические объекты
	{
	
		if ((sec.at(i)->visible == true) && (sec.at(i)->syndist<sysrad))
		{
			float t;//перевод координат объекта в координаты радара
			float b;
			b = x - (syspozx[PlayerSys] - sec.at(i)->x)*scalefactor;
			t = y - (syspozy[PlayerSys] - sec.at(i)->y)*scalefactor;

			switch (sec.at(i)->type)
			{
			case -1:
				radarRED[0]->RenderEx(b, t, 0, 0.3f, 0.3f);
				break;
			case 0:
				radarRED[0]->RenderEx(b, t, 0, 0.3f, 0.3f);
				break;
			case 1:
				switch (sec.at(i)->fraction)
				{
				case 1://люди
					radarRED[1]->RenderEx(b, t, 0, 0.5f, 0.5f);
					break;
				}

				break;
			case 100:
				radarRED[4]->RenderEx(b, t, 0, 0.5f, 0.5f);
				break;
			};
		};
	};

	auto itm = sectors.at(PlayerSys)->cargoobjects;//вектор вещей

	for (int i = 0; i < itm.size(); i++)//все динамические объекты
	{
		float dist;
		dist = point_distanse(syspozx[PlayerSys], syspozy[PlayerSys], itm.at(i)->x, itm.at(i)->y);
		if (dist<sysrad)
		{
			float t;//перевод координат объекта в координаты радара
			float b;
			b = x - (syspozx[PlayerSys] - itm.at(i)->x)*scalefactor;
			t = y - (syspozy[PlayerSys] - itm.at(i)->y)*scalefactor;

			radarRED[3]->RenderEx(b, t, 0, 0.2f, 0.2f);
		};
	};



	//в самом конце рисуем рамку
	borderx = x - (syspozx[PlayerSys] - ScreenCenterX)*scalefactor;
	bordery = y - (syspozy[PlayerSys] - ScreenCenterY)*scalefactor;

	if (mouse_on(x, y, borderx, bordery, 150, 150))
	{
		border->RenderEx(borderx, bordery, 0, 0.3, 0.3);
	};


	if (MouseTest())
	{
		hge->Input_GetMousePos(&mdx, &mdy);
		mdx = (x - MouseX) / scalefactor;
		mdy = (y - MouseY) / scalefactor;

		if (hge->Input_KeyDown(HGEK_LBUTTON))
		{
			plr->SetCamPos(syspozx[PlayerSys] - mdx + ScreenWidth / 2, syspozy[PlayerSys] - mdy + ScreenHeight / 2);
			plr->camlock = false;
		};
	};
};


bool dsradar::MouseTest()
{
	hgeRect *rr = new hgeRect();
	back->GetBoundingBoxEx(x, y, 0, 1, 1, rr);
	if (rr->TestPoint(MouseX, MouseY))
	{
		delete rr;
		return true;
	}
	else
	{
		delete rr;
		return false;
	};
};