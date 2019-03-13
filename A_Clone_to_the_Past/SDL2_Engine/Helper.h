#pragma once

#include <string>

class Point;

#define HANDLE_ERROR(CHECK)						\
if(CHECK)										\
{												\
	std::cout << SDL_GetError() << std::endl;	\
	return false;								\
}												\

// get parent directory
std::string GetParentDirectory(std::string _path, int _depth = 1);

// get complete asset path
std::string GetAssetPath(const char* _path, int _depth = 1);

// save string to file
void SaveStringToFile(const char* _pString, const char* _pFileName);

// load string from file
std::string LoadStringFromFile(const char* _pFileName);

// Random
// Hasan Sahin
int Random();

// Nils Jungjohann
static class Helper 
{
public:
	// get playerpos
	inline static Point* GetPlayerPos() { return m_pPlayerPos; };

	// set playerpos
	inline static void SetPlayerPos(Point* _pPlayerPos) { m_pPlayerPos = _pPlayerPos; };

	// player pos
	static Point* m_pPlayerPos;
};