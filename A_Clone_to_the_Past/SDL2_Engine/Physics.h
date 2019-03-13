#pragma once
class Rect;

class Physics
{
public:
	// collision between two rects
	static bool RectRectCollision(Rect* _pRectOne, Rect* _pRectTwo);
};