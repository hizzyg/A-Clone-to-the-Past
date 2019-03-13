#pragma once

// forward decleration
class SDL_Window;
class SDL_Surface;
class Renderer;
class Scene;
class Time;

class Engine
{
public:
	// constructor
	Engine();

	// initialize sdl
	bool Init();

	// loading images
	bool Load();

	// running program
	void Run();

	// quit engine
	void Quit();

	// cleaning program
	void Clean();

	// change current scene
	void ChangeScene(Scene* _pNewScene);

private:
	// if program is running
	bool m_isRunning;

	// current scene
	Scene* m_pScene;

	// sdl window
	SDL_Window* m_pWindow;

	// sdl surface
	SDL_Surface* m_pSurface;

	// renderer
	Renderer* m_pRenderer;

	// time
	Time* m_pTime;

	// render every frame
	void Render();

	// update every frame
	void Update();
};