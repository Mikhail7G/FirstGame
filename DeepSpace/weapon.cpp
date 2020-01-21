#include "weapon.h"


turret::turret(float _reloadtimer,float _ammoreload,float _fireradius,float _optimal,int _ammoclip,float _sigradius,float _tracking)
{
	
	ammoclip=_ammoclip-1;
	ammo=ammoclip;
	reloadtimer=_reloadtimer;
	timer1=reloadtimer;
	ammoreload=_ammoreload;
	timer2=ammoreload;
	fireradius=_fireradius;
	autofire=true;
	armed=true;
	x=0;
	y=0;
	dir=0;
	shoot=false;
	optimal=_optimal;
    sigradius=_sigradius;
	hitchance=0;	
	tracking=_tracking;

	damagemod=1;
	bonusdamage=0;
	DPS=0;
	alphastrike=0;

	name="нет";
	itemlevel=0;
	mass=1;
	type=2;

	ITEMID1++;
	zz=ITEMID1;

};

turret::~turret()
{
	RemoveBullet();
	hge->System_Log("ќрудие:%s уничтожен в системе:%i",name,sysid);	
};

void turret::Update(float _x,float _y)
{
	x=_x;
	y=_y;
	ReloadTimer();

};

void turret::Fire()
{
	if(armed)
	{
		if(target.expired())//провер€ем наличие цели
		{
			target.reset();
			shoot=false;
		
		}else
		{
			auto trr=target.lock();
			//if(point_distanse(x,y,trr->x,trr->y) < fireradius)
			{
				if(bull)
				{
					Launch();//запускаем снар€д
					armed=false;//даем команду на перезар€дку

					auto ln=parient.lock();
					ln->FirstAttack();//при каждом выстреле провер€ем, необходим ли флаг агрессии стрел€ющего
					
				};
			};
		};
	};
};

bool turret::SetBullet(std::shared_ptr<bullet> _bull)
{
	if ((_bull->BSize == Wsize) && _bull->totalCount > 0)
	{
		ammo=0;
		armed=false;
		RemoveBullet();
		timer1=reloadtimer;
		bull=_bull;//так же тут пересчитываютс€ факторы, вли€ющие на оруди€ от снар€да +\- бонусы к дальности,оптималу и т.д.
		SetBonusFromBullet();
		CalculateDPS();	
		return true;
	}
	else
	{
		return false;
	};
};

void turret::RemoveBullet()//тут будет разр€дка оруди€
{
	if(bull)
	{
		//bull->totalCount+=ammoclip;//возвращ€ем снар€ды
	};
	SetClearVar();
	bull.reset();	
};

void turret::DestroyBullet()//тут будет разр€дка оруди€
{
	bull.reset();
};

void turret::SetParient(std::weak_ptr<dynamic> _parient)
{
	parient=_parient;
};

void turret::Launch()
{
	if(parient.expired())//передаем снар€ду некоторые данные от того кто стрельнул
		{
			parient.reset();		
		}else
		{
			auto prr=parient.lock();
			auto trr=target.lock();

			hitchance=0;

			x=x+hge->Random_Float(-5,5);
			y=y+hge->Random_Float(-5,5);

			sysid = prr->sysid;

			std::shared_ptr<bullet> pr(bull->clone());//делаем копию снар€да который загружен
			//расчитывем шанс поподани€ отношение% радиусов сигнатур цели и оруди€+ дистанци€ до оптимала
			float d1=point_distanse(x,y,trr->x,trr->y);//рассто€ние до цели

			//расчитывем трекинг оруди€
			float distanse = point_distanse(prr->x,prr->y,trr->x,trr->y);//дистанци€ до цели
			float tdir=point_direction(prr->x,prr->y,trr->x,trr->y);//направление от оруди€ до цели
			float cordir1=tdir+90;//пр€мой угл
			float trgdir=trr->dir;//считаем направление цели, немного криво но работает
			float trgx=trr->x+cos(trgdir)*50;
			float trgy=trr->y+sin(trgdir)*50;
			float newtrgdir=point_direction(trr->x,trr->y,trgx,trgy);//тут показанно в какую сторону направлена цель
			float correctdir=cordir1-newtrgdir;
			double cosangle=cos(correctdir*3.14/180);
			float transsped=abs(trr->speed*cosangle);//”глова€ скорость тут
			//
			hitchance=pow(0.5,pow((max(0,d1-optimal)/fireradius),2)+pow( (transsped/(distanse*tracking))*(sigradius/trr->sigradius),2))*100;

			float ch=hge->Random_Float(0,100);

			if(ch<hitchance)//если есть така€ возможность то стрел€ем по цели
			{
				pr->oncourse=true;
			};
			pr->hitchance=hitchance;
			pr->damagemod=damagemod;
			////////////////////
			pr->SetTarget(target,x,y);
			pr->SetParient(parient);
			pr->sysid=prr->sysid;//передаем данные

			//dyn.push_back(pr);
			sectors.at(sysid)->AddToList(pr);
		};

};

void turret::SetTarget(std::weak_ptr<dynamic> _target)
{
	target=_target;
	//shoot=false;
	
};

void turret::StartFiring()
{
	if(bull)
	{
		 if(!shoot)
		   { 
			 shoot=true; 
		   }else
		   { 
			shoot=false;
		   };
	};
};

void turret::CalculateDPS()
{
	if(bull)
	{
		float dd;
		dd=bull->Edmg+bull->Kdmg+bull->Tdmg+bull->Rdmg;
		DPS=(dd*damagemod)/(reloadtimer+ammoreload)*(ammoclip+1);
		alphastrike=dd*damagemod;
	}
	else
	{
		alphastrike=0;
		DPS=0;
	};
};

void turret::ReloadTimer()
{
	if(!GPAUSED)
	{
		if(!armed)//если незар€жено то
		{
			if(ammo==0)//при пустой обойме запускаем таймер1
			{
				if(Timer1())
				{
					if(bull)
					{
						ammo=min(bull->totalCount,ammoclip);//то перезар€жаем обойму
						bull->totalCount-=ammoclip;

						auto par = parient.lock();
						par->scharge_flag1 = true;

						if(ammo<=0)//если не можем перезар€дить, то удал€ем снар€д
						{
							bull->totalCount=0;
							RemoveBullet();

							auto par = parient.lock();
							par->scharge_flag1 = false;
						};
					}
					else
					{
						SetClearVar();
						CalculateDPS();
					};
				};
			}
			else//тут таймер2 
			{
				if(Timer2())
				{
					ammo--;//отнимаем один снар€д
				};
			};
		}
		else
		{
			if(shoot)//если включена автострельба, то стрел€ем
			{
				shoot=false;
				if(autofire)
				{
					shoot=true;
				};
				Fire();
			};
		};
	};
};

bool turret::Timer1()
{
	timer1-=1*dt;
	if(timer1<0)
	{
		timer1=reloadtimer;
		armed=true;
		return true;
	}else
	{
		return false;
	};
};

bool turret::Timer2()
{
	timer2-=1*dt;
	if(timer2<0)
	{
		timer2=ammoreload;
		armed=true;
		return true;
	}else
	{
		return false;
	};
};

void turret::DropTarget()
{
	target.reset();
	shoot=false;
};

void turret::SetDefaultVar()
{
	d_ammoclip=ammoclip;
	d_reloadtimer=reloadtimer;
	d_ammoreload=ammoreload;
	d_fireradius=fireradius;
	d_optimal=optimal;
	d_tracking=tracking;
	d_sigradius=sigradius;
	d_damagemod=damagemod;
	d_mass=mass;


};

void turret::GenerateRandomVar(int _level,float _rand,float _dispread)
{//начинаем веселье(
	int lvl=_level;//ур вещи
	itemlevel=lvl;
	float rand=_rand;//коэффициент понижени€ параметров вещей, дефолт 0,02f
	rand=0.03f;//от 0.02f до 0.08f 

	float rec;//коэффициент снижени€ характеристик
	rec=(rand*lvl)/(1+rand*lvl);

	//считем фаллоф и оптимал
	float dist1;//без потри значени€
	dist1=d_fireradius+d_fireradius*(0.1f*lvl);
	float dist2;//с прогрессивной потерей значени€
	dist2=d_fireradius+d_fireradius*(0.1f*(lvl-1)*rec);
	//считаем новый радиус атаки
	fireradius=d_fireradius+(dist1-dist2)/2;

	dist1=d_optimal+d_optimal*(0.1f*lvl);
	dist2=d_optimal+d_optimal*(0.1f*(lvl-1)*rec);
	optimal=d_optimal+(dist1-dist2)/2;

	//считаем сигнатуру турели
	float sig1;//сигнатура без снидени€
	sig1=d_sigradius*lvl*0.1f;
	float sig2;//сигнатура с уменьшением значений
	sig2=d_sigradius*(0.1f*(lvl-1)*rec);
	sigradius=d_sigradius-(d_sigradius*0.5f*(sig2/sig1));

	//считаем кол-во снар€дов в обойме
	float arm1;
	arm1=d_ammoclip+d_ammoclip*(0.1f*lvl);
	float arm2;
	arm2=d_ammoclip+d_ammoclip*(0.1f*(lvl-1)*rec);
	ammoclip=d_ammoclip+(arm1-arm2)/5;
	ammo=ammoclip;

	//считаем перезар€дку
	float ammor1;
	ammor1=d_ammoreload+d_ammoreload*(0.1f*lvl);
	float ammor2;
	ammor2=d_ammoreload*(0.1f*(lvl-1)*rec);
	ammoreload=d_ammoreload-(d_ammoreload*0.5f*(ammor2/ammor1));

	ammor1=d_reloadtimer+d_reloadtimer*(0.1f*lvl);
	ammor2=d_reloadtimer*(0.1f*(lvl-1)*rec);
	reloadtimer=d_reloadtimer-(d_reloadtimer*0.5f*(ammor2/ammor1));

	//считаем множитель урона
	float dmg1;
	dmg1=d_damagemod+d_damagemod*(0.1f*lvl);
	float dmg2;
	dmg2=d_damagemod+d_damagemod*(0.1f*(lvl-1)*rec);
	damagemod=d_damagemod+(dmg1-dmg2)/2;

	//считаем трекинг
	float trc1;
	trc1=d_tracking+d_tracking*(0.1f*lvl);
	float trc2;
	trc2=d_tracking+d_tracking*(0.1f*(lvl-1)*rec);
	tracking=d_tracking+(trc1-trc2)/5;

	float mass1=d_mass+d_mass*(0.1f*lvl);
	float mass2=d_mass+d_mass*(0.1f*(lvl-1)*rec);
	mass=d_mass+((mass1-mass2)/1.5f);


	GetClearVar();
	SetBonusFromBullet();
	CalculateDPS();//финал


};

void turret::LevelUp(int _level)
{
	int level=_level;
	itemlevel+=level;
	GenerateRandomVar(itemlevel,0,0);

};

void turret::GetClearVar()
{
	s_fireradius=fireradius;
	s_optimal=optimal;
	s_sigradius=sigradius;
	s_tracking=tracking;
};

void turret::SetClearVar()
{
	fireradius=s_fireradius;
	optimal=s_optimal;
	sigradius=s_sigradius;
	tracking=s_tracking;
};

void turret::SetBonusFromBullet()
{
	if(bull)
	{
		fireradius=s_fireradius+fireradius*(bull->fireradius_b);
		optimal=s_optimal+optimal*(bull->optimal_b);
		sigradius=s_sigradius-sigradius*(bull->sigradius_b);//радиус ”ћ≈Ќ№Ўј≈ћ
		tracking=s_tracking+tracking*(bull->tracking_b);
	}
	else
	{
		SetClearVar();
	};
};