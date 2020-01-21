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
extern float ScreenWidth;//������ ������
extern float ScreenHeight;//������ ������


class shipsinfo :public DSGUI
{
public:
	player *plr;//�����

	int layer;//���� ����������
	bool loadmen;//���� ��������
	bool loadmenlock;//���������� ������� �� ������ ��� ���� ���������

	float scalefactor;

	float pozx;
	float pozy;

	float slotx[10];
	float sloty[10];

	float engx;//���������� ����� ���������
	float engy;

	shipsinfo(player *plr);
	~shipsinfo();

	void Render();
	void Show();//���������� �������
	bool MouseTest();//�������� ��������� ����� �� ���������
	bool MouseOn();

protected:
	int lastid;
	int lastwslot;//��������� �� ���������� ���� ������
	int lastbullslot;//��������� �� ���������� ���� �������

	void WeaponInfo();//������� ���� �� ������������� ������
	void BulletInfo();//������� ���� �� �������
	void HullInfo();//������� ���� � �������
	void EngInfo();//����� ���� � ���������

	void RenderMain();
	void CreateLoadMenu(int id);
	void MouseOperations();


};



#endif