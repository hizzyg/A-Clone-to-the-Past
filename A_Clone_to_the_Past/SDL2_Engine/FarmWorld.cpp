// Christian Thielsch(auch die .bmp Dateien erstellt) && Nils Jungjohann(Kollisionssystem)

#include "FarmWorld.h"

#include <math.h>
#include <SDL_surface.h>
#include <string>

#include "Collider.h"
#include "Rect.h"
#include "Renderer.h"

FarmWorld::FarmWorld(Renderer * _pRenderer, const char * _pFile, Rect * _pRect, Collider* _pCollider)
	: TexturedEntity(_pRenderer, _pFile, _pRect, _pCollider)
{
}

FarmWorld::~FarmWorld()
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

void FarmWorld::LoadLayer1(Renderer * _pRenderer, const char* _pFileName)
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

			// if pixel is red shades set dirt
			if (r == 255 && g == 0 && b == 0)
				m_Layer1[x][y] = 0;

			else if (r == 240 && g == 0 && b == 0)
				m_Layer1[x][y] = 16;

			else if (r == 230 && g == 0 && b == 0)
				m_Layer1[x][y] = 32;

			else if (r == 220 && g == 0 && b == 0)
				m_Layer1[x][y] = 48;

			else if (r == 210 && g == 0 && b == 0)
				m_Layer1[x][y] = 64;

			else if (r == 200 && g == 0 && b == 0)
				m_Layer1[x][y] = 80;

			else if (r == 190 && g == 0 && b == 0)
				m_Layer1[x][y] = 96;


			// if pixel is blue shades set water
			else if (r == 0 && g == 0 && b == 255)
				m_Layer1[x][y] = 240;

			else if (r == 0 && g == 0 && b == 240)
				m_Layer1[x][y] = 256;

			else if (r == 0 && g == 0 && b == 230)
				m_Layer1[x][y] = 272;

			else if (r == 0 && g == 0 && b == 220)
				m_Layer1[x][y] = 288;


			// if pixel is green shades set gras
			else if (r == 0 && g == 255 && b == 0)
				m_Layer1[x][y] = 304;

			else if (r == 0 && g == 240 && b == 0)
				m_Layer1[x][y] = 320;
			else
				m_Layer1[x][y] = 544;

			// set collision
			if (m_Layer1[x][y] > 224 && m_Layer1[x][y] < 304)
			{
				TexturedEntity* e = new TexturedEntity(_pRenderer, nullptr, 
					new Rect(x * UNIT, y * UNIT, &Point::Unit()), nullptr);

				e->SetCollider(new Collider(new Rect(&Point::Unit()),
					e->GetRect(), ECollisionType::FLOOR));

				m_pCollisionEntities.push_back(e);
			}

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

void FarmWorld::LoadLayer2(Renderer * _pRenderer, const char* _pFileName)
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

			// if pixels are not blueish set dirt border
			if (r == 255 && g == 0 && b == 0)
				m_Layer2[x][y] = 112;

			else if (r == 255 && g == 100 && b == 0)
				m_Layer2[x][y] = 128;

			else if (r == 255 && g == 200 && b == 0)
				m_Layer2[x][y] = 144;

			else if (r == 0 && g == 255 && b == 0)
				m_Layer2[x][y] = 160;

			else if (r == 0 && g == 255 && b == 100)
				m_Layer2[x][y] = 176;

			else if (r == 0 && g == 255 && b == 200)
				m_Layer2[x][y] = 192;

			else if (r == 0 && g == 0 && b == 0)
				m_Layer2[x][y] = 208;

			else if (r == 10 && g == 100 && b == 100)
				m_Layer2[x][y] = 224;

			// if colors are blue-ish set water borders
			else if (r == 0 && g == 0 && b == 255)
				m_Layer2[x][y] = 432;

			else if (r == 100 && g == 0 && b == 255)
				m_Layer2[x][y] = 336;

			else if (r == 200 && g == 0 && b == 255)
				m_Layer2[x][y] = 496;

			else if (r == 0 && g == 100 && b == 255)
				m_Layer2[x][y] = 512;

			else if (r == 0 && g == 200 && b == 255)
				m_Layer2[x][y] = 448;

			else if (r == 100 && g == 100 && b == 255)
				m_Layer2[x][y] = 464;

			else if (r == 200 && g == 200 && b == 255)
				m_Layer2[x][y] = 576;

			else if (r == 10 && g == 10 && b == 255)
				m_Layer2[x][y] = 544;

			// if color is white set tile to none
			else if (r == 255 && g == 255 && b == 255)
				m_Layer2[x][y] = -1;

			// increase pointer to 3
			pPixels += 3;

			// set collision
			if (m_Layer2[x][y] > 720 && m_Layer2[x][y] < 992)
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

void FarmWorld::LoadLayer3(Renderer * _pRenderer, const char* _pFileName)
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

			//23

			// if pixel is red shades set top Tree row
			if (r == 255 && g == 0 && b == 0)
				m_Layer3[x][y] = 592;

			if (r == 240 && g == 0 && b == 0)
				m_Layer3[x][y] = 608;

			if (r == 230 && g == 0 && b == 0)
				m_Layer3[x][y] = 624;

			if (r == 220 && g == 0 && b == 0)
				m_Layer3[x][y] = 640;

			if (r == 210 && g == 0 && b == 0)
				m_Layer3[x][y] = 656;

			// if pixel is blue shades set bottom Tree row
			if (r == 0 && g == 0 && b == 255)
				m_Layer3[x][y] = 672;

			if (r == 0 && g == 0 && b == 240)
				m_Layer3[x][y] = 688;

			if (r == 0 && g == 0 && b == 230)
				m_Layer3[x][y] = 704;

			if (r == 0 && g == 0 && b == 220)
				m_Layer3[x][y] = 720;

			if (r == 0 && g == 0 && b == 210)
				m_Layer3[x][y] = 736;

			// if pixel is yellow shades set left Tree row
			if (r == 200 && g == 255 && b == 0)
				m_Layer3[x][y] = 752;

			if (r == 200 && g == 240 && b == 0)
				m_Layer3[x][y] = 768;

			if (r == 200 && g == 230 && b == 0)
				m_Layer3[x][y] = 784;

			// if pixel is lime shades set left Tree row
			if (r == 100 && g == 255 && b == 0)
				m_Layer3[x][y] = 800;

			if (r == 100 && g == 240 && b == 0)
				m_Layer3[x][y] = 816;

			if (r == 100 && g == 230 && b == 0)
				m_Layer3[x][y] = 832;

			// if pixel is green shades set inner corner Tree row
			if (r == 0 && g == 255 && b == 0)
				m_Layer3[x][y] = 848;

			if (r == 0 && g == 240 && b == 0)
				m_Layer3[x][y] = 864;

			if (r == 0 && g == 230 && b == 0)
				m_Layer3[x][y] = 880;

			if (r == 0 && g == 220 && b == 0)
				m_Layer3[x][y] = 896;

			// if pixel is purple shades set middle Tree row
			if (r == 200 && g == 0 && b == 255)
				m_Layer3[x][y] = 912;

			if (r == 200 && g == 0 && b == 240)
				m_Layer3[x][y] = 928;

			if (r == 200 && g == 0 && b == 230)
				m_Layer3[x][y] = 944;

			// if color is white set tile to none
			else if (r == 255 && g == 255 && b == 255)
				m_Layer3[x][y] = -1;

			// set collision
			if (m_Layer3[x][y] > 0 && m_Layer3[x][y] < 1536)
			{
				TexturedEntity* e = new TexturedEntity(_pRenderer, nullptr,
					new Rect(x * UNIT, y * UNIT, &Point::Unit()), nullptr);

				e->SetCollider(new Collider(new Rect(&Point::Unit()),
					e->GetRect(), ECollisionType::WALL));

				m_pCollisionEntities.push_back(e);
			}

			// increase pointer to 3
			pPixels += 3;
		}
	}

	// create new textured entities
	// screen resolution / UNIT + border
	// 1 UNIT 64x64
	for (int i = 0; i < (ceil(SCREEN_WIDTH / UNIT) + 4) * (ceil(SCREEN_HEIGHT / UNIT) + 4); i++)
		m_pRenderEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(&Point::Unit()), nullptr));
}

void FarmWorld::LoadLayer4(Renderer * _pRenderer, const char* _pFileName)
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

			// if pixels are red, blue or green set plants
			if (r == 255 && g == 0 && b == 0)
				m_Layer4[x][y] = 1408;

			else if (r == 0 && g == 0 && b == 210)
				m_Layer4[x][y] = 1424;

			else if (r == 210 && g == 0 && b == 0)
				m_Layer4[x][y] = 1440;

			else if (r == 0 && g == 0 && b == 255)
				m_Layer4[x][y] = 1456;

			else if (r == 200 && g == 255 && b == 0)
				m_Layer4[x][y] = 1472;

			else if (r == 200 && g == 240 && b == 0)
				m_Layer4[x][y] = 1488;

			else if (r == 200 && g == 230 && b == 0)
				m_Layer4[x][y] = 1504;

			else if (r == 100 && g == 255 && b == 0)
				m_Layer4[x][y] = 1520;

			// if colors purple set well
			else if (r == 200 && g == 0 && b == 230)
				m_Layer4[x][y] = 1376;

			else if (r == 200 && g == 0 && b == 240)
				m_Layer4[x][y] = 1392;

			// if color is white set tile to none
			else if (r == 255 && g == 255 && b == 255)
				m_Layer4[x][y] = -1;

			// set collision
			if (m_Layer4[x][y] > 1360 && m_Layer4[x][y] < 1536)
			{
				TexturedEntity* e = new TexturedEntity(_pRenderer, nullptr,
					new Rect(x * UNIT, y * UNIT, &Point::Unit()), nullptr);

				e->SetCollider(new Collider(new Rect(&Point::Unit()),
					e->GetRect(), ECollisionType::WALL));

				m_pCollisionEntities.push_back(e);
			}

			// increase pointer to 3
			pPixels += 3;
		}
	}

	// create new textured entities
	// screen resolution / UNIT + border
	// 1 UNIT 64x64
	for (int i = 0; i < (ceil(SCREEN_WIDTH / UNIT) + 4) * (ceil(SCREEN_HEIGHT / UNIT) + 4); i++)
		m_pRenderEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(&Point::Unit()), nullptr));
}

void FarmWorld::LoadLayer5(Renderer * _pRenderer, const char* _pFileName)
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

			// if pixels are blue set fence
			if (r == 0 && g == 0 && b == 250)
				m_Layer5[x][y] = 1024;

			else if (r == 0 && g == 0 && b == 200)
				m_Layer5[x][y] = 944;

			else if (r == 0 && g == 0 && b == 150)
				m_Layer5[x][y] = 960;

			else if (r == 0 && g == 0 && b == 100)
				m_Layer5[x][y] = 976;

			else if (r == 100 && g == 0 && b == 255)
				m_Layer5[x][y] = 992;

			else if (r == 200 && g == 0 && b == 255)
				m_Layer5[x][y] = 1008;

			// if pixels are black or gray set stairs
			else if (r == 0 && g == 0 && b == 0)
				m_Layer5[x][y] = 1344;

			else if (r == 100 && g == 100 && b == 100)
				m_Layer5[x][y] = 1360;

			// if colors green shade set Farm
			else if (r == 0 && g == 255 && b == 0)
				m_Layer5[x][y] = 1040;

			else if (r == 0 && g == 240 && b == 0)
				m_Layer5[x][y] = 1056;

			else if (r == 0 && g == 230 && b == 0)
				m_Layer5[x][y] = 1072;

			else if (r == 0 && g == 220 && b == 0)
				m_Layer5[x][y] = 1088;

			else if (r == 0 && g == 210 && b == 0)
				m_Layer5[x][y] = 1104;

			else if (r == 0 && g == 200 && b == 0)
				m_Layer5[x][y] = 1120;

			else if (r == 0 && g == 190 && b == 0)
				m_Layer5[x][y] = 1136;

			else if (r == 0 && g == 180 && b == 0)
				m_Layer5[x][y] = 1152;

			else if (r == 0 && g == 170 && b == 0)
				m_Layer5[x][y] = 1168;

			else if (r == 0 && g == 160 && b == 0)
				m_Layer5[x][y] = 1184;

			else if (r == 0 && g == 150 && b == 0)
				m_Layer5[x][y] = 1200;

			else if (r == 0 && g == 140 && b == 0)
				m_Layer5[x][y] = 1216;

			else if (r == 0 && g == 130 && b == 0)
				m_Layer5[x][y] = 1232;

			else if (r == 0 && g == 120 && b == 0)
				m_Layer5[x][y] = 1248;

			else if (r == 0 && g == 110 && b == 0)
				m_Layer5[x][y] = 1264;

			// if color is red set Farm roof
			else if (r == 200 && g == 0 && b == 0)
				m_Layer5[x][y] = 1280;

			else if (r == 150 && g == 0 && b == 0)
				m_Layer5[x][y] = 1296;

			else if (r == 100 && g == 0 && b == 0)
				m_Layer5[x][y] = 1312;

			else if (r == 50 && g == 0 && b == 0)
				m_Layer5[x][y] = 1328;

			// if color is white set tile to none
			else if (r == 255 && g == 255 && b == 255)
				m_Layer5[x][y] = -1;

			// set collision
			if (m_Layer5[x][y] > 0 && m_Layer5[x][y] < 1344)
			{
				TexturedEntity* e = new TexturedEntity(_pRenderer, nullptr,
					new Rect(x * UNIT, y * UNIT, &Point::Unit()), nullptr);

				e->SetCollider(new Collider(new Rect(&Point::Unit()),
					e->GetRect(), ECollisionType::WALL));

				m_pCollisionEntities.push_back(e);
			}

			// increase pointer to 3
			pPixels += 3;
		}
	}

	// create new textured entities
	// screen resolution / UNIT + border
	// 1 UNIT 64x64
	for (int i = 0; i < (ceil(SCREEN_WIDTH / UNIT) + 4) * (ceil(SCREEN_HEIGHT / UNIT) + 4); i++)
		m_pRenderEntities.push_back(new TexturedEntity(_pRenderer, nullptr, new Rect(&Point::Unit()), nullptr));
}

void FarmWorld::RenderEntities(Renderer* _pRenderer, int _playerPosX, int _playerPosY)
{
	// player position in x, y coordinates
	int posX = (_playerPosX - SCREEN_WIDTH / 2) / UNIT;
	int posY = (_playerPosY - SCREEN_HEIGHT / 2) / UNIT;

	// destination and source rect
	Rect destination;
	Rect Source;
	Rect SourceLayer1;
	Rect SourceLayer2;
	Rect SourceLayer3;
	Rect SourceLayer4;
	Rect SourceLayer5;

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
			int tileLayer4 = 0;
			int tileLayer5 = 0;

			// get entity at index
			std::list<TexturedEntity*>::iterator entity = std::next( m_pRenderEntities.begin(), y * ceil(SCREEN_WIDTH / UNIT) + 3 + x);

			if (realX < -1 || realX > GetWorldSize() || realY < -1 || realY > GetWorldSize())
			{
				(*entity)->SetCollider(new Collider(new Rect(UNIT, UNIT),
					(*entity)->GetRect(), ECollisionType::FLOOR));
				continue;
			}

			// set tile
			tileLayer1 = m_Layer1[realX][realY];
			tileLayer2 = m_Layer2[realX][realY];
			tileLayer3 = m_Layer3[realX][realY];
			tileLayer4 = m_Layer4[realX][realY];
			tileLayer5 = m_Layer5[realX][realY];

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

			SourceLayer4 = Source;
			SourceLayer4.x = tileLayer4;

			SourceLayer5 = Source;
			SourceLayer5.x = tileLayer5;

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
			if (tileLayer4 != -1)
			{
				_pRenderer->RenderTexture(m_pTexture, &destination, &SourceLayer4, 0, true);
			}
			if (tileLayer5 != -1)
			{
				_pRenderer->RenderTexture(m_pTexture, &destination, &SourceLayer5, 0, true);
			}
		}
	}
}