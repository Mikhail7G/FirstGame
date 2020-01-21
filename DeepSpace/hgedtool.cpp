#include "hgeDTool.h"
#include <math.h>
 
hgeDTool::hgeDTool()
{
	
}
 
hgeDTool::~hgeDTool()
{
	
}
 
void hgeDTool::RenderQuad(hgeRect pos, hgeRect uv, HTEXTURE tex = 0, DWORD col0 = -1, DWORD col1 = -1, DWORD col2 = -1, DWORD col3 = -1, int blend = BLEND_DEFAULT)
{
	hgeQuad Quad;
 
	float tx0 = pos.x1;
	float ty0 = pos.y1;
	float tx1 = pos.x2;
	float ty1 = pos.y2;
 
	Quad.tex = tex;
	Quad.blend = blend;
 
	Quad.v[0].col = col0;
	Quad.v[0].tx = uv.x1;
	Quad.v[0].ty = uv.y1;
	Quad.v[0].x = tx0;
	Quad.v[0].y = ty0;
	Quad.v[0].z = 0.0f;
 
	Quad.v[1].col = col1;
	Quad.v[1].tx = uv.x2;
	Quad.v[1].ty = uv.y1;
	Quad.v[1].x = tx1;
	Quad.v[1].y = ty0;
	Quad.v[1].z = 0.0f;
 
	Quad.v[2].col = col2;
	Quad.v[2].tx = uv.x2;
	Quad.v[2].ty = uv.y2;
	Quad.v[2].x = tx1;
	Quad.v[2].y = ty1;
	Quad.v[2].z = 0.0f;
 
	Quad.v[3].col = col3;
	Quad.v[3].tx = uv.x1;
	Quad.v[3].ty = uv.y2;
	Quad.v[3].x = tx0;
	Quad.v[3].y = ty1;
	Quad.v[3].z = 0.0f;
 
 
	hge->Gfx_RenderQuad(&Quad);
}
 
void hgeDTool::RenderQuad(hgeRect pos, hgeRect uv, HTEXTURE tex = 0, DWORD col = -1, int blend = BLEND_DEFAULT)
{
	RenderQuad(pos, uv, tex, col, col, col, col, blend);
}
 
void hgeDTool::RenderQuad(hgeRect pos, HTEXTURE tex = 0, DWORD col = -1, int blend = BLEND_DEFAULT)
{
	RenderQuad(pos, hgeRect(0, 0, 1, 1), tex, col, col, col, col, blend);
}
 
void hgeDTool::RenderRect(float x0, float y0, float x1, float y1, DWORD Col = -1)
{
	float tx0 = x0+1;
	float ty0 = y0;
	float tx1 = x1;
	float ty1 = y1;
	hge->Gfx_RenderLine(tx0-1, ty0, tx1, ty0, Col);
	hge->Gfx_RenderLine(tx1, ty0, tx1, ty1, Col);
	hge->Gfx_RenderLine(tx1, ty1, tx0, ty1, Col);
	hge->Gfx_RenderLine(tx0, ty1, tx0, ty0, Col);
}
 
void hgeDTool::RenderRect(hgeRect pos, DWORD Col)
{
	RenderRect(pos.x1, pos.y1, pos.x2, pos.y2, Col);
}
 
void hgeDTool::RenderCircle(float x, float y, float r, float segments, HTEXTURE tex, DWORD iner_col, DWORD outer_col, int blend, float sa, float a)
{
	if (segments == 0) return; 
 
	hgeTriple tri; ZeroMemory(&tri, sizeof(tri));
 
	float _a = sa;
	float da = a/segments;
 
	float fpx = r*cos(_a);
	float fpy = -r*sin(_a);
	float spx = 0;
	float spy = 0;
 
	tri.blend = blend;
	tri.tex = tex;
 
	tri.v[0].col = iner_col;
	tri.v[0].tx = 0; tri.v[0].ty = 0;
	tri.v[0].z = 0;
	tri.v[0].x = x;
	tri.v[0].y = y;
 
	for (int i = 0; i<segments; i++)
	{
		_a += da;
		spx = r*cos(_a);
		spy = -r*sin(_a);
 
		tri.v[1].col = outer_col;
		tri.v[1].tx = 0; tri.v[1].ty = 0;
		tri.v[1].z = 0;
		tri.v[1].x = x + fpx;
		tri.v[1].y = y + fpy;
 
		tri.v[2].col = outer_col;
		tri.v[2].tx = 0; tri.v[2].ty = 0;
		tri.v[2].z = 0;
		tri.v[2].x = x + spx;
		tri.v[2].y = y + spy;
 
		hge->Gfx_RenderTriple(&tri);
 
		//hge->Gfx_RenderLine(x+fpx, y+fpy, x+spx, y+spy);
 
		fpx = spx;
		fpy = spy;
	}
}
 
void hgeDTool::RenderCircumference(float x, float y, float r, float segments, DWORD col, float sa, float a)
{
	if (segments == 0) return; 
 
	hgeTriple tri; ZeroMemory(&tri, sizeof(tri));
 
	float _a = sa;
	float da = a/segments;
 
	float fpx = r*cos(_a);
	float fpy = -r*sin(_a);
	float spx = 0;
	float spy = 0;
 
	for (int i = 0; i<segments; i++)
	{
		_a += da;
		spx = r*cos(_a);
		spy = -r*sin(_a);
 
		hge->Gfx_RenderLine(x+fpx, y+fpy, x+spx, y+spy, col);
 
		fpx = spx;
		fpy = spy;
	}
}