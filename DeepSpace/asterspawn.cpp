#include "asterspawn.h"

asterctr::asterctr(float _timer)
{
	spawntimer=_timer;
	timer1=spawntimer;

};

asterctr::~asterctr()
{
};

void asterctr::Update()
{
	if(!GPAUSED)
	{
	//timer1-=1*dt;
	};

	if(timer1<0)
	{
		timer1=spawntimer;
		SpawnRandom();
	};
};

void asterctr::SpawnRandom()
{
	int rndsys=hge->Random_Int(0,sectors.size()-1);//выбираем сучайный известынй сектор
	//int rndsys = 0;

	std::shared_ptr<asteroid> ast(new asteroid(50, 50, rndsys));
	//dyn.push_back(ast);	
	sectors.at(rndsys)->AddToList(ast);
};