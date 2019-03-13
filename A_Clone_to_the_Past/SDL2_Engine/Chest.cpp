// Nils Jungjohann

#include "Chest.h"
#include "Macros.h"
#include "Scene.h"
#include "TriggerEntity.h"
#include "Rect.h"
#include "Helper.h"
#include "Rect.h"
#include "Soulstone.h"
#include "Renderer.h"
#include "Health_Potion.h"
#include "Stamina_Potion.h"
#include "Collider.h"

bool Chest::m_isDisplayed = false;

Chest::Chest(Renderer * _pRenderer, const char * _pFileName,
	Rect * _pRect, Collider* _pCollider, Scene* _pScene)
	: InteractiveEntity(_pRenderer, _pFileName, _pRect, _pCollider, _pScene)
{
	Rect* rect = new Rect(m_pRect->x + 16, m_pRect->y + 64, 32, 8);

	m_pTrigger = new TriggerEntity(this, rect, nullptr);

	m_pTag = CHEST;
}

void Chest::Render(Renderer * _pRenderer)
{
	InteractiveEntity::Render(_pRenderer);
}

void Chest::Interact()
{
	if (!m_isOpened)
	{
		m_sourceX = 64;

		m_pScene->RemoveMoveEntity(m_pTooltip);

		Chest::SetTooltipDisplayed(true);

		Chest::Drop(1);

		m_isOpened = true;
	}
}

// Hasan Sahin
void Chest::Drop(int _amount)
{
	int x;
	x = Random();

	if (x <= 32)
	{
		Chest::StaminaPotion();
	}
	else if (x > 32 && x <= 66)
	{
		Chest::HealthPotion();
	}
	else
	{
		Chest::Gold();
	}
}

void Chest::HealthPotion()
{
	// create health
	Health_Potion* health = new Health_Potion(m_pRenderer, F_HEALTHPOTION,
		new Rect(m_pRect->x + 16, m_pRect->y + 32, new Point(32)), nullptr);

	// add health potion to moveEntity
	m_pScene->AddMoveEntity(health);
}

void Chest::StaminaPotion()
{
	// create stamina potion
	Stamina_Potion* stamina = new Stamina_Potion(m_pRenderer, F_STAMINAPOTION,
		new Rect(m_pRect->x + 16, m_pRect->y + 32, new Point(32)), nullptr);

	// add stamina potion to moveEntity
	m_pScene->AddMoveEntity(stamina);
}

void Chest::Gold()
{
	// create soulstone
	Soulstone* soulstone = new Soulstone(m_pRenderer, F_GOLD,
		new Rect(m_pRect->x + 16, m_pRect->y + 32, new Point(32)), nullptr);

	// add soulstone to moveEntity
	m_pScene->AddMoveEntity(soulstone);
}