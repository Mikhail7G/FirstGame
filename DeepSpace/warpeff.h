#ifndef WARPEFF_H
#define WARPEFF_H

#include "effect.h"

#include <vector>

#include <hge.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"

#include "dsanim.h"
#include "dsanimate.h"

extern HANIM    *animportal[];

class warpportal: public effect
{
public:

	float effdir;//����������� �������


    warpportal(float x,float y,float lifetime,int sysid);//����� ��������
	~warpportal();

	void Update();
	void Render();

protected:
	float timer0;//����� ��������� �������
	float timer1;//����� ������ �������
	int type;// 0 -���������, 1 - ���������
	int state;//0-���������� 1-��������

	hgeAnim *init;
	hgeAnim *runing;

};



#endif