#include "Physics.h"
#include "Rect.h"

bool Physics::RectRectCollision(Rect * _pRectOne, Rect * _pRectTwo)
{
	// if second rect x is higher than first rect x + w
	if (_pRectTwo->x > _pRectOne->x + _pRectOne->w)
		return false;

	// if first rect x is higher than second rect x + w
	if (_pRectOne->x > _pRectTwo->x + _pRectTwo->w)
		return false;

	// if second rect y is higher than first rect y + h
	if (_pRectTwo->y > _pRectOne->y + _pRectOne->h)
		return false;

	// if first rect y is higher than second rect y + h
	if (_pRectOne->y > _pRectTwo->y + _pRectTwo->h)
		return false;

	// if collision return true
	return true;
}