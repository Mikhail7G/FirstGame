#ifndef DSGUICTR_H
#define DSGUICTR_H

/* ��� �������� � ����������� ��� �������� ���������� */

#include "DSmainGUI.h"
#include <vector>

using namespace std;

extern bool MouseOnGUI;

class guictr
{
public:
	vector<DSGUI*> GUI_list;//������ ���� ��������� ��� ��� ����������


	guictr();
	~guictr();

	void Render();//���������� ���
	void AddCtrl(DSGUI *gi);//��������� ����� ������� � ���
	void MouseTest();

	bool CloseAll();//������� ���


};


#endif