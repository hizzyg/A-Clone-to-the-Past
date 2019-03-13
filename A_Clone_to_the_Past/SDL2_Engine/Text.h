#pragma once
class Font;
class Rect;
class Color;
class Renderer;
class SDL_Surface;
class SDL_Texture;

class Text
{
public:
	// constructor
	Text(Rect* _pRect, const char* _pText, 
		Font* _pFont, Color* _pColor);

	// destructor
	~Text();

	// load text
	void Load(Renderer* _pRenderer);

	// render text
	void Render(Renderer* _pRenderer);

	// get color
	inline Color* GetColor() { return m_pColor; };

	// set color
	inline void SetColor(Color* _pColor) { m_pColor = _pColor; };

	// set font
	inline void SetFont(Font* _pFont) { m_pFont = _pFont; };

	// set text
	inline void SetText(const char* _pText) { m_pText = _pText; };

	// get rect
	inline Rect* GetRect() { return m_pRect; };

	// set rect
	inline void SetRect(Rect* _pRect) { m_pRect = _pRect; };

private:
	// text
	const char* m_pText;

	// font
	Font* m_pFont;

	// font color
	Color* m_pColor;

	// rect
	Rect* m_pRect;

	// surface sdl
	SDL_Surface* m_pSurface;

	// sdl texture
	SDL_Texture* m_pTexture;
};