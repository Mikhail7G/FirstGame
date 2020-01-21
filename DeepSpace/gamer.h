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
extern float ScreenWidth;//ширина экрана
extern float ScreenHeight;//высота экрана
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

extern hgeSprite  *hud1;//панель игрока
extern hgeSprite *itemhelp;

extern enum CargoState;


class player: public pilotctr
{
	public:

		int debugmenu;//отладочное меню(F2-F10);
		

		 //MainGUI *mainHUD;//соновной ГУЙ игрока и цели
		 //MainGUI *PlayerMap;
		 //MainGUI *PlayerRadar;
		 //MainGUI *PlayerCargo;
		 //MainGUI *PlayerShipInfo;

		DSGUI *PlayerCargoGUI;//грузовой отсек
		DSGUI *PlayerMapGUI;//карта космоса
		DSGUI *PlayerRadarGUI;//Радар сектора
		DSGUI *PlayerShipGUI;//Радар сектора
		DSGUI *PlayerCombatGUI;//Радар сектора

		 int camspeed;

		 int NextSys;

		 float scalefactor;//маштабный коэф для расстояний


		 bool camlock;//фиксируем камеру на игроке
		 bool cancomm;//можно ли передать команду кораблю игрока?
		 bool lefHUD;//левая панель игрока(рисовать ли ее?)
		 bool renderRdr;//рисовать ли радар?
		 bool renderMap;//рисовать ли карту?
		 bool cargobay;//рисовать ли грузовой отсек корабля?
		 bool spiphlp;//рисовать ли панель оснащения корабля?

		 std::shared_ptr<ship> PlayerShip;//корабль игрока

		 std::weak_ptr<dynamic> trr;	

		player();
		~player();
		void Update();
		void Render();
		void SetCamPos(float x,float y);//уствновить позицию для камеры
		void ShipOperations();//действия над кораблем
		void MouseOperations();//обработка нажатий мышки
		void KeyInput();//нажатие кнопок
	
		void ScangeMap(int sysid);

		void PlanetOperations();//действия с планетами
		void PlanetInfo(planet *pln);//табличка с описанием планеты

		void WeaponIconRenderer();//рисует иконки орудий, которые наведенены на цель
		void MapTarget(int sysid);//выбранная система для полета


		void DebugRender();

		void DebugDraw()
		{

		};

		void NoAmmo()
		{

		};

		bool LoadAmmo();//функция для тсеста самозарадки орудий



protected:
	int levelupvar;//значение, на которое поднять урвоень объекта в отладочном меню

	 explosion *ex;

};



#endif