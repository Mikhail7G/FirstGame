#include "gamecore.h"


gameclass::gameclass()
{
	xview=-ScreenWidth/2+syspozx[0];//начальное положение камеры
    yview=-ScreenHeight/2+syspozy[0];
	camspeed=300;
	DebugInfo=false;//вывод отладочной инфы на F1

	GameGUI = new guictr();//контроллер всех ГУИ
	hgeTools=new hgeDTool();

	PlayerSysInBorder = true;

	GlobalMapScaleFactor = 0.003f;//коэффициент раземера карты(чем меньше, тем больше карта) 0.003 - самая маленькая(18 св.лет)
	Max_Systems = 40;

	upd_from = 0;
	upd_to = 1;
};

gameclass::~gameclass()
{

};

void gameclass::WorldUpdate()
{	//операции с камерой
	hge->Input_GetMousePos(&mx,&my);
	MouseX=mx+xview;
	MouseY=my+yview;

	cormx=MouseX-syspozx[PlayerSys];
	cormy=MouseY-syspozy[PlayerSys];
  
    ScreenCenterX=xview+ScreenWidth/2;//пересчет для нахождения центра экрана(для рисования ГУИ и пр)
    ScreenCenterY=yview+ScreenHeight/2;

	corcamx=ScreenCenterX-syspozx[PlayerSys];
	corcamy=ScreenCenterY-syspozy[PlayerSys];
	
	Player->Update();//обновляем игрока

	mainBG->UpdateBG();//обновление заднего фона для красоты

	UpdateVectors();//Обновление динамических объектов
	
	


};

void gameclass::WorldRender()
{
	Test1();//тесовая функция, частый вызов не так важен тут
	///////////////////////////////////

	 mainBG->RenderBG();//рисуем задний фон
	
	
     RenderVectors();//рисуем все динамические объекты на экране

	 hge->Gfx_SetTransform(-xview,-(yview),-(xview),-(yview),0,1,1);//движем камеру

	 Player->Render();
	 GameGUI->Render();//рисуем ГУИ игрока

	 if(DebugInfo)//вывод отладочной информации на F1
	 {
		 int total_dyn = 0;

		 for (int i = 0; i < sectors.size(); i++)
		 {
			 total_dyn += sectors.at(i)->objects.size();
		 };

		 int total_itm = 0;

		 for (int i = 0; i < sectors.size(); i++)
		 {
			 total_itm += sectors.at(i)->cargoobjects.size();
		 };
		 
		 float ups = 0;
		 ups = 1.0f / dt;

		 fnt->printf(xview + 5, yview + 5, HGETEXT_LEFT, "dt:%.4f\nUPS:%.1f\nFPS:%d\nMX:%.1f\nMY:%.1f\nDYN:%d/%d\nITM:%d/%d\nUpdate calls:%i/%i\nCall time:%0.5f", hge->Timer_GetDelta(),ups, hge->Timer_GetFPS(), MouseX, MouseY, total_dyn, dyn.size(), ItemCount, total_itm, sectors.at(PlayerSys)->objects.size(), sectors.at(PlayerSys)->cargoobjects.size(), Call_Time);
		 fnt->printf(xview+150, yview+5, HGETEXT_LEFT, "MX:%.1f\nMY:%.1f\nWX:%.1f\nWY:%.1f\nsys:%i",cormx,cormy,corcamx,corcamy,sectors.at(PlayerSys)->cur_col_obj);
	 };

	 //////////////////////////Контроллер атсероидов////////////
	 astspawner->Update();
};


void gameclass::ResourseLoad()//загрузка ресурсов, пока грузят все, потом по типу графики: облегченная и полная
{
	mainf=Mpack->GetFont("textf");//основной шрифт
	fnt1=Mpack->GetFont("textf");//шрифт урона
	star=Mpack->GetSprite("star01");
	mainspace=Mpack->GetSprite("spacem"); 
	//загружаем корабли
	animships[0] = new HANIM("data/ships/people1.ani");


	///da
	//анимированные эффекты
	animeffects[0]=new HANIM("data/effect/explosion1.ani");
	animeffects[1]=new HANIM("data/effect/sparks1.ani");
	animeffects[2] = new HANIM("data/effect/explosion2.ani");

	bganimeffects[0]=new HANIM("data/bg/star1.ani");
	bganimeffects[1]=new HANIM("data/bg/star2.ani");

	animportal[0]=new HANIM("data/portal/start.ani");
	animportal[1]=new HANIM("data/portal/run.ani");

	cargobox = new HANIM("data/items/box.ani");
	map_poz = new HANIM("data/hud/map_poz.ani");

	////иконки карты
	mapeffects[0] = new HANIM("data/map/g0.ani");

	
	//объекты космоса
	//asteroids[0]=Mpack->GetSprite("asteroid1");
	animitem[0]=new HANIM("data/asteroids/asteroid1.ani");//астероид 1
	animitem[1]=new HANIM("data/items/minerals/ruda1.ani");

	bullspr[0]=Mpack->GetSprite("projectile01");
	//
	effects[0]=Mpack->GetParticleSystem("eng01");//1 след от двигателя
	effects[1]=Mpack->GetParticleSystem("canon1");//1 эффект от попадания
	effects[2]=Mpack->GetParticleSystem("bang01");//Взрыв корабля

	suns[0] = Mpack->GetParticleSystem("sun01");//подложка солнца
	suns[1] = Mpack->GetParticleSystem("sun02");
	suns[2] = Mpack->GetParticleSystem("sun03");

	hud1=Mpack->GetSprite("hud1");//лев.панель
	hradar=Mpack->GetSprite("radar");

	sysmap=Mpack->GetSprite("map");
	cargobayspr=Mpack->GetSprite("cargom");
	cargobayslot=Mpack->GetSprite("slot");
	planethlp = Mpack->GetSprite("planethlp");

	fail1spr=Mpack->GetSprite("fail1");

	radarRED[0]=new hgeSprite(*Mpack->GetSprite("radared"));
	radarRED[0]->SetColor(ARGB(255,255,0,0));;
	radarRED[1]=new hgeSprite(*Mpack->GetSprite("radared"));
	radarRED[1]->SetColor(ARGB(255,255,200,60));	
	radarRED[2]=new hgeSprite(*Mpack->GetSprite("radared"));
	radarRED[2]->SetColor(ARGB(255,131,220,254));	
	radarRED[3]=new hgeSprite(*Mpack->GetSprite("radared"));
	radarRED[3]->SetColor(ARGB(255,0,255,216));	
	radarRED[4]=new hgeSprite(*Mpack->GetSprite("radared"));
	radarRED[4]->SetColor(ARGB(255,255,255,255));	

	border=Mpack->GetSprite("border");
	tractorspr=Mpack->GetSprite("tractor");

	resized_info[0]=Mpack->GetSprite("info_up");
	resized_info[1]=Mpack->GetSprite("info_center");
	resized_info[2]=Mpack->GetSprite("info_down");

	shipinfospr=Mpack->GetSprite("mship");

	ataico=Mpack->GetSprite("curata1");

	staticitems[0]=Mpack->GetSprite("cannon1p");//иконка пулемета 1 уровня
	staticitems[1]=Mpack->GetSprite("ship01");//иконка корпуса 1 уровня
	staticitems[2]=Mpack->GetSprite("engine1");//иконка двигателя 1 уровня
	staticitems[3]=Mpack->GetSprite("asteroid1");//иконка руды bullet1p
	staticitems[4]=Mpack->GetSprite("bullet1p");//иконка снарядов

	//спрайты планет
	//PlanetsSpr[0]=Mpack->GetSprite("earth");

	shadow=Mpack->GetSprite("shadow");
	itemhelp=Mpack->GetSprite("maginfo");

	wpt[0]=new hgeSprite(*Mpack->GetSprite("wpt"));//красный
	wpt[0]->SetColor(ARGB(255,255,0,0));
	wpt[1]=new hgeSprite(*Mpack->GetSprite("wpt"));//Зеленый

	SysIcons[0]=Mpack->GetSprite("sys1");

	//BGsprites[0]=Mpack->GetSprite("bg01");
	//BGsprites[1]=Mpack->GetSprite("cloud01");

	shad1 = hge->Shader_Create("data/shaders/shader1.psh");

	//фон
	BG_Spr[0] = "bg/bg01.png";
	BG_Spr[1] = "bg/bg02.png";
	//туманности
	BG_PartSpr[0] = "bg/cloud1.png";
	BG_PartSpr[1] = "bg/cloud2.png";
	BG_PartSpr[2] = "bg/cloud3.png";
	BG_PartSpr[3] = "bg/cloud4.png";
	BG_PartSpr[4] = "bg/cloud5.png";
	BG_PartSpr[5] = "bg/cloud6.png";
	BG_PartSpr[6] = "bg/cloud7.png";
	//планеты
	PLN_Spr[0] = "planets/earth.png";
	PLN_Spr[1] = "planets/mars.png";
	PLN_Spr[2] = "planets/venus.png";


	PLN_Spr[10] = "planets/earth.png";
	PLN_Spr[11] = "planets/good0.png";
	PLN_Spr[12] = "planets/good1.png";

	PLN_Spr[20] = "planets/bad0.png";

	{
		systems_names.push_back("Акамар\0");
		systems_names.push_back("Ахернар\0");
		systems_names.push_back("Ахирд\0");
		systems_names.push_back("Акраб\0");
		systems_names.push_back("Акрукс\0");
		systems_names.push_back("Акубенс\0");
		systems_names.push_back("Адара\0");
		systems_names.push_back("Аладфар\0");
		systems_names.push_back("Аламак\0");
		systems_names.push_back("Алатфар\0");
		systems_names.push_back("Алараф\0");
		systems_names.push_back("Альбалдах\0");
		systems_names.push_back("Альбирео\0");
		systems_names.push_back("Альчиба\0");
		systems_names.push_back("Алькор\0");
		systems_names.push_back("Альциона\0");
		systems_names.push_back("Альдебаран\0");
		systems_names.push_back("Альдерамин\0");
		systems_names.push_back("Аль Данаб\0");
		systems_names.push_back("Алиот\0");
		systems_names.push_back("Арракис\0");
		systems_names.push_back("Альтарф\0");

		systems_names.push_back("Бекрукс\0");
		systems_names.push_back("Беллатрикс\0");
		systems_names.push_back("Бетельгейзе\0");
		systems_names.push_back("Бирдун\0");

		systems_names.push_back("Канопус\0");
		systems_names.push_back("Капелла\0");
		systems_names.push_back("Каф\0");
		systems_names.push_back("Кастор\0");
		systems_names.push_back("Дабих\0");
		systems_names.push_back("Денеб\0");
		systems_names.push_back("Денебола\0");
		systems_names.push_back("Диадема\0");
		systems_names.push_back("Дифда\0");
		systems_names.push_back("Днокес\0");
		systems_names.push_back("Дшубба\0");
		systems_names.push_back("Дубхе\0");
		systems_names.push_back("Гакрукс\0");
		systems_names.push_back("Гиртаб\0");
		systems_names.push_back("Гитхаб\0");
		systems_names.push_back("Хардкор\0");
		systems_names.push_back("Хадар\0");
		systems_names.push_back("Хамаль\0");
		systems_names.push_back("Ицар\0");
		systems_names.push_back("Кеид\0");
		systems_names.push_back("Кохаб\0");
		systems_names.push_back("Махасим\0");
		systems_names.push_back("Майя\0");
		systems_names.push_back("Маркаб\0");

		systems_names.push_back("Мегрец\0");
		systems_names.push_back("Менкар\0");
		systems_names.push_back("Мерак\0");
		systems_names.push_back("Меропа\0");
		systems_names.push_back("Мезартим\0");
		systems_names.push_back("Миаплацидус\0");
		systems_names.push_back("Минтака\0");
		systems_names.push_back("Мира\0");

		systems_names.push_back("Мирфак\0");
		systems_names.push_back("Мицар\0");
		systems_names.push_back("Мусцида\0");
		systems_names.push_back("Мирцам\0");
		systems_names.push_back("Наккар\0");
		systems_names.push_back("Нусакан\0");
		systems_names.push_back("Феркад\0");
		systems_names.push_back("Плейона\0");

		systems_names.push_back("Процион\0");
		systems_names.push_back("Поллукс\0");
		systems_names.push_back("Пропус\0");
		systems_names.push_back("Рана\0");
		systems_names.push_back("Регул\0");
		systems_names.push_back("Ригель\0");
		systems_names.push_back("Садр\0");
		systems_names.push_back("Саргас\0");
	};//названия секторов в космосе


};

void gameclass::ChangeMap(int _sys)//тут идет смена картинок заднего фона, планет и прочего
{
	mainBG->RestartSun();//перезапуск системы частиц
	ReloadTextures();//смена текстур фона и планет
	sectors.at(_sys)->PreInit();


};

void gameclass::ReloadTextures()
{
	for (int i = 0; i<bgobjects.size(); i++)//Перезагружаем текстуры фона
	{
		bgobjects[i]->ChangeMap();
	};

	for (int i = 0; i<planetary.size(); i++)//Смена текстур планет
	{
		planetary.at(i)->ChangeMap();
	};


};

void gameclass::NewGame()
{
	ResourseLoad();//загрузка ресурсов

	fnt->SetColor(ARGB(255,255,0,0));
    mainBG=new worldbg();//создаем класс управления задним фоном
	astspawner=new asterctr(0.1f);//каждые N секунд радномно создаются астероиды

	GenerateItems();//создаем базовые вещи

	CreateSectors();//создаем сектора

	CreatePlayer();//создаем игрока
	


	
};

void gameclass::GenerateItems()//создаём все начальные вещи в игре
{
	
	GenetareHulls();
	GenerateEngines();
	GenerateBullets();
	GenerateWeapons();


};

void gameclass::GenetareHulls()
{
	defaulthull = new hull(effects[0], animships[0]);
	defaulthull->engrad = 10;
	defaulthull->scale = 0.3f;
	defaulthull->maxhp = 150;
	defaulthull->radiores = 0;
	defaulthull->termres = 0;
	defaulthull->kinres = 0;
	defaulthull->explres = 0;
	defaulthull->sensorrange = 900;
	defaulthull->wslot = 2;
	defaulthull->sigradius = 100;
	defaulthull->enginesize = SMALL;
	defaulthull->wslotsize = SMALL;
	defaulthull->mass = 250;
	defaulthull->name = "Учебный фригат";
	defaulthull->description = "Учебный фригат, не предназначен для долгого боя. Можно установить 2 орудия малого размера. Обладает малой сигнатурой корпуса и малой массой.\0";
	defaulthull->SetDefaultVar();
	defaulthull->fraction = 1;//люди
	defaulthull->ico = staticitems[1];

};

void gameclass::GenerateEngines()
{
	//начальный двигатель фригатов
	eng1 = new engine(3.5f, 300, SMALL);
	eng1->warprange = 45000;
	eng1->name = "Плазменный двигатель";
	eng1->ico = staticitems[2];
	eng1->mass = 5;
	eng1->impulse = 200;
	eng1->description = "Прототип плазменного двигателя, который в последствии был пущен в серию. Почти безопасен для экипажа, дешев в эксплуатации.\0";
	eng1->SetDefaultVar();
};

void gameclass::GenerateBullets()
{
	////Снаряды
	projectile1 = std::shared_ptr<projectile>(new projectile(bullspr[0], 2, 1, 0, 0));
	projectile1->effect = effects[1];//эффект частицами
	projectile1->animeff = animeffects[1];//анимированный эффект
	projectile1->efftype = 1;//эффекты анимацией
	projectile1->BSize = SMALL;
	projectile1->name = "ОФС малого калибра";
	projectile1->ico = staticitems[4];
	projectile1->totalCount = 500;
	projectile1->optimal_b = 0.1f;//бонус на оптимал 10%
	projectile1->description = "Система сборки снарядов, может подготавливать снаряды для всех орудий малого калибра. Обратно снаряды разобрать нельзя! Увеличивает дальность на 10%\0";

};

void gameclass::GenerateWeapons()
{
	trsmall1 = new turret(20, 0.9f, 150, 90, 50, 70, 0.9f);//пулемет 1 уровня(начальный)
	trsmall1->damagemod = 1.8f;
	trsmall1->name = "120 мм автопушка";
	trsmall1->Wsize = SMALL;
	trsmall1->ico = staticitems[0];
	trsmall1->mass = 5;
	trsmall1->description = "Огнестрельная автоматическая пушка, можно заряжать снаряды малого калибра. Идеально подходит для уничтожения малых быстролетящих целей на близкой дистанции.\0";
	trsmall1->SetDefaultVar();//устанавливаем введенные выше значения за начальные для этой вещи


};



void gameclass::CreatePlayer()
{
	Player= new player();//создаем игрока

	//Player->mainHUD=new HUD(Player);//создаем интерфейс игрока
	//Player->PlayerMap=new spacemap(Player);
	//Player->PlayerRadar=new radar(Player);
	//Player->PlayerCargo=new cargobay(Player);
	//Player->PlayerShipInfo= new shippanel(Player, dynamic_cast<cargobay*>( Player->PlayerCargo));
	

	/*hdd=0;
	hdd=dynamic_cast<HUD*>(Player->PlayerRadar);
	MainGUI *gi = Player->mainHUD;*/

	Player->PlayerCargoGUI = new shipcargoGUI(Player);//грузовой отсек
	GameGUI->AddCtrl(Player->PlayerCargoGUI);

	Player->PlayerMapGUI = new dsmap(Player);//карта системы
	GameGUI->AddCtrl(Player->PlayerMapGUI);

	Player->PlayerRadarGUI = new dsradar(Player);//радар игрока
	GameGUI->AddCtrl(Player->PlayerRadarGUI);

	Player->PlayerShipGUI = new shipsinfo(Player);//экран параметров игрока
	GameGUI->AddCtrl(Player->PlayerShipGUI);

	Player->PlayerCombatGUI = new combathud(Player);
	GameGUI->AddCtrl(Player->PlayerCombatGUI);


	 cargo *crg;
	//создаем корпус корабля
	hull *hl;
	hl=defaulthull->clone_default();//копируем из стандартного набора подготовленных объектов
	hl->maxhp = 999999.9f;
	hl->explres = 99;
	hl->radiores = 99;
	hl->kinres = 99;
	hl->termres = 99;

	hl->SetDefaultVar();

	hl->GenerateRandomVar(1,0,0);//ставим 1 уровень
	hl->Install();//вызывается только при создании 1 раз(это на корабле)
	crg=hl;//помещяем в общее хранилище
	//cargoobjects.push_back(crg);


	//двигатель для игрока
	engine *eng;
	eng = eng1->clone_default();
	eng->GenerateRandomVar(1,0,0);
	eng->Install();
	eng->speed = 800;
	eng->impulse = 300;
	crg=eng;
	//cargoobjects.push_back(crg);
	
	//создаём контроллер игрока
	std::shared_ptr<ship> PlayerShip(new ship(0,hl));
	PlayerShip->type=100;
	PlayerShip->name="Игрок";
	Player->PlayerShip=PlayerShip;

	PlayerShip->obj = PlayerShip;//ссылка на ptr;
	sectors.at(0)->AddToList(PlayerShip);//добавляем корабль игрока в список объектов системы
	//dyn.push_back(PlayerShip);//общий список всех объектов

	PlayerShip->InstallEngine(eng);//ставим двигательc

	// создаем снаряд для орудия малого размера 
	std::shared_ptr<projectile> pr(projectile1->clone());
	bullcont* bl;
	bl=new bullcont(pr);
	bl->InitializeSpace(0,60,124);
	sectors.at(0)->AddItemToList(bl);

	//создаем орудие для каждого слота на корабле игрока и заряжаем снаряд(выше)
	
	turret *tr;//прототип орудия
	tr=trsmall1->clone_default();
	tr->GenerateRandomVar(1,0,0);
	crg=tr;
	crg->InitializeSpace(0,50,100);//подготавливаем объект в космосе в фиксированных координатах
	sectors.at(0)->AddItemToList(crg);

	tr = trsmall1->clone_default();
	tr->GenerateRandomVar(1, 0, 0);
	crg = tr;
	crg->InitializeSpace(0, 50, 190);
	sectors.at(0)->AddItemToList(crg);




	PlayerShip->pilot=Player;//тот кто управляет кораблем, отсюда берутся скилы пилота

	
	
   

};


void gameclass::CreateSectors()
{
	CreateStartSectors();//создаем базовые сектора с фиксированными планетами

	CreateConstantSectiors();

};

void gameclass::CreateConstantSectiors()//размещаем  открытые системы в игре
{
	int maxsys = Max_Systems;//минимум систем 40

	

	int breakpoint = 0;//это защита от зацикливания
	int maxbreaks = 100000;

	float dx;
	float dy;

	bool goodpoz = false;//подходят ли координаты?

	bool flag1 = true;

	float maxx = 420 / GlobalMapScaleFactor;//правая нижняя граница карты
	float maxy = 380 / GlobalMapScaleFactor;

	int cursys = 0;

	for (int i = 0; i < maxsys; i++)
	{

		while (flag1)
		{
			flag1 = false;

			dx = sectors.at(cursys)->x + hge->Random_Float(-40000, 40000);
			dy = sectors.at(cursys)->y + hge->Random_Float(-40000, 40000);

			if (PlayerSysInBorder)
			{
				cursys = sectors.size() - 1;
			}
			else
			{
				cursys = hge->Random_Int(0, sectors.size() - 1);
			};
		
	
			for (int d = 0; d < sectors.size(); d++)
				{
					float pdist = point_distanse(dx, dy, sectors.at(d)->x, sectors.at(d)->y);
					if (pdist>15000)//минимальное расстояние между секторами
					{						
							goodpoz = true;
					}
					else
					{

						breakpoint++;
						if (breakpoint > maxbreaks)
						{
							flag1 = false;
						}
						else
						{
							flag1 = true;
						};
					};
				    };
		};

		if (goodpoz)//если позиция подходит, то создаем систему
		{//сделать отдельную функцию
			goodpoz = false;

			bool table_name = false;//откуда брать имя,из списка или генерировать
			int namecr;
			if (systems_names.size() > 1)
			{
				namecr = hge->Random_Int(0, systems_names.size() - 1);
				table_name = true;
			};


			sector *sr;
			sr = new sector(dx, dy, mapeffects[0]);//создаем рандомно сектора пока все 0
			sr->frac = NONE;
			sr->raiting = 0;
			sr->level = 0;
			if (table_name)//получаем имя системы из списка
			{
				sr->name = systems_names.at(namecr);
				systems_names.erase(systems_names.begin() + namecr);//удаляем занятое имя из списка
			};

			sectors.push_back(sr);
			flag1 = true;

			int rnd0 = hge->Random_Int(1, 4);
			planet *pln;
			for (int z = 0; z < rnd0; z++)
			{
				pln = new planet(sectors.size() - 1, z + 1);
				pln->name = "Нет";//начальные параметры для планеты
				planetary.push_back(pln);
				sectors.at(pln->sysid)->planetlist.push_back(pln);//помещяем планету в список планет сектора
			};


			int rnd1 = hge->Random_Int(1, 5);
			spacefog *fgr;//туманности в секторе
			for (int b = 0; b < rnd1; b++)
			{
				fgr = new spacefog(hge->Random_Int(2,6) , sectors.size() - 1, hge->Random_Float(-8000, 8000), hge->Random_Float(-8000, 8000), hge->Random_Int(0, 6));
				bgobjects.push_back(fgr);
			};

		};

		//cursys++;

	};
	

};

void gameclass::CreateAISystems()
{

};


void gameclass::CreateStartSectors()
{
	sector *sr;//сектор игрока
	sr = new sector(5000, 5000, mapeffects[0]);
	sr->frac = PEOPLE;
	sr->raiting = 1;
	sr->name = "Солнце";
	sectors.push_back(sr);



	planet *pln;//Планета земного типа
	pln = new planet(0, 3);
	pln->SpriteID = 0;
	pln->scale = 0.4f;
	pln->LoadTexture();//загружаем текстуру начальной планеты
	pln->name = "Земля";//начальные параметры для планеты
	pln->fraction = 1;
	pln->population = 100;
	pln->type = 2;
	planetary.push_back(pln);
	sectors.at(pln->sysid)->planetlist.push_back(pln);//помещяем планету в список планет сектора

	pln = new planet(0, 4);
	pln->SpriteID = 1;
	pln->LoadTexture();//загружаем текстуру начальной планеты
	pln->name = "Марс";//начальные параметры для планеты
	pln->scale = 0.5f;
	pln->fraction = 1;
	pln->population = 14;
	pln->type = 2;
	planetary.push_back(pln);
	sectors.at(pln->sysid)->planetlist.push_back(pln);//помещяем планету в список планет сектора

	pln = new planet(0, 2);
	pln->SpriteID = 2;
	pln->LoadTexture();//загружаем текстуру начальной планеты
	pln->name = "Венера";//начальные параметры для планеты
	pln->scale = 0.3f;
	planetary.push_back(pln);
	sectors.at(pln->sysid)->planetlist.push_back(pln);//помещяем планету в список планет сектора

	pln = new planet(0, 5);
	pln->LoadTexture();//загружаем текстуру начальной планеты
	pln->name = "Юпитер";//начальные параметры для планеты
	pln->scale = 0.6f;
	planetary.push_back(pln);
	sectors.at(pln->sysid)->planetlist.push_back(pln);//помещяем планету в список планет сектора




	spacefog *fgr;//туманности в секторе
	fgr = new spacefog(1, 0, 0, 0, 0);
	fgr->LoadTex();//Загружаем текстуру сразу т.к. это начальная система
	bgobjects.push_back(fgr);

	fgr = new spacefog(2, 0, 4742, 4115, 0);
	fgr->LoadTex();
	bgobjects.push_back(fgr);

};



void gameclass::UpdateVectors()
{
	Call_Time = dt * Max_Systems;//время вызова быстрого обновления

	//обновление посекторно
	
	//sectors.at(PlayerSys)->Update();//сектор игрока обновляется всегда 1
	//sectors.at(PlayerSys)->FastUpdate();//сектор игрока обновляется всегда 1
	
	//for (int i = upd_from; i < upd_to; i++)//обнволяем вторичные(неактивные системы)
	//{
	//	if (sectors.at(i)->id != PlayerSys)
	//	{
	//		sectors.at(i)->FastUpdate();//функция упрощенных расчетов
	//	};
	//};
	//
	//if (upd_to < sectors.size())//один фрейм, 1 система
	//{
	//	upd_from++;
	//	upd_to++;
	//}
	//else
	//{
	//	upd_from = 0;
	//	upd_to = 1;
	//}

	for (int i = 0; i < sectors.size(); i++)
	{
		sectors.at(i)->Update();
	}
	

	for(int i=0;i<eff.size();i++)//все эффекты в мире
	{
		if(eff.at(i)->kill==false)//если его не надо удалить, то обновляем
		{
			eff.at(i)->Update();
		}else
		{
			delete eff[i];
			eff.erase(eff.begin()+i);
		};
	};
};

void gameclass::RenderVectors()
{
	 for(int i=0;i<bgobjects.size();i++)//Рисуем только те объекты, которые в секторе игрока Фоновые объекты
	 {	 
		 if (bgobjects[i]->sysid == PlayerSys)
		 {
			 
			 bgobjects[i]->Render();
		 };
	 };

	 sectors.at(PlayerSys)->Render();//рисуем только 1 сектор

	 for(int i=0;i<eff.size();i++)//Рисуем только те объекты, которые в секторе игрока
			{
				if(eff[i]->sysid==PlayerSys)
				{
					eff[i]->Render();
				};
			};
};

void gameclass::Test1()
{

	if (hge->Input_KeyUp(HGEK_5))//Так просто для теста
	{
		Func_switch = !Func_switch;
	};

	if(hge->Input_KeyUp(HGEK_8))//Так просто для теста
	{ 
		

		for(int i=0;i<1;i++)
		{
			int cur_sys = 0;

			cargo *crg;
			hull *hl;
			hl=defaulthull->clone_default();
	        hl->GenerateRandomVar(1,0,0);
			hl->Install();
			crg=hl;

			std::shared_ptr<ship> PlayerShip(new ship(cur_sys, hl));
			/*PlayerShip->dx=15000;
			PlayerShip->dy=5000;*/
			PlayerShip->name = "Фригат";			

			PlayerShip->autopilot=2;

			PlayerShip->obj = PlayerShip;
			sectors.at(cur_sys)->AddToList(PlayerShip);

		/*	pilotctr *pil;
			pil = new pilotctr();
			PlayerShip->pilot = pil;*/

			defender *def;
			def = new defender();
			def->Ship = PlayerShip;
			def->homeplanet = sectors.at(0)->planetlist.at(0);//роданя планета бота
			def->homeplanet->AddDefenceShip(PlayerShip);//является защитником планеты
			PlayerShip->pilot = def;


			engine *eng;
			eng=eng1->clone_default();
			eng->GenerateRandomVar(1,0,0);
			eng->Install();
			PlayerShip->InstallEngine(eng);
			crg=eng;

			std::shared_ptr<projectile> pr(projectile1->clone());
			pr->totalCount = 65;
			bullcont* bl;
			bl = new bullcont(pr);
			PlayerShip->SetItem(bl);
			bl->Install();

			//создаем орудие для каждого слота на корабле игрока и заряжаем снаряд(выше)
			for(int i=0;i<PlayerShip->wslot;i++)
			{
				turret *tr;//прототип орудия
				tr=trsmall1->clone_default();
				tr->GenerateRandomVar(1,0,0);
				tr->SetBullet(pr);
				tr->SetParient(PlayerShip);
				tr->Install();
				PlayerShip->InstallWeapon(tr);
				crg=tr;
			};	

			//PlayerShip->WarpOn(hge->Random_Int(1, sectors.size() - 1));
			//PlayerShip->WarpOn(1);
			//PlayerShip->FlyTo(6000, 5000);
			//PlayerShip->SetTarget(sectors.at(0)->objects.at(0));

		};
	};

	if(hge->Input_KeyUp(HGEK_0))//тоже для теста
	{ 
		//for(int i=1;i<dyn.size();i++)//все динамические объекты
		//{
		//	dyn.at(i)->kill=true;
		//};
		for (int i = 0; i < sectors.size(); i++)
		{
			for (int t = 0; t < sectors.at(i)->objects.size(); t++)
			{
				if (sectors.at(i)->objects.at(t)->type != 100)
				{
					sectors.at(i)->objects.at(t)->Damage(9000, 9000, 9000, 9000);
				}
			};
		}

	};

	if(hge->Input_KeyUp(HGEK_9))//тоже для теста
	{ 
		for (int i = 0; i < sectors.size(); i++)
		{
			for (int t = 0; t < sectors.at(i)->cargoobjects.size(); t++)
			{

				if (sectors.at(i)->cargoobjects.at(t)->state == 0)
				{
					sectors.at(i)->cargoobjects.at(t)->kill = true;
				};
			};
		};
		
	};


	
};

