#ifndef SHIPHULL_H
#define SHIPHULL_H

#include <hgeparticle.h>
#include <hge.h>
#include "dsanim.h"
#include <hgesprite.h>
#include "Itemcore.h"

extern enum WeaponSize;

static int ITEMID=0;

class hull :public cargo
{
public:
	int wslot;//������ ��� ������
	int itemlevel;
	float scale;//������ �������
	float engrad;//�� ������� ���� �������� ���� �� ��������� ��� ��� ����������� ������������
	float maxhp;//������� �������� ����� ���������
	float sensorrange;//��������� ������� ����
	///������������� 4 ����� �����: ��������,������������,��������,������������.
	float explres;
	float kinres;
	float termres;
	float radiores;
	float sigradius;//�������� ������ �������

	//char *name;

	WeaponSize enginesize;//������ ���������
	WeaponSize wslotsize;//������ ������ ������

	HANIM *anim;//�������� �������
	hgeParticleSystem *eng;//���� �� ���������
	//hgeSprite *ico;//�������� �������

	hull(hgeParticleSystem *eng,HANIM *anim);
	~hull();
	void SetDefaultVar();//���������� ����������� ��������
	void SetDispreadVar(float dispread);//���������� ��������� ��������� � ���������
	void GenerateRandomVar(int level,float rand,float dispread);
	void LevelUp(int level);//������� ������� ����

	hull *clone_default() const//��� ���� ������ ����������� ������� �������� ��� ��������� �������������!
	{
		ItemCount++;
		return new hull(*this);
	};

protected:
	//����������� ���������� ���. ��� ��������� ������
	float d_scale;
	float d_maxhp;

	float d_explres;
	float d_kinres;
	float d_termres;
	float d_radiores;

	float d_sensorrange;
	float d_mass;
	float d_sigradius;

	int zz;

};


#endif