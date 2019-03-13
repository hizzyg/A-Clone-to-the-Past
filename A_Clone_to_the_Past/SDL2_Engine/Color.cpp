#include "Color.h"

Color::Color()
{
	Color(255, 255, 255);
}

Color::Color(Uint8 _r, Uint8 _g, Uint8 _b)
{
	Color(_r, _g, _b, 255);
}

Color::Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a)
{
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}