// Christian Thielsch(auch die .bmp Dateien erstellt) && Nils Jungjohann(Kollisionssystem)

#include "TownWorld.h"

#include <math.h>
#include <SDL_surface.h>
#include <string>

#include "Collider.h"
#include "Rect.h"
#include "Renderer.h"

TownWorld::TownWorld(Renderer * _pRenderer, const char * _pFile, Rect * _pRect, Collider* _pCollider)
	: TexturedEntity(_pRenderer, _pFile, _pRect, _pCollider)
{
}

TownWorld::~TownWorld()
{
	// save counter of entities
	int countR = m_pRenderEntities.size();
	int countC = m_pCollisionEntities.size();

	// delete all entities
	for (int i = 0; i < countR; i++)
		m_pRenderEntities.pop_front();

	for (int i = 0; i < countC; i++)
		m_pCollisionEntities.pop_front();
}

void TownWorld::LoadLayer1(Renderer * _pRenderer, const char* _pFileName)
{
	// create sdl surface
	SDL_Surface* pLevelData = SDL_LoadBMP(_pFileName);

	// load pixel in char*
	char* pPixels = (char*)pLevelData->pixels;

	for (int y = 0; y < GetWorldSize(); y++)
	{
		for (int x = 0; x < GetWorldSize(); x++)
		{
			// get pixel color
			unsigned char b = pPixels[0];
			unsigned char g = pPixels[1];
			unsigned char r = pPixels[2];

			// if pixel is green shades set gras
			if (r == 0 && g == 200 && b == 0)
				m_Layer1[x][y] = 0;

			else if (r == 0 && g == 100 && b == 0)
				m_Layer1[x][y] = 16;


			// if pixel are brown-ish shades set dirt
			else if (r == 200 && g == 200 && b == 0)
				m_Layer1[x][y] = 32;

			else if (r == 175 && g == 175 && b == 0)
				m_Layer1[x][y] = 48;

			else if (r == 150 && g == 150 && b == 0)
				m_Layer1[x][y] = 64;

			else if (r == 125 && g == 125 && b == 0)
				m_Layer1[x][y] = 80;

			else if (r == 100 && g == 100 && b == 0)
				m_Layer1[x][y] = 96;

			else if (r == 75 && g == 75 && b == 0)
				m_Layer1[x][y] = 112;

			else if (r == 50 && g == 50 && b == 0)
				m_Layer1[x][y] = 128;

			else if (r == 25 && g == 25 && b == 0)
				m_Layer1[x][y] = 144;


			// if pixel is gray shade set road
			else if (r == 200 && g == 200 && b == 200)
				m_Layer1[x][y] = 160;

			else if (r == 150 && g == 150 && b == 150)
				m_Layer1[x][y] = 176;

			else if (r == 100 && g == 100 && b == 100)
				m_Layer1[x][y] = 192;

			else if (r == 50 && g == 50 && b == 50)
				m_Layer1[x][y] = 208;

			else if (r == 0 && g == 0 && b == 0)
				m_Layer1[x][y] = 224;


			// if pixel is blue shade set upper and lower dirt border
			else if (r == 0 && g == 255 && b == 255)
				m_Layer1[x][y] = 240;

			else if (r == 0 && g == 200 && b == 200)
				m_Layer1[x][y] = 256;


			// if pixel is yellow shade set left and right dirt border
			else if (r == 255 && g == 255 && b == 0)
				m_Layer1[x][y] = 272;

			else if (r == 200 && g == 150 && b == 0)
				m_Layer1[x][y] = 288;


			// if pixel is pink shades set top and bottom dirt border
			else if (r == 200 && g == 0 && b == 200)
				m_Layer1[x][y] = 304;

			else if (r == 255 && g == 0 && b == 255)
				m_Layer1[x][y] = 320;

			else if (r == 255 && g == 255 && b == 255)
				m_Layer1[x][y] = 336;

			// if pixel is other color set error texture
			else
				m_Layer1[x][y] = 1360;

			// increase pointer to 3
			pPixels += 3;
		}
	}

	// create north border collisions
	TexturedEntity* north = new TexturedEntity(_pRenderer, nullptr,
		new Rect(0, -UNIT, GetWorldSize() * UNIT, UNIT), nullptr);

	north->SetCollider(new Collider(new Rect(GetWorldSize() * UNIT, UNIT),
		north->GetRect(), ECollisionType::FLOOR));

	m_pCollisionEntities.push_back(north);

	// create south border collisions
	TexturedEntity* south = new TexturedEntity(_pRenderer, nullptr,
		new Rect(0, GetWorldSize() * UNIT, GetWorldSize() * UNIT, UNIT), nullptr);

	south->SetCollider(new Collider(new Rect(GetWorldSize() * UNIT, UNIT),
		south->GetRect(), ECollisionType::FLOOR));

	m_pCollisionEntities.push_back(south);

	// create east border collisions
	TexturedEntity* east = new TexturedEntity(_pRenderer, nullptr,
		new Rect(GetWorldSize() * UNIT, 0, UNIT, GetWorldSize() * UNIT), nullptr);

	east->SetCollider(new Collider(new Rect(UNIT, GetWorldSize() * UNIT),
		east->GetRect(), ECollisionType::FLOOR));

	m_pCollisionEntities.push_back(east);

	// create west border collisions
	TexturedEntity* west = new TexturedEntity(_pRenderer, nullptr,
		new Rect(-UNIT, 0, UNIT, GetWorldSize() * UNIT), nullptr);

	west->SetCollider(new Collider(new Rect(UNIT, GetWorldSize() * UNIT),
		west->GetRect(), ECollisionType::FLOOR));

	m_pCollisionEntities.push_back(west);

	// create new textured entities
	// screen resolution / UNIT + border
	// 1 UNIT 64x64
	for (int i = 0; i < (ceil(SCREEN_WIDTH / UNIT) + 4) * (ceil(SCREEN_HEIGHT / UNIT) + 4); i++)
		m_pRenderEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(&Point::Unit()), nullptr));
}

void TownWorld::LoadLayer2(Renderer * _pRenderer, const char* _pFileName)
{
	// create sdl surface
	SDL_Surface* pLevelData = SDL_LoadBMP(_pFileName);

	// load pixel in char*
	char* pPixels = (char*)pLevelData->pixels;

	for (int y = 0; y < GetWorldSize(); y++)
	{
		for (int x = 0; x < GetWorldSize(); x++)
		{
			// get pixel color
			unsigned char b = pPixels[0];
			unsigned char g = pPixels[1];
			unsigned char r = pPixels[2];

			// if pixels are not white set trees
			if (r == 0 && g == 255 && b == 255)
				m_Layer2[x][y] = 352;

			else if (r == 0 && g == 200 && b == 200)
				m_Layer2[x][y] = 368;

			else if (r == 255 && g == 255 && b == 0)
				m_Layer2[x][y] = 384;

			else if (r == 200 && g == 150 && b == 0)
				m_Layer2[x][y] = 400;

			else if (r == 200 && g == 200 && b == 200)
				m_Layer2[x][y] = 416;

			else if (r == 150 && g == 150 && b == 150)
				m_Layer2[x][y] = 432;

			else if (r == 100 && g == 100 && b == 100)
				m_Layer2[x][y] = 448;

			else if (r == 255 && g == 0 && b == 255)
				m_Layer2[x][y] = 464;

			else if (r == 200 && g == 0 && b == 200)
				m_Layer2[x][y] = 480;

			else if (r == 200 && g == 200 && b == 0)
				m_Layer2[x][y] = 496;

			else if (r == 0 && g == 200 && b == 0)
				m_Layer2[x][y] = 512;

			else if (r == 0 && g == 100 && b == 0)
				m_Layer2[x][y] = 528;

			else if (r == 0 && g == 0 && b == 0)
				m_Layer2[x][y] = 544;

			// if color is white set tile to none
			else if (r == 255 && g == 255 && b == 255)
				m_Layer2[x][y] = -1;

			// if pixel is other color set error texture
			else
				m_Layer2[x][y] = 1360;

			// increase pointer to 3
			pPixels += 3;

			// set collision
			if (m_Layer2[x][y] > 0 && m_Layer2[x][y] < 5000)
			{
				TexturedEntity* e = new TexturedEntity(_pRenderer, nullptr,
					new Rect(x * UNIT, y * UNIT, &Point::Unit()), nullptr);

				e->SetCollider(new Collider(new Rect(&Point::Unit()),
					e->GetRect(), ECollisionType::WALL));

				m_pCollisionEntities.push_back(e);
			}
		}
	}

	// create new textured entities
	// screen resolution / UNIT + border
	// 1 UNIT 64x64
	for (int i = 0; i < (ceil(SCREEN_WIDTH / UNIT) + 4) * (ceil(SCREEN_HEIGHT / UNIT) + 4); i++)
		m_pRenderEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(&Point::Unit()), nullptr));
}

void TownWorld::LoadLayer3(Renderer * _pRenderer, const char* _pFileName)
{
	// create sdl surface
	SDL_Surface* pLevelData = SDL_LoadBMP(_pFileName);

	// load pixel in char*
	char* pPixels = (char*)pLevelData->pixels;

	for (int y = 0; y < GetWorldSize(); y++)
	{
		for (int x = 0; x < GetWorldSize(); x++)
		{
			// get pixel color
			unsigned char b = pPixels[0];
			unsigned char g = pPixels[1];
			unsigned char r = pPixels[2];


			// if pixel is black shades set chimney
			if (r == 0 && g == 0 && b == 0)
				m_Layer3[x][y] = 560;

			else if (r == 50 && g == 50 && b == 50)
				m_Layer3[x][y] = 576;

			// if pixel is gray shades set stairs
			else if (r == 100 && g == 100 && b == 100)
				m_Layer3[x][y] = 592;

			else if (r == 150 && g == 150 && b == 150)
				m_Layer3[x][y] = 608;

			// if pixel is brown shade set door
			else if (r == 100 && g == 50 && b == 25)
				m_Layer3[x][y] = 624;

			else if (r == 100 && g == 70 && b == 25)
				m_Layer3[x][y] = 640;

			else if (r == 100 && g == 90 && b == 25)
				m_Layer3[x][y] = 656;

			else if (r == 100 && g == 110 && b == 25)
				m_Layer3[x][y] = 672;

			// if pixel is blue shade set window
			else if (r == 25 && g == 50 && b == 100)
				m_Layer3[x][y] = 688;

			else if (r == 25 && g == 100 && b == 100)
				m_Layer3[x][y] = 704;

			else if (r == 25 && g == 150 && b == 100)
				m_Layer3[x][y] = 720;

			else if (r == 25 && g == 200 && b == 100)
				m_Layer3[x][y] = 736;

			// if color is red shade set roof
			else if (r == 200 && g == 25 && b == 25)
				m_Layer3[x][y] = 752;

			else if (r == 100 && g == 25 && b == 25)
				m_Layer3[x][y] = 768;

			// if color is light green shade set bottom row
			else if (r == 25 && g == 100 && b == 0)
				m_Layer3[x][y] = 784;

			else if (r == 25 && g == 150 && b == 0)
				m_Layer3[x][y] = 800;

			else if (r == 25 && g == 200 && b == 0)
				m_Layer3[x][y] = 816;

			// if color is yellow shades set middle textures
			else if (r == 200 && g == 100 && b == 0)
				m_Layer3[x][y] = 832;

			else if (r == 200 && g == 200 && b == 0)
				m_Layer3[x][y] = 848;

			// if color is purple shade set wood row
			else if (r == 200 && g == 0 && b == 200)
				m_Layer3[x][y] = 864;

			else if (r == 200 && g == 30 && b == 200)
				m_Layer3[x][y] = 880;

			else if (r == 200 && g == 60 && b == 200)
				m_Layer3[x][y] = 896;

			else if (r == 200 && g == 90 && b == 200)
				m_Layer3[x][y] = 912;

			else if (r == 200 && g == 120 && b == 200)
				m_Layer3[x][y] = 928;

			else if (r == 200 && g == 150 && b == 200)
				m_Layer3[x][y] = 944;

			// if color is light blue shade set corners

			else if (r == 150 && g == 200 && b == 200)
				m_Layer3[x][y] = 960;

			else if (r == 100 && g == 200 && b == 200)
				m_Layer3[x][y] = 976;

			else if (r == 50 && g == 200 && b == 200)
				m_Layer3[x][y] = 992;

			else if (r == 0 && g == 200 && b == 200)
				m_Layer3[x][y] = 1008;

			// if color is dark purple set inn sign
			else if (r == 100 && g == 50 && b == 200)
				m_Layer3[x][y] = 1024;

			else if (r == 100 && g == 0 && b == 200)
				m_Layer3[x][y] = 1040;

			//if color is dark green set flower pot
			else if (r == 0 && g == 200 && b == 0)
				m_Layer3[x][y] = 1056;

			else if (r == 0 && g == 180 && b == 0)
				m_Layer3[x][y] = 1072;

			else if (r == 0 && g == 160 && b == 0)
				m_Layer3[x][y] = 1088;

			else if (r == 0 && g == 140 && b == 0)
				m_Layer3[x][y] = 1104;

			else if (r == 0 && g == 120 && b == 0)
				m_Layer3[x][y] = 1120;

			else if (r == 0 && g == 90 && b == 0)
				m_Layer3[x][y] = 1136;

			// if color is orange shade set tower roof
			else if (r == 255 && g == 130 && b == 0)
				m_Layer3[x][y] = 1152;

			else if (r == 255 && g == 120 && b == 0)
				m_Layer3[x][y] = 1168;

			else if (r == 255 && g == 110 && b == 0)
				m_Layer3[x][y] = 1184;

			else if (r == 255 && g == 100 && b == 0)
				m_Layer3[x][y] = 1200;

			else if (r == 255 && g == 90 && b == 0)
				m_Layer3[x][y] = 1216;

			else if (r == 255 && g == 80 && b == 0)
				m_Layer3[x][y] = 1232;

			else if (r == 255 && g == 70 && b == 0)
				m_Layer3[x][y] = 1248;

			else if (r == 255 && g == 60 && b == 0)
				m_Layer3[x][y] = 1264;

			else if (r == 255 && g == 50 && b == 0)
				m_Layer3[x][y] = 1280;

			else if (r == 255 && g == 40 && b == 0)
				m_Layer3[x][y] = 1296;

			else if (r == 255 && g == 30 && b == 0)
				m_Layer3[x][y] = 1312;

			else if (r == 255 && g == 20 && b == 0)
				m_Layer3[x][y] = 1328;

			else if (r == 255 && g == 10 && b == 0)
				m_Layer3[x][y] = 1344;

			// if color is white set tile to none
			else if (r == 255 && g == 255 && b == 255)
				m_Layer3[x][y] = -1;

			// if pixel is other color set error texture
			else
				m_Layer1[x][y] = 1360;

			// increase pointer to 3
			pPixels += 3;

			// set collision
			if (m_Layer3[x][y] == 576 ||
				m_Layer3[x][y] > 608 && m_Layer3[x][y] < 5000)
			{
				TexturedEntity* e = new TexturedEntity(_pRenderer, nullptr,
					new Rect(x * UNIT, y * UNIT, &Point::Unit()), nullptr);

				e->SetCollider(new Collider(new Rect(&Point::Unit()),
					e->GetRect(), ECollisionType::WALL));

				m_pCollisionEntities.push_back(e);
			}
		}
	}

	// create new textured entities
	// screen resolution / UNIT + border
	// 1 UNIT 64x64
	for (int i = 0; i < (ceil(SCREEN_WIDTH / UNIT) + 4) * (ceil(SCREEN_HEIGHT / UNIT) + 4); i++)
		m_pRenderEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(&Point::Unit()), nullptr));
}

void TownWorld::RenderEntities(Renderer* _pRenderer, int _playerPosX, int _playerPosY)
{
	// player position in x, y coordinates
	int posX = (_playerPosX - SCREEN_WIDTH / 2) / UNIT - 1;
	int posY = (_playerPosY - SCREEN_HEIGHT / 2) / UNIT - 1;

	// destination and source rect
	Rect destination;
	Rect Source;
	Rect SourceLayer1;
	Rect SourceLayer2;
	Rect SourceLayer3;

	// go through all entities
	for (int y = 0; y < ceil(SCREEN_HEIGHT / UNIT) + 4; y++)
	{
		for (int x = 0; x < ceil(SCREEN_WIDTH / UNIT) + 4; x++)
		{
			// save position x, y and tile id
			int realX = posX + x;
			int realY = posY + y;
			int tileLayer1 = 0;
			int tileLayer2 = 0;
			int tileLayer3 = 0;

			// get entity at index
			std::list<TexturedEntity*>::iterator entity = std::next(
				m_pRenderEntities.begin(), y * ceil(SCREEN_WIDTH / UNIT) + 3 + x);

			// set tile
			tileLayer1 = m_Layer1[realX][realY];
			tileLayer2 = m_Layer2[realX][realY];
			tileLayer3 = m_Layer3[realX][realY];

			// set destination rect
			destination.x = realX * UNIT;
			destination.y = (posY + y) * UNIT;
			destination.h = UNIT;
			destination.w = UNIT;

			// set rect of entity
			(*entity)->SetRect(&destination);

			// set source rect
			Source.x = 0;
			Source.y = 0;
			Source.h = 16;
			Source.w = 16;

			SourceLayer1 = Source;
			SourceLayer1.x = tileLayer1;

			SourceLayer2 = Source;
			SourceLayer2.x = tileLayer2;

			SourceLayer3 = Source;
			SourceLayer3.x = tileLayer3;
			// render rect
			_pRenderer->RenderTexture(m_pTexture, &destination, &SourceLayer1, 0, true);
			if (tileLayer2 != -1)
			{
				_pRenderer->RenderTexture(m_pTexture, &destination, &SourceLayer2, 0, true);
			}
			if (tileLayer3 != -1)
			{
				_pRenderer->RenderTexture(m_pTexture, &destination, &SourceLayer3, 0, true);
			}
		}
	}
}