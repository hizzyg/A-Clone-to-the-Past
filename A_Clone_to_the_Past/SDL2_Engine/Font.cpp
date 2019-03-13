#include "Font.h"

Font::Font(const char * _pFile, int _size)
{
	// get file name
	m_pFile = _pFile;

	// open font
	m_pFont = TTF_OpenFont(m_pFile, _size);
}

Font::~Font()
{
	TTF_CloseFont(m_pFont);
}