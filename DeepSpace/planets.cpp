#include "planets.h"

planet::planet(int _sysid, float _alt, float _speed, float _scale, int _SpriteID)
{
	////alt=_alt;
	//alt = _alt * 1000+hge->Random_Float(-500,500);

	//SpriteID = _SpriteID;
	////speed=_speed/100;
	//speed = 0.01f/(alt/1000);
	//scale=_scale;
	//spr = new hgeSprite(0, 0, 0, 0, 0);
	//name="Нет";
	//sysid=_sysid;
	//dx=syspozx[sysid];
	//dy=syspozy[sysid];
	////dir = hge->Random_Float(0, 6.20f);
	//dir = 0;
	//border=scale*500;
	//fraction = 0;
	//population = 0;
	//type = 0;
	//resourse = 0;

	//poptimer = 30;
	//pt1 = poptimer;

	//reloaded = false;
};

planet::planet(int _sysid, int _syspoz)
{
	//alt=_alt;
	alt = _syspoz * 1000 + hge->Random_Float(-200, 200);

	SpriteID = 0;
	//speed=_speed/100;
	speed = 0.01f / (alt / 1000);
	scale = hge->Random_Float(0.2f, 0.7f);
	spr = new hgeSprite(0, 0, 0, 0, 0);
	name = "Нет";
	sysid = _sysid;
	dx = syspozx[sysid];
	dy = syspozy[sysid];
	//dir = hge->Random_Float(0, 6.20f);
	dir = 0;
	border = 500;
	fraction = 0;
	population = 0;
	type = 0;
	resourse = 0;

	poptimer = 30;
	pt1 = poptimer;

	reloaded = false;


	switch (_syspoz)//в зависимости от удаленности от солнца выбираем ботатство ресурсов
	{
	case 1:
		resourse = 0;
		SpriteID = 20;
	break;
	case 2:
		resourse = 1;
		SpriteID = 20;
		break;
	case 3:
		resourse = 2;
		SpriteID = hge->Random_Int(10, 12);
		break;
	case 4:
		resourse = 3;
		SpriteID = hge->Random_Int(10, 12);
		break;
	case 5:
		resourse = 2;
		SpriteID = 20;
		break;
	case 6:
		resourse = 1;
		SpriteID = 20;
		break;
	}

};



void planet::Update()
{
	if(!GPAUSED)
	{
		x=dx+alt*cos(dir);
		y=dy+alt*sin(dir);
		dir+=(speed*dt);//Опасный участок!!!!
		if(dir>(6.28f))
		{
			dir=0;
		};
		Ptimer1();
	};
};

void planet::Render()
{
	spr->RenderEx(x,y,0,scale,scale);
	//shadow->RenderEx(x,y,dir+3.14/2,scale,scale);
};

void planet::LoadTexture()
{
	tex = hge->Texture_Load(PLN_Spr[SpriteID]);
	spr->SetTexture(tex);
	spr->SetTextureRect(0, 0, hge->Texture_GetHeight(tex), hge->Texture_GetWidth(tex));
	//spr->SetHotSpot(hge->Texture_GetHeight(tex) / 2, hge->Texture_GetHeight(tex) / 2);
	spr->SetHotSpot(250, 250);
	//spr->SetBlendMode(BLEND_COLORMUL);
};

void planet::ChangeMap()
{
	if (sysid == PlayerSys)//если сектор не игрока то обнуляем текстуры
	{
		LoadTexture();
		reloaded = true;
	}
	else//иначе загружаем то что нужно
	{
		if (reloaded)
		{
			spr->SetTexture(0);
			spr->SetTextureRect(0, 0, 0, 0);
			spr->SetHotSpot(0, 0);
			hge->Texture_Free(tex);
			reloaded = false;
		};
	};
};

void planet::Ptimer1()
{
	pt1 -= dt;
	if (pt1 < 0)
	{
		pt1 = poptimer;
		UpdatePopulation();
	};
};

void planet::UpdatePopulation()
{
	if (fraction > 0)
	{
		population = population + population*hge->Random_Float(0.03f,0.08f);
	};

};

void planet::PeopleKill()
{
	population -= 1 + hge->Random_Int(5, 25);
	if (population < 0)//если кончатся все жители, то планета станет заброшенной
	{
		population = 0;
		fraction = 0;
		type = 0;

	};
};

void planet::FastUpdate(float _dt)
{
	if (!GPAUSED)
	{
		dir += (speed*_dt);
		if (dir>(6.28f))
		{
			dir = 0;
		};
		Ptimer1_F(_dt);
	};

};

void planet::Ptimer1_F(float _dt)
{
	pt1 -= _dt;
	if (pt1 < 0)
	{
		pt1 = poptimer;
		UpdatePopulation();
	};
};


bool planet::MouseTest()
{
	hgeRect *rr = new hgeRect();
	spr->GetBoundingBoxEx(x, y, 0, scale, scale, rr);
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


void planet::AddAggressiveToList(std::weak_ptr<dynamic> _attacker)//создаем и наполняем список целей, атаковавших корабль
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

void planet::AddDefenceShip(weak_ptr<dynamic> ships)
{
	defense_ships.push_back(ships);
};

