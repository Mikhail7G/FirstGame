#ifndef SPACEFOG_H
#define SPACEFOG_H

//космические туманности

#include <hge.h>
#include <hgesprite.h>
#include "bgobj.h"

extern float syspozx[];
extern float syspozy[];

extern char *BG_Spr[];
extern char *BG_PartSpr[];

extern float ScreenCenterX;
extern float ScreenCenterY;

//extern hgeSprite *BGsprites[];

extern int PlayerSys;


class spacefog: public bgobj
{
public:

	hgeSprite *spr;
	HTEXTURE tex;
	int SpriteID;

	spacefog(int layer,int sysid,float x,float y,int SpriteID);
	~spacefog();
	void Render();
	void LoadTex();//загрузка текстуры бг по необходимости
	void ChangeMap();//тут проверка в каком секторе игрок и происходит загрузка или выгрузка нужной текстуры

protected:
	float div;

	bool reloaded;//сброс текстур

};


#endif