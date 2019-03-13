#include "Music.h"

Music::Music(const char * _pFileName)
{
	// load music
	m_pMusic = Mix_LoadMUS(_pFileName);
}

Music::~Music()
{
	// free music
	Mix_FreeMusic(m_pMusic);
}

void Music::Play(bool _loop)
{
	// int for loop
	// 1 = 1 time
	// -1 = endless
	int loop = 1;

	// if loop set int
	if (_loop)
		loop = -1;

	// play music
	Mix_PlayMusic(m_pMusic, loop);
}

void Music::Stop()
{
	// stop music
	Mix_HaltMusic();
}