#include "projectile.h"


projectile::projectile(hgeSprite *_spr,float _Edmg,float _Kdmg,float _Tdmg,float _Rdmg)
{
	spr=_spr;
	speed=2000;
	

	Edmg=_Edmg;//повреждения от 4 видов урона
	Kdmg=_Kdmg;
	Tdmg=_Tdmg;
	Rdmg=_Rdmg;

	lifetime=5;
};

projectile::~projectile()
{
	switch (efftype)
	{
	case 0:
			if(effect>0)//Если есть эффект при взрыве снаряда то создаем его
			 {
			 explosion *expl;
			 expl=new explosion(effect,x,y,1,sysid);
			 eff.push_back(expl);
			 };
		break;
	case 1:
		if(animeff>0)//Если есть эффект при взрыве снаряда то создаем его
			 {
			 explosion *expl;
			 expl=new explosion(animeff,x,y,1,sysid);
			 eff.push_back(expl);
			 };
		break;

	};

};



void projectile::Update()
{
	//отправляем пульку в свободный полет 

	if(GPAUSED==false)//тут передвижение и все что требует реального времени на расчеты
	{
		x=x+cos(dir)*speed*dt;
		y=y+sin(dir)*speed*dt;

		if(!target.expired())//проверяем наличие цели
		{
			auto tr=target.lock();
			if(mouse_on(x,y,tr->x,tr->y,10,10))//столкновение с целью
			{
				if(oncourse)
				{
					Edmg=Edmg*damagemod*critdamage;
					Kdmg=Kdmg*damagemod*critdamage;
					Tdmg=Tdmg*damagemod*critdamage;
					Rdmg=Rdmg*damagemod*critdamage;

					tr->Damage(Edmg,Kdmg,Tdmg,Rdmg);
					if ((tr->type == 1) || (tr->type == 100))//определяет тип цели, и передает ей отакующего.
					{
						ship *sg;
						dynamic *d;
						d = tr.get();
						sg = dynamic_cast<ship*>(d);
						sg->AddAggressiveToList(parient);
					};
					kill=true;
				};
			};

			if(oncourse)//при срабатывании шанса на поподание, снаряд всегда следует за целью иначе снаряд непоподает
			{
				dir=point_dir2(tr->x,tr->y,x,y);
			};
		
		}else
		{
			target.reset();
			kill=true;
		};

		lifetime-=1*dt;//время жизни полета снаряда
		if(lifetime<0)
		{
			kill=true;
		};

	};

};

void projectile::Render()
{
	spr->RenderEx(x,y,dir,1,1);
};
void projectile::SetTarget(std::weak_ptr<dynamic> _target,float _x,float _y)
{
	target=_target;
	x=_x;
	y=_y;
	//считаем шанс крита
	//float ch=hge->Random_Float(0,100);
	float ch=30;

	if(ch>95)//300%крит
	{
		critdamage=3;
	};
	if((ch<95)&&(ch>75))//150% крита
	{
		critdamage=1.5;
	};
	if((ch<75)&&(ch>50))//120% крита
	{
		critdamage=1.2;
	};
	if((ch<50)&&(ch>25))//100% крита
	{
		critdamage=1.0;
	};
	if(ch<25)//50% крита
	{
		critdamage=0.5;
	};

	//пересчитывем базовый урон

	//направляем снаряд в полет
	if(target.expired())//проверяем наличие цели
		{
			target.reset();
		
		}else
		{
			auto tr=target.lock();
			if(oncourse)
			{
				dir=point_dir2(tr->x,tr->y,x,y);
			}
			else
			{
				dir=point_dir2(tr->x+hge->Random_Float(-20,20),tr->y+hge->Random_Float(-20,20),x,y);
			};
		};


};

