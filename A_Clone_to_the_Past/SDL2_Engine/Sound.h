#pragma once
#include <SDL_mixer.h>

class Sound
{
public:
	// constructor
	Sound(const char* _pFileName);

	// destructor
	~Sound();

	// play sound
	void Play();

	// get sdl sound
	inline Mix_Chunk* GetSound() { return m_pSound; };

	// set sdl sound
	inline void SetSound(Mix_Chunk* _pSound) { m_pSound = _pSound; };

private:
	// sdl sound
	Mix_Chunk* m_pSound = nullptr;
};