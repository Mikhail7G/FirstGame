#ifndef BULLCONTAINER_H
#define BULLCONTAINER_H

//Ётот класс €вл€етс€ контейнером контйнера, т.к. структура снар€дов наследуетс€ от dynamic и поэтому происходит наложение некоторых переменных.
//ѕоэтому пришлось сделать так.

#include <hge.h>
#include "Itemcore.h"
#include "bullets.h"
#include <memory>

using namespace std;



class bullcont:public cargo
{
public:

	shared_ptr<bullet> bull;//хранимый снар€д

	bullcont(shared_ptr<bullet> bull);
	~bullcont();

	shared_ptr<bullet> GetBull();

	void SetAmmo(int ammo);//добавить снар€дов



};

#endif