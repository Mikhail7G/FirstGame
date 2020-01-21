#include "cargogui.h"


shipcargoGUI::shipcargoGUI(player *_plr)
{
	plr = _plr;
	back = cargobayspr;
	screenx = 0;
	screeny = 0;
	maxslot = 28;
	

};

shipcargoGUI::~shipcargoGUI()
{

};

void shipcargoGUI::Render()
{
	screenx = ScreenWidth / 2 + xview + 350;
	screeny = ScreenHeight / 2 + yview + 150;

	dx = ScreenWidth / 2 + xview + 50;// ����� ���� �������� �������� ��������� 1 ��� � ����������� �� ���������� ���������� ������
	dy = ScreenHeight / 2 + yview;

	back->RenderEx(screenx, screeny, 0, 1, 1);

	slotx = screenx - 90;
	sloty = screeny - 190;

	int t = 0;
	for (int i = 0; i<maxslot; i++)
	{
		cargobayslot->RenderEx(slotx, sloty, 0, 1, 1);

		DrawItem(i, slotx, sloty);

		slotx += 60;
		t++;
		if (t>3)
		{
			t = 0;
			slotx = screenx - 90;
			sloty += 60;

		};
	};


	if (hge->Input_KeyDown(HGEK_L))//����������(���� ���)
	{
		auto cr = plr->PlayerShip->crgmgr;
		cr->SortAllItems();
	};

};

void shipcargoGUI::DrawItem(int _id, float _x, float _y)
{
	int id = _id;

	auto cr = plr->PlayerShip->crgmgr;

	if (cr->crg.size()>id)
	{
		cr->crg.at(id)->ico->Render(_x, _y);
		MouseOper(id, _x, _y);
	};
};

void shipcargoGUI::Show()
{
	render = !render;
};

bool shipcargoGUI::MouseTest()
{
	hgeRect *rr = new hgeRect();
	back->GetBoundingBoxEx(screenx, screeny, 0, 1, 1, rr);
	if (rr->TestPoint(MouseX, MouseY))
	{
		delete rr;
		return true;
	}
	else
	{
		delete rr;
		return false;
	};

};

void shipcargoGUI::MouseOper(int _id, float _x, float _y)
{
	auto cr = plr->PlayerShip->crgmgr;
	if (mouse_on(MouseX, MouseY, _x, _y, 20, 20))//����������� �������� ��������
	{
		//itemhelp->RenderEx(ScreenWidth/2+xview+50,MouseY,0,1,1);
		switch (cr->crg.at(_id)->type)
		{
		case 0:
			DrawHullData(_id);
			break;
		case 1:
			DrawEngineData(_id);
			break;
		case 2:
			DrawWeaponData(_id);
			break;
		case 3:
			DrawBullData(_id);
			break;
		case 4:
			DrawMineralData(_id);
			break;

		}
	};

	///��������� ����� �� �������
	if (hge->Input_KeyDown(HGEK_LBUTTON))//��������� ����� �� ������� � �������(���� ��?)
	{
		if (mouse_on(MouseX, MouseY, _x, _y, 20, 20))
		{
			switch (cr->crg.at(_id)->type)
			{
			case 1://��������� ���������
			//	InstallEngine(_id);//������ �� ��������
				break;
			case 2://��������� �����
					InstallTurret(_id);
				break;
			case 3://������� ��������
					InstallBullet(_id);
				break;
			}
		};
	};
	//��� ����� ���������
	if (hge->Input_KeyDown(HGEK_RBUTTON))//������ ����� �� ����
	{
		if (mouse_on(MouseX, MouseY, _x, _y, 20, 20))
		{
			//cr->DropItem(_id,plr->PlayerShip->sysid,plr->PlayerShip->x,plr->PlayerShip->y);
			switch (cr->crg.at(_id)->type)
			{
			case 3://����� �������� � ������
				WeaponTest(_id);
				break;
			};
			plr->PlayerShip->DropItem(_id);
		};
	};
};

void shipcargoGUI::WeaponTest(int _id)
{
	int id = _id;
	auto cr = plr->PlayerShip;

	for (int i = 0; i<cr->weapons.size(); i++)
	{
		shared_ptr<bullet> pr;
		bullcont *cnt;
		cnt = dynamic_cast<bullcont*>(plr->PlayerShip->crgmgr->crg.at(id));

		if (cr->weapons.at(i)->bull == cnt->GetBull())//���� ����� ������ �������, �� ��������� ������
		{
			cr->weapons.at(i)->DestroyBullet();
		};
	};


};

void shipcargoGUI::InstallTurret(int _id)
{
	int id = _id;
	auto cr = plr->PlayerShip->crgmgr;


	if (plr->PlayerShip->InstallWeapon(dynamic_cast<turret*>(cr->crg.at(id))))
	{
		dynamic_cast<turret*>(cr->crg.at(id))->SetParient(plr->PlayerShip);//��������� ������ ��� ��������
		cr->DropItem(id);
	};
};

void shipcargoGUI::InstallBullet(int _id)
{
	int id;
	id = _id;
	auto cr = plr->PlayerShip;

	for (int i = 0; i<cr->weapons.size(); i++)//��������� ������� ������ �� �������
	{
		if (cr->weapons.at(i)->bull == false)//���� ������ �� ���������, �� ������������� ������
		{
			shared_ptr<bullet> pr;
			bullcont *cnt;
			cnt = dynamic_cast<bullcont*>(plr->PlayerShip->crgmgr->crg.at(id));
			cr->weapons.at(i)->SetBullet(cnt->GetBull());
			break;
		};
	};
};
void shipcargoGUI::InstallEngine(int _id)
{
	int id;
	id = _id;
	auto cr = plr->PlayerShip;
	if (cr->shipengine == 0)//��������� ������� ��������� �� �������
	{
		cr->InstallEngine(dynamic_cast<engine*>(cr->crgmgr->crg.at(id)));
		cr->DropItem(id);//������� �� ��������� ������
	};


};


void shipcargoGUI::DrawWeaponData(int _id)
{
	int id = _id;

	auto cr = plr->PlayerShip->crgmgr;

	dyntxt->GetText(cr->crg.at(id)->description);

	dyntxt->Render(dx, dy - 70, 8, 15);//������������ ��������	

	turret *wpn;
	wpn = dynamic_cast<turret*>(cr->crg.at(id));
	//������� ���� � ������(����������� ��� ��������)
	wpn->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "���:%s", wpn->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "���������:%1.0f", ((wpn->optimal) + (wpn->fireradius)) / scalefactor);
	mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "���������� �������:%1.0f ���", wpn->reloadtimer);
	mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "����������������:%0.1f ���", wpn->ammoreload);
	mainf->printf(dx - 130, dy - 10, HGETEXT_LEFT, "���������� �������:%1.0f", wpn->sigradius);
	mainf->printf(dx - 130, dy + 5, HGETEXT_LEFT, "�������:%0.1f ����/�", (wpn->tracking) / 3.14f * 180);
	mainf->printf(dx - 130, dy + 20, HGETEXT_LEFT, "��������� �������:%0.1f", (wpn->damagemod));
	mainf->printf(dx - 130, dy + 35, HGETEXT_LEFT, "�������� � �������:%i", (wpn->ammoclip + 1));
	mainf->printf(dx - 130, dy + 50, HGETEXT_LEFT, "%s", (dyntxt->newdescr));

	mainf->printf(dx + 30, dy - 115, HGETEXT_LEFT, "�������:%i", wpn->itemlevel);
	mainf->printf(dx + 30, dy - 100, HGETEXT_LEFT, "�����:%1.0f", wpn->mass);
};

void shipcargoGUI::DrawHullData(int _id)
{
	int id = _id;

	auto cr = plr->PlayerShip->crgmgr;

	hull *hl;
	hl = dynamic_cast<hull*>(cr->crg.at(id));

	//	GetDescriptionData(id);

	dyntxt->GetText(cr->crg.at(id)->description);
	dyntxt->Render(dx, dy - 70, 8, 15);//������������ ��������

	hl->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "���:%s", hl->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "����� ���������:%1.0f", hl->maxhp);
	mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "������������� �:%1.0f �:%1.0f �:%1.0f �:%1.0f", hl->explres, hl->kinres, hl->termres, hl->radiores);
	mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "��������� �������:%1.0f", (hl->sensorrange) / scalefactor);
	mainf->printf(dx - 130, dy - 10, HGETEXT_LEFT, "��������� ������:%i", hl->wslot);
	mainf->printf(dx - 130, dy + 5, HGETEXT_LEFT, "���������:%1.0f", hl->sigradius);
	mainf->printf(dx - 130, dy + 20, HGETEXT_LEFT, "�����:%1.0f", hl->mass);
	mainf->printf(dx - 130, dy + 35, HGETEXT_LEFT, "%s", dyntxt->newdescr);

	mainf->printf(dx + 30, dy - 115, HGETEXT_LEFT, "�������:%i", hl->itemlevel);
	mainf->printf(dx + 30, dy - 100, HGETEXT_LEFT, "�����:%1.0f", hl->mass);

};

void shipcargoGUI::DrawEngineData(int _id)
{
	int id = _id;

	auto cr = plr->PlayerShip->crgmgr;

	engine *eng;
	eng = dynamic_cast<engine*>(cr->crg.at(id));

	//	GetDescriptionData(id);
	dyntxt->GetText(cr->crg.at(id)->description);
	dyntxt->Render(dx, dy - 70, 5, 15);//������������ ��������

	eng->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "���:%s", eng->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "����:%0.1f �/�", eng->speed);
	mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "�������:%0.1f �/�", eng->impulse);
	mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "��������� ������:%0.1f ��.���", (eng->warprange) / 10000);
	mainf->printf(dx - 130, dy - 10, HGETEXT_LEFT, "%s", dyntxt->newdescr);

	mainf->printf(dx + 30, dy - 115, HGETEXT_LEFT, "�������:%i", eng->itemlevel);
	mainf->printf(dx + 30, dy - 100, HGETEXT_LEFT, "�����:%1.0f", eng->mass);
};

void shipcargoGUI::DrawBullData(int _id)
{
	int id = _id;

	auto cr = plr->PlayerShip->crgmgr;

	shared_ptr<bullet> pr;
	bullcont *cnt;
	cnt = dynamic_cast<bullcont*>(cr->crg.at(id));

	pr = cnt->GetBull();

	//GetDescriptionData(id);
	dyntxt->GetText(pr->description);
	dyntxt->Render(dx, dy - 70, 3, 15);//������������ ��������

	pr->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "���:%s", pr->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "���� �:%1.0f �:%1.0f �:%1.0f �:%1.0f", pr->Kdmg, pr->Edmg, pr->Tdmg, pr->Rdmg);
	mainf->printf(dx - 130, dy - 40, HGETEXT_LEFT, "���������� :%i", pr->totalCount);
	mainf->printf(dx - 130, dy - 25, HGETEXT_LEFT, "%s", dyntxt->newdescr);

};

void shipcargoGUI::DrawMineralData(int _id)
{
	int id = _id;

	auto cr = plr->PlayerShip->crgmgr;

	ruda *rd;
	rd = dynamic_cast<ruda*>(cr->crg.at(id));

	//	GetDescriptionData(id);
	dyntxt->GetText(cr->crg.at(id)->description);
	dyntxt->Render(dx, dy - 70, 1, 15);//������������ ��������

	rd->ico->Render(dx, dy - 100);
	mainf->printf(dx - 130, dy - 70, HGETEXT_LEFT, "���:%s", rd->name);
	mainf->printf(dx - 130, dy - 55, HGETEXT_LEFT, "%s", dyntxt->newdescr);

	mainf->printf(dx + 30, dy - 100, HGETEXT_LEFT, "�����:%1.0f", rd->mass);
};