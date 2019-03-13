#pragma once
#include "SDL_pixels.h"

class Color : public SDL_Color
{
public:
	// constructor
	Color();

	// constructor with rgb
	Color(Uint8 _r, Uint8 _g, Uint8 _b);

	// constructor with rgba
	Color(Uint8 _r, Uint8 _g, Uint8 _b, Uint8 _a);
};