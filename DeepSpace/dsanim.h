#ifndef DSANIM_H
#define DSANIM_H

#include <hge.h>
#include <hgesprite.h>
#include <fstream>
#include <iostream>
#include <vector>
#include "zlib.h"
extern HGE *hge;

using namespace std;

class HANIM
{
public:
    HANIM(char *name);
	~HANIM();
	FILE *f;

	char *name;
	//HTEXTURE tex[100];//больше не используется
	int wight;
	int height;
	int numframes;

	vector<HTEXTURE> tex;

protected:
		DWORD *val;
		DWORD tz;
		DWORD a;
		DWORD red;
		DWORD green;
		DWORD blue;
		int loadmode;

		DWORD testmass;

		unsigned long destLen;
		unsigned long compLen;




};




#endif