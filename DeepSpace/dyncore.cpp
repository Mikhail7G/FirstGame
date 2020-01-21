#include "dyncore.h"

dynamic::dynamic()
{
	x=0;
	y=0;
	kill=false;
	name="нет";
	sysid=0;
	nextsys=0;
	type=0;
	fraction=0;
	radius=1;
	sigradius=1;
	hp=0;
	maxhp=0;
	speed=0;
	maxspeed=0;
	syndist=0;
	visible=true;
	mass=0;
	cargomass=0;
	scale=1;

    id=Total;
	Total++;

	GlobalDynObj++;
	

};

dynamic::~dynamic()
{
	 hge->System_Log("DYN Killed");
	 Total--;
	 GlobalDynObj--;
};

void dynamic::Update()
{
		

};

void dynamic::Render()
{
		

};

void dynamic::Damage(float e,float k,float t,float r)
 {
	
 };

 

 int dynamic::GetTotal()
 {
	 return Total;
 }

 void dynamic::FirstAttack()
 {

 };

 void dynamic::FullLevelUp(int lvl)
 {
 };

 void dynamic::FastUpdate(float dt)
 {

 };

 void dynamic::AddCollisionTest(std::weak_ptr<dynamic> _col)
 {
	 bool b = true;
	 auto tr = _col.lock();
	 int poz = 0;

	 if (tr->type >= 0)//проверка на не коллизионные объекты мира
	 {

		 //attackers.push_back(_attacker);
		 for (int i = 0; i < collisions.size(); i++)
		 {
			 auto vec = collisions.at(i).lock();

			 if (tr == vec)
			 {
				 b = false;
				 break;
			 }
			 else
			 {
				 b = true;
				 poz = i;
			 };
		 };
		 if (b == true)
		 {
			 collisions.push_back(_col);
			 // tr->AddCollisionTest(collisions.at(poz));
		 };
	 };
 };

 void dynamic::CalculaceCollision()
 {

 };