#ifndef SHIPSUPPLY_H
#define SHIPSUPPLY_H

#include <hge.h>
#include <vector>
#include <hgefont.h>
#include "guicontrol.h"
#include < hgerect.h>
#include "DSmainGUI.h"
#include "resizlabel.h"
#include "gamer.h"
#include "bullcontainer.h"

extern HGE *hge;
extern float dt;

extern hgeFont	*fnt;
extern hgeFont *mainf;

extern hgeSprite *shipinfospr;
extern hgeSprite *cargobayslot;

extern hgeSprite *wpt[];

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);

extern float MouseX;
extern float MouseY;
extern float ScreenCenterX;
extern float ScreenCenterY;
extern float xview;
extern float yview;
extern float ScreenWidth;//ширина экрана
extern float ScreenHeight;//высота экрана


class shipsinfo :public DSGUI
{
public:
	player *plr;//игрок

	int layer;//слой интерфейса
	bool loadmen;//меню загрузки
	bool loadmenlock;//блокировка нажатия на кнопку под меню загрузкой

	float scalefactor;

	float pozx;
	float pozy;

	float slotx[10];
	float sloty[10];

	float engx;//координаты слота двигателя
	float engy;

	shipsinfo(player *plr);
	~shipsinfo();

	void Render();
	void Show();//показывать элемент
	bool MouseTest();//проверка наведения мышки на интерфейс
	bool MouseOn();

protected:
	int lastid;
	int lastwslot;//указатель на наведенный слот орудия
	int lastbullslot;//указатель на наведенный слот снаряда

	void WeaponInfo();//выводит инфу об установленном орудии
	void BulletInfo();//выводит инфу об снаряде
	void HullInfo();//выводит инфу о корпусе
	void EngInfo();//вывод инфы о двигателе

	void RenderMain();
	void CreateLoadMenu(int id);
	void MouseOperations();


};



#endif