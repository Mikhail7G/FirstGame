#include "bullets.h"


bullet::bullet()
{
	type=-2;//��� ������
	name="������";
	Edmg=0;//����������� �� 4 ����� �����
	Kdmg=0;
	Tdmg=0;
	Rdmg=0;
	oncourse=false;
	hitchance=0;
	damagemod=1;
	effect=0;
	animeff=0;
	critchance=0;
	doublecrit=false;
	critdamage=1;
	name="���";

	fireradius_b=0;
	optimal_b=0;
	sigradius_b=0;
	tracking_b=0;

	description="null\0";
	BULLID++;
	zz=BULLID;
	totalCount=10;
};


bullet::~bullet()
{
	auto trr=target.lock();
	if(!target.expired())//�������� ������� ��������� ������ �� ���� ��� ���������
		{
		 hge->System_Log("������ ��:%s ������� � :%s � �������:%i",name,trr->name,sysid);	
		}
	else
	{
		 hge->System_Log("������ ��:%s ��������� � �������:%i",name,sysid);	
	};
};

void bullet::SetTarget(std::weak_ptr<dynamic> _target,float _x,float _y)
{

};

void bullet::SetParient(std::weak_ptr<dynamic> _parient)
{
	parient = _parient;
};

