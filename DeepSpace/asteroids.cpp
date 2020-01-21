#include "asteroids.h"


asteroid::asteroid(float _x, float _y, int _sysid, hgeSprite *_spr)
{
	float tmp;
	tmp=hge->Random_Float(-360,360);
	x=syspozx[_sysid]+12000*cos(tmp);
	y=syspozy[_sysid]+12000*sin(tmp);
	spr=new hgeSprite(*_spr);
	drawtupe=0;
	hp=10;
	speed=hge->Random_Float(25,255);
	dir=point_dir2(syspozx[_sysid],syspozy[_sysid],x,y)+hge->Random_Float(-40*3.14/180,40*3.14/180);
	name="Астероид";
	type=0;
	sysid=_sysid;
	AsteroidCount++;
	sigradius=500;
	scale=1.0f;

	cor_x = syspozx[_sysid] + hge->Random_Float(-1000, 1000);
	cor_y = syspozy[_sysid] + hge->Random_Float(-1000, 1000);
};

asteroid::asteroid(float _x,float _y,int _sysid,HANIM *_anim)
{
	float tmp;
	tmp=hge->Random_Float(-360,360);
	x=syspozx[_sysid]+12000*cos(tmp);
	y=syspozy[_sysid]+12000*sin(tmp);

	img=new hgeAnim(_anim,hgeAnim::PLAY_LOOP);//крутится постоянно
	drawtupe=1;

	hp=10;
	speed=hge->Random_Float(25,255);
	dir=point_dir2(syspozx[_sysid],syspozy[_sysid],x,y)+hge->Random_Float(-40*3.14/180,40*3.14/180);
	name="Астероид";
	type=0;
	sysid=_sysid;
	AsteroidCount++;
	sigradius=10;
	scale=1.0f;

	cor_x = syspozx[_sysid] + hge->Random_Float(-1000, 1000);
	cor_y = syspozy[_sysid] + hge->Random_Float(-1000, 1000);
};

asteroid::asteroid(float _x,float _y,int _sysid)
{
	float tmp;
	tmp=hge->Random_Float(-360,360);
	x=syspozx[_sysid]+12000*cos(tmp);
	y=syspozy[_sysid]+12000*sin(tmp);

	img=new hgeAnim(animitem[0],hgeAnim::PLAY_LOOP);//крутится постоянно
	drawtupe=1;

	hp=10;
	speed=hge->Random_Float(25,255);
	dir=point_dir2(syspozx[_sysid],syspozy[_sysid],x,y)+hge->Random_Float(-40*3.14/180,40*3.14/180);
	name="Астероид";
	type=0;
	sysid=_sysid;
	AsteroidCount++;
	sigradius=10;
	scale=1.0f;

	cor_x = syspozx[_sysid] + hge->Random_Float(-1000, 1000);
	cor_y = syspozy[_sysid] + hge->Random_Float(-1000, 1000);
};

void asteroid::Update()//двигаем астероид, гравитация солнца влияет на его траекторию
{
	if(!GPAUSED)
	{
		x=x+cos(dir)*speed*dt;
		y=y+sin(dir)*speed*dt;
		syndist=point_distanse(x,y,syspozx[sysid],syspozy[sysid]);
		if(syndist<2500)//влияние гравитации на траекторию
		{
			float tmp1;
			tmp1=0;
			tmp1=point_dir2(syspozx[sysid],syspozy[sysid],x,y);
			dir-=slow_rotate(0.003,dir,tmp1);	
			speed+=10*dt;
		};
		if(syndist<100)
		{
			kill=true;
		};
		if(syndist>13000)//если далеко отлетает, то разворачиваем
		{
           dir=point_dir2(syspozx[sysid],syspozy[sysid],x,y)+hge->Random_Float(-40*3.14/180,40*3.14/180);
		   speed = hge->Random_Float(50, 255);
		};
	};

	CalculaceCollision();

};

void asteroid::Render()//рисуем спрайт, так же затемняем отдаленные от солнца объекты
{
	  float light=255-syndist*lighting;

	switch (drawtupe)
	{
	   case 0:
			  spr->RenderEx(x,y,0,scale);//рисуем сам спрайт
				if(light<1)//освещение, в зависимости от удаленности от центра
				{
				   light=0;
				};
				spr->SetColor(ARGB(255,light,light,light));

				if(syndist<1000)//эффект падения на солнце
				{
					scale=syndist/1000;
				}
				else
				{
					scale=1;
				};
	   break;
       case 1:
			img->RenderEx(x,y,(dir+3.14/2),scale,scale);
			img->Update();
			if(light<1)//освещение, в зависимости от удаленности от центра
				{
				   light=0;
				};
				img->sprite->SetColor(ARGB(255,light,light,light));

				if(syndist<1000)//эффект падения на солнце
				{
					scale=syndist/1000;
				}
				else
				{
					scale=1;
				};
		break;
	};

	if (DrawCollisionData)
	{
		for (int i = 0; i < collisions.size(); i++)
		{
			if (collisions.at(i).expired())//проверяем наличие 
			{
			}
			else
			{
				auto obj = collisions.at(i).lock();
				hge->Gfx_RenderLine(x - 10, y, obj->x, obj->y, ARGB(255, 255, 0, 0));
			};
		};
		fnt->printf(x, y + 20, HGETEXT_LEFT, "c:%i", collisions.size());
	};

};

asteroid::~asteroid()
{
	switch (drawtupe)
	{
	case 0:
		delete spr;
	break;
	case 1:
		 delete img;
	break;
	};
	AsteroidCount--;
	
	explosion *effex;//тут только пока анимицией, сделать возможность менять на частицы
	effex=new explosion(animeffects[0],x,y,5,sysid);
	eff.push_back(effex);

	 cargo *crg;
	 int z=hge->Random_Int(1,5);
	 int cc=hge->Random_Int(1,10);
	 for(int i=0;i<z;i++)
	 {
		 crg=new ruda();
		 crg->InitializeInside();
		 crg->ShipDrop(sysid,x,y);
		 crg->count=cc;
		 crg->mass=crg->mass*cc;
		 sectors.at(sysid)->AddItemToList(crg);//добавляем руду в список системы
	 };



};

void asteroid::Damage(float _e,float _k,float _t,float _r)
{
	float dm=_e+_k+_t+_r;
	hp=-dm;
	if(hp<1)
	{
		kill=true;
	};

};

void asteroid::ShipCollision()
{
	
};

void asteroid::FastUpdate(float _dt)
{
	float newdt = _dt;
	float n_speed = speed / 5000.0f;//маштабный фактор скорости для разных систем расчта движения

	if (!GPAUSED)
	{
		x = x + (cor_x - x)*n_speed*newdt;
		y = y + (cor_y - y)*n_speed*newdt;

		if (mouse_on(x, y, syspozx[sysid], syspozy[sysid], 100, 100))//убивается об солнце
		{
			kill = true;
		}

		if (mouse_on(x, y, cor_x, cor_y, 500, 500))//улетает в космос
		{
			if (go_around)
			{
				cor_x = hge->Random_Float(-10000, 10000);
				cor_y = hge->Random_Float(-10000, 10000);
				go_around = false;
			};
		}

		if (!mouse_on(x, y, syspozx[sysid], syspozy[sysid], 10000, 10000))//летит назад
		{
			cor_x = syspozx[sysid] + hge->Random_Float(-1000, 1000);
			cor_y = syspozy[sysid] + hge->Random_Float(-1000, 1000);
			go_around = true;
		};




	};



};

void asteroid::CalculaceCollision()
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

			if (mouse_on(x, y, obj->x, obj->y, 50, 50))
			{
				obj->Damage(0, 50, 0, 0);
				this->Damage(0, 50, 0, 0);
			};

		};


	}
};