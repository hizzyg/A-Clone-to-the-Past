#include "Sound.h"

Sound::Sound(const char * _pFileName)
{
	// load sound
	if(_pFileName)
		m_pSound = Mix_LoadWAV(_pFileName);
}

Sound::~Sound()
{
	// free sound
	Mix_FreeChunk(m_pSound);
}

void Sound::Play()
{
	// play sound
	// loops are not as in music
	// 0 = 1 time
	Mix_PlayChannel(-1, m_pSound, 0);
}