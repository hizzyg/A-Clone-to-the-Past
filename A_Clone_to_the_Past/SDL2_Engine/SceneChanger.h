// Nils Jungjohann

#pragma once
#include "TexturedEntity.h"

class Point;
class Scene;

class SceneChanger :
	public TexturedEntity
{
public:
	// constructor
	SceneChanger(Renderer* _pRenderer, const char* _pFileName, Rect* _pRect, 
		Collider* _pCollider, Scene* _pScene, Point* _pPlayerPos);

	// trigger
	bool Trigger(Player* _pPlayer) override;

private:
	// scene reference
	Scene* m_pScene;

	// point reference
	Point* m_pPlayerPos;
};