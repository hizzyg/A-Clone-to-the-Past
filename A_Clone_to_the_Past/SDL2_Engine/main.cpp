#include <SDL.h>
#include <iostream>

// main from sdl2 undefined
#undef main

using namespace std;
#include "Engine.h"

int main()
{
	// create engine
	Engine engine;

	// init sdl
	if (engine.Init() && engine.Load())
	{
		// run program
		engine.Run();
	}

	// clean engine
	engine.Clean();

	return 0;
}