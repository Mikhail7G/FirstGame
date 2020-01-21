#ifndef DEFENDERBOT_H
#define DEFENDERBOT_H

#include <hge.h>
#include "dyncore.h"
#include "warship.h"
#include <memory>
#include "pilot.h"
#include "Itemcore.h"
#include "planets.h"
#include "sector.h"
#include "bullcontainer.h"

extern int PlayerSys;
extern bool GPAUSED;

using namespace std;

extern vector<sector*> sectors;

extern hgeFont	*fnt;
extern HGE *hge;


static int PilotId = 0;//����� ������


class defender : public pilotctr
{
public:
	int fraction;//���� �����������
	int state;//0-������ 1-�������
	int p_id;

	bool ready_to_fly;//���� ����� �������������

	float timer1;
	float t_timer1;

	std::weak_ptr<ship> Ship;//������� 

	planet *homeplanet;//�������� �������


	defender();
	~defender();
	virtual void ScangeMap(int sysid);
	virtual void LogicUpdate();//���������� ������ ����
	 void ShipLost();//����������� �������

	 void CheckShip();//�������� �������
	 void Patrol();
	 void SleepTimer();

	 void Alarm();
	 void WarActions();//������ ��������
	 void ReturnToBase();//������������ �� ����

	 void DebugDraw();//���������� ����

	 void GetBadTarget();//�������� ��� ����, ������� ���������� ��� ���� �������

	 void LoadAmmo();//�������� ������� � ������

	 int GetId();



};



#endif