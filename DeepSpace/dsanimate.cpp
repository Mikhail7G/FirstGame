#include "dsanimate.h"

hgeAnim::hgeAnim(HANIM *_img, hgeAnim::playMode _playmode)
{
	img=_img;
    currentPlayMode=_playmode;
	width=img->wight;
	height=img->height;
	sprite=new hgeSprite(img->tex.at(0),0,0,width,height);
    sprite->SetHotSpot(width/2,height/2);
	numFrames=img->numframes;
	changeImg=true;
	if(numFrames>1)//Для статической картинки сразу делаем режим одиночного проигрования
	{
	//currentFrame=hge->Random_Int(2,numFrames-2);
		currentFrame=1;
	}else
	{
		currentFrame=1;
    	currentPlayMode=PLAY_ONCE;
	};
	renderspeed=5;
	lastDrawTime=0.1f;

};
hgeAnim::~hgeAnim()
{
	delete sprite;
	hge->System_Log("ANIM free");

};

void hgeAnim::RandomStart()
{
	if(numFrames>1)//Для статической картинки сразу делаем режим одиночного проигрования
	{
		currentFrame=hge->Random_Int(2,numFrames-2);
	}else
	{
		currentFrame=1;
    	currentPlayMode=PLAY_ONCE;
	};
};

void hgeAnim::Update()
{
	lastDrawTime-=dt;
	if(lastDrawTime<0)
	{
		lastDrawTime=dt*renderspeed;
		if(currentFrame==numFrames-2)//если конец кадров, то ставим на начало
		{
			if(currentPlayMode==1)
			{
				 currentFrame=0;	
			}
			else
			{
				currentFrame=numFrames-2;
			};
		}
		else
		{	
			currentFrame+=1;
		};		

      changeImg=true;
	};

	if(changeImg)
	{
		changeImg=false;
		sprite->SetTexture(img->tex.at(currentFrame)); 
	};


};

void hgeAnim::RenderEx(float _x, float _y, float _dir, float _hscale, float _wscale)
{
	x=_x;
	y=_y;
	dir=_dir;
	hscale=_hscale;
	wscale=_wscale;
	sprite->RenderEx(x,y,dir,hscale,wscale);

};