//стандартные бибилиотеки
#include <vector>
#include <iostream>
#include <math.h>
#include <fstream>
#include <memory>

//библиотеки движка
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeresource.h>

//доп. включения
#include "dsanim.h"
#include "dsanimate.h"
#include "hgeDTool.h"
//игровые включения
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


const float lighting=0.0213f;//коэффициент освещенности объектов(старый0.063f)

//направление на точку
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


///подходит для вращения корабля
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
//дистанция до точки
float point_distanse(float x1,float y1,float x2,float y2)
{
	return sqrt((x2-x1)*(x2-x1)+((y2-y1))*(y2-y1));

};

//наведение мышки на прямоугольную область
bool mouse_on(float x,float y,float mx,float my,float h,float w)
{
	if(((mx<(x+w))&&(mx>(x-w)))&&((my<(y+h))&&(my>(y-h)))){
	return true;
	}else return false;
};




HGE *hge=0;
hgeResourceManager *Mpack;//архив со всеми файлами
hgeDTool *hgeTools;//рисовальщик фигур
guictr *GameGUI;//контроллер ГУИ игрока

double Call_Time;//время вызова функций быстрого обновления

bool Func_switch=true;//переключение тест функций

bool DrawCollisionData = false;//вывод инфы о столкновениях

float dt;//дельта таймер
float ScreenWidth=1024;//ширина экрана1366
float ScreenHeight=768;//высота экрана768
float ScreenCenterX;//центр экрана ТОЛЬКО ДЛЯ ЧТЕНИЯ(НЕ ИЗМЕНЯЮТСЯ)
float ScreenCenterY;
float xview;
float yview;//смещение камеры относительно правого верхнего угла(ВОЗМОЖНО МЕНЯТЬ)
float MouseX;
float MouseY;

float CollRad = 5000;//радиус проверки столкновения

float GlobalMapScaleFactor = 0;//фактор маштаба для игрового мира

int GameState = 0;//в каком режиме игра? 0-меню. -1- загрузка.1-игра
int NextGameState = 0;//следующий режим игры

int PlayerSys = 0;//сектор игрока

int AsteroidCount = 0;//сколько астероидов в игре
int ItemCount = 0;//вещей в игре

bool GPAUSED = false;//тактическая пауза
bool DebugInfo;//отладочная информация

bool MouseOnGUI=false;//мышка наведена на элементы ГУИ

bool PlayerSysInBorder = true;//Находится ли стартовая система игрока в углу или центре

float syspozx[500];//координаты секторов в космосе
float syspozy[500];
//начальные файлы, показывающие процесс загрузки
HEFFECT				snd;
hgeGUI				*gui;
hgeFont				*fnt;//красный шрифт для отладки+ названия в космосе
hgeFont				*mainf;//тут должен быть основной шрфит игры
hgeFont				*fnt1;//шрифт для отображения урона(разного цвета)
hgeAnimation    *load;
hgeSprite		*load2;

bool once=true; //воспроизведение анимации загрузки

hgeSprite *mainbg;

///ИГРОВЫЕ ДАННЫЕ/////////////////////////
gameclass *MainWorld;//основной класс игры, где идет расчет и обновление всего мира
dynlabel *dynhlp;//динамическая табличка

//Картинки игры
hgeSprite *star;//звезда(центр системы)
hgeSprite *mainspace;//звездное небо
hgeSprite  *hud1;//лев панель
hgeSprite  *hradar;//фон радара
hgeSprite *radarRED[10];//метки на радаре
hgeSprite *border;//показанно где находится граница вида
hgeSprite *shadow;//темная часть планеты
hgeSprite *itemhelp;//описание объектов
hgeSprite *wpt[2];//для игрока, показывает статус орудия
hgeSprite *sysmap;//карта звездной системы
hgeSprite *cargobayspr;//картинка грузового отсека корабля
hgeSprite *cargobayslot;//картинка ячейки грузового отсека корабля
hgeSprite *tractorspr;//эффект тягового луча
hgeSprite *fail1spr;//эффект указателя направления на цель
hgeSprite *resized_info[3];//картинки с растягивающейся подсказкой
hgeSprite *shipinfospr;//интерфейс корабля
hgeSprite *planethlp;//описание планеты

HANIM    *animships[100];//анимированные корабли
HANIM    *animitem[100];//анимированные различные космические объекты
HANIM    *animeffects[10];//анимированные эффекты
HANIM    *bganimeffects[10];//анимированные эффекты фона
HANIM    *mapeffects[10];//анимированные эффекты карты
HANIM    *animportal[2];//эффект ухода корабля в варп, может потом сделаю 3 эффекта, а пока только 2
HANIM    *cargobox;//грузвовой контейнер
HANIM    *cursor1;
HANIM    *map_poz;

hgeSprite *asteroids[5];//спрайты астероидов
hgeSprite *bullspr[5];//спрайты снарядов
hgeSprite *PlanetsSpr[10];//спрайты планет
hgeSprite *SysIcons[10];//иконки секторов на зв.карте
hgeSprite *BGsprites[10];//картинки статических объектов фона
hgeParticleSystem  *effects[5];//все эффекты игры
hgeSprite *staticitems[50];//статические картинки вещей
hgeSprite *ataico;//картинка атаки по цели
hgeParticleSystem  *suns[5];//эффекты солнца

char *BG_Spr[10];//названия файлов заднего фона
char *BG_PartSpr[10];//названия файлов туманностей заднего фона
char *PLN_Spr[30];//названия файлов заднего фона

char *GoodPlanets[10];//планеты, для заселения
char *BadPlanets[10];//планеты, с трудностью заселения

vector <char*> systems_names;//названия систем

//информационные переменные, показывают количество различных созданных объектов в игре
int GlobalDynObj = 0;//глобальная переменная динамических объектов
int GlobalShipObj = 0;//количество кораблей

//вектора с динамическими данными
player  *Player;
//vector<dynamic*> dyn;//старый вектор
vector<shared_ptr<dynamic>> dyn;

vector<effect*> eff;//все эффекты обрабатываются тут

vector<planet*> planetary;//все планеты в игре
vector<sector*> sectors;//все системы в игре

vector<bgobj*> bgobjects;//все объекты фона в игре

vector<cargo*> cargoobjects;//все вещи в игре

HSHADER             shad1;

bool FrameFunc()
{
	dt = hge->Timer_GetDelta();
	if (hge->Input_GetKeyState(HGEK_ESCAPE)) return true;//при нажатии сразу выключаем

	int id;
	static int lastid = 0;


	switch(GameState)
	{
	case 0://меню игры
		id=gui->Update(dt);
		if(id == -1)
		{
			switch(lastid)
			{//новая игра
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
    case 1://основной цикл игры
		  MainWorld->WorldUpdate();//обновляем мир

	break;
	case 2://загрузка
		  GameState = -1;
	break;
	case 3://смена карты в игре, загрузка ресурсов новой игры
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
	case -1://картинка загрузки
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
	case 0://рисуем меню игры
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
	case 1://основной цикл игры
		MainWorld->WorldRender();//рисуем все что надо

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
     //Тут задаем начальные координаты секторов, средний размер системы 10К*10К + рассояние между ними примерно 5К.
	 syspozx[0]=5000;
	 syspozy[0]=5000;


	if(hge->System_Initiate())
	{//подключаем архив данных
		if(hge->Resource_AttachPack("res.zip"))
		{
           hge->System_Log("Resourse pack attach...OK");
		}else
		{
			hge->System_Log("Cant load res.zip");
		};
		Mpack=new hgeResourceManager("scripts.cfg");
        //начальные файлы
		snd=Mpack->GetEffect("menu");
		fnt=Mpack->GetFont("main");
		load=Mpack->GetAnimation("loading");
		load->Play();
		load2=Mpack->GetSprite("loading2");
		mainbg=Mpack->GetSprite("bg00");
		/////////Создаём главное меню
		gui=new hgeGUI();
		gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Новая игра"));
		gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,240,0.1f,"Продолжить"));
		gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,280,0.2f,"Настройки"));
		gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,320,0.3f,"Авторы"));
		gui->AddCtrl(new hgeGUIMenuItem(5,fnt,snd,400,360,0.4f,"Выйти"));
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