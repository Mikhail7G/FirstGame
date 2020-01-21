#ifndef GAMECORE_H
#define GAMECORE_H

#include <vector>
#include <hge.h>
#include <hgefont.h>
#include <hgeresource.h>

#include "bgcore.h"

#include "dsanim.h"
#include "dsanimate.h"
#include "dyncore.h"
#include "asteroids.h"
#include "gamer.h"
#include "warship.h"
#include "shuphull.h"
#include "weapon.h"
#include "effect.h"
#include "explosion.h"
#include "projectile.h"
#include "planets.h"
#include "sector.h"
#include "spacefog.h"
#include "bgobj.h"
#include "asterspawn.h"
#include "shipengine.h"
#include "Itemcore.h"
#include "rudacore.h"
#include "resizlabel.h"
#include "hgeDTool.h"
#include "bullcontainer.h"
#include "Defenderbot.h"

#include "DSmainGUI.h"
#include "DSguictr.h"
#include "cargogui.h"
#include "dsmap.h"
#include "playerradar.h"
#include "shipsupply.h"
#include "combatpanel.h"


//#include "playerhud.h"
//#include "pradar.h"
//#include "map.h"

extern hgeFont *fnt;
extern hgeFont *mainf;
extern hgeFont *fnt1;
extern HGE *hge;
extern hgeResourceManager *Mpack;
extern hgeDTool *hgeTools;
extern float dt;

extern 	bool DebugInfo;

extern bool PlayerSysInBorder;

extern float ScreenWidth;
extern float ScreenHeight;
extern float ScreenCenterX;
extern float ScreenCenterY;
extern float MouseX;
extern float MouseY;
extern int PlayerSys;

extern int GlobalDynObj;
extern int GlobalShipObj;
extern int ItemCount;

extern double Call_Time;
extern bool Func_switch;

extern hgeSprite *star;
extern hgeSprite *mainspace;
extern hgeSprite  *hud1;
extern HANIM    *animships[];
extern HANIM    *animitem[];
extern HANIM    *animeffects[];
extern HANIM    *bganimeffects[];
extern HANIM    *animportal[];
extern HANIM    *mapeffects[];
extern HANIM    *cargobox;
extern HANIM    *cursor1;
extern HANIM    *map_poz;

extern hgeSprite *asteroids[];
extern hgeSprite *bullspr[];
extern hgeSprite  *hradar;
extern hgeSprite *radarRED[];
extern hgeSprite *border;
extern hgeSprite *shadow;
extern hgeSprite *PlanetsSpr[];
extern hgeSprite *SysIcons[];
//extern hgeSprite *BGsprites[];
extern hgeSprite *itemhelp;
extern hgeSprite *wpt[];
extern hgeSprite *staticitems[];
extern hgeSprite *sysmap;
extern hgeSprite *cargobayspr;
extern hgeSprite *cargobayslot;
extern hgeParticleSystem  *effects[];
extern hgeParticleSystem  *suns[];
extern hgeSprite *ataico;
extern hgeSprite *tractorspr;
extern hgeSprite *fail1spr;
extern hgeSprite *resized_info[];
extern hgeSprite *shipinfospr;
extern hgeSprite *planethlp;

extern char *BG_Spr[];
extern char *BG_PartSpr[];
extern char *PLN_Spr[];
extern char *GoodPlanets[];
extern char *BadPlanets[];
extern vector <char*> systems_names;

using namespace std;
extern float xview;
extern float yview;
extern float syspozx[];//���������� �������� � �������
extern float syspozy[];

extern guictr *GameGUI;

extern player  *Player;
extern dynlabel *dynhlp;
//extern vector<dynamic*> dyn;
extern vector<shared_ptr<dynamic>> dyn;
extern vector<effect*> eff;
extern vector<planet*> planetary;
extern vector<sector*> sectors;
extern vector<bgobj*> bgobjects;
extern vector<cargo*> cargoobjects;

extern HSHADER             shad1;

extern float GlobalMapScaleFactor;

extern float point_distanse(float x1, float y1, float x2, float y2);



enum Fraction
{
	NONE = 0,
	PEOPLE = 1,
	PIRATE = 2
};

enum WeaponSize
{
	SMALL=0,
	MEDIUM=1,
	LARGE=2
};

enum DynamicType
{
	ASTEROID=0,
	SHIP=1,
	TRASH=2

};

enum CargoType // ��� ����� � ����������
{
	SHULL=0,
	SENG=1,
	SWPN=2,
	SBULL=3
};

enum CargoState
{
	SPACE=0,
	ONBOARD=1
};



class gameclass
{
public:


	//float xview,yview;//�������� ������ ������������ ������� �������� ����
	float mx,my;//��������� ��������� ��� ���������� ��������� �����
    int camspeed;

	int Max_Systems;//����� ������ � ����

	float cormx;
	float cormy;
	float corcamx;
	float corcamy;

	gameclass();
	~gameclass();

	//guictr *GameGUI;//���������� ��� ������

	void WorldUpdate();
	void WorldRender();
	void ResourseLoad();
	void NewGame();
	void CreatePlayer();//������� ������

	void CreateSectors();//������� ������� � �������
	void CreateStartSectors();//������� ��������� ������� �������� 

	void UpdateVectors();//��������� ��� ������� � ���������
	void RenderVectors();//������ ��� �������

	void GenerateItems();//��� ��������� ��� ��������� ���� � ����

	void CreateAISystems();//�������� ������� ������ �������

	void Test1();

	void ChangeMap(int sys);

	worldbg *mainBG;//�����, ���������� �� ����������� �������� �� ����.

	asterctr *astspawner;//���������� ������ ����������


	float testval1;

protected:
	//������ ���� ��������� �����
	//�������
	hull *defaulthull;//��������� ������ �������� �����

	//���������
	engine *eng1;// ����� ������� 1 ���������



	//�������
	std::shared_ptr<projectile> projectile1;//�������� ������ 1 ������
	std::shared_ptr<projectile> projectile2;//����������� � ������� �������� ������ 1 ������
	std::shared_ptr<projectile> projectile3;//������� �������� ��� �������


	void ReloadTextures();

	//������
	turret *trsmall1;//������ ����� 1 ������

	/////////////////////////////
	/*HUD *hdd;*/

	void GenetareHulls();//��� �������� ���� ��������
	void GenerateEngines();//�������� ���� ����������
	void GenerateBullets();//�������� �����������
	void GenerateWeapons();//�������� ������

	void CreateConstantSectiors();//������� ���������� �������

	float testsize;
	hgeSprite *testspr1;
	HTEXTURE tex1[10];

	int upd_from;//� ����� ������� ���������
	int upd_to;//�� ����� ������� ��������� �� 1 ����

};


#endif