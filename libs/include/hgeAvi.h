#include "hge.h"
#include "hgesprite.h"
#include <vfw.h>

#ifndef HGEAVI_H
#define HGEAVI_H
 	enum AviState {
		STOP = 0,
		PLAY = 1,
		PAUSE = 2
	};
 
class hgeAVI;


class hgeAVI {
public:
	hgeAVI(const char *filename, bool bLoop = false);
	virtual void Update();
	virtual ~hgeAVI();
	bool Load(const char *filename, bool bLoop = false);

	void Render(float x1, float y1, float x2, float y2,float x3, float y3,float x4, float y4);
	void Render(float x, float y, float rot, float hscale, float vscale);
	void Render(float x1, float y1, float x2, float y2);
	void Render(float x, float y);

	void Play();
	void Pause();
	void Stop();

	int Video_GetHeight() const;
	int Video_GetWidth() const;

	float Video_GetLength();
	float Video_GetFrameLength();
	int Video_GetFrameFPS();
	int Video_GetFrameTotal();

	float GetPos();
	int GetFramePos() const;
	void SetPos(float fPos);

	void SetSpeed(float fSpeed);
	float GetSpeed();

	inline bool IsPlaying(){return GetState(PLAY);}
	bool GetState(AviState);

HTEXTURE ExtractFramePos(float fPos);
HTEXTURE ExtractFrame(unsigned int nFrame);

hgeSprite* Video_GetSprite() {return zsprite;}

private : AviState zcurrentState;HTEXTURE ztexture;hgeSprite *zsprite;HGE *zhge;AVIFILEINFO zaviInfo;PAVIFILE zaviFile;PAVISTREAM zaviStream;PGETFRAME zaviFrame;bool zbLoop;int zfirstFrame,znumFrames;float zFmLen,zClipLen,zlastDrawTime,zcurrentFrame,zfSpeed;virtual bool zUpdateTexture(HTEXTURE tex, int nFrame);};
 



#endif /* HGEAVI_H */