#ifndef DSGUICTR_H
#define DSGUICTR_H

/* “ут хран€тс€ и обновл€ютс€ все элементы интерфейса */

#include "DSmainGUI.h"
#include <vector>

using namespace std;

extern bool MouseOnGUI;

class guictr
{
public:
	vector<DSGUI*> GUI_list;//список всех элементов гуи при обновлении


	guictr();
	~guictr();

	void Render();//обновление гуи
	void AddCtrl(DSGUI *gi);//добавл€ем новый элемент в гуи
	void MouseTest();

	bool CloseAll();//закрыть все


};


#endif