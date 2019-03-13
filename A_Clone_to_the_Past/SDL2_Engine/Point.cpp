// Nils Jungjohann

#include "Point.h"

Point::Point()
{
	x = 0;
	y = 0;
}

Point::Point(int _xy)
{
	x = _xy;
	y = _xy;
}

Point::Point(int _x, int _y)
{
	x = _x;
	y = _y;
}

Point::~Point()
{
}