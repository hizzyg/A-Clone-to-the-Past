// Sabrina Schmitz && Nils Jungjohann (Implementierung des Players)

#pragma once
#include "Macros.h"
#include "Renderer.h"
#include "Rect.h"
#include "TexturedEntity.h"
#include "Engine.h"
#include "Texture.h"
#include "Text.h"
#include <list>

class UI : public TexturedEntity
{
public:
	// constructor
	UI(Renderer * _pRenderer, Player* _pPlayer, Rect * _pRect, Collider* _pCollider, 
		const char* _pLifeText, const char* _pLifeFull, const char* _pLifeEmpty, 
		const char* _pEnduranceText, const char* _pEnduranceBar, const char* _pEnduranceBg, 
		const char* _pCoin, const char* _pSword, const char* _pBow);

	// destructor
	~UI();

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// life text
	Texture * m_pLifeText;

	// healthbar full textured entity
	Texture * m_pLifeFull;

	// healthbar empty textured entity
	Texture * m_pLifeEmpty;

	// endurance text
	Texture * m_pEnduranceText;

	// endurancebar full textured entity
	Texture * m_pEnduranceBar;

	// endurancebar empty textured entity
	Texture * m_pEnduranceBg;

	// coin count full textured entity
	Texture * m_pCoin;

	// coin count text
	Text * m_pCoinCount;

	// selected weapon
	// sword textured entity
	Texture * m_pSword;

	// bow textured entity
	Texture * m_pBow;

private:
	// player reference
	Player* m_pPlayer;
};