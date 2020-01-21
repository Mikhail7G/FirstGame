#ifndef SHIPENGINE_H
#define SHIPENGINE_H

#include <hge.h>
#include <hgesprite.h>
#include "Itemcore.h"

extern enum WeaponSize;//��� �� ������ ������ � ������ ������ ������ ���������������� ������

class engine :public cargo
{
public:
	int itemlevel;
	WeaponSize size;

	float speed;//�������� ���������� �.�. ��� ���������� ����
	float warptime;//����� ����� � ����
	float warprange;//��������� ������
	float impulse;//�������� ������� ����������

	//char *name;

	//hgeSprite *ico;

	engine(float warptime,float speed,WeaponSize size);
	~engine();

	void SetDefaultVar();//���������� ����������� ��������
	void GenerateRandomVar(int level,float rand,float dispread);
	void LevelUp(int level);//������� ������� ����

	engine *clone_default() const//��� ���� ������ ����������� ������� �������� ��� ��������� �������������!
	{
		ItemCount++;
		return new engine(*this);
	};

protected:
	//����������� ��������
	float d_mass;//����� ���������
	float d_speed;//�������� ���������� �.�. ��� ���������� ����
	float d_warptime;//����� ����� � ����

};



#endif