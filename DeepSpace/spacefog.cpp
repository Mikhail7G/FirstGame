#include "spacefog.h"

spacefog::spacefog(int _layer, int _sysid, float _x, float _y, int _SpriteID)
{
	sysid=_sysid;
	SpriteID = _SpriteID;
	dx=syspozx[sysid]+_x;
	dy=syspozy[sysid]+_y;
	x=0;
	y=0;
	div=1.1f;
	//spr = BGsprites[SpriteID];
	spr = new hgeSprite(0, 0, 0, 0, 0);
	layer=_layer;
	switch(layer)
	{
		case 0://уровень заднего фона
			div=1.1f;
		break;
		case 1:
			div=1.2f;
		break;
		case 2:
			div=1.3f;
		break;
		case 3:
			div=1.35f;
		break;
		case 4:
			div = 1.39f;
			break;
		case 5:
			div = 1.4f;
			break;
		case 6:
			div = 1.44f;
			break;

	};
	reloaded = false;

};
spacefog::~spacefog()
{
};

void spacefog::Render()
{
	x=dx-((dx-ScreenCenterX)/div);
	y=dy-((dy-ScreenCenterY)/div);
	spr->Render(x,y);

};

void spacefog::LoadTex()
{
	if (layer == 1)
	{
		tex = hge->Texture_Load(BG_Spr[SpriteID]);//задний фон
	}
	else
	{
		tex = hge->Texture_Load(BG_PartSpr[SpriteID]);//туманности
	};
	spr->SetTexture(tex);
	spr->SetTextureRect(0, 0, hge->Texture_GetHeight(tex), hge->Texture_GetWidth(tex));
	spr->SetHotSpot(hge->Texture_GetHeight(tex) / 2, hge->Texture_GetHeight(tex) / 2);
	spr->SetBlendMode(BLEND_COLORMUL);
	reloaded = true;
};

void spacefog::ChangeMap()//смена карты
{
	if (sysid == PlayerSys)//если сектор не игрока то обнуляем текстуры
	{
		LoadTex();
		reloaded = true;
	}
	else//иначе загружаем то что нужно
	{
		if (reloaded)
		{

			spr->SetTexture(0);
			spr->SetTextureRect(0, 0, 0, 0);
			spr->SetHotSpot(0, 0);
			hge->Texture_Free(tex);
			reloaded = false;
		};
	};

};