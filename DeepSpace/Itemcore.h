#ifndef ITEMCORE_H
#define ITEMCORE_H


// ���� ����� �������� �� �������� ����� � ����, ������������ ����� ���������, � ����� ������ ��� ���� �����. ����� ���: ������ �������, �������, ���� � ������.

#include <hge.h>
#include "cmath"
#include <hgesprite.h>
#include <memory>

#include "dsanim.h"
#include "dsanimate.h"

#include "effect.h"
#include "explosion.h"

//#include "shuphull.h"
//#include "weapon.h"
//#include "bullets.h"
//#include "shipengine.h"
//#include "shipengine.h"

using namespace std;
extern HGE *hge;
extern float dt;
extern int PlayerSys;
extern int ItemCount;

extern float syspozx[];//���������� �������� � �������
extern float syspozy[];

extern HANIM    *cargobox;
extern HANIM    *animeffects[];
extern vector<effect*> eff;



static int coreid=0;


class cargo
{
public:
	bool moving;//����, ���������� �� �������� ���������� ����� ������� �� ��������� ������
	bool kill;//��������� �� ������?
	bool hidekill;//��� ����� ����������� ����� ���������� ��� �������
	bool canstak;//����� �� ������� � ����?

	int count;//������� ����� � ����
	int sysid;//������
	int fraction;//1-����

	int slotid;// � ����� ����� ����� ������ ������(����� ��� ������)

	float x;//���������� � �������
	float y;
	float dx;
	float dy;

	float mass;

	float ItemDispread;//������� ������� ����������

	int type;//0-������,1-���������,2-������,3-������,4-����
	int state;//0-������,1-�� ������� ��� � ��������


	HANIM    *crgbox;
	hgeAnim *box;//������ �� �� ��� ����������, ���������,��������� ��� �������������
	hgeSprite *ico;//�������� ����

	char *name;//�������� �������
	char *description;//�������� �������
	
	cargo();// ���������� � � � ��������������� � ��������� ����������� �������!
    virtual	~cargo();

	virtual void Render();
	void Update();
	void MoveCrg();//����� ������ � ��������� ������ ��������� ������� ����� � ��������� �����������
	void Install();//���������� ������ �� �������

	void CreateAnim();//������� �������� ����� ����������� �.�. ���������� 1 ��������� ��������
	void InitializeSpace(int sysid,float x,float y);//������� ������� � �������
	void InitializeInside();//������� ������� � �������� ������ ��� �� �������
	void ShipDrop(int sysid,float x,float y);//�������� ���� � �������
	void TractorBeam(float x,float y);//������� ���

	//������ �������
	void SetPoz(int sysid,float x,float y);//���������� ������� ������������ ���������� ������� ���������
	void SetFixedPoz(int sysid,float x,float y);//���������� ������� ������������ ��������� ��������� �������

protected:
	float timer1;
	float speed;
	float dispread;
	int zz;




};



//class cargo
//{
//public:
//
//	bool moving;//����, ���������� �� �������� ���������� ����� ������� �� ��������� ������
//
//	int sysid;//������
//
//	float x;//���������� � �������
//	float y;
//	float dx;
//	float dy;
//
//	int type;//0-������,1-���������,2-������,3-������
//	int state;//0-������,1-�� ������� ��� � ��������
//
//	hgeAnim *img;//������ �� �� ��� ����������, ���������,��������� ��� �������������
//	hgeSprite *ico;//�������� ����
//
//	char *name;
//	
//	hull *shiphull;//������ �������
//	engine *shipengine;//��������� �������
//	turret *weapon;//������
//	std::shared_ptr<bullet> bull;
//
//	cargo(int sysid,float x,float y);// ���������� � � � ��������������� � ��������� ����������� �������!
//	~cargo();
//	cargo(int sysid,float x,float y,hull *shiphull);//�������� ������ � ���������
//	cargo(int sysid,float x,float y,engine *shipengine);//�������� ��������� � ���������
//	cargo(int sysid,float x,float y,turret *weapon);//�������� ������ � ���������
//	cargo(int sysid,float x,float y,std::shared_ptr<bullet> bull);//�������� ������ � ���������
//
//	void Render();
//	void SetPoz(float x,float y);//���������� ������� ������������ ���������� ������� ���������
//	void MoveCrg();//����� ������ � ��������� ������ ��������� ������� ����� � ��������� �����������
//
//protected:
//	float timer1;
//	float speed;
//	float dispread;
//
//
//
//
//
//
//
//};





#endif