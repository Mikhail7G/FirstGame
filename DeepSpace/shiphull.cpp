#include "shuphull.h"


hull::hull(hgeParticleSystem *_eng,HANIM *_anim)
{
	eng=_eng;
	anim=_anim;
	scale=1;
	engrad=0;
	maxhp=1;
	sensorrange=1;
	explres=0;
	kinres=0;
	termres=0;
	radiores=0;
	wslot=0;
	sigradius=0;
	name="���";
	type=0;

	ITEMID++;
	zz=ITEMID;

};

hull::~hull()
{
	hge->System_Log("������:%s ��������� � �������:%i",name,sysid);	
};

void hull::SetDefaultVar()
{
	d_scale=scale;
	d_maxhp=maxhp;

	d_explres=explres;
	d_kinres=kinres;
	d_termres=termres;
	d_radiores=radiores;

	d_sensorrange=sensorrange;
	d_mass=mass;
	d_sigradius=sigradius;


};

void hull::SetDispreadVar(float _dispread)
{
	float disp = _dispread / 100;//��������� �� %

	d_maxhp = maxhp + maxhp*disp*(hge->Random_Int(-1, 1));

	d_explres = explres + explres*disp*(hge->Random_Int(-1, 1));
	d_kinres = kinres + kinres*disp*(hge->Random_Int(-1, 1));
	d_termres = termres + termres*disp*(hge->Random_Int(-1, 1));
	d_radiores = radiores + radiores*disp*(hge->Random_Int(-1, 1));

	d_sensorrange = sensorrange + sensorrange*disp*(hge->Random_Int(-1, 1));
	d_mass = mass + mass*disp*(hge->Random_Int(-1, 1));
	d_sigradius = sigradius + sigradius*disp*(hge->Random_Int(-1, 1));
};

void hull::GenerateRandomVar(int _level,float _rand,float _dispread)
{
	int lvl=_level;//�� ����
	itemlevel=lvl;
	float rand=_rand;//����������� ��������� ���������� �����, ������ 0,02f
	rand=0.02f;

	float rec;//����������� �������� �������������
	rec=(rand*lvl)/(1+rand*lvl);

	//������� ������
	float scale1=d_scale+d_scale*(0.1f*lvl);
	float scale2=d_scale+d_scale*(0.1f*(lvl-1)*rec);
	scale=d_scale+((scale1-scale2)/3);

	//������� ��� �����
	float hp1=d_maxhp+d_maxhp*(0.1f*lvl);
	float hp2=d_maxhp+d_maxhp*(0.1f*(lvl-1)*rec);
	maxhp=d_maxhp+((hp1-hp2)/1);

	//������� �������������
	float rec1=rec*100;
	float scaler=2.0f;//����. �������� �����
	float s1=d_explres+(rec1/scaler-(rec1/scaler*(d_explres/100)));
	explres=s1;

	s1=d_kinres+(rec1/scaler-(rec1/scaler*(d_kinres/100)));
	kinres=s1;

	s1=d_termres+(rec1/scaler-(rec1/scaler*(d_termres/100)));
	termres=s1;

	s1=d_radiores+(rec1/scaler-(rec1/scaler*(d_radiores/100)));
	radiores=s1;

	//������� ��������� �������
	float sencor1=d_sensorrange+d_sensorrange*(0.1f*lvl);
	float sencor2=d_sensorrange+d_sensorrange*(0.1f*(lvl-1)*rec);
	sensorrange=d_sensorrange+((sencor1-sencor2)/3.5f);

	//������� �����
	float mass1=d_mass+d_mass*(0.1f*lvl);
	float mass2=d_mass+d_mass*(0.1f*(lvl-1)*rec);
	mass=d_mass+((mass1-mass2)/3);

	//������� ������ ��������� �������
	float sig1=d_sigradius+d_sigradius*(0.1f*lvl);
	float sig2=d_sigradius+d_sigradius*(0.1f*(lvl-1)*rec);
	sigradius=d_sigradius+((sig1-sig2)/4);





};

void hull::LevelUp(int _level)
{
	int level=_level;
	itemlevel+=level;
	GenerateRandomVar(itemlevel,0,0);

};