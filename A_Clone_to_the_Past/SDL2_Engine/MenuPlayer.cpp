// Sabrina Schmitz

#include "MenuPlayer.h"

#include "Color.h"
#include "Engine.h"
#include "FarmScene.h"
#include "Input.h"
#include "Scene.h"
#include "Text.h"

MenuPlayer::MenuPlayer()
{
}

Rect* MenuPlayer::GetRect()
{
	return nullptr;
}

void MenuPlayer::SetRect(Rect * _pRect)
{
}

void MenuPlayer::Update(float _deltaTime)
{
	if (m_start)
	{
		// set end text color to white
		m_pStartText->GetColor()->r = 74;
		m_pStartText->GetColor()->g = 164;
		m_pStartText->GetColor()->b = 77;

		// set end text color to green
		m_pEndText->GetColor()->r = 255;
		m_pEndText->GetColor()->g = 255;
		m_pEndText->GetColor()->b = 255;
	}

	// if end chosen
	else
	{
		// set end text color to green
		m_pStartText->GetColor()->r = 255;
		m_pStartText->GetColor()->g = 255;
		m_pStartText->GetColor()->b = 255;

		// set end text color to white
		m_pEndText->GetColor()->r = 74;
		m_pEndText->GetColor()->g = 164;
		m_pEndText->GetColor()->b = 77;
	}

	// change selection
	if (Input::GetKeyDown(SDL_SCANCODE_W) ||
		Input::GetKeyDown(SDL_SCANCODE_S))
	{
		m_start = !m_start;
	}

	// if enter is pressed
	if (Input::GetKeyDown(SDL_SCANCODE_RETURN))
	{
		// if start chosen
		if (m_start)
		{
			// create new scene and change scene
			FarmScene* farmscene = new FarmScene(m_pScene->GetEngine());
			m_pScene->GetEngine()->ChangeScene(farmscene);
		}

		// if end chosen
		else
		{
			// quit engine
			m_pScene->GetEngine()->Quit();
		}
	}
}

void MenuPlayer::Render(Renderer * _pRenderer)
{
	m_pStartText->Load(_pRenderer);
	m_pEndText->Load(_pRenderer);
}

bool MenuPlayer::Trigger(Player * _pPlayer)
{
	return false;
}