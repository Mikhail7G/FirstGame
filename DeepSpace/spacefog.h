#ifndef SPACEFOG_H
#define SPACEFOG_H

//����������� ����������

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
	void LoadTex();//�������� �������� �� �� �������������
	void ChangeMap();//��� �������� � ����� ������� ����� � ���������� �������� ��� �������� ������ ��������

protected:
	float div;

	bool reloaded;//����� �������

};


#endif