#ifndef DYNCORE_H
#define DYNCORE_H
#include <vector>
#include "dsanim.h"
#include "dsanimate.h"
#include <memory>

using namespace std;

extern int GlobalDynObj;


extern bool DrawCollisionData;

static int Total=0;//����� ������������ ��������



class dynamic
{
public:
	 float x;//���������� �������, ��� ���� �����.
	 float y;
	 float dx;
	 float dy;//���� ������� ������
	 float dir;//����������� �������
	 int id;
	 int itemlevel;//������� ����
	 bool kill;
	 bool visible;//����� �� ������ � ����
	 char *name;//��� �������
	 int sysid;//� ����� ������� ������
	 int nextsys;//���� ������� ������
     int type;//��� �������, 0-��������,1-�������(����� 100) >0-�� ����������� �������!
	 int fraction;//���� ����������� 0-�����,1-����,2-����������� ������
	 float radius;//������ �������(��� ��������� � ������������)
	 float sigradius;//�������� ������ �������
	 float hp;//���� �����
	 float maxhp;//����������� �����
	 float speed;//�������� �������
	 float maxspeed;//����������� ���������
	 float syndist;//���������� �� ������ �������
	 float mass;//����� �������
	 float cargomass;//����� ������������� ����� � ����� ���� ������

	 float scale;//������ �������

	 float rotatespeed;//�������� ��������

	 /////��������� ����� �������
	 float explres;
	 float kinres;
	 float termres;
	 float radiores;
	 float EXParmor;//������������� ����� � ������ �������������

	 bool underAttack;//��������� �� ������� ��� ����.
	 bool firstAttack;//����, �������� �� ��������� ����� �������, ���� �� �� ����� ��� �����+ ���� ��� ����� underAttack �� ���� ������.
	

	 vector<std::weak_ptr<dynamic>>collisions;//�������� ������������ � ���������� ���������


	 ///��� �������
	 bool scharge_flag1 = true; //��� ����, ���������� ��� �� ������ ���������


	dynamic();
	virtual ~dynamic();
	virtual void Update();
	virtual void Render();
	virtual void Damage(float e,float k,float t,float r);
	virtual void FirstAttack();//������� �������� � ��������� ������� ������ �� ������������ ���� ��� ��������
	virtual void FullLevelUp(int lvl);//�������� ������� �������
	virtual void FastUpdate(float dt);//������� ���������� �������� �� ��������� ������� ������
	int GetTotal();

	//��������� ������������
	void AddCollisionTest(std::weak_ptr<dynamic> col);//��������� ������ �������� ������������
	virtual void CalculaceCollision();//������ ������������


};



#endif