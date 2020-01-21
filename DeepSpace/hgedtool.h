#ifndef HGEDTOOL_H
#define HGEDTOOL_H

#include "hge.h"
#include "hgefont.h"
extern 	HGE * hge;
 
class hgeDTool
{
public:
	hgeDTool();
	~hgeDTool();
	// QUADS
	void RenderQuad(hgeRect pos, hgeRect uv, HTEXTURE tex, DWORD col0, DWORD col1, DWORD col2, DWORD col3, int blend);
	void RenderQuad(hgeRect pos, hgeRect uv, HTEXTURE tex, DWORD col, int blend);
	void RenderQuad(hgeRect pos, HTEXTURE tex, DWORD col, int blend);
	// RECTS
	void RenderRect(float x0, float y0, float x1, float y1, DWORD Col);
	void RenderRect(hgeRect pos, DWORD Col);
	// CIRCLES
	void RenderCircle(float x, float y, float r, float segments, HTEXTURE tex, DWORD iner_col, DWORD outer_col, int blend, float sa, float a);
	void RenderCircumference(float x, float y, float r, float segments, DWORD col, float sa, float a);
};


#endif