#ifndef BGOBJ_H
#define BGOBJ_H

//данный класс отвечает за все фоновые объекты в игре, туманности мусор и прочее

#include <hge.h>
#include <hgesprite.h>

extern float syspozx[];
extern float syspozy[];

extern HGE *hge;

extern float ScreenCenterX;
extern float ScreenCenterY;

extern int PlayerSys;


class bgobj
{
public:

	float dx;
	float dy;

	float x;
	float y;

	int sysid;

	int layer;//слой, от него зависит скорость движения 

     bgobj();
	virtual ~bgobj();
	virtual void Render();
	virtual void ChangeMap();//смнета карты

};


#endif