#pragma once
#include <SDL_ttf.h>

class Font
{
public:
	// constructor
	Font(const char* _pFile, int _size = 12);

	// destructor
	~Font();

	// get font
	inline TTF_Font* GetFont() { return m_pFont; };

	// get size of font
	inline int GetFontSize() { return m_size; };

	// set size of font
	inline void SetFontSize(int _size)
	{
		m_size = _size;
		m_pFont = TTF_OpenFont(m_pFile, _size);
	}

private:
	// font
	TTF_Font* m_pFont;

	// size of font
	int m_size;

	// file name
	const char* m_pFile;
};