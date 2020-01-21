#include "cargooper.h"


cargomanager::cargomanager()
{
	maxslot=0;
	totalmass=0;

};

cargomanager::~cargomanager()
{
	hge->System_Log("crg_free");
};

bool cargomanager::GetItem(cargo *_itm)
{
	if(SortItem(_itm))
	{
		return true;
	}
	else
	{
		return false;
	};

};

bool cargomanager::SortItem(cargo *_itm)
{
	for(int i=0;i<crg.size();i++)//������� ��������� ���� �� ����� ������ � ������ � ����� �� �� �������?
	{
		if((_itm->type==crg.at(i)->type)&&(_itm->canstak))
		{
			crg.at(i)->count+=_itm->count;
			crg.at(i)->mass+=_itm->mass;
			totalmass+=_itm->mass;
			_itm->hidekill=true;
			_itm->kill=true;
			return true;
			break;
		};
	};

	if(crg.size()<maxslot)
	{
		crg.push_back(_itm);
		_itm->Install();
		totalmass+=_itm->mass;
		return true;
	}
	else
	{
		return false;
	};


};

void cargomanager::DropItem(int id,int sysid,float x,float y)
{
	sectors.at(sysid)->AddItemToList(crg.at(id));//����� ������� �� ����, ��������� � ������

	crg.at(id)->ShipDrop(sysid,x,y);
	totalmass-=crg.at(id)->mass;
	crg.erase(crg.begin()+id);

};

void cargomanager::DropItem(int id)
{
	totalmass-=crg.at(id)->mass;
	crg.erase(crg.begin()+id);
	
};

void cargomanager::DropAll(int _sysid, float _x, float _y)
{
	for (int i = 0; i < crg.size(); i++)
	{
		sectors.at(_sysid)->AddItemToList(crg.at(i));//����� ������� �� ����, ��������� � ������

		crg.at(i)->ShipDrop(_sysid, _x, _y);

	};
};

void cargomanager::DropEngine(int _sysid, float _x, float _y)
{
	sectors.at(_sysid)->AddItemToList(shipeng);//����� ������� �� ����, ��������� � ������
	shipeng->ShipDrop(_sysid, _x, _y);
};

void cargomanager::DropHull(int _sysid, float _x, float _y)
{
	sectors.at(_sysid)->AddItemToList(shiphull);//����� ������� �� ����, ��������� � ������
	shiphull->ShipDrop(_sysid, _x, _y);
};

void cargomanager::DropWeapon(int _sysid, float _x, float _y)
{
	for (int i = 0; i < shipwpn.size(); i++)
	{
		sectors.at(_sysid)->AddItemToList(shipwpn.at(i));
		shipwpn.at(i)->ShipDrop(_sysid, _x, _y);
	};
};

void cargomanager::SortAllItems()
{
	std::sort(crg.begin(), crg.end());
};
