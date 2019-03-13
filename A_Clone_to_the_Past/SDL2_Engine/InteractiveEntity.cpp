// Nils Jungjohann

#include "InteractiveEntity.h"

#include "Collider.h"
#include "Helper.h"
#include "Point.h"
#include "Rect.h"
#include "Renderer.h"
#include "Scene.h"
#include "TriggerEntity.h"

InteractiveEntity::InteractiveEntity(Renderer * _pRenderer, const char * _pFileName,
	Rect * _pRect, Collider* _pCollider, Scene* _pScene)
	: TexturedEntity(_pRenderer, _pFileName, _pRect, _pCollider)
{
	m_pRenderer = _pRenderer;
	m_pScene = _pScene;

	m_pCollider = new Collider(new Rect(m_pRect->w, m_pRect->h),
		m_pRect, ECollisionType::WALL);
}

InteractiveEntity::~InteractiveEntity()
{
	delete m_pTrigger;
	delete m_pTooltip;
}

void InteractiveEntity::Render(Renderer * _pRenderer)
{
	// render texture
	_pRenderer->RenderTexture(m_pTexture, m_pRect,
		new Rect(m_sourceX, 0, &Point::Unit()), m_angle, true);
}

void InteractiveEntity::ShowTooltip()
{
	if (!m_pTooltip)
	{
		Rect* rect = new Rect(m_pRect->x + 16, m_pRect->y - 48, 32, 32);

		m_pTooltip = new TexturedEntity(m_pRenderer,
			F_TOOLTIP, rect, nullptr);
	}

	m_pScene->AddMoveEntity(m_pTooltip);
}

void InteractiveEntity::HideTooltip()
{
	if (m_pTooltip)
	{
		m_pScene->RemoveMoveEntity(m_pTooltip);
	}
}