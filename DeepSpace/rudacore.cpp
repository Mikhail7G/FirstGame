#include "rudacore.h"

ruda::ruda()
{
	canstak=true;
	count=1;
	mass=0.1f;
	name="Руда";
	type=4;
	ico=staticitems[3];
	crgbox=animitem[1];
	ItemCount++;
	description = "Основной компонент для производства всего оборудования и инфраструктуры планет. Содержит широкий спектр веществ известных так и ранее неизученных\0";
};

ruda::~ruda()
{

};

