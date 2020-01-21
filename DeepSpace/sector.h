#ifndef SECTOR_H
#define SECTOR_H


//��� ���� ���������� �� ������� � �������, ������ ���������� �������,��� ��������� �������, �������� �� �� � ��.


#include <hge.h>
#include <hgefont.h>
#include <vector>
#include <memory>
#include "Itemcore.h"

#include "dsanim.h"
#include "dsanimate.h"
#include "dyncore.h"

#include "planets.h"

using namespace std;

extern double Call_Time;

extern HGE *hge;
extern float dt;

extern HANIM    *mapeffects[];//������������� �������

extern vector<shared_ptr<dynamic>> dyn;

extern float CollRad;

extern int PlayerSys;
extern float syspozx[];//���������� �������� � �������
extern float syspozy[];

extern enum Fraction;//���� ����������� ������� ��������� � gamecore

static int Count=0;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);

class sector
{
public:
	int id;

    int raiting;//������� �������� �������, �� 0 �� 100. - �������� ������������ ������� �� ����
	int level;//������� �������

	float x;//��������� ������� � ������������
	float y;

	bool hide;//������ �� ������� �� ��������

	hgeSprite *ico;//�������� �������
	HANIM *ani;
	hgeAnim  *aico;//������������� ������� �������

	Fraction frac;

	char *name;//���

	vector<planet*> planetlist;//������ ������, ������� ������ � ������

	vector<shared_ptr<dynamic>> objects;//��� ������������ ������� � ������ �������

	vector<cargo*> cargoobjects;//���� � ������� �������

	sector(float x,float y,hgeSprite *ico);
	sector(float x, float y, HANIM *ani);
	~sector();
	void Render(float x,float y);
	void AddToList(shared_ptr<dynamic> obj);//��������� ������ � ������, ��� ������������� ��� ��� �������� � ������
	void RemoveFromList(shared_ptr<dynamic> obj);//������� ������ �� �����

	void Update();//���������� �������� � ������ �������
	void Render();//������ ������� � ������ ������

	void PreInit();//��������� ������� � Update();

	void FastUpdate();//��������������� ������� � ���������� ��������

	float call_time;
	float last_time;

	void AddItemToList(cargo* item);//��������� ������ � ������

	int cur_col_obj;




};


#endif