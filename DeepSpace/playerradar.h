#ifndef PLAYERRADAR_H
#define PLAYERRADAR_H

#include <hge.h>
#include <hgeresource.h>
#include "dyncore.h"
#include <memory>
#include "cmath"
#include "planets.h"
#include "guicontrol.h"
#include "gamer.h"
#include "Itemcore.h"
#include "DSmainGUI.h"


extern float MouseX;
extern float MouseY;
extern int PlayerSys;
extern float xview;
extern float yview;
extern float ScreenWidth;//������ ������
extern float ScreenHeight;//������ ������
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

extern float point_distanse(float x1, float y1, float x2, float y2);
extern bool mouse_on(float x, float y, float mx, float my, float h, float w);


class dsradar : public DSGUI
{
public:
	player *plr;//�����

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
	float scalefactor;//�� ������� ���� ��������� 
	float sysrad;//������ �������

	//��� �������������� �����->���
	float mdx;
	float mdy;

	dsradar(player *plr);
	~dsradar();

	void Render();
	bool MouseTest();
	void Show();

protected:
	int sec_start;//������ �������� ���������
	int sec_end;//�� ���� ���������




};


#endif