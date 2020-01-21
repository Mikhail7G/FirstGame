#ifndef BGCORE_H
#define BGCORE_H

#include <hge.h>
#include <hgefont.h>
#include <vector>

#include "dsanim.h"
#include "dsanimate.h"

#include "effect.h"
#include "explosion.h"

using namespace std;
extern HGE *hge;
extern float dt;


extern float ScreenCenterX;
extern float ScreenCenterY;

extern hgeSprite *star;
extern hgeSprite *mainspace;

extern vector<effect*> eff;

extern HANIM    *bganimeffects[];

extern hgeParticleSystem  *suns[];

extern float syspozx[];
extern float syspozy[];

extern int PlayerSys;

class worldbg
{
public:
	float dx;
	float dy;

	float x;
	float y;

	float randomtimer;//таймер рандомного спавна раличных
	float timer1;


	worldbg();
	~worldbg();
	void RenderBG();
	void UpdateBG();
    void SpawnRandom();//создаём рандомно эффекты фона
	void RestartSun();



};


#endif