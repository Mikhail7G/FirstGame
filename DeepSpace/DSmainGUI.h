#ifndef DSMAINGUI_H
#define DSMAINGUI_H

/* Это основа всех компонентов интерфейса, тут хранятся все единые компоненты для всех ГУИ элементов */

#include <hge.h>
#include <hgefont.h>
#include < hgerect.h>
#include <memory>
#include "resizlabel.h"




class DSGUI
{
public:

	hgeSprite *back;//фон эемента ГУИ
	bool render;//рисовать ли элемент?
	bool lockkeyboard;//блокировать ли кнопи?
	float scalefactor;

	dynlabel *dyntxt;

	DSGUI();
	~DSGUI();

	virtual void Render();//функция рисования ГУИ, для каждого свое
	virtual bool MouseTest();//проверка наведения мышки на конкретный элемент ГУИ
	virtual void Show();//показать элемент гуи



};


#endif