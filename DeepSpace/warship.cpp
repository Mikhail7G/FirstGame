#include "warship.h"



//ship::ship(int _sysid, HANIM *_anim,hgeParticleSystem *_eng)
ship::ship(int _sysid, hull *_shiphull)
{
	sysid = _sysid;//задаем начальные значения
	x = syspozx[sysid] + hge->Random_Float(-100.0f, 100.0f);
	y = syspozy[sysid] + hge->Random_Float(-100.0f, 100.0f);


	type = 1;

	shiphull = 0;
	shipengine = 0;
	//создаем картинку корабля
	shiphull = _shiphull;//сначала корпус корабля
	anim = shiphull->anim;
	img = new hgeAnim(anim, hgeAnim::PLAY_LOOP);//крутится постоянно


	rotatespeed = 0.04f;//0.04

	eng = new hgeParticleSystem(*shiphull->eng);//создаём эффект двигателя
	eng->FireAt(x, y);
	smoke = true;//дым от двигателя
	//загружаем данные из корпуса корабля
	engrad = shiphull->engrad;
	maxhp = shiphull->maxhp;
	hp = maxhp;
	scale = shiphull->scale;
	sensorrange = shiphull->sensorrange;
	sigradius = shiphull->sigradius;
	mass = shiphull->mass;

	autopilot = 0;
	attackradius = 100;
	maxattackradius = 200;
	dir = 0;
	alpha = 255;

	maxspeed = 10;
	speed = maxspeed;

	prmlock = true;
	dx = x + hge->Random_Float(-500, 500);
	dy = y + hge->Random_Float(-500, 500);
	state = FLY;
	totalVolley = 0;
	//подгатавливаем сопротивления корпуса сразу переводим из процентов
	explres = (shiphull->explres) / 100;
	kinres = (shiphull->kinres) / 100;
	termres = (shiphull->termres) / 100;
	radiores = (shiphull->radiores) / 100;

	fraction = shiphull->fraction;//потом брать из класса pilot

	EXParmor = maxhp / (1 - (explres + kinres + termres + radiores) / 4);//показывает сколько примерно можно выдержать урона

	wslot = shiphull->wslot;//слотов под орудия

	crgmgr = new cargomanager();
	crgmgr->maxslot = 28;//слотов в груз. отсеке

	crgmgr->shiphull = shiphull;

	warponse = true;
	warptime = 0;
	wrpt1 = warptime;

	underAttack = false;
	attackTimer = 30;//время агрессии 30 сек
	attacktim1 = attackTimer;

	firstAttack = false;
	firstAttackTim = 15;
	firstAttacktim1 = firstAttackTim;

	itempuckuprad = 100;
	tractorradius = 500;
	tractorpower = 15;

	dist = 0;

	GlobalShipObj++;
	acceleration = 0;
	acc = 200;

	startsys = 0;
	go_to_next_sys = true;
	autoflight = false;
};

ship::~ship()//удаляем кораблик и все созданные для него ресурсы
{
	pilot->ShipLost();
	hge->System_Log("Корабль:%s уничтожен в системе:%i", name, sysid);
	delete img;//удаляем созданную анимацию корабля


	explosion *expl;//тут только пока анимицией, сделать возможность менять на частицы
	expl = new explosion(animeffects[0], x, y, 5, sysid);
	eff.push_back(expl);

	//сбрасываем все из трюма и все модули, пока все(потом с % шансом)
	crgmgr->DropEngine(sysid, x, y);
	crgmgr->DropHull(sysid, x, y);


	for (int i = 0; i < crgmgr->shipwpn.size(); i++)
	{
		weapons.at(i)->RemoveBullet();//разряжаем орудие и выбрасываем за борт
		weapons.at(i)->DropTarget();
	};
	crgmgr->DropWeapon(sysid, x, y);//сбрасываем орудие, находящееся в слотах корабля

	crgmgr->DropAll(sysid, x, y);//сбрасыввем все остальное

	delete crgmgr;

	obj.reset();//сбрасывем ссылку на самого себя

	GlobalShipObj--;
};

void ship::Update()//тут все расчеты
{
	syndist = point_distanse(x, y, syspozx[sysid], syspozy[sysid]);//пока тут, потом оптимизирую

	if (GPAUSED == false)//тут передвижение и все что требует реального времени на расчеты
	{
		//движение 
		switch (state)
		{
		case STOP:
			break;
		case FLY:
			MoveTo();
			break;
		case WARP:
			WarpRun();
			break;
		};

	};

	TargetOperations();//проверяем наличие цели?
	WeaponUpdate();//работа с орудиями

	AggressiveTimer();//обновляем таймер флага военных действий
	FirstAttackTimer();//таймер флага проявления агрессии

	CalculaceCollision();//проверяем столкновения

	pilot->LigicUpdate();//обновляем пилота.


};

void ship::Render()//рисуем кораблик и его эффекты
{
	if (smoke == true)
	{
		eng->MoveTo(x-cos(dir)*engrad,y-sin(dir)*engrad);
		eng->Update(dt);
		eng->Render();
	};
	img->RenderEx(x, y, (dir + 3.14 / 2), scale, scale);
	img->Update();

	// hge->Gfx_RenderLine(x,y,dx,dy,ARGB(255,255,0,0));
	//освещение корабля в зависимости от удаления от солнца
	/*float light=255-syndist*lighting;
	if(light<1)
	{
	light=0;
	};*/
	//img->sprite->SetColor(ARGB(alpha,255,255,255));

	if (DrawCollisionData)
	{
		//сетка столкновений
		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions.at(i).expired())//проверяем наличие 
			{
			}
			else
			{
				auto obj = collisions.at(i).lock();
				hge->Gfx_RenderLine(x + 10, y, obj->x, obj->y, ARGB(255, 0, 255, 0));
			};
		};

		fnt->printf(x, y + 20, HGETEXT_LEFT, "c:%i", collisions.size());
		//fnt->printf(x, y + 35, HGETEXT_LEFT, "chf1:%i", scharge_flag1);
	};


	pilot->DebugDraw();

};

void ship::FlyTo(float _x, float _y)
{
	dx = _x;
	dy = _y;

	
	
	state = FLY;//меняем режим на полет
	warpengine = OFF;//отключаем варп двиг
	warponse = true;//

	ResetSpeed();//перерасчет сокорсти

};

void ship::MoveTo()//функция движения корабля к заданным в FlyTo координатам
{
	
	
	//newdir = point_dir2(x, y, dx, dy);
	PatchCorr();

	dir += slow_rotate(rotatespeed, dir, newdir);

	dist = point_distanse(x, y, dx, dy);


	x = x + cos(dir)*speed*dt;
	y = y + sin(dir)*speed*dt;

	if (dist < maxspeed)
	{
		// acceleration += dt * acc;
		speed += dt * acc;
		speed = min(speed, dist*dt*acc);
		speed = min(speed, maxspeed);
	}
	else
	{
		// acceleration += dt * acc;
		speed += dt*acc;
		speed = min(speed, maxspeed);
	};


	if (dist < 10)
	{
		state = STOP;
		speed = 0;

		PozTest();//корректировка координат стоянки

		if (warpengine == ON)
		{
			state = WARP;
		};
		if (warpengine == RUN)
		{
			state = WARP;
		};
	};


};


void ship::WarpOn(int _nextsys)//движение корабля к точке перехода в нужную ситсему
{
	nextsys = _nextsys;
	float sx = 0;
	float sy = 0;
	float wdir = 0;
	float w_dist = 0;

	if (syndist<10000)
	{
		wdir = point_dir2(sectors.at(nextsys)->x, sectors.at(nextsys)->y, x, y);
		sx = sectors.at(sysid)->x + (hge->Random_Float(9000,9500)) * cos(wdir);
		sy = sectors.at(sysid)->y + (hge->Random_Float(9000, 9500)) * sin(wdir);
		FlyTo(sx, sy);
		warpengine = ON;
	}
	else
	{	
		//отправляем корабль к точке перехода в нужную систему
		wdir = point_dir2(sectors.at(nextsys)->x, sectors.at(nextsys)->y, x, y);

		float realx;
		float realy;
		realx = sectors.at(sysid)->x + (hge->Random_Float(9000, 9500)) * cos(wdir);
		realy = sectors.at(sysid)->y + (hge->Random_Float(9000, 9500)) * sin(wdir);

		if (point_distanse(x, y, realx, realy)<1000)
		{
			sx = x + 500 * cos(wdir);
			sy = y + 500 * sin(wdir);
			FlyTo(sx, sy);
			warpengine = ON;
		}
		else
		{
			sx = sectors.at(sysid)->x + (hge->Random_Float(9000, 9500)) * cos(wdir);
			sy = sectors.at(sysid)->y + (hge->Random_Float(9000, 9500)) * sin(wdir);
			FlyTo(sx, sy);
			warpengine = ON;
		};
	};
};

void ship::WarpRun()//Переход в новый сектор
{

	float zx;
	float zy;
	float sx;
	float sy;

	if (warponse)
	{
		warponse = false;
		wrpt1 = warptime;

		float wdir;
		wdir = point_dir2(sectors.at(nextsys)->x, sectors.at(nextsys)->y, x, y);
		sx = x + 500 * cos(wdir);
		sy = y + 500 * sin(wdir);

		FlyTo(sx, sy);
		//SetWarpSpeed();

		warpengine = RUN;
		warponse = false;

		//создаём эффект активации двигателей
		warpportal *prt;
		prt = new warpportal(sx, sy, (15), sysid);
		prt->effdir = wdir;
		prt->scale = scale;
		eff.push_back(prt);

		wdir = point_dir2(sectors.at(sysid)->x, sectors.at(sysid)->y, sectors.at(nextsys)->x, sectors.at(nextsys)->y);
		zx = sectors.at(nextsys)->x + 9500 * cos(wdir) + hge->Random_Float(-100.0f, 100.0f);
		zy = sectors.at(nextsys)->y + 9500 * sin(wdir) + hge->Random_Float(-100.0f, 100.0f);

		prt = new warpportal(zx, zy, (15), nextsys);
		prt->effdir = wdir;
		prt->scale = scale;
		eff.push_back(prt);
	};

	float w_dist = point_distanse(x, y, dx, dy);
	if (w_dist < 150)
	{
		float wdir = point_dir2(sectors.at(sysid)->x, sectors.at(sysid)->y, sectors.at(nextsys)->x, sectors.at(nextsys)->y);

		sectors.at(nextsys)->AddToList(obj);//переносим корабль в другой сектор
		//sectors.at(sysid)->RemoveFromList(obj);//убрал эту функцию, был баг из за нее.


		sysid = nextsys;
		x = sectors.at(sysid)->x + 9500 * cos(wdir) + hge->Random_Float(-100.0f, 100.0f);
		y = sectors.at(sysid)->y + 9500 * sin(wdir) + hge->Random_Float(-100.0f, 100.0f);

		ResetSpeed();

		float zx = sectors.at(sysid)->x + 9000 * cos(wdir) + hge->Random_Float(-100.0f, 100.0f);
		float zy = sectors.at(sysid)->y + 9000 * sin(wdir) + hge->Random_Float(-100.0f, 100.0f);
	
		warpengine = OFF;
		warponse = true;
		pilot->ScangeMap(sysid);
		FlyTo(zx, zy);
	}



	

};

bool ship::SetTarget(std::weak_ptr<dynamic> _target)//установка цели для слежения
{
	auto trr = _target.lock();
	if (point_distanse(x, y, trr->x, trr->y) < sensorrange)
	{
		target = _target;
		return true;
	}
	else
	{
		return false;
		//сообщение: Цель слишком далеко
	};
};


void ship::TargetOperations()
{
	if (target.expired())//проверяем наличие цели
	{
		target.reset();
		//сообщение: Цель потеряна
	}
	else
	{
		auto trr = target.lock();
		float tdist = point_distanse(x, y, trr->x, trr->y);
		float tdir = point_direction(x, y, trr->x, trr->y);

		if ((tdist > sensorrange) || (trr->sysid!=sysid))//выход цели за радиус обзора радара
		{
			target.reset();
			DropTarget();
			//сообщение: цель слишком далеко
		};


		switch (autopilot)
		{
		case 1://режим приследования на минимальной дистанции
			if (tdist>attackradius)//если далеко то летим к цели
			{
				FlyTo(trr->x, trr->y);
			}
			else
			{
				if (tdist< (attackradius - 50))//иначе летим от цели
				{
					float dxx = trr->x + cos(tdir*3.14 / 180 + 0.001f)*attackradius;
					float dyy = trr->y + sin(tdir*3.14 / 180 + 0.001f)*attackradius;
					FlyTo(dxx, dyy);
				};
			};
			break;
		case 2://режим приследования на максимальной дистанции
			if (tdist>maxattackradius)//если далеко то летим к цели
			{
				FlyTo(trr->x, trr->y);
			}
			else
			{
				if (tdist< (maxattackradius - 50))//иначе летим от цели
				{
					float dxx = trr->x + cos(tdir*3.14 / 180 + 0.001f)*maxattackradius;
					float dyy = trr->y + sin(tdir*3.14 / 180 + 0.001f)*maxattackradius;
					FlyTo(dxx, dyy);
				};
			};
			break;
		}



	};

};

void ship::WeaponUpdate()//обновление установленных орудий
{
	for (int i = 0; i<weapons.size(); i++)
	{
		weapons.at(i)->Update(x, y);
	};
};

void ship::Fire()//огонь из всех орудий по текущей цели(на кнопку F)
{
	for (int i = 0; i<weapons.size(); i++)
	{
		SetTrgToWeap();
		weapons.at(i)->StartFiring();
	};
};

void ship::SetTrgToWeap()//установка цели орудий
{
	for (int i = 0; i<weapons.size(); i++)
	{
		weapons.at(i)->SetTarget(target);
	};
};

void ship::SetOneTrgToWeap(int _weaponid)//устанока цели для конкретного орудия(через панель инфо)
{
	weapons.at(_weaponid)->SetTarget(target);
};


void ship::Damage(float _e, float _k, float _t, float _r)//получение урона
{
	//расчитываем урон с учетом сопротивлений для брони
	float Edmg = _e - _e*explres;
	float Kdmg = _k - _k*kinres;
	float Tdmg = _t - _t*termres;
	float Rdmg = _r - _r*radiores;

	float totaldmg = Edmg + Kdmg + Tdmg + Rdmg;//посчитали весь урон

	//урон по броне
	hp -= totaldmg;

	if (hp<1)//все помер=)
	{
		kill = true;
		obj.reset();
	};

	dmgtext *txt;
	txt = new dmgtext(totaldmg, x, y, sysid);
	eff.push_back(txt);

	AggressiveActive();//сообщение об аттаке по кораблю

};

void ship::DropTarget()//сброс цели для всех орудий
{
	target.reset();
	for (int i = 0; i < weapons.size(); i++)
	{
		weapons.at(i)->DropTarget();
	};
};

void ship::GetWeaponDPS()//просчет урона от орудий
{
	totalDPS = 0;
	totalVolley = 0;
	for (int i = 0; i<weapons.size(); i++)
	{
		weapons.at(i)->CalculateDPS();
		totalDPS += weapons.at(i)->DPS;
		totalVolley += weapons.at(i)->alphastrike;

	};

	attackradius = 9999999;
	maxattackradius = 99999999;

	for (int i = 0; i<weapons.size(); i++)
	{
		if (weapons.at(i)->optimal<attackradius)//выбираем самое маленькое рассояние для автоплота корабля
		{
			attackradius = weapons.at(i)->optimal;//выходим на оптимальное расстояние
		};
		if ((weapons.at(i)->fireradius + weapons.at(i)->optimal)<maxattackradius)//выбираем самое маленькое рассояние для автоплота корабля
		{
			maxattackradius = (weapons.at(i)->fireradius + weapons.at(i)->optimal);//выходим на оптимальное расстояние
		};
	};

};

void ship::RecalculateVariables()
{
	//пока не используется
};

bool ship::InstallEngine(engine *_shipengine)//установка двигателя на корабль
{
	shipengine = _shipengine;

	if (shipengine->size == shiphull->enginesize)//проверяем на соответствие слотов 
	{
		crgmgr->shipeng = shipengine;

		//maxspeed=shipengine->speed;
		maxspeed = (shipengine->speed)*(((shipengine->speed) * 100 / mass) / 100);
		speed = maxspeed;

		acc = shipengine->impulse;

		warptime = shipengine->warptime;
		wrpt1 = warptime;
		return true;
	}
	else
	{
		return false;
		//сообщение: Размер двигателя неподходит
	};

};

bool ship::RemoveEngine()
{
	if (crgmgr->GetItem(shipengine))
	{
		acc = 1;
		maxspeed = 5;
		speed = maxspeed;
		warptime = 5000;
		wrpt1 = warptime;
		shipengine = 0;

		return true;
	}
	else
	{
		return false;
		//сообщение:нет свободного места
	};
};

bool ship::InstallWeapon(turret *_weapon)//установка орудия на корабль
{
	weapon = _weapon;

	if (weapon->Wsize == shiphull->wslotsize)
	{
		if (weapons.size()<wslot)
		{
			weapons.push_back(weapon);
			crgmgr->shipwpn.push_back(weapon);
			UpgradeHull();
			GetWeaponDPS();//считаем увс

			return true;
		}
		else
		{
			return false;
			//сообщение: Нет свободных отсеков крепления орудия
		};
	}
	else
	{
		return false;
		//сообщение: Размер орудия неподходит
	};

};

bool ship::RemoveWeapon(int _id)//снимаем орудие
{
	int id = _id;
	if (crgmgr->GetItem(weapons.at(id)))
	{
		weapons.at(id)->RemoveBullet();
		weapons.at(id)->DropTarget();
		weapons.erase(weapons.begin() + id);

		UpgradeHull();
		GetWeaponDPS();//считаем увс

		return true;
	}
	else
	{
		return false;
		//сообщение: Грузовой отсек полн, невозможно выгрузить
	};
};

void ship::AggressiveActive()
{
	underAttack = true;
	attacktim1 = attackTimer;//в случае аттаки по кораблю запускаем таймер агресии, и постоянно обновляем во время боя, потом так

	pilot->Alarm();

	if (firstAttack)
	{
		firstAttacktim1 = firstAttackTim;//если корабль атаковал безобидную цель, то его будут лупть все подраяд, пока он не помрет либо не улетит.
	};
};

void ship::AggressiveTimer()
{
	if (underAttack)
	{
		attacktim1 -= 1 * dt;
		if (attacktim1<0)
		{
			underAttack = false;
			attackers.clear();//очищаем список кораблей, которые участвовали в атаке.
		};
	};
};

void ship::FirstAttack()
{
	if (target.expired())//проверяем наличие цели	
	{
		target.reset();

	}
	else
	{
		auto trr = target.lock();

		if (!trr->firstAttack)//если цель не агрессивная, то мы становимся агрессивными
		{
			firstAttack = true;
			firstAttacktim1 = firstAttackTim;
		}

	};

};

void ship::FirstAttackTimer()
{
	if (firstAttack)
	{
		firstAttacktim1 -= 1 * dt;
		if (firstAttacktim1<0)
		{
			firstAttack = false;
		};
	};
};

void ship::UpgradeHull()//обновляем параметры корабля
{
	engrad = shiphull->engrad;
	maxhp = shiphull->maxhp;
	hp = maxhp;
	scale = shiphull->scale;
	sensorrange = shiphull->sensorrange;
	sigradius = shiphull->sigradius;

	explres = (shiphull->explres) / 100;
	kinres = (shiphull->kinres) / 100;
	termres = (shiphull->termres) / 100;
	radiores = (shiphull->radiores) / 100;

	EXParmor = maxhp / (1 - (explres + kinres + termres + radiores) / 4);//показывает сколько примерно можно выдержать урона

	GetWeaponDPS();
	CheckMass();

};

void ship::CheckMass()//перерасчет массы корабля
{
	cargomass = 0;//сбрасываем на 0

	for (int i = 0; i<weapons.size(); i++)
	{
		cargomass += weapons.at(i)->mass;
	};

	//считаем массу установленных модулей и всех объектов в грузовом отсеке

	//итого масса корабля
	mass = (shiphull->mass) + cargomass + (crgmgr->totalmass);


	maxspeed = (shipengine->speed)*(((shipengine->speed) * 100 / mass) / 100);
	//speed=maxspeed;

};

void ship::FullLevelUp(int _lvl)//повышаем уровенль всех установленных вещей на корабле
{
	int lvl = _lvl;

	for (int i = 0; i<weapons.size(); i++)
	{
		weapons.at(i)->LevelUp(lvl);
	};

	shiphull->LevelUp(lvl);
	shipengine->LevelUp(lvl);
	UpgradeHull();

};

void ship::ResetSpeed()//обновление скорости корабля+ учет различных бонусов скорости
{
	CheckMass();
};

void ship::SetItem(cargo *_itm)//загрузка вещи в груз. отсек
{
	if (crgmgr->GetItem(_itm))
	{
		CheckMass();
	}
	else
	{
		//сообщение: отсек заполнен, невозможно загрузить
	};
};


bool ship::PickItem(cargo *_itm)//подбор вещи из космоса
{
	float dist = point_distanse(x, y, _itm->x, _itm->y);//загрузка вещи с помощью тагового луча

	if (dist<itempuckuprad)//подбор ближайшего
	{
		if (tractorpower > _itm->mass)
		{
			if (crgmgr->GetItem(_itm))
			{
				CheckMass();
				return true;
			}
			else
			{
				return false;
				//сообщение: отсек заполнен, невозможно загрузить
			};
		}
		else
		{
			//сообщение: слишком тяжелый объект
		};
	}
	else
	{
		if (dist<tractorradius)//тяговый луч
		{
			if (tractorpower > _itm->mass)
			{
				_itm->TractorBeam(x, y);

				tractor *trt;
				trt = new tractor(x, y, _itm, sysid);
				eff.push_back(trt);
			}
			else
			{
				//сообщение: недостаточно мощности луча
				tractor *trt;
				trt = new tractor(x, y, _itm, sysid);
				eff.push_back(trt);
			};


		};
		return false;
		//сообщение: Слишком далеко, нехаватает мощности тягового луча
	};
};

void ship::DropItem(int _id)//сброс вещи в космос
{
	crgmgr->DropItem(_id, sysid, x, y);
	CheckMass();
};

void ship::ScanForItems()//ищем все объекты в космосе и пытаемся их подтянуть, возможно потом отключю это(кнопка T)
{
	for (int i = 0; i< sectors.at(sysid)->cargoobjects.size(); i++)
	{
		PickItem(sectors.at(sysid)->cargoobjects.at(i));
	};
};

void ship::AddAggressiveToList(std::weak_ptr<dynamic> _attacker)//создаем и наполняем список целей, атаковавших корабль
{
	bool b = true;
	//attackers.push_back(_attacker);
	for (int i = 0; i < attackers.size(); i++)
	{
		auto vec = attackers.at(i).lock();
		auto tr = _attacker.lock();

		if (tr == vec)
		{
			b = false;
			break;
		}
		else
		{
			b = true;
		};
	};
	if (b == true)
	{
		attackers.push_back(_attacker);
	};
};

bool ship::GetNearlestTarget()
{
	float dist;

	for (int i = 0; i < attackers.size(); i++)
	{
		auto vec = attackers.at(i).lock();

		dist = point_distanse(x, y, vec->x, vec->y);
		if ((dist < sensorrange) &&(vec->visible))
		{
			SetTarget(vec);
			return true;
		};

	};
	return false;

};

bool ship::MoveToNearlestAggr()
{
	float dist;
	float neard = 999999;
	int t = -1;

	for (int i = 0; i < attackers.size(); i++)
	{
		auto vec = attackers.at(i).lock();

		dist = point_distanse(x, y, vec->x, vec->y);
		if ((dist < neard) && (sysid==vec->sysid) &&(vec->visible))
		{
			neard = dist;
			t = i;
		};
	};

	if (t >= 0)
	{

		auto vec = attackers.at(t).lock();
		FlyTo(vec->x, vec->y);
		return true;
	}
	
	return false;

};



void ship::CalculaceCollision()//расчет столкновений с ближайшими объектами
{
	for (int i = 0; i < collisions.size(); i++)
	{
		if (collisions.at(i).expired())//проверяем наличие 
		{
			collisions.at(i).reset();
			collisions.erase(collisions.begin() + i);
		}
		else
		{
			auto obj = collisions.at(i).lock();
			if (!mouse_on(x, y, obj->x, obj->y, CollRad, CollRad))
			{
				collisions.erase(collisions.begin() + i);
			};

		};
	};
};


void ship::FastUpdate(float _dt)//простые расчеты движений для кораблей в других системах(НЕ ДОДЕЛАНО)
{
	float newdt = _dt;

	syndist = point_distanse(x, y, syspozx[sysid], syspozy[sysid]);

	if (GPAUSED == false)//тут передвижение и все что требует реального времени на расчеты
	{
	};

	//TargetOperations();//проверяем наличие цели?
	//WeaponUpdate();//работа с орудиями

	//AggressiveTimer();//обновляем таймер флага военных действий
	//FirstAttackTimer();//таймер флага проявления агрессии

};

void ship::F_MoveTo(float _dt)//быстрое перемещение без больших расчетов
{
	float newdt = _dt;

	float n_speed = speed / 5000.0f;//маштабный фактор скорости для разных систем расчта движения

	x = x + (dx - x)*n_speed*newdt;//двигаемся в точке
	y = y + (dy - y)*n_speed*newdt;

	dir = point_dir2(dx, dy, x, y);


	//newdir = point_dir2(x, y, dx, dy);
	//dir += slow_rotate(rotatespeed, dir, newdir);
	dist = point_distanse(x, y, dx, dy);



	//if (dist<10)
	if (mouse_on(x, y, dx, dy, 500, 500))
	{
		state = STOP;
		/*speed = 0;
		acceleration = 0;*/

		if (warpengine == ON)//летим в другую систему
		{
			warpengine = RUN;
		};
	};

};

void ship::PatchCorr()
{

	newdir = point_dir2(x, y, dx, dy);

	if (warpengine != RUN)
	{

		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions.at(i).expired())//проверяем наличие 
			{
			}
			else
			{
				auto obj = collisions.at(i).lock();
				if (mouse_on(x, y, obj->x, obj->y, 50, 50))
				{
					newdir = point_dir2(x, y, obj->x, obj->y) + 3.14f / 2;
				};
			};
		};
	};
};

void ship::PozTest()
{
	if (warpengine == OFF)
	{
		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions.at(i).expired())//проверяем наличие 
			{
			}
			else
			{
				auto obj = collisions.at(i).lock();
				if (mouse_on(x, y, obj->x, obj->y, 50, 50))
				{
					float dist = 100;
					float tx = x + hge->Random_Float(-dist, dist);
					float ty = y + hge->Random_Float(-dist, dist);
					FlyTo(tx, ty);
				};
			};
		};
	};

};
