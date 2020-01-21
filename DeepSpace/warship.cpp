#include "warship.h"



//ship::ship(int _sysid, HANIM *_anim,hgeParticleSystem *_eng)
ship::ship(int _sysid, hull *_shiphull)
{
	sysid = _sysid;//������ ��������� ��������
	x = syspozx[sysid] + hge->Random_Float(-100.0f, 100.0f);
	y = syspozy[sysid] + hge->Random_Float(-100.0f, 100.0f);


	type = 1;

	shiphull = 0;
	shipengine = 0;
	//������� �������� �������
	shiphull = _shiphull;//������� ������ �������
	anim = shiphull->anim;
	img = new hgeAnim(anim, hgeAnim::PLAY_LOOP);//�������� ���������


	rotatespeed = 0.04f;//0.04

	eng = new hgeParticleSystem(*shiphull->eng);//������ ������ ���������
	eng->FireAt(x, y);
	smoke = true;//��� �� ���������
	//��������� ������ �� ������� �������
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
	//�������������� ������������� ������� ����� ��������� �� ���������
	explres = (shiphull->explres) / 100;
	kinres = (shiphull->kinres) / 100;
	termres = (shiphull->termres) / 100;
	radiores = (shiphull->radiores) / 100;

	fraction = shiphull->fraction;//����� ����� �� ������ pilot

	EXParmor = maxhp / (1 - (explres + kinres + termres + radiores) / 4);//���������� ������� �������� ����� ��������� �����

	wslot = shiphull->wslot;//������ ��� ������

	crgmgr = new cargomanager();
	crgmgr->maxslot = 28;//������ � ����. ������

	crgmgr->shiphull = shiphull;

	warponse = true;
	warptime = 0;
	wrpt1 = warptime;

	underAttack = false;
	attackTimer = 30;//����� �������� 30 ���
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

ship::~ship()//������� �������� � ��� ��������� ��� ���� �������
{
	pilot->ShipLost();
	hge->System_Log("�������:%s ��������� � �������:%i", name, sysid);
	delete img;//������� ��������� �������� �������


	explosion *expl;//��� ������ ���� ���������, ������� ����������� ������ �� �������
	expl = new explosion(animeffects[0], x, y, 5, sysid);
	eff.push_back(expl);

	//���������� ��� �� ����� � ��� ������, ���� ���(����� � % ������)
	crgmgr->DropEngine(sysid, x, y);
	crgmgr->DropHull(sysid, x, y);


	for (int i = 0; i < crgmgr->shipwpn.size(); i++)
	{
		weapons.at(i)->RemoveBullet();//��������� ������ � ����������� �� ����
		weapons.at(i)->DropTarget();
	};
	crgmgr->DropWeapon(sysid, x, y);//���������� ������, ����������� � ������ �������

	crgmgr->DropAll(sysid, x, y);//���������� ��� ���������

	delete crgmgr;

	obj.reset();//��������� ������ �� ������ ����

	GlobalShipObj--;
};

void ship::Update()//��� ��� �������
{
	syndist = point_distanse(x, y, syspozx[sysid], syspozy[sysid]);//���� ���, ����� �����������

	if (GPAUSED == false)//��� ������������ � ��� ��� ������� ��������� ������� �� �������
	{
		//�������� 
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

	TargetOperations();//��������� ������� ����?
	WeaponUpdate();//������ � ��������

	AggressiveTimer();//��������� ������ ����� ������� ��������
	FirstAttackTimer();//������ ����� ���������� ��������

	CalculaceCollision();//��������� ������������

	pilot->LigicUpdate();//��������� ������.


};

void ship::Render()//������ �������� � ��� �������
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
	//��������� ������� � ����������� �� �������� �� ������
	/*float light=255-syndist*lighting;
	if(light<1)
	{
	light=0;
	};*/
	//img->sprite->SetColor(ARGB(alpha,255,255,255));

	if (DrawCollisionData)
	{
		//����� ������������
		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions.at(i).expired())//��������� ������� 
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

	
	
	state = FLY;//������ ����� �� �����
	warpengine = OFF;//��������� ���� ����
	warponse = true;//

	ResetSpeed();//���������� ��������

};

void ship::MoveTo()//������� �������� ������� � �������� � FlyTo �����������
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

		PozTest();//������������� ��������� �������

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


void ship::WarpOn(int _nextsys)//�������� ������� � ����� �������� � ������ �������
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
		//���������� ������� � ����� �������� � ������ �������
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

void ship::WarpRun()//������� � ����� ������
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

		//������ ������ ��������� ����������
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

		sectors.at(nextsys)->AddToList(obj);//��������� ������� � ������ ������
		//sectors.at(sysid)->RemoveFromList(obj);//����� ��� �������, ��� ��� �� �� ���.


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

bool ship::SetTarget(std::weak_ptr<dynamic> _target)//��������� ���� ��� ��������
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
		//���������: ���� ������� ������
	};
};


void ship::TargetOperations()
{
	if (target.expired())//��������� ������� ����
	{
		target.reset();
		//���������: ���� ��������
	}
	else
	{
		auto trr = target.lock();
		float tdist = point_distanse(x, y, trr->x, trr->y);
		float tdir = point_direction(x, y, trr->x, trr->y);

		if ((tdist > sensorrange) || (trr->sysid!=sysid))//����� ���� �� ������ ������ ������
		{
			target.reset();
			DropTarget();
			//���������: ���� ������� ������
		};


		switch (autopilot)
		{
		case 1://����� ������������� �� ����������� ���������
			if (tdist>attackradius)//���� ������ �� ����� � ����
			{
				FlyTo(trr->x, trr->y);
			}
			else
			{
				if (tdist< (attackradius - 50))//����� ����� �� ����
				{
					float dxx = trr->x + cos(tdir*3.14 / 180 + 0.001f)*attackradius;
					float dyy = trr->y + sin(tdir*3.14 / 180 + 0.001f)*attackradius;
					FlyTo(dxx, dyy);
				};
			};
			break;
		case 2://����� ������������� �� ������������ ���������
			if (tdist>maxattackradius)//���� ������ �� ����� � ����
			{
				FlyTo(trr->x, trr->y);
			}
			else
			{
				if (tdist< (maxattackradius - 50))//����� ����� �� ����
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

void ship::WeaponUpdate()//���������� ������������� ������
{
	for (int i = 0; i<weapons.size(); i++)
	{
		weapons.at(i)->Update(x, y);
	};
};

void ship::Fire()//����� �� ���� ������ �� ������� ����(�� ������ F)
{
	for (int i = 0; i<weapons.size(); i++)
	{
		SetTrgToWeap();
		weapons.at(i)->StartFiring();
	};
};

void ship::SetTrgToWeap()//��������� ���� ������
{
	for (int i = 0; i<weapons.size(); i++)
	{
		weapons.at(i)->SetTarget(target);
	};
};

void ship::SetOneTrgToWeap(int _weaponid)//�������� ���� ��� ����������� ������(����� ������ ����)
{
	weapons.at(_weaponid)->SetTarget(target);
};


void ship::Damage(float _e, float _k, float _t, float _r)//��������� �����
{
	//����������� ���� � ������ ������������� ��� �����
	float Edmg = _e - _e*explres;
	float Kdmg = _k - _k*kinres;
	float Tdmg = _t - _t*termres;
	float Rdmg = _r - _r*radiores;

	float totaldmg = Edmg + Kdmg + Tdmg + Rdmg;//��������� ���� ����

	//���� �� �����
	hp -= totaldmg;

	if (hp<1)//��� �����=)
	{
		kill = true;
		obj.reset();
	};

	dmgtext *txt;
	txt = new dmgtext(totaldmg, x, y, sysid);
	eff.push_back(txt);

	AggressiveActive();//��������� �� ������ �� �������

};

void ship::DropTarget()//����� ���� ��� ���� ������
{
	target.reset();
	for (int i = 0; i < weapons.size(); i++)
	{
		weapons.at(i)->DropTarget();
	};
};

void ship::GetWeaponDPS()//������� ����� �� ������
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
		if (weapons.at(i)->optimal<attackradius)//�������� ����� ��������� ��������� ��� ��������� �������
		{
			attackradius = weapons.at(i)->optimal;//������� �� ����������� ����������
		};
		if ((weapons.at(i)->fireradius + weapons.at(i)->optimal)<maxattackradius)//�������� ����� ��������� ��������� ��� ��������� �������
		{
			maxattackradius = (weapons.at(i)->fireradius + weapons.at(i)->optimal);//������� �� ����������� ����������
		};
	};

};

void ship::RecalculateVariables()
{
	//���� �� ������������
};

bool ship::InstallEngine(engine *_shipengine)//��������� ��������� �� �������
{
	shipengine = _shipengine;

	if (shipengine->size == shiphull->enginesize)//��������� �� ������������ ������ 
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
		//���������: ������ ��������� ����������
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
		//���������:��� ���������� �����
	};
};

bool ship::InstallWeapon(turret *_weapon)//��������� ������ �� �������
{
	weapon = _weapon;

	if (weapon->Wsize == shiphull->wslotsize)
	{
		if (weapons.size()<wslot)
		{
			weapons.push_back(weapon);
			crgmgr->shipwpn.push_back(weapon);
			UpgradeHull();
			GetWeaponDPS();//������� ���

			return true;
		}
		else
		{
			return false;
			//���������: ��� ��������� ������� ��������� ������
		};
	}
	else
	{
		return false;
		//���������: ������ ������ ����������
	};

};

bool ship::RemoveWeapon(int _id)//������� ������
{
	int id = _id;
	if (crgmgr->GetItem(weapons.at(id)))
	{
		weapons.at(id)->RemoveBullet();
		weapons.at(id)->DropTarget();
		weapons.erase(weapons.begin() + id);

		UpgradeHull();
		GetWeaponDPS();//������� ���

		return true;
	}
	else
	{
		return false;
		//���������: �������� ����� ����, ���������� ���������
	};
};

void ship::AggressiveActive()
{
	underAttack = true;
	attacktim1 = attackTimer;//� ������ ������ �� ������� ��������� ������ �������, � ��������� ��������� �� ����� ���, ����� ���

	pilot->Alarm();

	if (firstAttack)
	{
		firstAttacktim1 = firstAttackTim;//���� ������� �������� ���������� ����, �� ��� ����� ����� ��� �������, ���� �� �� ������ ���� �� ������.
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
			attackers.clear();//������� ������ ��������, ������� ����������� � �����.
		};
	};
};

void ship::FirstAttack()
{
	if (target.expired())//��������� ������� ����	
	{
		target.reset();

	}
	else
	{
		auto trr = target.lock();

		if (!trr->firstAttack)//���� ���� �� �����������, �� �� ���������� ������������
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

void ship::UpgradeHull()//��������� ��������� �������
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

	EXParmor = maxhp / (1 - (explres + kinres + termres + radiores) / 4);//���������� ������� �������� ����� ��������� �����

	GetWeaponDPS();
	CheckMass();

};

void ship::CheckMass()//���������� ����� �������
{
	cargomass = 0;//���������� �� 0

	for (int i = 0; i<weapons.size(); i++)
	{
		cargomass += weapons.at(i)->mass;
	};

	//������� ����� ������������� ������� � ���� �������� � �������� ������

	//����� ����� �������
	mass = (shiphull->mass) + cargomass + (crgmgr->totalmass);


	maxspeed = (shipengine->speed)*(((shipengine->speed) * 100 / mass) / 100);
	//speed=maxspeed;

};

void ship::FullLevelUp(int _lvl)//�������� �������� ���� ������������� ����� �� �������
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

void ship::ResetSpeed()//���������� �������� �������+ ���� ��������� ������� ��������
{
	CheckMass();
};

void ship::SetItem(cargo *_itm)//�������� ���� � ����. �����
{
	if (crgmgr->GetItem(_itm))
	{
		CheckMass();
	}
	else
	{
		//���������: ����� ��������, ���������� ���������
	};
};


bool ship::PickItem(cargo *_itm)//������ ���� �� �������
{
	float dist = point_distanse(x, y, _itm->x, _itm->y);//�������� ���� � ������� �������� ����

	if (dist<itempuckuprad)//������ ����������
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
				//���������: ����� ��������, ���������� ���������
			};
		}
		else
		{
			//���������: ������� ������� ������
		};
	}
	else
	{
		if (dist<tractorradius)//������� ���
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
				//���������: ������������ �������� ����
				tractor *trt;
				trt = new tractor(x, y, _itm, sysid);
				eff.push_back(trt);
			};


		};
		return false;
		//���������: ������� ������, ���������� �������� �������� ����
	};
};

void ship::DropItem(int _id)//����� ���� � ������
{
	crgmgr->DropItem(_id, sysid, x, y);
	CheckMass();
};

void ship::ScanForItems()//���� ��� ������� � ������� � �������� �� ���������, �������� ����� ������� ���(������ T)
{
	for (int i = 0; i< sectors.at(sysid)->cargoobjects.size(); i++)
	{
		PickItem(sectors.at(sysid)->cargoobjects.at(i));
	};
};

void ship::AddAggressiveToList(std::weak_ptr<dynamic> _attacker)//������� � ��������� ������ �����, ����������� �������
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



void ship::CalculaceCollision()//������ ������������ � ���������� ���������
{
	for (int i = 0; i < collisions.size(); i++)
	{
		if (collisions.at(i).expired())//��������� ������� 
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


void ship::FastUpdate(float _dt)//������� ������� �������� ��� �������� � ������ ��������(�� ��������)
{
	float newdt = _dt;

	syndist = point_distanse(x, y, syspozx[sysid], syspozy[sysid]);

	if (GPAUSED == false)//��� ������������ � ��� ��� ������� ��������� ������� �� �������
	{
	};

	//TargetOperations();//��������� ������� ����?
	//WeaponUpdate();//������ � ��������

	//AggressiveTimer();//��������� ������ ����� ������� ��������
	//FirstAttackTimer();//������ ����� ���������� ��������

};

void ship::F_MoveTo(float _dt)//������� ����������� ��� ������� ��������
{
	float newdt = _dt;

	float n_speed = speed / 5000.0f;//��������� ������ �������� ��� ������ ������ ������ ��������

	x = x + (dx - x)*n_speed*newdt;//��������� � �����
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

		if (warpengine == ON)//����� � ������ �������
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
			if (collisions.at(i).expired())//��������� ������� 
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
			if (collisions.at(i).expired())//��������� ������� 
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
