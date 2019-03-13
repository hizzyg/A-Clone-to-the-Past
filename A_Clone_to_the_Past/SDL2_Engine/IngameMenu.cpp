// Nils Jungjohann

#include "IngameMenu.h"
#include "Color.h"
#include "Font.h"
#include "Helper.h"
#include "Input.h"
#include "Rect.h"
#include "Scene.h"
#include "Text.h"
#include "Engine.h"

IngameMenu::IngameMenu(Scene* _pScene, Renderer* _pRenderer)
{
	m_pScene = _pScene;
	m_pRenderer = _pRenderer;

	Load();
}

IngameMenu::~IngameMenu()
{
	// delete texts when game is not paused
	if (!m_pScene->GetPaused())
	{
		delete m_pResumeText;
		delete m_pCheckpointText;
		delete m_pQuitText;
	}
}

void IngameMenu::Update(float _deltaTime)
{
	// if p is pressed toggle menu
	if (Input::GetKeyDown(SDL_SCANCODE_P))
		ToggleMenu();

	// if game is not paused return
	if (!m_pScene->GetPaused())
		return;

	// change selection
	if (Input::GetKeyDown(SDL_SCANCODE_W))
	{
		m_selection--;
		if (m_selection < 0)
			m_selection = 0;

		Change();
	}
	if (Input::GetKeyDown(SDL_SCANCODE_S))
	{
		m_selection++;
		if (m_selection > 2)
			m_selection = 2;

		Change();
	}

	// if enter is pressed
	if (Input::GetKeyDown(SDL_SCANCODE_RETURN))
	{
		if (m_selection == 0)
		{
			// toggle menu
			ToggleMenu();
		}
		else if(m_selection == 1)
		{
			LOG("TODO: Savepoint in 'IngameMenu'")
		}
		else
		{
			// quit engine
			m_pScene->GetEngine()->Quit();
		}
	}
}

void IngameMenu::ToggleMenu()
{
	// remove texts from scene text list when game is continued
	if (m_pScene->GetPaused())
	{
		m_pScene->RemoveText(m_pResumeText);
		m_pScene->RemoveText(m_pCheckpointText);
		m_pScene->RemoveText(m_pQuitText);

		m_pScene->SetPaused(false);
	}

	// add texts to scene text list when game is paused
	else
	{
		m_pScene->AddText(m_pResumeText);
		m_pScene->AddText(m_pCheckpointText);
		m_pScene->AddText(m_pQuitText);

		m_pScene->SetPaused(true);

		m_selection = 0;
		Change();
	}
}

void IngameMenu::Load()
{
	m_pResumeText = new Text(new Rect(SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 - 130, 180, 60), 
		"Resume", new Font(GetAssetPath("Texture/Font/T_Pixel.ttf", 5).c_str(), 24),
		new Color());

	m_pResumeText->Load(m_pRenderer);

	m_pCheckpointText = new Text(new Rect(SCREEN_WIDTH / 2 - 315, SCREEN_HEIGHT / 2 - 30, 630, 60),
		"Restart at Checkpoint", new Font(GetAssetPath("Texture/Font/T_Pixel.ttf", 5).c_str(), 24),
		new Color());

	m_pCheckpointText->Load(m_pRenderer);

	m_pQuitText = new Text(new Rect(SCREEN_WIDTH / 2 - 60, SCREEN_HEIGHT / 2 + 70, 120, 60),
		"Quit", new Font(GetAssetPath("Texture/Font/T_Pixel.ttf", 5).c_str(), 24),
		new Color());

	m_pQuitText->Load(m_pRenderer);
}

void IngameMenu::Change()
{
	// change the color on all texts, when the selection changes
	if (m_selection == 0)
	{
		m_pResumeText->GetColor()->r = 74;
		m_pResumeText->GetColor()->g = 164;
		m_pResumeText->GetColor()->b = 77;

		m_pCheckpointText->SetColor(new Color(255, 255, 255));
		m_pQuitText->SetColor(new Color(255, 255, 255));
	}
	else if (m_selection == 1)
	{
		m_pResumeText->SetColor(new Color(255, 255, 255));

		m_pCheckpointText->GetColor()->r = 74;
		m_pCheckpointText->GetColor()->g = 164;
		m_pCheckpointText->GetColor()->b = 77;

		m_pQuitText->SetColor(new Color(255, 255, 255));
	}
	else
	{
		m_pResumeText->SetColor(new Color(255, 255, 255));
		m_pCheckpointText->SetColor(new Color(255, 255, 255));

		m_pQuitText->GetColor()->r = 74;
		m_pQuitText->GetColor()->g = 164;
		m_pQuitText->GetColor()->b = 77;
	}

	// load all text
	m_pResumeText->Load(m_pRenderer);
	m_pCheckpointText->Load(m_pRenderer);
	m_pQuitText->Load(m_pRenderer);
}