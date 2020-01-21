#ifndef PLANETS_H
#define PLANETS_H
#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"
#include <memory>
#include "dyncore.h"


using namespace std;
extern HGE *hge;
extern float dt;

extern hgeSprite *shadow;

extern int PlayerSys;

extern float MouseX;
extern float MouseY;

//extern hgeSprite *PlanetsSpr[];

extern char *PLN_Spr[];

extern float syspozx[];//���������� �������� � �������
extern float syspozy[];

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);
extern float slow_rotate(float speed,float dir,float newdir);

class planet
{
public:
	int sysid;

	float x;
	float y;
	float dx;
	float dy;
	float speed;//�������� ��������
	float alt;//������
	float scale;
	float border;//������ �������
	float dir;//���� �������� ������������ ������

	char *name;
	int fraction;//��� ����� �� ������� 0-�����, 1 - ����
	float population;//����� �������
	int type;//��� ������ 0 - ���, 1 - ��������, 2-������������
	int resourse;//��������� ������� ���������� ��������� 0 - ������ 1 - �������� 2 - ������� � ��


	vector<std::weak_ptr<dynamic>>attackers;//������ ����, ��� ���� ���� �������

	vector<std::weak_ptr<dynamic>>defense_ships;//������ �������� �������� �������

	bool canland;

	hgeSprite *spr;
	HTEXTURE tex;
	int SpriteID;

	planet(int sysid,float alt,float speed,float scale,int SpriteID);
	planet(int sysid, int syspoz);
	~planet();
	void Update();
	void Render();
	void LoadTexture();//�������� �������� �������
	void ChangeMap();//����� ����� ��� 
	void PeopleKill();//�������� ������� �� ���������� � ��.
	void FastUpdate(float dt);//�������� ���������� �������

	bool MouseTest();//�������� ��������� �����

	void AddAggressiveToList(std::weak_ptr<dynamic> attacker);//��������� ���������� ����� � ������

	void AddDefenceShip(weak_ptr<dynamic> ships);//��� �������� ������� �� ������� �������� ��� � ������

protected:
	bool reloaded;// ������� �� ��������

	float poptimer;//������ �������� ��������� �� �������
	float pt1;
	void Ptimer1();
	void Ptimer1_F(float dt);
	void UpdatePopulation();//������� ��������� ��� ������


};


#endif