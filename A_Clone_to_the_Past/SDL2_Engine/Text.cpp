#include "Text.h"
#include "Font.h"
#include "Color.h"
#include "Renderer.h"
#include "Rect.h"
#include <SDL.h>
#include <SDL_ttf.h>

Text::Text(Rect * _pRect, const char * _pText, 
	Font * _pFont, Color * _pColor)
{
	m_pRect = _pRect;
	m_pText = _pText;
	m_pFont = _pFont;
	m_pColor = _pColor;
}

Text::~Text()
{
	delete m_pFont;
	delete m_pColor;
	delete m_pRect;

	SDL_FreeSurface(m_pSurface);

	if (m_pTexture != nullptr)
		SDL_DestroyTexture(m_pTexture);
}

void Text::Load(Renderer * _pRenderer)
{
	// free surface
	SDL_FreeSurface(m_pSurface);

	// update surface
	m_pSurface = TTF_RenderText_Solid(m_pFont->GetFont(),
		m_pText, *m_pColor);

	// sdl texture destroy
	if (m_pTexture)
		SDL_DestroyTexture(m_pTexture);

	// create texture
	m_pTexture = SDL_CreateTextureFromSurface(
		_pRenderer->GetRenderer(), m_pSurface);
}

void Text::Render(Renderer * _pRenderer)
{
	// render text
	SDL_RenderCopy(_pRenderer->GetRenderer(), m_pTexture,
		nullptr, m_pRect);
}