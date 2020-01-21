#ifndef CARGOGUI_H
#define CARGOGUI_H

#include <hge.h>
#include <hgeresource.h>
#include "DSmainGUI.h"
#include "gamer.h"
#include "bullcontainer.h"
#include "resizlabel.h"

extern float MouseX;
extern float MouseY;
extern int PlayerSys;
extern float xview;
extern float yview;
extern float ScreenWidth;//ширина экрана
extern float ScreenHeight;//высота экрана
extern float ScreenCenterX;
extern float ScreenCenterY;


extern hgeSprite *cargobayspr;
extern hgeSprite *cargobayslot;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);


class shipcargoGUI :public DSGUI
{
public:
	player *plr;//игрок

	int maxslot;//сколько слотов рисовать
	float screenx;
	float screeny;//координаты главногого фона

	float slotx;//координаты ячеек интерфейса
	float sloty;

	shipcargoGUI(player *plr);
	~shipcargoGUI();

	bool MouseTest();//проверка наведения мышки на интерфейс
	void Render();
	void DrawItem(int id, float x, float y);//рисует иконку объекта в слоте
	void Show();//показывать элемент
	void MouseOper(int id, float x, float y);//Операции над объектами

protected:
	float dx;
	float dy;//координаты для рисования таблички описания модулей

	void WeaponTest(int id);//функция проверки на наличие снаряда в отсеке корабля

	void InstallTurret(int id);//установка орудия на корабль
	void InstallBullet(int id);//Зарядка снаряда в орудие
	void InstallEngine(int id);//установка двигателя

	void DrawWeaponData(int id);//нарисовать информацию об выбранном орудии
	void DrawHullData(int id);//нарисовать информацию об выбранном корпусе
	void DrawEngineData(int id);//нарисовать информацию об выбранном двигателе
	void DrawBullData(int id);//нарисовать информацию об выбранном снаряде
	void DrawMineralData(int id);//нарисовать информацию о руде




};


#endif