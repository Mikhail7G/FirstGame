#include "bullcontainer.h"

bullcont::bullcont(shared_ptr<bullet> _bull)
{
	bull=_bull;
	name=bull->name;
    type=3;
	ico=bull->ico;
	description=bull->description;
	count=bull->totalCount;
	ItemCount++;
};

bullcont::~bullcont()
{
	bull.reset();
};

shared_ptr<bullet> bullcont::GetBull()
{
	return bull;
};

void bullcont::SetAmmo(int _ammo)
{
	bull->totalCount = _ammo;
}