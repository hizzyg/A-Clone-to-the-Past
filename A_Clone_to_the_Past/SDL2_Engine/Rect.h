#pragma once
#include "SDL_rect.h"
#include "Point.h"

class Rect : public SDL_Rect
{
public:
	// construtor
	Rect();

	// constructor with with and height
	Rect(int _w, int _h);
	Rect(Point* _b);

	// constructor with width, height, x and y pos
	Rect(Rect* _pRect);
	Rect(Point* _p, Point* _b);
	Rect(Point* _p, int _w, int _h);
	Rect(int _x, int _y, Point* _b);
	Rect(int _x, int _y, int _w, int _h);

	// get center point
	inline Point* GetCenterPoint() { return new Point(x + w / 2, y + h / 2); };
};