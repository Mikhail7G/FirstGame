#include "shipsupply.h"

shipsinfo::shipsinfo(player *_plr)
{
	plr = _plr;
	back = shipinfospr;

	pozx = 0;
	pozy = 0;
	loadmen = false;
	loadmenlock = false;
	layer = -1;//0-начальный слой. 1-слой выбора снарядов 2-выбор снаряда 3-слот двигателя
	lastwslot = -1;
	lastbullslot = -1;

	engx = 0;
	engy = 0;

	scalefactor = 10;

};

shipsinfo::~shipsinfo()
{

};

void shipsinfo::Render()
{
	RenderMain();
	CreateLoadMenu(lastid);
	MouseOperations();
};

void shipsinfo::RenderMain()
{
	auto pship = plr->PlayerShip;

	pozx = xview + ScreenWidth / 2 - 100;//положение на экране
	pozy = yview + ScreenHeight / 2;

	/*float slotx[10];
	float sloty[10];*/

	engx = pozx + 200;
	engy = pozy - 160;

	slotx[0] = pozx - 29; sloty[0] = pozy - 122;
	slotx[1] = pozx + 41; sloty[1] = pozy - 122;
	slotx[2] = pozx - 115; sloty[2] = pozy - 63;
	slotx[3] = pozx + 115; sloty[3] = pozy - 63;
	slotx[4] = pozx - 125; sloty[4] = pozy + 10;
	slotx[5] = pozx + 125; sloty[5] = pozy + 10;
	slotx[6] = pozx - 103; sloty[6] = pozy + 86;
	slotx[7] = pozx + 103; sloty[7] = pozy + 86;
	slotx[8] = pozx - 29; sloty[8] = pozy + 125;
	slotx[9] = pozx + 41; sloty[9] = pozy + 125;


	back->RenderEx(pozx, pozy, 0, 1, 1);//подложка интерфейса
	pship->shiphull->ico->RenderEx(pozx, pozy, 0, 1, 1);//корпус корабля в центральной части

	if (MouseTest())
	{
		layer = 0;
	}
	else
	{
		layer = -1;
	};

	for (int i = 0; i<pship->wslot; i++)//рисуем слоты под оружие
	{
		cargobayslot->Render(slotx[i], sloty[i]);

		if (i<pship->weapons.size())//рисуем установленное оружие
		{
			if (!pship->weapons.at(i)->bull)
			{
				wpt[0]->RenderEx(slotx[i], sloty[i], 0, 0.5f, 0.5f);
			};
			pship->weapons.at(i)->ico->Render(slotx[i], sloty[i]);

			if (mouse_on(slotx[i], sloty[i], MouseX, MouseY, 25, 25))
			{
				layer = 1;
				lastwslot = i;

				WeaponInfo();//показ инфы об орудии
			};
		};

	};

	//слот с двигателем


	cargobayslot->Render(engx, engy);

	if (plr->PlayerShip->shipengine>0)
	{
		plr->PlayerShip->shipengine->ico->Render(engx, engy);
	};

	if (mouse_on(engx, engy, MouseX, MouseY, 25, 25))
	{
		layer = 3;
		EngInfo();
	};


	if (mouse_on(pozx, pozy, MouseX, MouseY, 50, 50))//наведение на корпус
	{
		if (!loadmen)
		{
			HullInfo();
		};
	};
};

void shipsinfo::CreateLoadMenu(int _id)
{
	int id = _id;
	float t_pozy = 55;
	auto pship = plr->PlayerShip;

	if (id<pship->weapons.size())//заражяем снаряд только в отсек у устаеновленным орудием
	{
		if (loadmen)
		{
			//cargobayslot->Render(slotx[id],sloty[id]-50);
			for (int i = 0; i<pship->crgmgr->crg.size(); i++)
			{
				if (pship->crgmgr->crg.at(i)->type == 3)//если нашли снаряд в карго то
				{
					cargobayslot->Render(slotx[id], sloty[id] - t_pozy);
					pship->crgmgr->crg.at(i)->ico->Render(slotx[id], sloty[id] - t_pozy);

					if (mouse_on(slotx[id], sloty[id] - t_pozy, MouseX, MouseY, 25, 25))
					{
						layer = 2;
						lastbullslot = i;

						BulletInfo();
					};
					t_pozy += 55;
				};
			};

		};
	};
};

void shipsinfo::MouseOperations()
{
	auto pship = plr->PlayerShip;

	if (hge->Input_KeyDown(HGEK_RBUTTON))
	{
		switch (layer)//в зависимости от слоя разные действия
		{
		case 0:
			break;
		case 1://снимаем орудие
			if (pship->weapons.size()>lastwslot)
			{
				pship->RemoveWeapon(lastwslot);
			};
			break;
		case 3://действие с двигателем
				//pship->RemoveEngine();//только на планете
			break;
		}
	};
	if (hge->Input_KeyDown(HGEK_LBUTTON))
	{
		switch (layer)//в зависимости от слоя разные действия
		{
		case 0:
			loadmen = false;
			break;
		case 1://открывем меню загрузки снарядов в орудие
			loadmen = !loadmen;
			lastid = lastwslot;
			break;
		case 2://установка снаряда в орудие
			shared_ptr<bullet> pr;
			bullcont *cnt;
			cnt = dynamic_cast<bullcont*>(pship->crgmgr->crg.at(lastbullslot));

			pship->weapons.at(lastid)->SetBullet(cnt->GetBull());
			loadmen = false;
			break;
		}
	};

};


void shipsinfo::Show()
{
	render = !render;
};


bool shipsinfo::MouseTest()
{
	hgeRect *rr = new hgeRect();
	back->GetBoundingBoxEx(pozx, pozy, 0, 1, 1, rr);
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

void shipsinfo::WeaponInfo()
{
	auto pship = plr->PlayerShip->crgmgr;//получаем менеджер инвентаря корабля игрока

	float dx;
	float dy;
	dx = ScreenWidth / 2 + xview + 300;
	dy = ScreenHeight / 2 + yview - 100;

	for (int i = 0; i<pship->shipwpn.size(); i++)
	{
		if (lastwslot<pship->shipwpn.size())
		{
			turret *wpn;
			wpn = dynamic_cast<turret*>(pship->shipwpn.at(lastwslot));

			//	dynhlp->GetText(pship->shipwpn.at(lastwslot)->description);

			dyntxt->Render(dx, dy - 70, 8, 15);

			wpn->ico->Render(dx, dy - 100);
			mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "Имя:%s", wpn->name);
			mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "Дальность:%1.0f", ((wpn->optimal) + (wpn->fireradius)) / scalefactor);
			mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "Перезардка кассеты:%1.0f сек", wpn->reloadtimer);
			mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "Скорострельность:%0.1f сек", wpn->ammoreload);
			mainf->printf(dx - 130, dy - 10, HGETEXT_LEFT, "Разрешение сенсора:%1.0f", wpn->sigradius);
			mainf->printf(dx - 130, dy + 5, HGETEXT_LEFT, "Поворот:%0.1f град/с", (wpn->tracking) / 3.14f * 180);
			mainf->printf(dx - 130, dy + 20, HGETEXT_LEFT, "Множитель калибра:%0.1f", (wpn->damagemod));
			mainf->printf(dx - 130, dy + 35, HGETEXT_LEFT, "УВС:%0.01f Залп:%0.01f", wpn->DPS, wpn->alphastrike);
			//	mainf->printf(dx-130,dy+50, HGETEXT_LEFT,"%s",(dynhlp->newdescr));

			mainf->printf(dx + 30, dy - 115, HGETEXT_LEFT, "Уровень:%i", wpn->itemlevel);
			mainf->printf(dx + 30, dy - 100, HGETEXT_LEFT, "Масса:%1.0f", wpn->mass);
		};
	};


};

void shipsinfo::BulletInfo()
{
	auto pship = plr->PlayerShip->crgmgr;//получаем менеджер инвентаря корабля игрока

	float dx;
	float dy;
	dx = ScreenWidth / 2 + xview + 300;
	dy = ScreenHeight / 2 + yview - 100;

	shared_ptr<bullet> pr;
	bullcont *cnt;
	cnt = dynamic_cast<bullcont*>(pship->crg.at(lastbullslot));

	pr = cnt->GetBull();//получаем снаряд с его характеристиками

	//dyntxt->GetText(pr->description);

	dyntxt->Render(dx, dy - 70, 3, 15);

	pr->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "Имя:%s", pr->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "Урон К:%1.0f В:%1.0f Т:%1.0f Р:%1.0f", pr->Kdmg, pr->Edmg, pr->Tdmg, pr->Rdmg);
	mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "Количество :%i", pr->totalCount);
	//mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "%s", dyntxt->newdescr);


};

void shipsinfo::HullInfo()
{
	float dx;
	float dy;
	dx = ScreenWidth / 2 + xview + 300;
	dy = ScreenHeight / 2 + yview - 100;

	dyntxt->Render(dx, dy - 70, 10, 15);

	plr->PlayerShip->GetWeaponDPS();

	plr->PlayerShip->shiphull->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "Имя:%s", plr->PlayerShip->shiphull->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "Прочность:%1.0f", plr->PlayerShip->hp);
	mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "Скорость:%1.0f", plr->PlayerShip->maxspeed);
	mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "Масса:%1.0f", plr->PlayerShip->mass);
	mainf->printf(dx - 130, dy - 10, HGETEXT_LEFT, "Дальность сенсора:%1.0f", plr->PlayerShip->sensorrange / scalefactor);
	mainf->printf(dx - 130, dy + 5, HGETEXT_LEFT, "Сигнатура:%1.0f", plr->PlayerShip->sigradius);
	mainf->printf(dx - 130, dy + 20, HGETEXT_LEFT, "Урон в секунду:%1.0f", plr->PlayerShip->totalDPS);
	mainf->printf(dx - 130, dy + 35, HGETEXT_LEFT, "Урон за залп:%1.0f", plr->PlayerShip->totalVolley);
	mainf->printf(dx - 130, dy + 50, HGETEXT_LEFT, "Сопротивление В:%1.0f К:%1.0f Т:%1.0f Р:%1.0f", plr->PlayerShip->explres * 100.0f, plr->PlayerShip->kinres * 100.0f, plr->PlayerShip->termres * 100.0f, plr->PlayerShip->radiores * 100.0f);
	mainf->printf(dx - 130, dy + 65, HGETEXT_LEFT, "Дальность тягового луча :%1.0f", plr->PlayerShip->tractorradius / scalefactor);
	mainf->printf(dx - 130, dy + 80, HGETEXT_LEFT, "Мощность тягового луча :%1.0f Т", plr->PlayerShip->tractorpower);

	mainf->printf(dx + 30, dy - 115, HGETEXT_LEFT, "Уровень:%i", plr->PlayerShip->shiphull->itemlevel);
};

void shipsinfo::EngInfo()
{
	if (plr->PlayerShip->shipengine > 0)
	{

		float dx;
		float dy;
		dx = ScreenWidth / 2 + xview + 300;
		dy = ScreenHeight / 2 + yview - 100;

		dyntxt->Render(dx, dy - 70, 4, 15);

		plr->PlayerShip->shipengine->ico->Render(dx, dy - 100);
		mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "Имя:%s", plr->PlayerShip->shipengine->name);
		mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "Тяга:%1.0f", plr->PlayerShip->shipengine->speed);
		mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "Импульс:%1.0f", plr->PlayerShip->shipengine->impulse);
		mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "Дальность прыжка:%0.1f св. год", plr->PlayerShip->shipengine->warprange / 10000);

		mainf->printf(dx + 30, dy - 115, HGETEXT_LEFT, "Уровень:%i", plr->PlayerShip->shipengine->itemlevel);
	};

};