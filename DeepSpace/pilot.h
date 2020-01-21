#ifndef PILOT_H
#define PILOT_H
//��� �������� ��� ������ �� ������� ������ �� ����� ������ ���������� ����� � ����
#include <hge.h>

extern HGE *hge;

class pilotctr
{
public:

	pilotctr();
	virtual ~pilotctr();
	virtual void ScangeMap(int sysid);
	virtual void ShipLost();//����������� �������
	virtual void LigicUpdate();//���������� ������ ����
	virtual void Alarm();//����� �� �������

	virtual void NoAmmo();//��������� �� ������� � ���, ��� ��������� �������

	virtual int GetId()//id ������
	{
		return 0;
	};


	virtual void DebugDraw()
	{

	};



};



#endif