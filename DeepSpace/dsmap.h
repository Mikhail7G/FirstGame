#ifndef DSMAP_H
#define DSMAP_H

#include <hge.h>
#include <vector>
#include <hgefont.h>
#include "DSmainGUI.h"
#include < hgerect.h>

#include "sector.h"
#include "gamer.h"

#include "dsanim.h"
#include "dsanimate.h"

extern HGE *hge;
extern float dt;

extern hgeFont	*fnt;
extern hgeFont *mainf;

extern HANIM    *map_poz;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);
extern float point_distanse(float x1, float y1, float x2, float y2);

extern float MouseX;
extern float MouseY;
extern float ScreenCenterX;
extern float ScreenCenterY;
extern float xview;
extern float yview;
extern float ScreenWidth;//ширина экрана
extern float ScreenHeight;//высота экрана

extern int PlayerSys;

extern vector<sector*> sectors;

extern hgeSprite *SysIcons[];
extern hgeSprite *sysmap;

extern float GlobalMapScaleFactor;


extern float point_distanse(float x1, float y1, float x2, float y2);

class dsmap : public DSGUI
{
public:
	float map_scale_factor;//маштабный коэф для карты

	hgeAnim *img;//ссылка на то что загруженно, создается,удаляется при необходимости
	player *plr;//игрок

	int flyto;//куда лететь

	float scalefactor;//коэф карты

	bool Selected;//выбрана ли система для полета?

	float mapx;
	float mapy;

	float sysx;
	float sysy;

	float dist;
	float maxdist;

	dsmap(player *plr);
	~dsmap();

	void Render();
	bool MouseTest();
	void Show();

protected:
	int targetid;//конесный ид сектора

	float map_movx;
	float map_movy;//смешение по карте

	int break_tim;
	
	bool drawpt;//рисовать путь?

	void DrawPath();//рисовать путь корабля

	void CalculatePath();//рассчитываем путь до нужной системы


	int startsys;//сектор положения игрока

	bool complete_path;//завершен ли поиск пути?

	float near_dist;//расстояние до ближайшей системы
	float far_dist;//рассояние между системой и целевой системой

	vector<int> systems_pos;//добавленные в список системы

	void CommandsUpdate();//обработка кнопок на рабочем интерфейсе


	///расчет для автопилота
	int max_errors = 1000;//число итераций
	int p_sys;//система игрока
	int cur_sys;
	float min_dist = 0;//минимальное расстояние

	vector<float> distanses;//расстояния между вершинами
	vector<bool> clear_systems;//вектор посешенных систем
	vector<int> last_calc_sys;//система из которой велся расчет
	int next_sys;
	int slow_calc_cur_sys;//текущая ситсема для обраюотки

	void SlowCalc();//медленный расчет 


};

#endif