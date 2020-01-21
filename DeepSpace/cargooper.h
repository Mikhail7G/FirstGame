#ifndef CARGOOPER_H
#define CARGOOPER_H

#include <hge.h>
#include "cmath"
#include <vector>
#include "Itemcore.h"
#include "sector.h"
#include <algorithm> 

using namespace std;
extern HGE *hge;
extern float dt;

extern vector<sector*> sectors;


class cargomanager
{
public:
	int maxslot;//�������� ������ � ������

	float totalmass;

	vector<cargo*> crg;//����, �������� � ������ �������
	cargo *shipeng;//��������� �������
	cargo *shiphull;//������ �������
	vector<cargo*> shipwpn;//������ �������


	cargomanager();
	~cargomanager();

	bool GetItem(cargo *itm);//��������� ���� � �������
	void DropItem(int id,int sysid,float x,float y);//���� �� id �����
	void DropItem(int id);//������� � ����� �� �������
	void DropAll(int sysid, float x, float y);//����� ���� �����
	void DropEngine(int sysid, float x, float y);//����� ���������(�� �������� �� �������� �������!)
	void DropHull(int sysid, float x, float y);//����� ������� ��� �������� �������
	void DropWeapon(int sysid, float x, float y);//����� ����� ������

	void SortAllItems();//������������� ��� ���� � ���� ������

protected:
	bool SortItem(cargo *itm);//


};


#endif