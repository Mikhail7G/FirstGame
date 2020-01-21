#ifndef PRADAR_H
#define PRADAR_H

#include <hge.h>
#include <hgeresource.h>
#include "dyncore.h"
#include <memory>
#include "cmath"
#include "planets.h"
#include "guicontrol.h"
#include "gamer.h"
#include "Itemcore.h"



extern float MouseX;
extern float MouseY;
extern int PlayerSys;
extern float xview;
extern float yview;
extern float ScreenWidth;//ширина экрана
extern float ScreenHeight;//высота экрана
extern float ScreenCenterX;
extern float ScreenCenterY;
extern float syspozx[];
extern float syspozy[];

extern hgeSprite  *hradar;
extern hgeSprite *radarRED[];
extern hgeSprite *border;
extern hgeSprite *star;

extern hgeFont	*fnt;

extern vector<shared_ptr<dynamic>> dyn;
extern vector<planet*> planetary;
extern vector<cargo*> cargoobjects;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern bool mouse_on(float x,float y,float mx,float my,float h,float w);

class radar :public MainGUI
{
public:
	player *plr;//игрок

	float x;
	float y;
	float transform;
	float tesval1;
	float borderx;
	float bordery;
	bool path;
	float dx;
	float dy;
	float dx1;
	float dy1;
	float scalefactor;//на сколько надо уменьшать 
	float sysrad;//радиус сектора

	//для преобразований радар->мир
	float mdx;
	float mdy;

	radar(player *plr);
	~radar();

	
	void Render();
	float Xreverer(float x);
	float Yreverer(float y);
	void ChangeMap();//смена карты
	bool MouseOn();
	



};




#endif