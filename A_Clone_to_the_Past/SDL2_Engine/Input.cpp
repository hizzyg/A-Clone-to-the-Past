#include "Input.h"

bool Input::s_keyIsDown[];
bool Input::s_keyWasDown[];

void Input::ParseEvent(SDL_Event * _pEvent)
{
	// key down
	if (_pEvent->type == SDL_KEYDOWN)
	{
		if (_pEvent->key.keysym.sym < 256)
		{
			// set pressed key to true
			s_keyIsDown[_pEvent->key.keysym.scancode] = true;
		}
	}

	// key up
	else
	{
		if (_pEvent->key.keysym.sym < 256)
		{
			// set presed key to false
			s_keyIsDown[_pEvent->key.keysym.scancode] = false;
		}
	}
}

void Input::RefreshState()
{
	// set key was down
	for (int i = 0; i < 256; i++)
		s_keyWasDown[i] = s_keyIsDown[i];
}

bool Input::GetKey(SDL_Scancode _key)
{
	return s_keyIsDown[_key];
}

bool Input::GetKeyDown(SDL_Scancode _key)
{
	return s_keyIsDown[_key] && !s_keyWasDown[_key];
}

bool Input::GetKeyUp(SDL_Scancode _key)
{
	return !s_keyIsDown[_key] && s_keyWasDown[_key];
}