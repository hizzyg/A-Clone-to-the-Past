// Christian Thielsch(auch die .bmp Dateien erstellt) && Nils Jungjohann(Kollisionssystem)

#pragma once
#include "TexturedEntity.h"
#include <list>

class ForestWorld : public TexturedEntity
{
public:
	// constructor
	ForestWorld(Renderer* _pRenderer, const char* _pFile, Rect* _pRect, Collider* _pCollider);

	// destructor
	~ForestWorld();

	// get world entities
	inline std::list<TexturedEntity*> GetCollisionEntities()
	{
		return m_pCollisionEntities;
	};

	// load world
	void LoadLayer1(Renderer* _pRenderer, const char* _pFileName);
	void LoadLayer2(Renderer* _pRenderer, const char* _pFileName);
	void LoadLayer3(Renderer* _pRenderer, const char* _pFileName);

	// renderer entities
	void RenderEntities(Renderer* _pRenderer, int _playerPosX,
		int _playerPosY);

	// get worldsize
	inline int GetWorldSize() { return sizeof(m_Layer1) / sizeof(m_Layer1[0]); };

private:
	// world entities
	std::list<TexturedEntity*> m_pRenderEntities;

	// collisions
	std::list<TexturedEntity*> m_pCollisionEntities;

	// world 2d array
	int m_Layer1[128][128];
	int m_Layer2[128][128];
	int m_Layer3[128][128];
};