#include "TownScene.h"

#include <fstream>

#include "Chest.h"
#include "Collider.h"
#include "Color.h"
#include "Enemy.h"
#include "FollowEntity.h"
#include "Font.h"
#include "ForestScene.h"
#include "Helper.h"
#include "IngameMenu.h"
#include "MenuScene.h"
#include "Music.h"
#include "Physics.h"
#include "Pickup.h"
#include "Player.h"
#include "Rect.h"
#include "Renderer.h"
#include "SceneChanger.h"
#include "Soulstone.h"
#include "Text.h"
#include "TexturedEntity.h"
#include "Time.h"
#include "TownWorld.h"
#include "UI.h"

TownScene::TownScene(Engine * _pEngine)
	: Scene(_pEngine)
{

}

TownScene::~TownScene()
{
}

void TownScene::Render(Renderer * _pRenderer)
{
	// set camera position before rendering anything
	_pRenderer->m_CameraX = m_pPlayer->GetRect()->x + m_pPlayer->GetRect()->w / 2;
	_pRenderer->m_CameraY = m_pPlayer->GetRect()->y + m_pPlayer->GetRect()->h / 2;

	// adjust camera position
	if (_pRenderer->m_CameraX < SCREEN_WIDTH / 2)
		_pRenderer->m_CameraX = SCREEN_WIDTH / 2;
	else if (_pRenderer->m_CameraX > m_pWorld->GetWorldSize() * UNIT - SCREEN_WIDTH / 2)
		_pRenderer->m_CameraX = m_pWorld->GetWorldSize() * UNIT - SCREEN_WIDTH / 2;

	if (_pRenderer->m_CameraY < SCREEN_HEIGHT / 2)
		_pRenderer->m_CameraY = SCREEN_HEIGHT / 2;
	else if (_pRenderer->m_CameraY > m_pWorld->GetWorldSize() * UNIT - SCREEN_HEIGHT / 2)
		_pRenderer->m_CameraY = m_pWorld->GetWorldSize() * UNIT - SCREEN_HEIGHT / 2;

	// render world entities
	m_pWorld->RenderEntities(_pRenderer, _pRenderer->m_CameraX, _pRenderer->m_CameraY);

	// render player
	m_pPlayer->Render(_pRenderer);

	// render every move entity
	for each(TexturedEntity* entity in m_pMoveEntities)
		entity->Render(_pRenderer);

	// render every text
	// important text after entities
	for each (Text* text in m_pTexts)
		text->Render(_pRenderer);

	// render ui
	m_pUI->Render(_pRenderer);
}

void TownScene::Update(float _deltaTime)
{
	m_pMenu->Update(_deltaTime);

	if (m_isPaused)
		return;

	// update every move entity
	for each(TexturedEntity* entity in m_pMoveEntities)
		entity->Update(_deltaTime);

	// update player
	m_pPlayer->Update(_deltaTime);

	// set player moveable
	m_pPlayer->SetMoveable(true);

	// check collision for all entities
	for each(TexturedEntity* entity in m_pMoveEntities)
	{
		// if entity is enemy
		if (entity->GetTag() == ENEMY)
		{
			((Enemy*)entity)->CheckCollision(m_pMoveEntities, _deltaTime);
			((Enemy*)entity)->CheckCollision(m_pWorld->GetCollisionEntities(), _deltaTime);
		}
	}

	// check collisions
	CheckCollision(_deltaTime);

	// check player collision with world and move entities
	m_pPlayer->CheckMoveable(m_pWorld->GetCollisionEntities(), _deltaTime);
	m_pPlayer->CheckMoveable(m_pMoveEntities, _deltaTime);
}

void TownScene::Load(Renderer * _pRenderer)
{
	// save renderer
	m_pRenderer = _pRenderer;

	// create all entities from textfile
	CreateEntities(_pRenderer);

	// create ingame menu
	m_pMenu = new IngameMenu(this, _pRenderer);

	// Christial Thielsch
	// create and load new world
	m_pWorld = new TownWorld(_pRenderer, GetAssetPath("Texture/World/T_Atlas_Town.png", 5).c_str(),
		new Rect(), nullptr);
	m_pWorld->LoadLayer1(_pRenderer, GetAssetPath("Texture/World/T_Town_Layer1_Bitmap.bmp", 5).c_str());
	m_pWorld->LoadLayer2(_pRenderer, GetAssetPath("Texture/World/T_Town_Layer2_Bitmap.bmp", 5).c_str());
	m_pWorld->LoadLayer3(_pRenderer, GetAssetPath("Texture/World/T_Town_Layer3_Bitmap.bmp", 5).c_str());

	// Sabrina Schmitz
	// create UI
	m_pUI = new UI(_pRenderer, m_pPlayer, new Rect(50, 50), nullptr,
		GetAssetPath("Texture/UI/T_Life_Text.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Life_full.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Life_empty.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Endurance_Text.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Endurance_Bar.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Endurance_Background.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Coin.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Sword.png", 5).c_str(),
		GetAssetPath("Texture/UI/T_Bow.png", 5).c_str());

	// create and play music
	m_pBackgroundMusic = new Music(F_MUSIC_TOWN);
	m_pBackgroundMusic->Play(true);

	// scene change trigger
	SceneChanger* forest = new SceneChanger(_pRenderer, nullptr, new Rect(1984, 320, 64, 256),
		nullptr, new ForestScene(m_pEngine), new Point(192, 832));
	
	forest->SetCollider(new Collider(new Rect(64, 256), forest->GetRect(), ECollisionType::TRIGGER));
	
	m_pMoveEntities.push_back(forest);
}

void TownScene::Unload()
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

	// delete world
	delete m_pWorld;

	// delete music
	delete m_pBackgroundMusic;

	// delete player
	delete m_pPlayer;

	// unload parent
	Scene::Unload();
}

// Nils Jungjohann
void TownScene::CreateEntities(Renderer * _pRenderer)
{
	// Create all Entities from textfile
	std::ifstream file;
	std::string text = "";

	// TODO: Proper load system
	file.open(GetAssetPath("Save/Save1/TownScene.txt", 5).c_str());
	if (file.is_open())
		text = LoadStringFromFile(GetAssetPath("Save/Save1/TownScene.txt", 5).c_str());
	else
		text = LoadStringFromFile(GetAssetPath("Save/Templates/TownScene.txt", 5).c_str());


	std::list<std::string> parts;

	std::string part;

	for (int i = 0; i < text.length(); i++)
	{
		// if i is :
		if (text[i] == ':')
		{
			// if part not emtpy add part and clear
			if (part.length() > 0)
			{
				parts.push_back(part);
				part = "";
			}
		}

		// if i is not : add char
		else
		{
			part += text[i];
		}
	}

	while (parts.size() > 0)
	{
		// if front part is Player
		if (parts.front() == PLAYER)
		{
			parts.pop_front();

			int x = 0;
			int y = 0;

			if (Helper::GetPlayerPos())
			{
				x = Helper::GetPlayerPos()->x;
				y = Helper::GetPlayerPos()->y;
				parts.pop_front();
				parts.pop_front();
			}
			else
			{
				x = std::stoi(parts.front());
				parts.pop_front();

				y = std::stoi(parts.front());
				parts.pop_front();
			}

			m_pPlayer = new Player(_pRenderer, F_PLAYER,
				new Rect(x, y, &Point::Unit()), nullptr);

			int speed = std::stoi(parts.front());
			parts.pop_front();

			// set speed
			m_pPlayer->SetSpeed(speed);

			// set current scene of player
			m_pPlayer->SetScene(this);

			// create companion
			FollowEntity* companion = new FollowEntity(_pRenderer, F_PIGSEL,
				new Rect(x, y, &Point::Unit()), nullptr, m_pPlayer);

			// set target
			companion->SetTargetActor(m_pPlayer);

			// add companion to list
			m_pMoveEntities.push_back(companion);
		}

		// if front part is Enemy
		else if (parts.front() == ENEMY)
		{
			parts.pop_front();

			int x = std::stoi(parts.front());
			parts.pop_front();

			int y = std::stoi(parts.front());
			parts.pop_front();

			// create enemy
			Enemy * enemy = new Enemy(_pRenderer, F_ENEMY,
				new Rect(x, y, &Point::Unit()), nullptr, F_HEALTHBAR);

			int speed = std::stoi(parts.front());
			parts.pop_front();

			// set speed
			enemy->SetSpeed(speed);

			// set player reference
			enemy->SetPlayer(m_pPlayer);

			// add enemy to list
			m_pMoveEntities.push_back(enemy);
		}

		// if front part is Chest
		else if (parts.front() == CHEST)
		{
			parts.pop_front();

			int x = std::stoi(parts.front());
			parts.pop_front();

			int y = std::stoi(parts.front());
			parts.pop_front();

			// create chest
			Chest* chest = new Chest(_pRenderer, F_CHEST,
				new Rect(x, y, &Point::Unit()), nullptr, this);

			// addchest to entity list
			m_pMoveEntities.push_back(chest);
			m_pMoveEntities.push_back((TexturedEntity*)chest->GetTrigger());
		}

		// if front part is FollowEntity
		else if (parts.front() == FOLLOWENTITY)
		{
			parts.pop_front();

			int x = std::stoi(parts.front());
			parts.pop_front();

			int y = std::stoi(parts.front());
			parts.pop_front();

			// create companion
			FollowEntity* companion = new FollowEntity(_pRenderer, F_PIGSEL,
				new Rect(x, y, &Point::Unit()), nullptr, m_pPlayer);

			// set target
			companion->SetTargetActor(m_pPlayer);

			// add companion to list
			m_pMoveEntities.push_back(companion);
		}

		// if nothing found delete first element
		else
			parts.pop_front();
	}
}

// Nils Jungjohann (Änderungen zum Unterricht)
void TownScene::CheckCollision(float _deltaTime)
{
	// bool if player dead
	bool playerDead = false;

	// check all move entities
	for each (TexturedEntity* entity in m_pMoveEntities)
	{
		// if bullet
		if (entity->GetCollider() &&
			entity->GetCollider()->GetColType() == ECollisionType::BULLET)
		{
			// check all move entities
			for each (TexturedEntity* moveEntity in m_pMoveEntities)
			{
				// if no collider or bullet / floor / trigger ignore entity
				if (!moveEntity->GetCollider() || 
					moveEntity->GetCollider()->GetColType() == ECollisionType::BULLET ||
					moveEntity->GetCollider()->GetColType() == ECollisionType::FLOOR ||
					moveEntity->GetCollider()->GetColType() == ECollisionType::TRIGGER)
				{
					continue;
				}

				// check collision
				Rect one = Rect(entity->GetCollider()->GetRect());
				Rect two = Rect(moveEntity->GetCollider()->GetRect());

				if (Physics::RectRectCollision(&one, &two))
				{
					m_pEntitiesToRemove.push_back(entity);

					// if hitted move entity is enemy
					if (moveEntity->GetTag() == ENEMY)
					{
						// take damage
						((Enemy*)moveEntity)->TakeDamage(25);
					}
				}
			}

			// check all world entities
			for each (TexturedEntity* moveEntity in m_pWorld->GetCollisionEntities())
			{
				// if no collider or bullet / floor / trigger ignore entity
				if (!moveEntity->GetCollider() || 
					moveEntity->GetCollider()->GetColType() == ECollisionType::BULLET ||
					moveEntity->GetCollider()->GetColType() == ECollisionType::FLOOR ||
					moveEntity->GetCollider()->GetColType() == ECollisionType::TRIGGER)
				{
					continue;
				}

				// check collision
				Rect one = Rect(entity->GetCollider()->GetRect());
				Rect two = Rect(moveEntity->GetCollider()->GetRect());

				if (Physics::RectRectCollision(&one, &two))
				{
					m_pEntitiesToRemove.push_back(entity);
				}
			}

			// if bullet hits player
			Rect one = Rect(entity->GetCollider()->GetRect());
			Rect two = Rect(m_pPlayer->GetCollider()->GetRect());

			if (Physics::RectRectCollision(&one, &two))
			{
				// add to remove list and take damage on player
				m_pEntitiesToRemove.push_back(entity);
				m_pPlayer->TakeDamage(1);
			
				// if player health under 0 set bool
				if (m_pPlayer->GetHealth() <= 0)
					playerDead = true;
			}

			// if bullet is out of screen
			if (entity->GetRect()->GetCenterPoint()->x < m_pRenderer->m_CameraX - (SCREEN_WIDTH / 2 + UNIT) ||
				entity->GetRect()->GetCenterPoint()->x > m_pRenderer->m_CameraX + (SCREEN_WIDTH / 2 + UNIT) ||
				entity->GetRect()->GetCenterPoint()->y < m_pRenderer->m_CameraY - (SCREEN_WIDTH / 2 + UNIT) ||
				entity->GetRect()->GetCenterPoint()->y > m_pRenderer->m_CameraY + (SCREEN_WIDTH / 2 + UNIT))
			{
				m_pEntitiesToRemove.push_back(entity);
			}
		}
	}

	// as long as there is a entity to remove
	// NO FOR EACH !!!
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

	// if player dead change scene
	if (playerDead)
	{
		MenuScene* menuScene = new MenuScene(m_pEngine);
		m_pEngine->ChangeScene(menuScene);
	}
}