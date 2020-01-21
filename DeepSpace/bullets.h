#ifndef BULLETS_H
#define BULLETS_H
//������� ����� ��� ���� ����������� ��������

#include "dyncore.h"
#include <hge.h>
#include "cmath"
#include <memory>
#include "dsanim.h"
#include "dsanimate.h"
#include "effect.h"
#include "explosion.h"
#include "Itemcore.h"



extern HGE *hge;
extern float dt;

extern bool GPAUSED;

extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_dir2(float x1,float y1,float x2,float y2);

extern vector<effect*> eff;


extern enum WeaponSize;

static int BULLID=0;


class bullet:  public dynamic
{
public:
		int totalCount;//���������� ��������
		float dir;//����������� ������
		float lifetime;//����� �����

		int efftype;//��� ������� 0-�������, 1 -��������

		float Edmg;//����������� �� 4 ����� �����
		float Kdmg;
		float Tdmg;
		float Rdmg;

		float damagemod;//����������� �����, ���������� �� ������
		//��� ��������� ����, ����=��������*��������+����� �� �������
		float critdamage;//����, ������� ������� �� �����(������)


		float hitchance;//
		float critchance;//���� �����(� ���� ���� �������)
		bool doublecrit;//��� ���� ����������� ���� �����
		bool oncourse;//������� �� ������ � ����, ������� �� ������ ���������� ������ � ����� ����

		char *name;//�������� �������
		char *description;//�������� �������

		///������, �������� �� ��������� ������, ��� ������ ���� � % !!!!!!!!!
		float fireradius_b;//����� ��������� ��������
		float optimal_b;//����� ������������ ���������� ��������
		float sigradius_b;//����� ���������
		float tracking_b;//����� �������� ��������

		hgeAnim *img;//������ �� �� ��� ����������, ���������,��������� ��� �������������
		HANIM *anim;//��� ��������� � ������ ��� ������ ����
		hgeSprite *spr;//���� �� ������������ ������
		hgeSprite *ico;//������ �������
		hgeParticleSystem *effect;//������ ��� ���������
		HANIM *animeff;//������������� ������, �� �������


		std::weak_ptr<dynamic> target;//���� �������
		std::weak_ptr<dynamic> parient;//��� ���������

		WeaponSize BSize;


		bullet();
		virtual ~bullet();
		virtual void SetTarget(std::weak_ptr<dynamic> target,float x,float y);//������ ���� � ��������� ������
		virtual void SetParient(std::weak_ptr<dynamic> parient);//������������� ������� �������

		 virtual bullet* clone() const//����������� ������� ��� �������� �� �����
		   {
			  return new bullet(*this);
		   };

		void FullLevelUp(int lvl)
		{
		};
		

protected:
	int zz;




};



#endif