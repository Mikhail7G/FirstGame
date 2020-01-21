#ifndef RESIZLABEL_H
#define RESIZLABEL_H
#include <hge.h>
#include <hgesprite.h>

//данный класс позволяет рисовать ратсягивающуюся по вертикали табличку для описания различных действий
extern HGE *hge;

extern hgeSprite *resized_info[];

class dynlabel
{
public:
	float x;//позиция на экране
	float y;
	float table_size;//число строк
	float font_size;//размер символа(пока 15)

	char newdescr[500];//новое описание
	int tables;//число строк в описании
	int maxsymbols;//макс число символов в строке

	dynlabel();
	~dynlabel();
	void Render(float x,float y,float table,float font);
	void GetText(char *txt);//отформатировать текст описания
	char DrawDescr();//нарисовать форматированный текст


};


#endif

