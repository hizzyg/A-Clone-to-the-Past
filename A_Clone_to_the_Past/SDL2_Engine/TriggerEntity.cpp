// Nils Jungjohann

#include "TriggerEntity.h"

#include "Chest.h"
#include "Collider.h"
#include "Input.h"
#include "InteractiveEntity.h"
#include "Rect.h"

TriggerEntity::TriggerEntity(InteractiveEntity* _pInterEntity, Rect* _pRect, Collider* _pCollider)
	: TexturedEntity(nullptr, nullptr, _pRect, _pCollider)
{
	m_pInterEntity = _pInterEntity;

	m_pCollider = new Collider(new Rect(m_pRect->w, m_pRect->h),
		m_pRect, ECollisionType::TRIGGER);
}

void TriggerEntity::Update(float _deltaTime)
{
	if (m_lastTriggered && !m_nowTriggered)
		m_pInterEntity->HideTooltip();

	m_lastTriggered = m_nowTriggered;
	m_nowTriggered = false;
	m_pInterEntity->SetTooltipDisplayed(false);
}

bool TriggerEntity::Trigger(Player * _pPlayer)
{
	if (m_pInterEntity->GetTag() == CHEST &&
		!Chest::GetTooltipDisplayed() &&
		!m_pInterEntity->GetTooltipDisplayed())
	{
		m_pInterEntity->ShowTooltip();
		m_pInterEntity->SetTooltipDisplayed(true);
	}

	if (Input::GetKeyDown(SDL_SCANCODE_E))
		m_pInterEntity->Interact();

	m_nowTriggered = true;

	return false;
}