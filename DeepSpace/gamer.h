#ifndef GAMER_H
#define GAMER_H

#include <hge.h>
#include "dyncore.h"
#include <hgefont.h>
#include "warship.h"
#include <memory>
#include "pilot.h"
#include "asteroids.h"
#include "asterspawn.h"
#include "Itemcore.h"
#include "effect.h"
#include "explosion.h"
#include "hgeDTool.h"
#include "radiushelp.h"
#include "planets.h"
#include "sector.h"

#include "DSguictr.h"

#include "bullcontainer.h"

extern bool MouseOnGUI;

extern guictr *GameGUI;

extern 	bool DebugInfo;
extern hgeFont	*fnt;
extern hgeFont *mainf;
extern HGE *hge;
extern hgeDTool *hgeTools;
extern float dt;
extern bool DrawCollisionData;

extern bool mouse_on(float x,float y,float mx,float my,float h,float w);
extern float point_distanse(float x1,float y1,float x2,float y2);
extern float point_direction(float x1,float y1,float x2,float y2);

extern int GameState;
extern float MouseX;
extern float MouseY;
extern int PlayerSys;
extern float xview;
extern float yview;
extern float ScreenWidth;//������ ������
extern float ScreenHeight;//������ ������
extern float ScreenCenterX;
extern float ScreenCenterY;
extern bool GPAUSED;
extern hgeSprite *radarRED[];
extern hgeSprite *wpt[];
extern hgeSprite *ataico;
extern hgeSprite *planethlp;

extern HANIM    *cursor1;


//extern vector<dynamic*> dyn;
extern vector<shared_ptr<dynamic>> dyn;
extern vector<cargo*> cargoobjects;
extern vector<effect*> eff;
extern vector<planet*> planetary;
extern vector<sector*> sectors;

extern hgeSprite  *hud1;//������ ������
extern hgeSprite *itemhelp;

extern enum CargoState;


class player: public pilotctr
{
	public:

		int debugmenu;//���������� ����(F2-F10);
		

		 //MainGUI *mainHUD;//�������� ��� ������ � ����
		 //MainGUI *PlayerMap;
		 //MainGUI *PlayerRadar;
		 //MainGUI *PlayerCargo;
		 //MainGUI *PlayerShipInfo;

		DSGUI *PlayerCargoGUI;//�������� �����
		DSGUI *PlayerMapGUI;//����� �������
		DSGUI *PlayerRadarGUI;//����� �������
		DSGUI *PlayerShipGUI;//����� �������
		DSGUI *PlayerCombatGUI;//����� �������

		 int camspeed;

		 int NextSys;

		 float scalefactor;//��������� ���� ��� ����������


		 bool camlock;//��������� ������ �� ������
		 bool cancomm;//����� �� �������� ������� ������� ������?
		 bool lefHUD;//����� ������ ������(�������� �� ��?)
		 bool renderRdr;//�������� �� �����?
		 bool renderMap;//�������� �� �����?
		 bool cargobay;//�������� �� �������� ����� �������?
		 bool spiphlp;//�������� �� ������ ��������� �������?

		 std::shared_ptr<ship> PlayerShip;//������� ������

		 std::weak_ptr<dynamic> trr;	

		player();
		~player();
		void Update();
		void Render();
		void SetCamPos(float x,float y);//���������� ������� ��� ������
		void ShipOperations();//�������� ��� ��������
		void MouseOperations();//��������� ������� �����
		void KeyInput();//������� ������
	
		void ScangeMap(int sysid);

		void PlanetOperations();//�������� � ���������
		void PlanetInfo(planet *pln);//�������� � ��������� �������

		void WeaponIconRenderer();//������ ������ ������, ������� ���������� �� ����
		void MapTarget(int sysid);//��������� ������� ��� ������


		void DebugRender();

		void DebugDraw()
		{

		};

		void NoAmmo()
		{

		};

		bool LoadAmmo();//������� ��� ������ ����������� ������



protected:
	int levelupvar;//��������, �� ������� ������� ������� ������� � ���������� ����

	 explosion *ex;

};



#endif