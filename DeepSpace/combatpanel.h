#ifndef COMBATPANEL_H
#define COMBAPTANEL_H

#include <hge.h>
#include <hgefont.h>
#include <memory>

#include "gamer.h"
#include "guicontrol.h"
#include "hgeDTool.h"
#include "DSmainGUI.h"

extern hgeFont	*fnt;
extern hgeFont *mainf;
extern HGE *hge;

extern hgeSprite  *hud1;//панель игрока

extern hgeDTool *hgeTools;


extern float dt;
extern float MouseX;
extern float MouseY;

extern float ScreenWidth;//ширина экрана
extern float ScreenHeight;//высота экрана
extern float ScreenCenterX;
extern float ScreenCenterY;
extern float xview;
extern float yview;
extern hgeSprite *itemhelp;
extern hgeSprite *wpt[];

extern bool GPAUSED;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);


class combathud : public DSGUI
{
public:
	float panx;//координаты панели
	float pany;
	float panx1;
	float pany1;
	float slotx[10];//слоты под орудия(всего 10 для большинства кораблей)
	float sloty[10];
	float scalefactor;//маштабный коэф для расстояний

	player *plr;//игрок

	combathud(player *plr);
	~combathud();

	void Render();
	bool MouseTest();
	void Show();

	void CalculatePoz();//пересчет координат для рендера

protected:
	void WeaponOperations();//действия над орудиями игрока
	void PlayerPanel();//обновляем панель игрока
	void TargetPanel();//панель цели
};

#endif