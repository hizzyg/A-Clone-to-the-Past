// Sabrina Schmitz && Nils Jungjohann (Implementierung des Players)

#include "UI.h"

#include "Input.h"
#include "Player.h"
#include "Helper.h"
#include "Color.h"
#include "Font.h"
#include "Scene.h"

UI::UI(Renderer * _pRenderer, Player* _pPlayer, Rect * _pRect, Collider* _pCollider, 
	const char* _pLifeText, const char* _pLifeFull, const char* _pLifeEmpty, 
	const char* _pEnduranceText, const char* _pEnduranceBar, const char* _pEnduranceBg, 
	const char* _pCoin, const char* _pSword, const char* _pBow)
	: TexturedEntity(_pRenderer, _pLifeFull, _pRect, _pCollider)
{
	// player reference
	m_pPlayer = _pPlayer;

	m_pLifeEmpty = new Texture(_pLifeEmpty, _pRenderer);

	// create display sword textured entity
	m_pSword = new Texture(_pSword, _pRenderer);

	// create display bow textured entity
	m_pBow = new Texture(_pBow, _pRenderer);

	// create text Life
	m_pLifeText = new Texture(_pLifeText, _pRenderer);

	// create health bar textured entity
	m_pLifeFull = new Texture(_pLifeFull, _pRenderer);

	// create text endurance
	m_pEnduranceText = new Texture(_pEnduranceText, _pRenderer);

	// create stamina bar textured entity
	m_pEnduranceBar = new Texture(_pEnduranceBar, _pRenderer);

	// create stamina background textured entity
	m_pEnduranceBg = new Texture(_pEnduranceBg, _pRenderer);

	// create coin count textured entity
	m_pCoin = new Texture(_pCoin, _pRenderer);

	// create text
	m_pCoinCount = new Text(new Rect(630, 45, 32, 32), "0", new Font(F_PIXEL_FONT, 24), new Color());
	m_pCoinCount->Load(_pRenderer);
	m_pPlayer->GetScene()->AddText(m_pCoinCount);
}

UI::~UI()
{
	delete m_pLifeText;
	delete m_pLifeFull;
	delete m_pLifeEmpty;
	delete m_pEnduranceText;
	delete m_pEnduranceBar;
	delete m_pEnduranceBg;
	delete m_pCoin;
	delete m_pSword;
	delete m_pBow;
}

void UI::Render(Renderer * _pRenderer)
{
	// render ui
	Rect r = *m_pRect;

	// render text health
	r.x = 0;
	r.y = 5;
	r.w = 300;
	r.h = 32;
	_pRenderer->RenderTexture(m_pLifeText, &r, nullptr, 0, false);

	// render health
	r.y = 48;
	r.w = 32;
	r.h = 32;
	for (int i = m_pPlayer->GetMaxHealth() - 1; i >= 0; i--)
	{
		r.x = 53 + i * (r.w - 15);
		if (i < m_pPlayer->GetHealth())
			_pRenderer->RenderTexture(m_pLifeFull, &r, nullptr, 0, false);
		else
			_pRenderer->RenderTexture(m_pLifeEmpty, &r, nullptr, 0, false);
	}

	// render text endurance
	r.x = 220;
	r.y = 3;
	r.w = 430;
	r.h = 32;
	_pRenderer->RenderTexture(m_pEnduranceText, &r, nullptr, 0, false);

	// render endurance
	r.y = 45;
	r.w = 230;
	r.h = 32;
	r.x = 320;
	_pRenderer->RenderTexture(m_pEnduranceBg, &r, nullptr, 0, false);
	r.y += 8;
	r.x += 5;
	r.h = 16;
	r.w = m_pPlayer->GetStamina() / m_pPlayer->GetMaxStamina() * 220;
	_pRenderer->RenderTexture(m_pEnduranceBar, &r, nullptr, 0, false);

	// render coin
	r.x = 630;
	r.y = 5;
	r.w = 32;
	r.h = 32;
	_pRenderer->RenderTexture(m_pCoin, &r, nullptr, 0, false);

	// render coin text
	std::string coins = std::to_string(m_pPlayer->GetGold());

	// won't render anymore if rect is set
	//r.w = coins.size() * 16;
	//r.x = 646 - r.w / 2;
	//r.y = 45;
	//m_pCoinCount->SetRect(&r);

	m_pCoinCount->SetText(coins.c_str());
	m_pCoinCount->Load(_pRenderer);

	// render bow or sword
	if (m_pPlayer->HasBowInHand())
	{
		// render bow
		r.x = 750;
		r.y = 5;
		r.w = 64;
		r.h = 64;
		_pRenderer->RenderTexture(m_pBow, &r, nullptr, 0, false);
	}
	else
	{
		// render sword
		r.x = 750;
		r.y = 5;
		r.w = 64;
		r.h = 64;
		_pRenderer->RenderTexture(m_pSword, &r, nullptr, 0, false);
	}

}
