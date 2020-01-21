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
extern float ScreenWidth;//������ ������
extern float ScreenHeight;//������ ������
extern float ScreenCenterX;
extern float ScreenCenterY;


extern hgeSprite *cargobayspr;
extern hgeSprite *cargobayslot;

extern bool mouse_on(float x, float y, float mx, float my, float h, float w);


class shipcargoGUI :public DSGUI
{
public:
	player *plr;//�����

	int maxslot;//������� ������ ��������
	float screenx;
	float screeny;//���������� ���������� ����

	float slotx;//���������� ����� ����������
	float sloty;

	shipcargoGUI(player *plr);
	~shipcargoGUI();

	bool MouseTest();//�������� ��������� ����� �� ���������
	void Render();
	void DrawItem(int id, float x, float y);//������ ������ ������� � �����
	void Show();//���������� �������
	void MouseOper(int id, float x, float y);//�������� ��� ���������

protected:
	float dx;
	float dy;//���������� ��� ��������� �������� �������� �������

	void WeaponTest(int id);//������� �������� �� ������� ������� � ������ �������

	void InstallTurret(int id);//��������� ������ �� �������
	void InstallBullet(int id);//������� ������� � ������
	void InstallEngine(int id);//��������� ���������

	void DrawWeaponData(int id);//���������� ���������� �� ��������� ������
	void DrawHullData(int id);//���������� ���������� �� ��������� �������
	void DrawEngineData(int id);//���������� ���������� �� ��������� ���������
	void DrawBullData(int id);//���������� ���������� �� ��������� �������
	void DrawMineralData(int id);//���������� ���������� � ����




};


#endif