#include "gamer.h"


player::player()
{
	camspeed=300;
	PlayerShip=0;
	camlock=false;

	lefHUD=false;
	cancomm=true;
	renderRdr=false;
	renderMap=false;
	cargobay=false;
	spiphlp=false;

	/*PlayerRadar=new radar();
	PlayerMap=new spacemap();*/
	scalefactor=10;

	
	ex=0;
	debugmenu=0;
	levelupvar=10;
};

player::~player()
{

};

void player::ScangeMap(int _sysid)
{
	PlayerSys=_sysid;
	GameState=3;//тут идет загрузка новой системы
	SetCamPos(PlayerShip->x,PlayerShip->y);
};

void player::Update()
{
	KeyInput();
	ShipOperations();

};

void player::KeyInput()
{
	//управление камерой
	if (PlayerMapGUI->lockkeyboard == false)
	{

		if ((hge->Input_GetKeyState(HGEK_UP)) || (hge->Input_GetKeyState(HGEK_W))){ yview -= camspeed*dt; camlock = false; };
		if ((hge->Input_GetKeyState(HGEK_DOWN)) || (hge->Input_GetKeyState(HGEK_S))){ yview += camspeed*dt; camlock = false; };
		if ((hge->Input_GetKeyState(HGEK_LEFT)) || (hge->Input_GetKeyState(HGEK_A))){ xview -= camspeed*dt; camlock = false; };
		if ((hge->Input_GetKeyState(HGEK_RIGHT)) || (hge->Input_GetKeyState(HGEK_D))){ xview += camspeed*dt; camlock = false; };
		if ((hge->Input_GetKeyState(HGEK_SHIFT))){ camspeed = 900; }
		else{ camspeed = 300; };
	};

	if(hge->Input_KeyUp(HGEK_SPACE))
	{ 
	   GPAUSED=!GPAUSED;
	};

	if(hge->Input_KeyUp(HGEK_Q))//левая панель
	{ 
		PlayerCombatGUI->Show();
	};

	if(hge->Input_KeyUp(HGEK_R))//Радар
	{ 
		PlayerRadarGUI->Show();
	};

	if(hge->Input_KeyUp(HGEK_M))//Карта
	{ 
		PlayerMapGUI->Show();
	};

	if(hge->Input_KeyUp(HGEK_P))//Грузовой отсек
	{ 
		PlayerCargoGUI->Show();
	};

	if(hge->Input_KeyUp(HGEK_I))//Панель оснащения
	{ 
		PlayerShipGUI->Show();
	};

	if(hge->Input_KeyDown(HGEK_C))//Блокировка камеры
		{
			camlock=true;
		};
	if(hge->Input_KeyUp(HGEK_TAB))//сброс цели
	{ 
		PlayerShip->DropTarget();
		GameGUI->CloseAll();
	};

	if(hge->Input_KeyDown(HGEK_F))//СТРЕЛЬБА
		{
			PlayerShip->Fire();
		};

	if(hge->Input_KeyUp(HGEK_T))//Собрать все рядом
	{ 
		PlayerShip->ScanForItems();
	};

	/////ТЕСТОВЫЕ КНОПКИ
	


	if(hge->Input_KeyUp(HGEK_K))//уничтожить цель немедленно
	{ 
		LoadAmmo();
	};

	//Отладочное меню вынести в отдельную функцию

	if(hge->Input_KeyUp(HGEK_F1))
	{
		DebugInfo=!DebugInfo;
		debugmenu=0;
		DrawCollisionData = false;
	};

	if(hge->Input_KeyUp(HGEK_F2))
	{
		if(DebugInfo)
		{
			debugmenu=1;//меню повышения зарактеристик игрока или цели
		};
	};
	if(hge->Input_KeyUp(HGEK_F3))
	{
		if(DebugInfo)
		{
			debugmenu=2;//меню повышения создания различных объектов
		};
	};
	if(hge->Input_KeyUp(HGEK_F4))
	{
		if(DebugInfo)
		{
			debugmenu=3;//меню повышения создания различных объектов
		};
	};
	if (hge->Input_KeyUp(HGEK_F5))
	{
		if (DebugInfo)
		{
			debugmenu = 4;//меню вывода отладочной инфы по игровым объектам
		};
	};
	//////////////////////////
	if(hge->Input_KeyUp(HGEK_1))
	{ 
		if(DebugInfo)
		{
			switch (debugmenu)
			{
			case 1://повышаем уровень корабля
				PlayerShip->FullLevelUp(levelupvar);
			break;
			case 2:
				for(int i=0;i<100;i++)
				{
					std::shared_ptr<asteroid> ast(new asteroid(50,50,PlayerSys));
					//dyn.push_back(ast);	
					sectors.at(PlayerSys)->AddToList(ast);
				};
			break;
			case 3:
				if(!PlayerShip->target.expired())//проверяем наличие цели
				{
					auto trg=PlayerShip->target.lock();
					trg->kill=true;
				};
			break;
			case 4:
				DrawCollisionData = !DrawCollisionData;
			break;
			}
		};
	};
	if(hge->Input_KeyUp(HGEK_2))
	{ 
		if(DebugInfo)
		{
			switch (debugmenu)
			{
			case 1://повышаем уровень корабля цели
				if(!PlayerShip->target.expired())//проверяем наличие цели
					{
						auto trg=PlayerShip->target.lock();
						trg->FullLevelUp(levelupvar);
					};						
			break;
			case 2:	
			break;
			case 3:
				//for(int i=1;i<dyn.size();i++)//все динамические объекты
				//{
				//	dyn.at(i)->kill=true;
				//};
				for (int t = 0; t < sectors.at(PlayerSys)->objects.size(); t++)
				{
					if (sectors.at(PlayerSys)->objects.at(t)->type != 100)
					{
						sectors.at(PlayerSys)->objects.at(t)->Damage(9000, 9000, 9000, 9000);
					}
				};
			break;
			}
		};
	};

	if(hge->Input_KeyUp(HGEK_3))
	{ 
		if(DebugInfo)
		{
			switch (debugmenu)
			{
			case 3:
				for (int t = 0; t < sectors.at(PlayerSys)->cargoobjects.size(); t++)
				{

					if (sectors.at(PlayerSys)->cargoobjects.at(t)->state == 0)
					{
						sectors.at(PlayerSys)->cargoobjects.at(t)->kill = true;
					};
				};
			break;
			};
		};
	};

};



void player::Render()//тут действия, которе не требуют очень точной обработки, поэтому данная функция выполняется не во frame()
{

	if (!MouseOnGUI)
	{
		MouseOperations();
		PlanetOperations();
	};

	 WeaponIconRenderer();
	 DebugRender();

};

void player::DebugRender()
{
	if(DebugInfo)
	{
		switch (debugmenu)
		{
			case 0:
				 fnt->printf(xview+300, yview+5, HGETEXT_LEFT, "Debug mode\nF2-level UP menu\nF3-spawn menu\nF4-destroy menu\nF5-pbj. param render");
			break;
			case 1:
				 fnt->printf(xview+300, yview+5, HGETEXT_LEFT, "Level UP menu\nkey_1-lvl UP player ship full\nkey_2 lvl UP target ship");
			break;
			case 2:
				 fnt->printf(xview+300, yview+5, HGETEXT_LEFT, "Spawn menu\nkey_1-Asteroid rush");
			break;
			case 3:
				 fnt->printf(xview+300, yview+5, HGETEXT_LEFT, "Destroy menu\nkey_1-Kill target\nkey2-destroy obj. in space\nkey3-destroy all items in space");
			break;
			case 4:
				fnt->printf(xview + 300, yview + 5, HGETEXT_LEFT, "Obj.params\nkey_1-Coll. data");
				break;
		};
	};

};

void player::SetCamPos(float _x, float _y)
{
	xview=_x-ScreenWidth/2;
	yview=_y-ScreenHeight/2;

};

void player::ShipOperations()
{
	if(PlayerShip)
	{
		if(hge->Input_KeyDown(HGEK_LBUTTON))//управление движением корабля
		{	
			if (!MouseOnGUI)
			{
				PlayerShip->FlyTo(MouseX, MouseY);//куда полететь кораблю
				PlayerShip->autopilot = 0;//отключаем автопилот	 
			};
		}

		if(hge->Input_KeyDown(HGEK_MBUTTON))
		{
			 PlayerShip->autopilot++;
		};

		if(camlock)//Камера(захват за кораблем игрока)//если до цели далековато, то камера как бы висит за кораблем, делая обзор вперед
			       //а если подойдет близко, то переключится на координаты цели
		{
			if(PlayerShip->autopilot==0)//если автопилот выключен то следим за игроком, иначе следим за целью
			{
				if(point_distanse(PlayerShip->x,PlayerShip->y,PlayerShip->dx,PlayerShip->dy)>500)
				{
				  float camx=(PlayerShip->x)+cos(PlayerShip->dir)*camspeed;
				  float camy=(PlayerShip->y)+sin(PlayerShip->dir)*camspeed;
				  SetCamPos(camx,camy);
				}
				else
				{ 
					float camx=ScreenCenterX;
					float camy=ScreenCenterY;
					float camspeed=50;
					float cx,cy;
					cx=(ScreenCenterX-PlayerShip->dx)/10;
					cy=(ScreenCenterY-PlayerShip->dy)/10;
					camx-=cx*dt*camspeed;
					camy-=cy*dt*camspeed;
					SetCamPos(camx,camy);
				};
			}
			else
			{
				float camx=ScreenCenterX;
				float camy=ScreenCenterY;
				float camspeed=50;
				float cx,cy;
				cx=(ScreenCenterX-PlayerShip->x)/10;
				cy=(ScreenCenterY-PlayerShip->y)/10;
				camx-=cx*dt*camspeed;
				camy-=cy*dt*camspeed;
				SetCamPos(camx,camy);

			};
		};

		

		/////
	};

};

void player::MouseOperations()
{

	auto sec = sectors.at(PlayerSys)->objects;

	for (int i = 0; i < sec.size(); i++)
	{
		float dx = sec.at(i)->scale * 30;//иаштабный коэффициент выделения корабля( пока непопиксельная проверка наведения)

		if (mouse_on(sec.at(i)->x, sec.at(i)->y, MouseX, MouseY, dx, dx))//сначала наводим мышку на объект, берем его тип и выводим данные в зависимости от типа объекта
					{
			switch (sec[i]->type)
						{
						case -1:
							fnt->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, sec.at(i)->name);
						break;
						case 0:
							fnt->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, sec.at(i)->name);
						break;
						case 1:
							fnt->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, sec.at(i)->name);
						break;
						case 100:
							fnt->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, "Игрок");
						break;
						};
						//тут обрабатываем захват мышкой объекта(берём в цель и передаем кораблю
			if (sec[i]->type == 100)//100 это игрок
			{				
			}
			else
			{	
				if (hge->Input_KeyUp(HGEK_RBUTTON))
				{		     
					trr = sec.at(i);
					if (!PlayerShip->SetTarget(sec.at(i)))//если невозможно захватить цель
						{
						radiusrenderer*rr;
						rr = new radiusrenderer(PlayerShip->sysid, PlayerShip->sensorrange, PlayerShip, sec.at(i));
						eff.push_back(rr);
						};
					};
				};
				break;//наводим только на 1 объект
			};//наведение мышки
	};

	auto itm = sectors.at(PlayerSys)->cargoobjects;//список вещей в системе
	for (int i = 0; i < itm.size(); i++)
	{
		if (mouse_on(itm.at(i)->x, itm.at(i)->y, MouseX + 5, MouseY + 5, 10, 10))//сначала наводим мышку на объект, берем его тип и выводим данные в зависимости от типа объекта
		{
			fnt->printf((MouseX), (MouseY)+20, HGETEXT_LEFT, itm.at(i)->name);

			if (hge->Input_KeyDown(HGEK_RBUTTON))
			{		
				PlayerShip->PickItem(itm.at(i));
			};
			break;
		};

	};

};





void player::MapTarget(int _sysid)
{
	NextSys=_sysid;
	PlayerShip->WarpOn(NextSys);
};

void player::WeaponIconRenderer()
{
	 //указатель выбранной цели
	 if(!PlayerShip->target.expired())//проверяем наличие цели
		{
			auto trg=PlayerShip->target.lock();
			ataico->RenderEx(trg->x,trg->y,0,0.8f,0.8f);

		};

	/*int p=-80;

	for(int i=0;i<PlayerShip->weapons.size();i++)
	{
		if(PlayerShip->weapons[i]>0)
		{
			if(!(PlayerShip->weapons[i]->target.expired()))
			{
				auto trr=(PlayerShip->weapons[i]->target.lock());

				if(PlayerShip->weapons[i]->shoot)
				{
					PlayerShip->weapons[i]->ico->RenderEx(trr->x+p,trr->y+40*(trr->scale),0,0.8f,0.8f);
					p+=20;
				};

			};
		};
	};*/

};

void player::PlanetOperations()
{
	auto pln = sectors.at(PlayerSys)->planetlist;

	for (int i = 0; i < pln.size(); i++)
	{
			/*float d;
			d = point_distanse(MouseX, MouseY, pln.at(i)->x, pln.at(i)->y);*/
		if (pln.at(i)->MouseTest())
			{
				PlanetInfo(pln.at(i));
				//fnt->printf((MouseX), (MouseY)+20, HGETEXT_LEFT, planetary.at(i)->name);
		};
	};
};

void player::PlanetInfo(planet *_pln)
{
	float scale = 0.6f;
	float size = planethlp->GetWidth() / 2 + 100;
	float rx = 0;
	float ry = 0;
	float delta = 200;

	if (_pln->x > ScreenCenterX)
	{
		rx = MouseX - size * scale;
	}
	else
	{
		rx = MouseX + size * scale;
	};
	if (_pln->y > ScreenCenterY)
	{
		ry = MouseY - size* scale;//координаты рендера таблички
	}
	else
	{
		ry = MouseY + size * scale;//координаты рендера таблички
	};


	planethlp->RenderEx(rx, ry, 0, scale, scale);
	_pln->spr->RenderEx(rx+140*scale, ry-120*scale, 0, scale / 3.0f);

	float texcoord = 120;

	mainf->printf(rx - 80 , ry - 90, HGETEXT_LEFT, _pln->name);
	switch (_pln->fraction)//кто живет
	{
	case 0:
		mainf->printf(rx - texcoord, ry - 20, HGETEXT_LEFT, "Жители: Нет");
		break;
	case 1:
		mainf->printf(rx - texcoord, ry - 20, HGETEXT_LEFT, "Жители: Люди");
		break;
	};
	mainf->printf(rx - texcoord, ry - 5, HGETEXT_LEFT, "Число жителей:%.1f тыс", _pln->population);
	switch (_pln->type)
	{
	case 0:
		mainf->printf(rx - texcoord, ry + 10, HGETEXT_LEFT, "Тип экономики: Нет");
		break;
	case 1:
		mainf->printf(rx - texcoord, ry + 10, HGETEXT_LEFT, "Тип экономики: Аграрная");
		break;
	case 2:
		mainf->printf(rx - texcoord, ry + 10, HGETEXT_LEFT, "Тип экономики: Промышленная");
		break;
	};
	switch (_pln->resourse)//богатство ресурсами
	{
	case 0:
		mainf->printf(rx - texcoord, ry + 25, HGETEXT_LEFT, "Ресурсы: Бедная");
		break;
	case 1:
		mainf->printf(rx - texcoord, ry + 25, HGETEXT_LEFT, "Ресурсы: Умеренная");
		break;
	case 2:
		mainf->printf(rx - texcoord, ry + 25, HGETEXT_LEFT, "Ресурсы: Средняя");
		break;
	case 3:
		mainf->printf(rx - texcoord, ry + 25, HGETEXT_LEFT, "Ресурсы: Богатая");
		break;
	case 4:
		mainf->printf(rx - texcoord, ry + 25, HGETEXT_LEFT, "Ресурсы: Богатейшая");
		break;
	};

};


bool player::LoadAmmo()
{
	int all_ok=0;//отвечает за зарядку всех типов орудий на корабле
	auto shp = PlayerShip;
	auto crg = shp->crgmgr->crg;//получаем список всех вещей в кузове

	for (int i = 0; i < crg.size(); i++)
	{
		if (crg.at(i)->type == 3)//заряжаем снаряд в орудие
		{
			for (int t = 0; t < shp->weapons.size(); t++)
			{
				bullcont *cnt;
				cnt = dynamic_cast<bullcont*>(shp->crgmgr->crg.at(i));//преобразуем тип вещи в контейнер снаряда
				if (shp->weapons.at(t)->SetBullet(cnt->GetBull()))//если снаряд подходит то
				{
					all_ok++;
				}
				else
				{
					
				}

			};
		};
	};

	if (all_ok==shp->weapons.size())
	{
		shp->scharge_flag1 = true;
		return true;
	}
	else
	{
		shp->scharge_flag1 = false;
		return false;
	};
};