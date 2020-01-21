#include "resizlabel.h"


dynlabel::dynlabel()
{
	x=0;
	y=0;
	table_size=0;
	font_size=0;
	tables=0;
	maxsymbols=32;
};

void dynlabel::Render(float _x,float _y, float _t,float _f)
{
	x=_x;
	y=_y;
	table_size=_t+tables;
	font_size=_f;
	float total;
	float scale = 0.5f;
	total=table_size*font_size;
	//total=
	resized_info[0]->RenderEx(x-1, y, 0, scale+0.1f, scale);
	resized_info[1]->RenderEx(x + 0.11f, y + (128 * scale), 0, scale + 0.1f, scale);
	resized_info[1]->SetTextureRect(0,0,512,total*2);
	resized_info[2]->RenderEx(x, y + (128 * scale) + total, 0, scale + 0.1f, scale);

	tables=0;
};

void dynlabel::GetText(char *_txt)
{
	tables=0;
	char *text=_txt;

	char cur=text[0];//берем 1 символ из описания
	int t=0;//счетчик символов
	int total=0;// max 33
	int lastpass=0;//символ пробел ' '
	
	while(!cur=='\0')
	{
		if(total==maxsymbols)
		{
			if(cur==' ')
			{
				newdescr[t]='\n';
				total=-1;//каждая строка начинается с 0 символа, но т.к. инкремент идет в конце функции, то пишем -1
				tables++;
			}
			else
			{
				newdescr[lastpass]='\n';
				newdescr[t]=cur;
				total=t-lastpass;//это начальная длинна новой строки после переноса
				tables++;
			};
		}
		else
		{
			if(cur==' ')
			{
				newdescr[t]=' ';
				lastpass=t;
			}
			else
			{
				newdescr[t]=cur;
			};

		};
		t++;
		total++;
		cur=text[t];
	}
	newdescr[t]='\0';

};

char dynlabel::DrawDescr()
{
	return *newdescr;
};

