#pragma once
#include <SDL.h>

class Input
{
public:
	// event sdl
	static void ParseEvent(SDL_Event* _pEvent);

	// refresh state of key pressed down
	static void RefreshState();

	// get key pressed
	static bool GetKey(SDL_Scancode _key);

	// get key pressed down this frame
	static bool GetKeyDown(SDL_Scancode _key);

	// get key pressed up this frame
	static bool GetKeyUp(SDL_Scancode _key);

private:
	// 256 keys was down last frame
	static bool s_keyWasDown[256];

	// 256 keys down this frame
	static bool s_keyIsDown[256];
};