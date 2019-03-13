#include <SDL_image.h>
#include "Texture.h"
#include "Renderer.h"

Texture::Texture(const char * _pFileName, Renderer * _pRenderer)
{
	// set texture to nullptr
	m_pTexture = nullptr;

	// load texture if renderer
	if(_pRenderer && _pFileName)
		m_pTexture = IMG_LoadTexture(_pRenderer->GetRenderer(), 
			_pFileName);
}

Texture::~Texture()
{
	// destroy texture
	if (m_pTexture != nullptr)
		SDL_DestroyTexture(m_pTexture);
}