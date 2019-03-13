#include "Renderer.h"
#include "Rect.h"
#include "Texture.h"
#include <SDL.h>

Renderer::Renderer(SDL_Window * _pWindow)
{
	// initialize nullptr
	m_pRenderer = nullptr;

	// create renderer
	m_pRenderer = SDL_CreateRenderer(
		_pWindow, 1,
		SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
}

Renderer::~Renderer()
{
	// destroy renderer
	if(m_pRenderer != nullptr)
		SDL_DestroyRenderer(m_pRenderer);
}

void Renderer::ClearScreen()
{
	// clear screen
	SDL_RenderClear(m_pRenderer);
}

void Renderer::RenderTexture(Texture * _pTexture)
{
	RenderTexture(_pTexture, nullptr, nullptr);
}

void Renderer::RenderTexture(Texture * _pTexture, Rect * _destinationRect)
{
	RenderTexture(_pTexture, _destinationRect, nullptr);
}

void Renderer::RenderTexture(Texture * _pTexture, Rect * _destinationRect, Rect * _sourceRect)
{
	RenderTexture(_pTexture, _destinationRect, _sourceRect, 0);
}

void Renderer::RenderTexture(Texture * _pTexture, 
	Rect * _destinationRect, Rect * _sourceRect, float _angle)
{
	RenderTexture(_pTexture, _destinationRect, _sourceRect, _angle, false);
}

void Renderer::RenderTexture(Texture * _pTexture, Rect * _destinationRect, Rect * _sourceRect, float _angle, bool _inWorld)
{
	// copy of destination rect
	Rect destination = *_destinationRect;

	// if destination in world
	if (_inWorld)
	{
		destination.x -= m_CameraX - SCREEN_WIDTH / 2;
		destination.y -= m_CameraY - SCREEN_HEIGHT / 2;
	}

	// set rotation point
	SDL_Point rotationPoint;
	rotationPoint.x = _destinationRect->w / 2;
	rotationPoint.y = _destinationRect->h / 2;

	// render texture with angle
	SDL_RenderCopyEx(m_pRenderer, _pTexture->GetSDLTexture(),
		_sourceRect, &destination, _angle, &rotationPoint,
		SDL_RendererFlip::SDL_FLIP_NONE);
}

void Renderer::Present()
{
	SDL_RenderPresent(m_pRenderer);
}