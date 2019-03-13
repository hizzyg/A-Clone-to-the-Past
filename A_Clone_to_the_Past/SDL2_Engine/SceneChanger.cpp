// Nils Jungjohann

#include "SceneChanger.h"

#include "Engine.h"
#include "Helper.h"
#include "Player.h"
#include "Point.h"
#include "Scene.h"

SceneChanger::SceneChanger(Renderer * _pRenderer, const char * _pFileName, Rect * _pRect,
	Collider * _pCollider, Scene* _pScene, Point* _pPlayerPos)
	: TexturedEntity(_pRenderer, _pFileName, _pRect, _pCollider)
{
	m_pScene = _pScene;
	m_pPlayerPos = _pPlayerPos;
}

bool SceneChanger::Trigger(Player * _pPlayer)
{
	_pPlayer->GetScene()->RemoveMoveEntity(this);
	_pPlayer->GetScene()->AddRemoveEntity(this);

	Helper::SetPlayerPos(m_pPlayerPos);

	// create new scene and change scene
	m_pScene->GetEngine()->ChangeScene(m_pScene);

	return true;
}