#include "Rect.h"

Rect::Rect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

Rect::Rect(int _w, int _h)
{
	x = 0;
	y = 0;
	w = _w;
	h = _h;
}
Rect::Rect(Point * _b)
{
	x = 0;
	y = 0;
	w = _b->x;
	h = _b->y;
}

Rect::Rect(Rect * _pRect)
{
	x = _pRect->x;
	y = _pRect->y;
	w = _pRect->w;
	h = _pRect->h;
}

Rect::Rect(Point * _p, Point * _b)
{
	x = _p->x;
	y = _p->y;
	w = _b->x;
	h = _b->y;
}

Rect::Rect(Point * _p, int _w, int _h)
{
	x = _p->x;
	y = _p->y;
	w = _w;
	h = _h;
}

Rect::Rect(int _x, int _y, Point * _b)
{
	x = _x;
	y = _y;
	w = _b->x;
	h = _b->y;
}

Rect::Rect(int _x, int _y, int _w, int _h)
{
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}