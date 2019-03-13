#pragma once

class SDL_Texture;
class Renderer;

class Texture
{
public:
	// constructor
	Texture(const char* _pFileName, Renderer* _pRenderer);

	// destructor
	~Texture();

	// get sdl texture
	inline SDL_Texture* GetSDLTexture() { return m_pTexture; };

	// set sdl texture
	inline void SetSDLTexture(SDL_Texture* _pTexture) { m_pTexture = _pTexture; };

private:
	// texture
	SDL_Texture* m_pTexture;
};