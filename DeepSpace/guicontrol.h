#ifndef GUICONTROL_H
#define GUICONTROL_H

#include <hge.h>
#include <hgefont.h>
#include < hgerect.h>
#include <memory>


extern float MouseX;
extern float MouseY;


class MainGUI
{
public:

	hgeSprite *spr;//��� ������� ���
	MainGUI();
	~MainGUI();
	
	virtual void Render();
	virtual bool MouseOn();//��������� ��������� ����� �� ����� ���

};

#endif