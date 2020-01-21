#ifndef DSMAP_H
#define DSMAP_H

#include <hge.h>
#include <vector>
#include <hgefont.h>
#include "DSmainGUI.h"
#include < hgerect.h>

#include "sector.h"
#include "gamer.h"

#include "dsanim.h"
#include "dsanimate.h"

extern HGE *hge;
extern float dt;

extern hgeFont	*fnt;
extern hgeFont *mainf;

extern HANIM    *map_poz;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);
extern float point_distanse(float x1, float y1, float x2, float y2);

extern float MouseX;
extern float MouseY;
extern float ScreenCenterX;
extern float ScreenCenterY;
extern float xview;
extern float yview;
extern float ScreenWidth;//������ ������
extern float ScreenHeight;//������ ������

extern int PlayerSys;

extern vector<sector*> sectors;

extern hgeSprite *SysIcons[];
extern hgeSprite *sysmap;

extern float GlobalMapScaleFactor;


extern float point_distanse(float x1, float y1, float x2, float y2);

class dsmap : public DSGUI
{
public:
	float map_scale_factor;//��������� ���� ��� �����

	hgeAnim *img;//������ �� �� ��� ����������, ���������,��������� ��� �������������
	player *plr;//�����

	int flyto;//���� ������

	float scalefactor;//���� �����

	bool Selected;//������� �� ������� ��� ������?

	float mapx;
	float mapy;

	float sysx;
	float sysy;

	float dist;
	float maxdist;

	dsmap(player *plr);
	~dsmap();

	void Render();
	bool MouseTest();
	void Show();

protected:
	int targetid;//�������� �� �������

	float map_movx;
	float map_movy;//�������� �� �����

	int break_tim;
	
	bool drawpt;//�������� ����?

	void DrawPath();//�������� ���� �������

	void CalculatePath();//������������ ���� �� ������ �������


	int startsys;//������ ��������� ������

	bool complete_path;//�������� �� ����� ����?

	float near_dist;//���������� �� ��������� �������
	float far_dist;//��������� ����� �������� � ������� ��������

	vector<int> systems_pos;//����������� � ������ �������

	void CommandsUpdate();//��������� ������ �� ������� ����������


	///������ ��� ����������
	int max_errors = 1000;//����� ��������
	int p_sys;//������� ������
	int cur_sys;
	float min_dist = 0;//����������� ����������

	vector<float> distanses;//���������� ����� ���������
	vector<bool> clear_systems;//������ ���������� ������
	vector<int> last_calc_sys;//������� �� ������� ����� ������
	int next_sys;
	int slow_calc_cur_sys;//������� ������� ��� ���������

	void SlowCalc();//��������� ������ 


};

#endif