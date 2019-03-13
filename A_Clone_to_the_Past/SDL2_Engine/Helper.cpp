#include "Helper.h"
#include <SDL.h>
#include <fstream>
#include <time.h>

Point* Helper::m_pPlayerPos = nullptr;

std::string GetParentDirectory(std::string _path, int _depth)
{
	// get parent directory recursive
	if (_depth > 1)
	{
		_path = GetParentDirectory(_path, _depth - 1);
	}

	//position of last sub
	size_t pos = _path.find_last_of("\\/");

	//return parent
	// if() else -> if() ? :
	return (std::string::npos == pos)
		? ""
		: _path.substr(0, pos);
}

std::string GetAssetPath(const char* _path, int _depth)
{
	// get parent directory
	std::string path = GetParentDirectory(SDL_GetBasePath(), _depth);

	// append sub path
	path.append("/Build/Assets/").append(_path);

	return path;
}

void SaveStringToFile(const char * _pString, const char * _pFileName)
{
	// file to open
	std::ofstream file;
	file.open(_pFileName);

	// if file not opened
	if (!file.is_open())
		return;

	// write string into file
	file << _pString;

	// always close stream
	file.close();
}

std::string LoadStringFromFile(const char * _pFileName)
{
	// string for text
	std::string text = "";

	// string for single line
	std::string line;

	// load file
	std::ifstream file;
	file.open(_pFileName);

	// if file not opened return null
	if (!file.is_open())
		return nullptr;

	// as long as there is a line
	while (std::getline(file, line))
	{
		text.append(line);
	}

	// close file
	file.close();

	// return text
	return text;
}

// Hasan Sahin
int Random()
{
	srand(time(NULL));
	int x = rand() % 100;
	return x;
}