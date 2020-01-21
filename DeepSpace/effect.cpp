#include "effect.h"


effect::effect()
{
	lifetime = 0;
	x = 0;
	y = 0;
	kill = false;
	sysid = 0;
};

effect::~effect()
{
	 hge->System_Log("EFF Killed");
};

void effect::Update()
{

};

void effect::Render()
{

};