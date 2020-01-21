#include "pilot.h"


pilotctr::pilotctr()
{

};

pilotctr::~pilotctr()
{
	hge->System_Log("Бот уничтожен");
};


void pilotctr::ScangeMap(int _sysid)
{

};

void pilotctr::ShipLost()
{
	delete this;
}

void pilotctr::LigicUpdate()
{

};

void pilotctr::Alarm()
{

};

void pilotctr::NoAmmo()
{

};
