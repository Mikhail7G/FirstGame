#include "Defenderbot.h"


defender::defender()
{
	fraction = 0;
	state = 0;

	t_timer1 = 5;
	timer1 = t_timer1;
	ready_to_fly = true;
	PilotId++;
	p_id = PilotId;

};

defender::~defender()
{
	hge->System_Log("защитный бот уничтожен");
};

int defender::GetId()
{
	return p_id;
};

void defender::LogicUpdate()
{
	switch (state)
	{
	case 0:
		CheckShip();
		break;
	case 1:
		Patrol();
		break;
	case 2:
		ReturnToBase();
		break;
	case 3:
		WarActions();
		break;
	};

	SleepTimer();

};

void defender::ScangeMap(int id)
{

};

void defender::ShipLost()
{
	Ship.reset();
	delete this;
}

void defender::CheckShip()
{
	if (Ship.expired())
	{
		Ship.reset();
		
	}
	else
	{
		auto shp = Ship.lock();
		ready_to_fly = true;

		//проверки различных систем корабля
		if (shp->scharge_flag1 == false)//если на корабле нет патрон
		{
			ready_to_fly = false;//летим за новыми на базу, или потом ближайшую не враждебную планету
		};
	

		if (ready_to_fly)//проверка на возможность воевать
		{
			state = 1;
			GetBadTarget();
		}
		else
		{
			state = 2;
		};
	};

};

void defender::Patrol()
{
	if (Ship.expired())
	{
		Ship.reset();

	}
	else
	{
		auto shp = Ship.lock();

		if (shp->state == 0)//если корабль стоит, то ищем новую точку полета
		{
			float x;
			float y;

			x = homeplanet->x + hge->Random_Float(-1000, 1000);
			y = homeplanet->y + hge->Random_Float(-1000, 1000);

			shp->FlyTo(x, y);
		};
		

	};
	
};

void defender::SleepTimer()
{
	timer1 -= 1 * dt;

	if (timer1 < 0)
	{
		t_timer1 = hge->Random_Int(3, 6);
		timer1 = t_timer1;
		state = 0;
	};
};

void defender::Alarm()
{
	auto shp = Ship.lock();

	for (int i = 0; i < shp->attackers.size(); i++)
	{
		auto ata = shp->attackers.at(i).lock();
		homeplanet->AddAggressiveToList(ata);
	};
	

};

void defender::WarActions()
{
	auto shp = Ship.lock();


	if (shp->GetNearlestTarget())
		{
			shp->autopilot = 1;
			shp->Fire();
		}
	else
	{
		if (!shp->MoveToNearlestAggr())
		{
			state = 0;
		};


	};

};


void defender::DebugDraw()
{
	auto shp = Ship.lock();

	fnt->printf(shp->x, shp->y+5, HGETEXT_LEFT, "state:%i",state);
	fnt->printf(shp->x, shp->y + 25, HGETEXT_LEFT, "upd:%.1f", timer1);
	fnt->printf(shp->x, shp->y + 40, HGETEXT_LEFT, "test_s:%i", ready_to_fly);
	fnt->printf(shp->x, shp->y + 55, HGETEXT_LEFT, "ammo:%i", shp->scharge_flag1);

	hge->Gfx_RenderLine(shp->x, shp->y, homeplanet->x, homeplanet->y);


};

void defender::GetBadTarget()
{
	auto shp = Ship.lock();

	for (int i = 0; i < homeplanet->attackers.size(); i++)
	{
		auto tr = homeplanet->attackers.at(i).lock();

		if (tr->sysid == shp->sysid)
		{
			shp->AddAggressiveToList(tr);
			state = 3;
		};
	};
};

void defender::LoadAmmo()
{
	auto shp = Ship.lock();
	auto crg = shp->crgmgr->crg;//получаем список всех вещей в кузове

	for (int i = 0; i < crg.size(); i++)
	{
		if (crg.at(i)->type == 3)//заряжаем снаряд в орудие
		{
			for (int t = 0; t < shp->weapons.size(); t++)
			{
				bullcont *cnt;
				cnt = dynamic_cast<bullcont*>(shp->crgmgr->crg.at(i));//преобразуем тип вещи в контейнер снаряда
				shp->weapons.at(t)->SetBullet(cnt->GetBull());
			};
		};
	};
};

void defender::ReturnToBase()
{
	auto shp = Ship.lock();
	auto crg = shp->crgmgr;
	shp->FlyTo(homeplanet->x, homeplanet->y);

	//пока так
	float dist = point_distanse(shp->x, shp->y, homeplanet->x, homeplanet->y);

	if (dist < 100)
	{
		for (int i = 0; i < crg->crg.size(); i++)//перезаряжаем снаряды
		{
			if (crg->crg.at(i)->type == 3)
			{
				bullcont *cnt;
				cnt = dynamic_cast<bullcont*>(shp->crgmgr->crg.at(i));//преобразуем тип вещи в контейнер снаряда
				cnt->SetAmmo(62);
			};
		};
		LoadAmmo();
		shp->scharge_flag1 = true;
	};
};