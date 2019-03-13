#pragma once
#include <SDL_mixer.h>

class Music
{
public:
	// constructor
	Music(const char* _pFileName);

	// destructor
	~Music();

	// play music
	void Play(bool _loop);

	// stop music
	void Stop();

	// get sdl music
	inline Mix_Music* GetMusic() { return m_pMusic; };

	// get volume
	inline int GetVolume() { return m_volume; };

	// set volume
	inline void SetVolume(int _volume)
	{
		m_volume = _volume;
		Mix_VolumeMusic(m_volume);
	}

private:
	// volume
	int m_volume = 100;

	// sdl music
	Mix_Music* m_pMusic = nullptr;
};