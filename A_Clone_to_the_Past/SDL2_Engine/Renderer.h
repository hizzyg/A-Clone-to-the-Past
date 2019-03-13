#pragma once

class Rect;
class Texture;
class SDL_Window;
class SDL_Renderer;

class Renderer
{
public:
	// constructor
	Renderer(SDL_Window* _pWindow);

	// desctrutor
	~Renderer();

	// sdl -> clear screen -> calculate image 
	// -> render image (not shown on screen)
	// -> present image

	// clear screen
	void ClearScreen();

	// render texture
	void RenderTexture(Texture* _pTexture);

	// render texture with destination rect
	void RenderTexture(Texture* _pTexture, Rect* _destinationRect);

	// render texture with destination and source rect
	void RenderTexture(Texture* _pTexture, Rect* _destinationRect,
		Rect* _sourceRect);

	// render texture with destination rect, source rect and angle
	void RenderTexture(Texture* _pTexture, Rect* _destinationRect,
		Rect* _sourceRect, float _angle);

	// render texture with destination rect, source rect, angle and is in world
	void RenderTexture(Texture* _pTexture, Rect* _destinationRect,
		Rect* _sourceRect, float _angle, bool _inWorld);

	// present image
	void Present();

	// inline function (no code in .cpp)
	// get renderer
	inline SDL_Renderer* GetRenderer() { return m_pRenderer; };

	// camera position x
	int m_CameraX;

	// camera position y
	int m_CameraY;

private:
	// sdl renderer
	SDL_Renderer* m_pRenderer;
};