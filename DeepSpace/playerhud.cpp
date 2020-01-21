#include "playerhud.h"


HUD::HUD(player *_plr)
{
	plr=_plr;
	spr=hud1;
	scalefactor=10;

	panx=(xview)+0;
	pany=(yview)+750;

	slotx[0]=panx+20;sloty[0]=pany-270;
	slotx[1]=panx+280;sloty[1]=pany-270;
	slotx[2]=panx+20;sloty[2]=pany-230;
	slotx[3]=panx+280;sloty[3]=pany-230;
	slotx[4]=panx+20;sloty[4]=pany-190;
	slotx[5]=panx+280;sloty[5]=pany-190;
	slotx[6]=panx+20;sloty[6]=pany-150;
	slotx[7]=panx+280;sloty[7]=pany-150;
	slotx[8]=panx+20;sloty[8]=pany-110;
	slotx[9]=panx+280;sloty[9]=pany-110;


};

HUD::~HUD()
{
	delete spr;
};

void HUD::CalculatePoz()
{
	panx=(xview)+0;
	pany=(yview)+750;

	slotx[0]=panx+20;sloty[0]=pany-270;
	slotx[1]=panx+280;sloty[1]=pany-270;
	slotx[2]=panx+20;sloty[2]=pany-230;
	slotx[3]=panx+280;sloty[3]=pany-230;
	slotx[4]=panx+20;sloty[4]=pany-190;
	slotx[5]=panx+280;sloty[5]=pany-190;
	slotx[6]=panx+20;sloty[6]=pany-150;
	slotx[7]=panx+280;sloty[7]=pany-150;
	slotx[8]=panx+20;sloty[8]=pany-110;
	slotx[9]=panx+280;sloty[9]=pany-110;

};

void HUD::Render()
{
	CalculatePoz();

	PlayerPanel();
	WeaponOperations();//действия над орудиями игрока
	TargetPanel();


};

void HUD::PlayerPanel()
{
	auto pship=plr->PlayerShip;

	hud1->RenderEx(panx,pany,0,0.6,0.6);
	mainf->printf(panx+120, pany-280, HGETEXT_LEFT,"Игрок");
	mainf->printf(panx+60, pany-250, HGETEXT_LEFT,"Прочность:%1.0f",pship->hp);
    mainf->printf(panx+60, pany-235, HGETEXT_LEFT,"Скорость:%1.0f",pship->speed);
	mainf->printf(panx+60, pany-220, HGETEXT_LEFT,"Режим АП:%i",pship->autopilot);
	mainf->printf(panx+60, pany-205, HGETEXT_LEFT,"Дальность сенсора:%1.0f",(pship->sensorrange)/scalefactor);
	mainf->printf(panx+60, pany-190, HGETEXT_LEFT,"Сигнатура корпуса:%1.0f",(pship->sigradius));

	if(pship->underAttack)
		{
			mainf->printf(panx+60, pany-175, HGETEXT_LEFT,"Вимание! Вы атакованны!");
		};
		if(pship->firstAttack)
		{
			mainf->printf(panx+60, pany-160, HGETEXT_LEFT,"Вы атаковали первым!");
		};

		if(mouse_on(panx+150, pany-205,MouseX,MouseY,10,80))//Отображение дальности сенсора
		{
			hgeTools->RenderCircumference(pship->x,pship->y,pship->sensorrange,100,ARGB(255,0,255,0),0,M_PI*2);
		};


		//if(mouse_on(panx+150, pany-235,MouseX,MouseY,10,80))//Включеие и выключение ограничителя оборотов на разворотах
		//{
		//	if(pship->prmlock)
		//	{
  //            fnt->printf(MouseX,MouseY+10, HGETEXT_LEFT,"Стабилизатор поворота:ON");
		//	}
		//	else
		//	{
		//	  fnt->printf(MouseX,MouseY+10, HGETEXT_LEFT,"Стабилизатор поворота:OFF");
		//	};

		//	if(hge->Input_KeyUp(HGEK_LBUTTON))
		//	{
		//	   if(!(pship->prmlock))
		//	   { 
		//			pship->prmlock=true; 					
		//		}
		//	   else
		//	   { 
		//			pship->prmlock=false;
		//	   };
		//	};
		//};

};

void HUD::WeaponOperations()
{
	auto pship=plr->PlayerShip;

	for(int i=0;i<pship->weapons.size();i++)
		{
			if(pship->weapons[i]->ammo>0)
				{
					fnt->printf(slotx[i]-10, sloty[i]-15, HGETEXT_LEFT,"%1.1f",pship->weapons[i]->timer2);
				}
				else
				{
					fnt->printf(slotx[i]-10, sloty[i]-15, HGETEXT_LEFT,"%1.1f",pship->weapons[i]->timer1);
				};
				if(mouse_on(MouseX,MouseY,slotx[i],sloty[i]-15,15,15))//наведение мышки на слоты с орудиями
				{
					float cx;
					float cy;
					cx=panx+430;
					cy=pany-150;

					//рисуем дальность стрельбы орудий
					hgeTools->RenderCircumference(pship->x,pship->y,pship->weapons[i]->optimal,100,ARGB(255,0,255,0),0,M_PI*2);
					hgeTools->RenderCircumference(pship->x,pship->y,pship->weapons[i]->optimal+pship->weapons[i]->fireradius,100,ARGB(255,255,246,0),0,M_PI*2);

					if (pship->weapons[i]->target.expired())//указатель на цель орудия
					{
					}
					else
					{
						auto trr = pship->weapons[i]->target.lock();
						hge->Gfx_RenderLine(pship->x, pship->y, trr->x, trr->y, ARGB(255, 255, 0, 0));
					};

					itemhelp->RenderEx(cx,cy,0,0.8,0.8);

					if(pship->weapons.at(i)->shoot==true)
					{
						wpt[0]->RenderEx(cx-1,cy-80,0,0.6,0.6);
					}
					else
					{
						wpt[1]->RenderEx(cx-1,cy-80,0,0.6,0.6);
					};

					pship->weapons[i]->ico->RenderEx(cx,cy-80,0,0.8,0.8);
					mainf->printf(cx-100,cy-60, HGETEXT_LEFT,"Имя:%s",pship->weapons[i]->name);
					mainf->printf(cx-100,cy-45, HGETEXT_LEFT,"Дальность:%1.0f",(pship->weapons[i]->optimal+pship->weapons[i]->fireradius)/scalefactor);
					//mainf->printf(cx-100,cy-30, HGETEXT_LEFT,"Возможная дальность:%1.0f",PlayerShip->weapons[i]->fireradius);
					if(pship->weapons[i]->bull)//если есть снаряд, то показывем уго урон
					{
						mainf->printf(cx-100,cy-30, HGETEXT_LEFT,"Урон снаряда:%1.0f,%1.0f,%1.0f,%1.0f",pship->weapons[i]->bull->Kdmg,pship->weapons[i]->bull->Edmg,pship->weapons[i]->bull->Tdmg,pship->weapons[i]->bull->Rdmg);
					}
					else
					{
						mainf->SetColor(ARGB(255,255,0,0));
						mainf->printf(cx-100,cy-30, HGETEXT_LEFT,"Незаряжен!");
						mainf->SetColor(ARGB(255,255,255,255));
					};
					mainf->printf(cx-100,cy-15, HGETEXT_LEFT,"Перезардка кассеты:%1.0f сек",pship->weapons[i]->reloadtimer);
					mainf->printf(cx-100,cy-0, HGETEXT_LEFT,"Скорострельность:%0.1f сек",pship->weapons[i]->ammoreload);
					mainf->printf(cx-100,cy+15, HGETEXT_LEFT,"Снаряд:%i",pship->weapons[i]->ammo);
					mainf->printf(cx-100,cy+30, HGETEXT_LEFT,"Разрешение сенсора:%1.0f",pship->weapons[i]->sigradius);
					mainf->printf(cx-100,cy+45, HGETEXT_LEFT,"Поворот:%0.1f град/с",pship->weapons[i]->tracking/3.14f*180);
					mainf->printf(cx-100,cy+60, HGETEXT_LEFT,"УВС:%0.01f Залп:%0.01f",pship->weapons[i]->DPS,pship->weapons[i]->alphastrike);
					mainf->printf(cx+30,cy-90, HGETEXT_LEFT,"%i",pship->weapons[i]->itemlevel);

					if(pship->weapons[i]->autofire)
					{
						mainf->printf(cx-100,cy-80, HGETEXT_LEFT,"Авто:ON");
					}
					else
					{
						mainf->printf(cx-100,cy-80, HGETEXT_LEFT,"Авто:OFF");
					};

					if(pship->weapons[i]->bull)//Информация о заряженном снаряде
					{
						
					}
					else
					{
						
					};

					if(hge->Input_KeyDown(HGEK_LBUTTON))//ручное управление орудиями.
					{
					  pship->SetOneTrgToWeap(i);
                      pship->weapons[i]->StartFiring();
					};
					if(hge->Input_KeyDown(HGEK_RBUTTON))//Переключение автострельбы
					{
                      pship->weapons[i]->autofire=!pship->weapons[i]->autofire;
					};
				};	
		};

};

void HUD::TargetPanel()
{
	auto pship=plr->PlayerShip;

	if(!pship->target.expired())//проверяем наличие цели
		{
			auto trg=pship->target.lock();

			panx1=(xview)+720;
			pany1=(yview)+750;

			float distanse = point_distanse(pship->x,pship->y,trg->x,trg->y);
      
			hud1->RenderEx(panx1,pany1,0,0.6,0.6);

			if(distanse > pship->sensorrange*0.7f)
			{
				mainf->printf(panx1+70, pany1-295, HGETEXT_LEFT,"Слабый сигнал!:далеко");
			};
			switch (trg->type)
			{
			case 0://для астероидов
				mainf->printf(panx1+120, pany1-280, HGETEXT_LEFT,trg->name);
				mainf->printf(panx1+60, pany1-250, HGETEXT_LEFT,"Прочность:%1.0f",trg->hp);
				mainf->printf(panx1+60, pany1-235, HGETEXT_LEFT,"Скорость:%1.0f",trg->speed);
				mainf->printf(panx1+60, pany1-220, HGETEXT_LEFT,"Расстояние:%1.0f",distanse/scalefactor);
				break;
			case 1://для кораблей
				mainf->printf(panx1+120, pany1-280, HGETEXT_LEFT,trg->name);
				mainf->printf(panx1+60, pany1-250, HGETEXT_LEFT,"Прочность:%1.0f %1.0f",trg->hp,(trg->hp*100/trg->maxhp));
				mainf->printf(panx1+60, pany1-235, HGETEXT_LEFT,"Скорость:%1.0f/%1.0f",trg->speed,trg->maxspeed);
				mainf->printf(panx1+60, pany1-220, HGETEXT_LEFT,"Расстояние:%1.0f",distanse/scalefactor);
				break;
			}
		};
	

};

bool HUD::MouseOn()
{
	if(plr->lefHUD)
	{
		hgeRect *rr=new hgeRect();
		hgeRect *rr1=new hgeRect();//не используется
		spr->GetBoundingBoxEx(panx,pany,0,0.6f,0.6f,rr);
		if(rr->TestPoint(MouseX,MouseY))
		{
			delete rr;
			delete rr1;
			return true;
		}
		else
		{
			delete rr;
			delete rr1;
			return false;
		};
	}
	else
	{
		return false;
	};

};