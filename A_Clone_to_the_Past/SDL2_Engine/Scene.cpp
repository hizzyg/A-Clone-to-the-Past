#include "Scene.h"

Scene::Scene(Engine * _pEngine)
{
	m_pEngine = _pEngine;
}

Scene::~Scene()
{
}

void Scene::Unload()
{
	delete this;
}