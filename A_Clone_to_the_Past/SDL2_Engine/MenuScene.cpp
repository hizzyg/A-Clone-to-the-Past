#include "MenuScene.h"
#include "Text.h"
#include "Font.h"
#include "Color.h"
#include "Rect.h"
#include "Helper.h"
#include "TexturedEntity.h"
#include "MenuPlayer.h"
#include "Music.h"

MenuScene::MenuScene(Engine * _pEngine)
	: Scene(_pEngine)
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::Update(float _deltaTime)
{
	// update entities
	for each (TexturedEntity* entity in m_pMoveEntities)
		entity->Update(_deltaTime);

	// update player
	m_pPlayer->Update(_deltaTime);
}

void MenuScene::Render(Renderer * _pRenderer)
{
	// render texts
	for each (Text* text in m_pTexts)
		text->Render(_pRenderer);

	// render enities
	for each (TexturedEntity* entity in m_pMoveEntities)
		entity->Render(_pRenderer);

	// render player
	m_pPlayer->Render(_pRenderer);
}

void MenuScene::Load(Renderer * _pRenderer)
{
	// create start text (revised)
	m_pStartText = new Text(new Rect(600, 300, 80, 50), "Start",
		new Font(GetAssetPath("Texture/Font/T_Pixel.ttf", 5).c_str(), 24),
		new Color());

	// load text
	m_pStartText->Load(_pRenderer);

	// add to list
	m_pTexts.push_back(m_pStartText);

	// create quit text (revised)
	m_pEndText = new Text(new Rect(600, 400, 80, 50), "Quit",
		new Font(GetAssetPath("Texture/Font/T_Pixel.ttf", 5).c_str(), 24),
		new Color());

	// load text
	m_pEndText->Load(_pRenderer);

	// add to list
	m_pTexts.push_back(m_pEndText);

	// create player
	m_pPlayer = new MenuPlayer();

	// set text references
	m_pPlayer->SetStartText(m_pStartText);
	m_pPlayer->SetEndText(m_pEndText);

	// set scene reference
	m_pPlayer->SetScene(this);

	// create music
	m_pBackgroundMusic = new Music(F_MUSIC_FARM);

	// play music
	m_pBackgroundMusic->Play(true);
}

void MenuScene::Unload()
{
	// delete all entities to remove
	while (m_pEntitiesToRemove.size() > 0)
	{
		// get first entity
		Entity* entity = m_pEntitiesToRemove.front();

		// remove entity from entites to remove
		m_pEntitiesToRemove.remove(entity);

		// remove entity from move entites
		m_pMoveEntities.remove((TexturedEntity*)entity);

		// delete entity
		delete entity;
	}

	while (m_pTexts.size() > 0)
	{
		// get first text
		Text* text = m_pTexts.front();

		// remove text from text list
		m_pTexts.remove(text);

		// delete text
		delete text;
	}

	while (m_pMoveEntities.size() > 0)
	{
		// get first entity
		TexturedEntity* entity = m_pMoveEntities.front();

		// remove entity from entity list
		m_pMoveEntities.remove(entity);

		// delete entity
		delete entity;
	}

	// delete background music
	delete m_pBackgroundMusic;

	// delete player
	delete m_pPlayer;

	// unload parent
	Scene::Unload();
}