#ifndef WEAPON_H
#define WEAPON_H

#include "cmath"
#include <memory>
#include <stdlib.h>
#include <stdio.h>

#include <hge.h>

#include "dsanim.h"
#include "dsanimate.h"
#include "dyncore.h"
#include "bullets.h"
#include "Itemcore.h"
#include "sector.h"


extern HGE *hge;

extern float dt;

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);
extern float point_direction(float x1,float y1,float x2,float y2);

extern vector<shared_ptr<dynamic>> dyn;
extern vector<sector*> sectors;

extern enum WeaponSize;


static int ITEMID1=0;

//����� turret - ����� ������, � ������ ����� ����� ����� �������� �������,������ � �.�.

class turret: public cargo
{
public:
	int itemlevel;//������� ����
	int ammoclip;//������� ������ � ������
	int ammo;//������� ������ � ��������

	float timer1;//������ ����������� ������
	float timer2;//������ ������� ������ ������
	float reloadtimer;//������ �����������
	float ammoreload;//�������� ����� ���������� ������ ������.
	float fireradius;//������ ��������
	float optimal;//������������� ������ ��������
	float tracking;//�������� �������� ������
	float sigradius;//������������� ������ ���������� �����


	//������ �� ����:
	float damagemod;//����������� ����� ��� ������
	float bonusdamage;//���. ����, ��������� �� ��� ���� ����� ��� ������ �����- ��� � %

	float DPS;//���� � �������
	float alphastrike;//���� � 1 �������

	float hitchance;//���� ��������� �� ����



	bool autofire;//���� �� ������������
	bool armed;//�������� ������?
	bool shoot;//����� �� ��������� ������

	//hgeSprite *ico;//�������� �����

	std::weak_ptr<dynamic> target;//���� �����
	std::weak_ptr<dynamic> parient;//� ���� ����������� �����
	std::shared_ptr<bullet> bull;//�������� ������ � �����
	//std::weak_ptr<bullet> bull;//�������� ������ � �����

	WeaponSize Wsize;//������ ������
	//char *name;//��� ������

	
protected:
	float x;
	float y;
	float dir;
	//����������� ��������� ��� ������, ����� ��� ��������� ��������� �����
	int d_mass;
	int d_ammoclip;
	float d_reloadtimer;
	float d_ammoreload;
	float d_fireradius;
	float d_optimal;
	float d_tracking;
	float d_sigradius;
	float d_damagemod;

	float zz;

	//��� ��������� ����� ��������� ����, �� �� ������� ����� ���� �������
	float s_fireradius;
	float s_optimal;
	float s_sigradius;
	float s_tracking;


public:
	turret(float reloadtimer,float ammoreload,float fireradius,float optimal,int ammoclip,float sigradius,float tracking);
	~turret();
	virtual void Update(float x,float y);//��� ���� �������� �� ������� ���� � ������ �������� �����������.
	virtual void StartFiring();//������ ������������?
	virtual void Fire();//�������� ���������� ����� �������
	virtual void Launch();//��������� ������
	virtual void SetTarget(std::weak_ptr<dynamic> target);//������������� ���� ��� �����
	virtual void DropTarget();//����� ����
	virtual bool SetBullet(std::shared_ptr<bullet> bull);//�������� ������
	virtual void RemoveBullet();//��������� ������ � ������� ������ �� �������
	virtual void DestroyBullet();//����������� ��� ������ ������� �� ����� ������ � ������ ��� ��� ������ �������, �� ��������� ����������� ������� � �������
	virtual void CalculateDPS();//���������� ����
	virtual void SetParient(std::weak_ptr<dynamic> parient);//��� �������� �� �����

	virtual void SetDefaultVar();//������������� ���������� �������� ��� ����� ���� ������

	virtual void GenerateRandomVar(int level,float rand,float dispread);
	virtual void LevelUp(int level);//������� ������� ����
	virtual void SetBonusFromBullet();//��������� ������ �� �������

	virtual void GetClearVar();//��������� ���������� �� ������� �������
	virtual void SetClearVar();//����� �������� ������� ���������� ����������� ��������

	turret *clone_default() const//��� ���� ������ ����������� ������� �������� ��� ��������� �������������!
	{
		ItemCount++;
		return new turret(*this);
	};



protected:
	void ReloadTimer();
	bool Timer1();
	bool Timer2();



};


#endif