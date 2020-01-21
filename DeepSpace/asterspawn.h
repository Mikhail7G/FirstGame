#ifndef ASTERSPAWN_H
#define ASTERSPAWN_H

#include <vector>
#include <hge.h>
#include "cmath"
#include "dsanim.h"
#include "dsanimate.h"
#include <memory>

#include "dyncore.h"
#include "asteroids.h"
#include "sector.h"

using namespace std;

extern HGE *hge;
extern float dt;

extern bool GPAUSED;

extern vector<shared_ptr<dynamic>> dyn;
extern vector<sector*> sectors;

extern HANIM    *animitem[];

class asterctr
{
public:
	float timer1;//таймер 1
	float spawntimer;//время респавна

	asterctr(float spawntimer);
	~asterctr();

	void Update();
	void SpawnRandom();

	

};



#endif