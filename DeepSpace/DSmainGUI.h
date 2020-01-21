#ifndef DSMAINGUI_H
#define DSMAINGUI_H

/* ��� ������ ���� ����������� ����������, ��� �������� ��� ������ ���������� ��� ���� ��� ��������� */

#include <hge.h>
#include <hgefont.h>
#include < hgerect.h>
#include <memory>
#include "resizlabel.h"




class DSGUI
{
public:

	hgeSprite *back;//��� ������� ���
	bool render;//�������� �� �������?
	bool lockkeyboard;//����������� �� �����?
	float scalefactor;

	dynlabel *dyntxt;

	DSGUI();
	~DSGUI();

	virtual void Render();//������� ��������� ���, ��� ������� ����
	virtual bool MouseTest();//�������� ��������� ����� �� ���������� ������� ���
	virtual void Show();//�������� ������� ���



};


#endif