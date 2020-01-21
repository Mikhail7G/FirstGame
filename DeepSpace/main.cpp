//����������� �����������
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include <memory>

//���������� ������
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeresource.h>

//���. ���������
#include "dsanim.h"
#include "dsanimate.h"
#include "hgeDTool.h"
//������� ���������
#include "menuitem.h"
#include "gamecore.h"
#include "dyncore.h"
#include "gamer.h"
#include "effect.h"
#include "planets.h"
#include "sector.h"
#include "bgobj.h"
#include "Itemcore.h"
#include "resizlabel.h"
#include "DSguictr.h"




using namespace std;


const float lighting=0.0213f;//����������� ������������ ��������(������0.063f)

//����������� �� �����
float point_direction(float x1,float y1,float x2,float y2)
{
	float dir;
	float temp;
	dir=0;
	temp=0;
	temp=(-atan2(y2-y1,x1-x2));
	if(temp<0)
	{
		dir=360+(temp*180/3.14);
	}else
	{
		dir=(temp*180/3.14);
	};

	return dir;


};


///�������� ��� �������� �������
float point_dir2(float x1,float y1,float x2,float y2)
{
	return -atan2(y2-y1,x1-x2);
};

float point_direction2(float x1, float y1, float x2, float y2)
{
	float f = -atan2(y2 - y1, x1 - x2);
	if (f < 0)
	{
		f = 2 * M_PI - abs(f);
	};
	return f;
};

float slerp(float angle0, float angle1, float delta)
{
	float ret = 0;
	return ret;
};

float slow_rotate(float speed,float dir,float newdir)
{
	float result=0;
	result=-sin(newdir-dir)*speed;
	return result;

};
//��������� �� �����
float point_distanse(float x1,float y1,float x2,float y2)
{
	return sqrt((x2-x1)*(x2-x1)+((y2-y1))*(y2-y1));

};

//��������� ����� �� ������������� �������
bool mouse_on(float x,float y,float mx,float my,float h,float w)
{
	if(((mx<(x+w))&&(mx>(x-w)))&&((my<(y+h))&&(my>(y-h)))){
	return true;
	}else return false;
};




HGE *hge=0;
hgeResourceManager *Mpack;//����� �� ����� �������
hgeDTool *hgeTools;//����������� �����
guictr *GameGUI;//���������� ��� ������

double Call_Time;//����� ������ ������� �������� ����������

bool Func_switch=true;//������������ ���� �������

bool DrawCollisionData = false;//����� ���� � �������������

float dt;//������ ������
float ScreenWidth=1024;//������ ������1366
float ScreenHeight=768;//������ ������768
float ScreenCenterX;//����� ������ ������ ��� ������(�� ����������)
float ScreenCenterY;
float xview;
float yview;//�������� ������ ������������ ������� �������� ����(�������� ������)
float MouseX;
float MouseY;

float CollRad = 5000;//������ �������� ������������

float GlobalMapScaleFactor = 0;//������ ������� ��� �������� ����

int GameState = 0;//� ����� ������ ����? 0-����. -1- ��������.1-����
int NextGameState = 0;//��������� ����� ����

int PlayerSys = 0;//������ ������

int AsteroidCount = 0;//������� ���������� � ����
int ItemCount = 0;//����� � ����

bool GPAUSED = false;//����������� �����
bool DebugInfo;//���������� ����������

bool MouseOnGUI=false;//����� �������� �� �������� ���

bool PlayerSysInBorder = true;//��������� �� ��������� ������� ������ � ���� ��� ������

float syspozx[500];//���������� �������� � �������
float syspozy[500];
//��������� �����, ������������ ������� ��������
HEFFECT				snd;
hgeGUI				*gui;
hgeFont				*fnt;//������� ����� ��� �������+ �������� � �������
hgeFont				*mainf;//��� ������ ���� �������� ����� ����
hgeFont				*fnt1;//����� ��� ����������� �����(������� �����)
hgeAnimation    *load;
hgeSprite		*load2;

bool once=true; //��������������� �������� ��������

hgeSprite *mainbg;

///������� ������/////////////////////////
gameclass *MainWorld;//�������� ����� ����, ��� ���� ������ � ���������� ����� ����
dynlabel *dynhlp;//������������ ��������

//�������� ����
hgeSprite *star;//������(����� �������)
hgeSprite *mainspace;//�������� ����
hgeSprite  *hud1;//��� ������
hgeSprite  *hradar;//��� ������
hgeSprite *radarRED[10];//����� �� ������
hgeSprite *border;//��������� ��� ��������� ������� ����
hgeSprite *shadow;//������ ����� �������
hgeSprite *itemhelp;//�������� ��������
hgeSprite *wpt[2];//��� ������, ���������� ������ ������
hgeSprite *sysmap;//����� �������� �������
hgeSprite *cargobayspr;//�������� ��������� ������ �������
hgeSprite *cargobayslot;//�������� ������ ��������� ������ �������
hgeSprite *tractorspr;//������ �������� ����
hgeSprite *fail1spr;//������ ��������� ����������� �� ����
hgeSprite *resized_info[3];//�������� � ��������������� ����������
hgeSprite *shipinfospr;//��������� �������
hgeSprite *planethlp;//�������� �������

HANIM    *animships[100];//������������� �������
HANIM    *animitem[100];//������������� ��������� ����������� �������
HANIM    *animeffects[10];//������������� �������
HANIM    *bganimeffects[10];//������������� ������� ����
HANIM    *mapeffects[10];//������������� ������� �����
HANIM    *animportal[2];//������ ����� ������� � ����, ����� ����� ������ 3 �������, � ���� ������ 2
HANIM    *cargobox;//��������� ���������
HANIM    *cursor1;
HANIM    *map_poz;

hgeSprite *asteroids[5];//������� ����������
hgeSprite *bullspr[5];//������� ��������
hgeSprite *PlanetsSpr[10];//������� ������
hgeSprite *SysIcons[10];//������ �������� �� ��.�����
hgeSprite *BGsprites[10];//�������� ����������� �������� ����
hgeParticleSystem  *effects[5];//��� ������� ����
hgeSprite *staticitems[50];//����������� �������� �����
hgeSprite *ataico;//�������� ����� �� ����
hgeParticleSystem  *suns[5];//������� ������

char *BG_Spr[10];//�������� ������ ������� ����
char *BG_PartSpr[10];//�������� ������ ����������� ������� ����
char *PLN_Spr[30];//�������� ������ ������� ����

char *GoodPlanets[10];//�������, ��� ���������
char *BadPlanets[10];//�������, � ���������� ���������

vector <char*> systems_names;//�������� ������

//�������������� ����������, ���������� ���������� ��������� ��������� �������� � ����
int GlobalDynObj = 0;//���������� ���������� ������������ ��������
int GlobalShipObj = 0;//���������� ��������

//������� � ������������� �������
player  *Player;
//vector<dynamic*> dyn;//������ ������
vector<shared_ptr<dynamic>> dyn;

vector<effect*> eff;//��� ������� �������������� ���

vector<planet*> planetary;//��� ������� � ����
vector<sector*> sectors;//��� ������� � ����

vector<bgobj*> bgobjects;//��� ������� ���� � ����

vector<cargo*> cargoobjects;//��� ���� � ����

HSHADER             shad1;

bool FrameFunc()
{
	dt = hge->Timer_GetDelta();
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;//��� ������� ����� ���������

	int id;
	static int lastid = 0;


	switch(GameState)
	{
	case 0://���� ����
		id=gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{//����� ����
			case 1:GameState = -1;NextGameState = 1;MainWorld->NewGame();gui->Leave();break;
			case 2:
				gui->SetFocus(1);
				gui->Enter();
				break;
			case 3:
				gui->SetFocus(1);
				gui->Enter();
				break;
			case 4:
				gui->SetFocus(1);
				gui->Enter();
				break;
		    case 5: return true;
			}
		}
		else if(id) 
		{
			lastid=id;
			gui->Leave(); 
		}

	break;
    case 1://�������� ���� ����
		  MainWorld->WorldUpdate();//��������� ���

	break;
	case 2://��������
		  GameState = -1;
	break;
	case 3://����� ����� � ����, �������� �������� ����� ����
		GameState = -1;
		MainWorld->ChangeMap(PlayerSys);
	break;

	}
	return false;
}


bool RenderFunc()
{
	hge->Gfx_BeginScene();
   	hge->Gfx_Clear(0);

	switch(GameState)
	{
	case -1://�������� ��������
           if(once)
					{
						load->Play();
						once=false;
					};
						if(load->GetFrame()<5)
						{
							load2->Render(ScreenCenterX-50,ScreenCenterY-14);
							load->Render(ScreenCenterX,ScreenCenterY);
							load->Update(dt);

						}else
						{
							GameState=NextGameState;once=true;
						};
	break;
	case 0://������ ���� ����
		if(load->GetFrame() == 5)
		{
		  mainbg->Render(0,0);
	      gui->Render();
	      fnt->SetColor(0xFFFFFFFF);
	      fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());

		}else
		{    
			load2->Render((1024/2)-50, (768/2)-14);
			load->Render(1024/2, 768/2);
	        load->Update(dt);
		};

	break;
	case 1://�������� ���� ����
		MainWorld->WorldRender();//������ ��� ��� ����

	break;
	}



	
	
    hge->Gfx_EndScene();
	return false;
}



int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "DS.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "Deep Space");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, ScreenWidth);
	hge->System_SetState(HGE_SCREENHEIGHT, ScreenHeight);
	hge->System_SetState(HGE_SCREENBPP, 32);
	hge->System_SetState(HGE_HIDEMOUSE,false);
	hge->System_SetState(HGE_FPS,100);
	hge->System_SetState(HGE_DONTSUSPEND,true);

	//FreeImage_Initialise();
     ScreenCenterX = ScreenWidth/2;
	 ScreenCenterY = ScreenHeight/2;
     //��� ������ ��������� ���������� ��������, ������� ������ ������� 10�*10� + ��������� ����� ���� �������� 5�.
	 syspozx[0]=5000;
	 syspozy[0]=5000;


	if(hge->System_Initiate())
	{//���������� ����� ������
		if(hge->Resource_AttachPack("res.zip"))
		{
           hge->System_Log("Resourse pack attach...OK");
		}else
		{
			hge->System_Log("Cant load res.zip");
		};
		Mpack=new hgeResourceManager("scripts.cfg");
        //��������� �����
		snd=Mpack->GetEffect("menu");
		fnt=Mpack->GetFont("main");
		load=Mpack->GetAnimation("loading");
		load->Play();
		load2=Mpack->GetSprite("loading2");
		mainbg=Mpack->GetSprite("bg00");
		/////////������ ������� ����
		gui=new hgeGUI();
		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"����� ����"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"����������"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"���������"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"������"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"�����"));
		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetFocus(1);
		gui->Enter();

		MainWorld = new gameclass();

        
		hge->System_Start();
	}

	// Clean up and shutdown




	hge->System_Shutdown();
	hge->Release();
	return 0;
}