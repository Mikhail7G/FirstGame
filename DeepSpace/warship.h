#ifndef WARSHIP_H
#define WARSHIP_H

#include <vector>
#include <hge.h>
#include <hgevector.h>
#include <hgesprite.h>
#include <hgeparticle.h>
#include "cmath"
#include <memory>

#include "dyncore.h"
#include "dsanim.h"
#include "dsanimate.h"

#include "damagetext.h"
#include "effect.h"
#include "explosion.h"


#include "shuphull.h"
#include "weapon.h"
#include "pilot.h"
#include "sector.h"
#include "warpeff.h"
#include "shipengine.h"
#include "Itemcore.h"
#include "cargooper.h"
#include "tractoreff.h"



using namespace std;
extern HGE *hge;
extern float dt;

extern int GlobalShipObj;

extern float syspozx[];//���������� �������� � �������
extern float syspozy[];
extern const float lighting;
extern bool GPAUSED;

extern hgeParticleSystem  *effects[];

extern float point_distanse(float x1, float y1, float x2, float y2);
extern float point_dir2(float x1, float y1, float x2, float y2);
extern float slow_rotate(float speed, float dir, float newdir);
extern float point_direction(float x1, float y1, float x2, float y2);
extern float point_direction2(float x1, float y1, float x2, float y2);
extern float slerp(float var1, float var2, float delta);
extern bool mouse_on(float x, float y, float mx, float my, float h, float w);

extern vector<effect*> eff;
extern vector<sector*> sectors;
extern vector<cargo*> cargoobjects;

extern float CollRad;

extern HANIM    *animeffects[];

extern HSHADER             shad1;


enum states
{
	STOP = 0,
	FLY = 1,
	WARP = 2
};

enum warpstatus
{
	OFF = 0,
	ON = 1,
	RUN = 2
};


class ship : public dynamic
{
public:
	hgeAnim *img;//������ �� �� ��� ����������, ���������,��������� ��� �������������
	HANIM *anim;//��� ��������� � ������ ��� ������ ����

	hgeParticleSystem *eng;//������ �� ���������

	hull *shiphull;//������ �������
	engine *shipengine;//��������� �������

	std::weak_ptr<dynamic> target;

	vector<std::weak_ptr<dynamic>>attackers;//������ ����, ��� ������� ������� 


	cargomanager *crgmgr;//�������� ��������� ������

	///����� ��� ������ 
	int wslot;//������� ������ ��� ������
	vector<turret*>weapons;
	// turret *weapons[10];
	turret *weapon;//��������� ����������

	float totalDPS;
	float totalVolley;//����� ����� �� ���� �����


	int autopilot;//� ����� ������ ���������
	vector<int> a_systems;//������� ��� ����������

	//int state;//��� ������ ������� 0-�����,1-�����
	states state;

	warpstatus warpengine;//� ����� ������ ���������

	//float scale;//������ ���������(������� �� �������)
	float alpha;//��� ������� ����� ���������� �����������
	float newdir;
	float testval1;
	float testval2;
	float testval3;
	float engrad;//�������� �� ��������� ������� �� ���������

	float sensorrange;//��������� ������� ����

	float attackradius;//������ ������ ��� ����������
	float maxattackradius;//������ ������ ��� ���������� ������������

	bool prmlock;//��������� �������� ��� ��������
	bool smoke;//�������� �� ���� �� ���������

	float warptime;
	float wrpt1;
	bool warponse;

	float itempuckuprad;//������ ������� �����
	float tractorradius;//������ �������� ����
	float tractorpower;//�������� �������� ���� � ��

	//bool underAttack;//��������� �� ������� ��� ����. ������ � dyn
	float attackTimer;//����� ����� ��������, ���� ����� 30 ���.
	float attacktim1;//

	//bool firstAttack;//����, �������� �� ��������� ����� �������, ���� �� �� ����� ��� �����+ ���� ��� ����� underAttack �� ���� ������.
	float firstAttackTim;//����� ������������� ������� ���������� 15 ���
	float firstAttacktim1;

	float acc;//��� ���������(������� �� ���������, �� ������ maxspeed)

	pilotctr *pilot;//��� ��������� ��������

	shared_ptr<dynamic > obj;//��������



	ship(int sysid, hull *shiphull);
	~ship();
	void Update();
	void Render();
	void FlyTo(float x, float y);//���� �������� �������
	void DropTarget();//����������� ����
	void Fire();//���� ������� �� ��������
	void TargetOperations();//�������� � �����
	void WeaponUpdate();//��������� ������
	void SetTrgToWeap();//�������� ���� �����������
	void SetOneTrgToWeap(int weaponid);//�������� ���� �������
	void GetWeaponDPS();//��������� ��� �� ������
	void RecalculateVariables();//�������� ���� ������� ��� �������

	bool SetTarget(std::weak_ptr<dynamic> target);

	void Damage(float e, float k, float t, float r);

	void WarpOn(int nextsys);//������ ��������� ��� ����������� � ������ �������
	void WarpRun();//������ ��������� ��� ����������� � ������ �������

	bool InstallEngine(engine *shipengine);
	bool InstallWeapon(turret *weapon);
	bool RemoveWeapon(int id);//������� ������ �� ������� �����
	bool RemoveEngine();//������� ���������

	void UpgradeHull();//�������� �������� �������
	void CheckMass();//�������� ���� ������� ��� ���������� ������� � �������� � �������� �������

	void FirstAttack();//������� �������� � ��������� ������� ������ �� ������������ ����

	void FullLevelUp(int lvl);//�������� ������� ����� ������� � ������������� �������

	bool PickItem(cargo *itm);//������� ���� �� ����
	void SetItem(cargo *itm);//�������������� �������� � ���� �����
	void DropItem(int id);//����� ����
	void ScanForItems();//�������� ��������� � ������� ����

	void AddAggressiveToList(std::weak_ptr<dynamic> attacker);//��������� ���������� ����� � ������



	//���������� �������
	void FastUpdate(float dt);//��������������� ���������� �������� ��� ���������� ������ � �������
	void F_MoveTo(float dt);


	//��������
	void CalculaceCollision();
	void PozTest();//�������� ����������� ������� � ������� ��������� � ���. ����������.
	void PatchCorr();//������������� ������

	//�������� ��� ����
	bool GetNearlestTarget();//�������� ��������� ���� �� ������ agressive
	bool MoveToNearlestAggr();//��������� � ��������� ����������� ����


protected:



	void MoveTo();//��� ���������� ������ ���� ������� ������ �������� � ��������� �������


	void AggressiveActive();//������� ��������� ������������ ����� ������� ��������
	void AggressiveTimer();

	void FirstAttackTimer();


	void ResetSpeed();//���������� ���������� ��������


	float centerx;//����� ������� �� ��� �, ������������ ��� ����������� ����� ��������� �� �������
	float centery;//����� �� ��� �

	float dist;

	float acceleration;//��������� �������

	//����������� ���������� ���. ��� ��������� ������
	float d_scale;
	float d_maxhp;

	float d_explres;
	float d_kinres;
	float d_termres;
	float d_radiores;

	float d_sensorrange;
	float d_mass;

	bool autoflight;//���������
	bool go_to_next_sys;
	int startsys;
	int sys_ind;



};



#endif