#include "Engine.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "MenuScene.h"
#include "Helper.h"
#include "Macros.h"
#include "Renderer.h"
#include "Input.h"
#include "Time.h"

Engine::Engine()
{	
}

bool Engine::Init()
{
	// initialize sdl
	HANDLE_ERROR(SDL_Init(SDL_INIT_VIDEO));

	// initialize sdl font
	HANDLE_ERROR(TTF_Init() < 0);

	// create window
	m_pWindow = SDL_CreateWindow(
		"SDL2 Engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		SDL_WINDOW_SHOWN);

	// if window error
	HANDLE_ERROR(m_pWindow == nullptr);

	// get surface
	m_pSurface = SDL_GetWindowSurface(m_pWindow);

	// if surface error
	HANDLE_ERROR(m_pSurface == nullptr);

	// fill surface with blue color
	SDL_FillRect(
		m_pSurface,
		nullptr,
		SDL_MapRGB(m_pSurface->format,
			0x00, 0x00, 0xff));

	// update surface
	SDL_UpdateWindowSurface(m_pWindow);

	// initialize renderer
	m_pRenderer = new Renderer(m_pWindow);

	// renderer error
	HANDLE_ERROR(m_pRenderer == nullptr);

	// initialize sdl mixer
	HANDLE_ERROR(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0);

	// set running
	m_isRunning = true;

	return true;
}

bool Engine::Load()
{
	// new time
	m_pTime = new Time();

	// create new pointer and value on heap
	MenuScene* pScene = new MenuScene(this);

	// create value stack
	// MainScene scene = MainScene(this);

	// get value from pointer
	//MainScene scene2 = *_pScene;

	// get pointer from value
	//MainScene* scene3 = &scene;

	ChangeScene(pScene);

	return true;
}

void Engine::Run()
{
	while (m_isRunning)
	{
		Update();
		Render();
	}
}

void Engine::Quit()
{
	// set running false
	m_isRunning = false;

	ChangeScene(nullptr);
}

void Engine::Clean()
{
	// delete renderer
	delete m_pRenderer;

	// close audio
	Mix_CloseAudio();
}

void Engine::ChangeScene(Scene * _pNewScene)
{
	// current scene delete
	if(m_pScene)
		m_pScene->Unload();

	// save variable
	m_pScene = _pNewScene;

	// new scene load
	if(m_pScene)
		m_pScene->Load(m_pRenderer);
}

void Engine::Render()
{
	// clear screen
	m_pRenderer->ClearScreen();

	// render scene
	if(m_pScene != nullptr)
		m_pScene->Render(m_pRenderer);

	// present screen
	m_pRenderer->Present();
}

void Engine::Update()
{
	// update time
	m_pTime->Update();

	// refresh state of input
	Input::RefreshState();

	// create sdl event
	SDL_Event e;

	// while getting events
	while (SDL_PollEvent(&e))
	{
		// if quit set running false
		if (e.type == SDL_EventType::SDL_QUIT)
			m_isRunning = false;

		// parse event to input
		if (e.type == SDL_EventType::SDL_KEYDOWN ||
			e.type == SDL_EventType::SDL_KEYUP)
			Input::ParseEvent(&e);
	}

	// update scene
	m_pScene->Update(m_pTime->GetDeltaTime());
}