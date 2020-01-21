#ifndef RUDACORE_H
#define RUDACORE_H

// онтейнер руды, выбиваемой с астероидов и пр.

#include <hge.h>
#include "dsanim.h"
#include "dsanimate.h"
#include "Itemcore.h"

extern hgeSprite *staticitems[];
extern HANIM    *animitem[];

using namespace std;
extern HGE *hge;
extern float dt;


class ruda:public cargo
{
public:


	ruda();
	~ruda();

};

#endif