#ifndef DSANIMATE_H
#define DSANIMATE_H
#include "dsanim.h"

extern HGE *hge;
extern float dt;

class hgeAnim
{
public:
	enum playMode 
	{
		PLAY_ONCE = 0,
		PLAY_LOOP = 1
	};
	enum state
	{
		STATE_STOP = 0,
		STATE_PLAY = 1,
		STATE_PAUSE = 2
	};
	state currentState;
	playMode currentPlayMode;

	hgeSprite *sprite;
	HANIM *img;
	bool changeImg;

	int firstFrame;
	int currentFrame;
	int numFrames;
	float lastDrawTime;

	float width;
	float height;
	unsigned pitch;
  	float renderspeed;

	hgeAnim(HANIM  *img,playMode playmode);
	~hgeAnim();
	void Update();
	void Render(float x,float y);
	void RenderEx(float x,float y,float dir,float hscale,float wscale);
	void SetSpeed(float renderspeed);
	void RandomStart();//случайный начальный индекс картинки
	float x;
	float y;
	float dir;	
	float hscale;
	float wscale;



};



#endif