#include "DSguictr.h"


guictr::guictr()
{

};

guictr::~guictr()
{

};

void guictr::Render()
{
	for (int i = 0; i < GUI_list.size(); i++)
	{
		if (GUI_list.at(i)->render)
		{
			GUI_list.at(i)->Render();
		}
	};
	MouseTest();

};

void guictr::AddCtrl(DSGUI *_gi)
{
	GUI_list.push_back(_gi);
};

void guictr::MouseTest()
{
	for (int i = 0; i < GUI_list.size(); i++)
	{
		if ((GUI_list.at(i)->render) && (GUI_list.at(i)->MouseTest()))
		{
			MouseOnGUI = true;
			break;
		}
		else
		{
			MouseOnGUI = false;
		};
	};
	
};

bool guictr::CloseAll()
{
	bool b = false;

	for (int i = 0; i < GUI_list.size(); i++)
	{
		if (GUI_list.at(i)->render)
		{
			b = true;
			GUI_list.at(i)->render = false;
			GUI_list.at(i)->lockkeyboard = false;
		};

	};

	if (b)
	{
		return true;
	}
	else
	{
		return false;
	};


};