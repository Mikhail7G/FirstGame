#ifndef BULLCONTAINER_H
#define BULLCONTAINER_H

//���� ����� �������� ����������� ���������, �.�. ��������� �������� ����������� �� dynamic � ������� ���������� ��������� ��������� ����������.
//������� �������� ������� ���.

#include <hge.h>
#include "Itemcore.h"
#include "bullets.h"
#include <memory>

using namespace std;



class bullcont:public cargo
{
public:

	shared_ptr<bullet> bull;//�������� ������

	bullcont(shared_ptr<bullet> bull);
	~bullcont();

	shared_ptr<bullet> GetBull();

	void SetAmmo(int ammo);//�������� ��������



};

#endif