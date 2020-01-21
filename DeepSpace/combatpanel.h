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

extern hgeSprite  *hud1;//������ ������

extern hgeDTool *hgeTools;


extern float dt;
extern float MouseX;
extern float MouseY;

extern float ScreenWidth;//������ ������
extern float ScreenHeight;//������ ������
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
	float panx;//���������� ������
	float pany;
	float panx1;
	float pany1;
	float slotx[10];//����� ��� ������(����� 10 ��� ����������� ��������)
	float sloty[10];
	float scalefactor;//��������� ���� ��� ����������

	player *plr;//�����

	combathud(player *plr);
	~combathud();

	void Render();
	bool MouseTest();
	void Show();

	void CalculatePoz();//�������� ��������� ��� �������

protected:
	void WeaponOperations();//�������� ��� �������� ������
	void PlayerPanel();//��������� ������ ������
	void TargetPanel();//������ ����
};

#endif