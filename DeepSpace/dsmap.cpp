#include "dsmap.h"

dsmap::dsmap(player *_plr)
{
	plr = _plr;
	Selected = false;
	maxdist = 1;
	back = sysmap;
	targetid = -1;
	drawpt = false;

	scalefactor = GlobalMapScaleFactor;//это не трогать
	map_scale_factor = 0.001f;//область, показываемая игроку
	map_movx = 0;
	map_movy = 0;

	complete_path = false;

	img = new hgeAnim(map_poz, hgeAnim::PLAY_LOOP);
};

dsmap::~dsmap()
{

};

void dsmap::CommandsUpdate()
{

	map_scale_factor += hge->Input_GetMouseWheel()*dt*0.05f;

	if (map_scale_factor < 0.0005f)//минимальный маштаб
	{
		map_scale_factor = 0.0005f;
	};

	if (map_scale_factor > 0.006f)//максимальный маштаб
	{
		map_scale_factor = 0.006f;
	};

	float mapspeed = 50 / map_scale_factor;

	if (lockkeyboard)//двигаем карту, когда на ней мышка
	{
		if ((hge->Input_GetKeyState(HGEK_UP)) || (hge->Input_GetKeyState(HGEK_W))){ map_movy += mapspeed*dt; };
		if ((hge->Input_GetKeyState(HGEK_DOWN)) || (hge->Input_GetKeyState(HGEK_S))){ map_movy -= mapspeed*dt; };
		if ((hge->Input_GetKeyState(HGEK_LEFT)) || (hge->Input_GetKeyState(HGEK_A))){ map_movx += mapspeed*dt; };
		if ((hge->Input_GetKeyState(HGEK_RIGHT)) || (hge->Input_GetKeyState(HGEK_D))){ map_movx -= mapspeed*dt; };
	};

};

void dsmap::Show()
{
	render = !render;
	drawpt = false;
	lockkeyboard = false;
	targetid = -1;

	maxdist = plr->PlayerShip->shipengine->warprange;//дальность прыжка двигателя корабля игрока
};

void dsmap::Render()
{

	mapx = xview + ScreenWidth / 2;//положение на экране
	mapy = yview + ScreenHeight / 2;

	float maxx = 420 / map_scale_factor;//правая нижняя граница карты
	float maxy = 380 / map_scale_factor;

	flyto = PlayerSys;
	Selected = false;

	back->RenderEx(mapx, mapy, 0, 1, 1);

	float p_x = (mapx)+(sectors.at(PlayerSys)->x + map_movx)*map_scale_factor;
	float p_y = (mapy)+(sectors.at(PlayerSys)->y + map_movy)*map_scale_factor;


	if (((p_x + map_movx) > -maxx / 2) && ((p_y + map_movy) > -maxy / 2) && (((p_x)+map_movx) < maxx / 2) && (((p_y + map_movy)) < maxy / 2))//проверяем те системы, которые видно на маштабируемой карте
	{
		img->RenderEx(p_x, p_y, 0, 1, 1);
		img->Update();
	};

	//mainf->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, "%f", map_scale_factor);

	for (int i = 0; i<sectors.size(); i++)
	{
		if (((sectors.at(i)->x + map_movx)> -maxx / 2) && ((sectors.at(i)->y + map_movy) > -maxy / 2) && (((sectors.at(i)->x) + map_movx) < maxx / 2) && (((sectors.at(i)->y + map_movy)) < maxy / 2))//проверяем те системы, которые видно на маштабируемой карте
		{

			if (sectors.at(i)->hide == false)//непоказывать квествоые и специальные системы на карте.
			{
				sysx = (mapx )  + (sectors.at(i)->x + map_movx)*map_scale_factor;
				sysy = (mapy )  + (sectors.at(i)->y + map_movy)*map_scale_factor;

				//sectors.at(i)->ico->RenderEx(sysx, sysy, 0, 1, 1);
				sectors.at(i)->Render(sysx, sysy);

				if (map_scale_factor > 0.004f)//рисуем имя сектора
				{
					float n_x=0;
					float n_y=0;
		
					if (sysx < mapx)
					{
						n_x = 0;
					}
					else
					{
						n_x = 10*strlen(sectors.at(i)->name);

					};

					if (sysy > mapy)
					{
						n_y =- 20;
					}
					else
					{
						n_y = 10;

					};
				
					//mainf->printf((sysx), (sysy), HGETEXT_LEFT, "%0.5f", n_x);

					mainf->printf((sysx)-n_x, (sysy)+n_y, HGETEXT_LEFT, "%s", sectors.at(i)->name);
				};

				if (mouse_on(sysx, sysy, MouseX, MouseY, 10, 10))
				{
					//mainf->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, "%s", sectors.at(i)->name);
					mainf->printf((MouseX), (MouseY)-20, HGETEXT_LEFT, "%i", i);

					dist = point_distanse(sectors.at(PlayerSys)->x, sectors.at(PlayerSys)->y, sectors.at(i)->x, sectors.at(i)->y);

					fnt->printf((mapx - 210), (mapy - 224), HGETEXT_LEFT, "%0.1f", dist / 10000);
					fnt->printf((mapx - 110), (mapy - 224), HGETEXT_LEFT, "%0.1f", maxdist / 10000);

					if (hge->Input_KeyDown(HGEK_LBUTTON))
					{
						maxdist = plr->PlayerShip->shipengine->warprange;
						lockkeyboard = false;

						if ((i != PlayerSys) && (dist < maxdist))
						{

							flyto = i;//куда полететь
							plr->MapTarget(flyto);
							render = false;
							drawpt = false;
						};
						//if ((drawpt == true) && (i == targetid))//летим на автопилоте
						//{
						//	plr->PlayerShip->ActiveAutoPilot(systems_pos);
						//	render = false;
						//	drawpt = false;
						//}

					};
					if (hge->Input_KeyUp(HGEK_RBUTTON))//рисуем траекторию полета корабля
					{
						if (targetid == i)
						{
							drawpt = false;
							targetid = -1;
						}
						else
						{
							//drawpt = true;
							targetid = i;
							CalculatePath();
						};
					};

				};
			};
		};

	};

	DrawPath();
	CommandsUpdate();

};

bool dsmap::MouseTest()
{
	hgeRect *rr = new hgeRect();
	back->GetBoundingBoxEx(mapx, mapy, 0, 1, 1, rr);
	if (rr->TestPoint(MouseX, MouseY))
	{
		lockkeyboard = true;
		delete rr;
		return true;
	}
	else
	{
		lockkeyboard = false;
		delete rr;
		return false;
	};
};

void dsmap::DrawPath()
{
	if (drawpt)
	{
	for (int i = 0; i < systems_pos.size()-1; i++)
		{
			float px0 = (mapx ) + (sectors.at(systems_pos.at(i))->x + map_movx)*map_scale_factor;//-210
			float py0 = (mapy) + (sectors.at(systems_pos.at(i))->y + map_movy)*map_scale_factor;//-180

			float px1 = (mapx ) + (sectors.at(systems_pos.at(i + 1))->x + map_movx)*map_scale_factor;
			float py1 = (mapy ) + (sectors.at(systems_pos.at(i + 1))->y + map_movy)*map_scale_factor;

			hge->Gfx_RenderLine(px0, py0, px1, py1, ARGB(255, 255, 255, 255));

		};
	};



};

void dsmap::CalculatePath()
{

};

void dsmap::SlowCalc()
{
	max_errors = 100;//число итераций
	//
	//systems_pos.clear();//очищаем путь
	////systems_pos.push_back(PlayerSys);//сразу добавляем начальную систему
	////тут идет расчет маршрута
	//p_sys = PlayerSys;
	//cur_sys = p_sys;//текущая выбрання система для нахождения ее веса
	//complete_path = true;//начать поиск пути



	//for (int i = 0; i < sectors.size(); i++)//заполняем бесконечностью
	//{
	//	distanses.push_back(9999999999);
	//	clear_systems.push_back(false);//пока нет посещенных систем
	//	last_calc_sys.push_back(0);
	//};
	//distanses.at(cur_sys) = 0;//начальная точка отсчета

	//while (complete_path)
	//{
	//	for (int i = 0; i < sectors.size(); i++)
	//	{
	//		if (i == cur_sys)//игнорируем систему от которой ведем отсчет
	//		{
	//		}
	//		else
	//		{
	//			float dist = point_distanse(sectors.at(cur_sys)->x, sectors.at(cur_sys)->y, sectors.at(i)->x, sectors.at(i)->y);
	//			if (dist < maxdist)//можно ли достать до этой системы?
	//			{
	//				float sum_dist = distanses.at(cur_sys) + dist;
	//				if (sum_dist < distanses.at(i))
	//				{
	//					distanses.at(i) = sum_dist;//записываем новое расстояние до этой системы из расчетной
	//					last_calc_sys.at(i) = cur_sys;
	//				};
	//			};

	//		};
	//	};
	//	clear_systems.at(cur_sys) = true;//отмечаем систему как посещенную

	//	min_dist = 99999999999;
	//	for (int i = 0; i < sectors.size(); i++)
	//	{
	//		if (clear_systems.at(i) == false)
	//		{
	//			if (distanses.at(i) < min_dist)
	//			{
	//				cur_sys = i;
	//				min_dist = distanses.at(i);

	//				//if (cur_sys == targetid)//укороченный просчет, не всегда показывет маршрут до цели
	//				//{
	//				//	complete_path = false;
	//				//}
	//				complete_path = false;
	//				for (int t = 0; t < clear_systems.size(); t++)
	//				{
	//					if (clear_systems.at(i) == false)
	//					{
	//						complete_path = true;
	//					}
	//				}


	//			};
	//		};
	//	};

	//	max_errors--;
	//	if (max_errors < 0)
	//	{
	//		complete_path = false;
	//		break;
	//	}
	//};
	//
	//	next_sys = targetid;
	//	vector<int> revers;

	//	while (next_sys != p_sys)
	//	{
	//		revers.push_back(last_calc_sys.at(next_sys));
	//		next_sys = last_calc_sys.at(next_sys);
	//	};

	//	for (int i = 0; i < revers.size(); i++)//обратный веткор, т.к. системы записываются от конечной к начальной
	//	{
	//		systems_pos.push_back(revers.at(revers.size() - 1 - i));
	//	};

	//	if (systems_pos.size()>1)
	//	{
	//		systems_pos.push_back(targetid);//в конце добавляем сектор назначения
	//	};

	//	drawpt = true;//рисуем путь
	

	

}