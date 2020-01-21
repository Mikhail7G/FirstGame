#include "sector.h"



sector::sector(float _x,float _y,hgeSprite *_ico)
{
	x=_x;
	y=_y;
	id = 0;
	syspozx[Count]=x;
	syspozy[Count]=y;
	Count++;
	level=1;

	ico=_ico;
	name="���";
	raiting=1;
	hide=false;

	//aico = new hgeAnim(ani, hgeAnim::PLAY_LOOP);

	call_time = 0;
	last_time = 0;
	cur_col_obj = 0;
	
}

sector::sector(float _x, float _y, HANIM *_ani)
{
	x = _x;
	y = _y;
	id = 0;
	syspozx[Count] = x;
	syspozy[Count] = y;
	id = Count;
	Count++;
	level = 1;

	ani = _ani;

	name = "���";
	raiting = 1;
	hide = false;

    aico = new hgeAnim(ani, hgeAnim::PLAY_LOOP);
	aico->RandomStart();

	call_time = 0;
	last_time = 0;

	cur_col_obj = 0;

}

void sector::Render(float _x,float _y)
{
	
	aico->RenderEx(_x, _y, 0, 1, 1);
	aico->Update();
};


sector::~sector()
{

};

void sector::AddToList(shared_ptr<dynamic> _obj)
{
	objects.push_back(_obj);
};

void sector::RemoveFromList(shared_ptr<dynamic> _obj)//��� ������� ������ �� �����!
{
	/*for (int i = 0; i < objects.size(); i++)
	{


		if (_obj == objects.at(i))
		{
			objects.erase(objects.begin() + i);
			cur_col_obj = 0;
			break;
		}

	};*/
	

};

void sector::Update()
{

	for (int i = 0; i < objects.size(); i++)//������������ �������
	{	
		if ((objects.at(i)->kill == false) && (objects.at(i)->sysid == id))
		{
			objects.at(i)->Update();

			if (objects.size()>1)
			{
				if (i >= objects.size())//�������, ����� ������. ������ �� ������� i �� ��������
				{
					i = objects.size()-1;
				};
				if (cur_col_obj >= objects.size())//�������, ����� ������. ������ �� ������� i �� ��������
				{
					cur_col_obj = objects.size() - 1;
				};
		
				if (mouse_on(objects.at(i)->x, objects.at(i)->y, objects.at(cur_col_obj)->x, objects.at(cur_col_obj)->y, CollRad, CollRad))
				{
					if (objects.at(cur_col_obj) != objects.at(i))//��� ���� ��������� �� ����!
					{
						objects.at(cur_col_obj)->AddCollisionTest(objects.at(i));//��������� ������� ������� � ������ ��� ����� ������ ��������
					};
				};
			};

		}
		else
		{
			objects.erase(objects.begin() + i);
			cur_col_obj = 0;
		};
	};

	cur_col_obj++;
	if (cur_col_obj == objects.size())
	{
		cur_col_obj = 0;
	}


	//���� � �������
	for (int i = 0; i < cargoobjects.size(); i++)
	{	
		if (cargoobjects[i]->state == 0)//���� � �������
		{
			if (cargoobjects[i]->kill == true)
			{
				delete cargoobjects[i];
				cargoobjects.erase(cargoobjects.begin() + i);
			};
		}
		else//���� ��������, �� ������� �� �������
		{
			cargoobjects.erase(cargoobjects.begin() + i);
		}
	};

	for (int i = 0; i < planetlist.size(); i++)//��������� �������
	{
		planetlist.at(i)->Update();
	};

	
};

void sector::Render()
{
	for (int i = 0; i < planetlist.size(); i++)//������ �������
	{
		planetlist.at(i)->Render();
	};

	for (int i = 0; i < objects.size(); i++)//������ �������(�������, ���������)
	{

		objects.at(i)->Render();
	};

	for (int i = 0; i < cargoobjects.size(); i++)//����������� ����
	{
		cargoobjects[i]->Render();
	};	
};

void sector::FastUpdate()
{	
	for (int i = 0; i < objects.size(); i++)
	{
		if ((objects.at(i)->kill == false) && (objects.at(i)->sysid == id))
		{
			objects.at(i)->FastUpdate(Call_Time);
		}
		else
		{
			objects.erase(objects.begin() + i);
		};
	};

	//���� � �������
	for (int i = 0; i < cargoobjects.size(); i++)
	{
		if (cargoobjects[i]->state == 0)//���� � �������
		{
			if (cargoobjects[i]->kill == true)
			{
				delete cargoobjects[i];
				cargoobjects.erase(cargoobjects.begin() + i);
			};
		}
		else//���� ��������, �� ������� �� �������
		{
			cargoobjects.erase(cargoobjects.begin() + i);
		}
	};


	for (int i = 0; i < planetlist.size(); i++)//��������� �������(���� ���)
	{
		planetlist.at(i)->FastUpdate(Call_Time);
	};


};

void sector::AddItemToList(cargo* _item)
{
	cargoobjects.push_back(_item);
};


//if (target.expired())//��������� ������� ����
//{
//	target.reset();

void sector::PreInit()
{
	cur_col_obj = 0;
};