// Nils Jungjohann

#pragma once
#include "TexturedEntity.h"

class TriggerEntity;
class Scene;

class InteractiveEntity :
	public TexturedEntity
{
public:
	// constructor
	InteractiveEntity(Renderer* _pRenderer, const char* _pFileName,
		Rect* _pRect, Collider* _pCollider, Scene* _pScene);

	// destructor
	~InteractiveEntity();

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// interact
	virtual void Interact() = 0;

	// show tooltip
	virtual void ShowTooltip();

	// hide tooltip
	virtual void HideTooltip();

	// get tooltip
	inline TexturedEntity* GetTooltip() { return m_pTooltip; };

	// get trigger
	TriggerEntity* GetTrigger() { return m_pTrigger; };

	// get tooltip displayed
	bool GetTooltipDisplayed() { return m_isDisplayed; }

	// set tooltip displayed
	void SetTooltipDisplayed(bool _isDisplayed) 
		{ m_isDisplayed = _isDisplayed; };

protected:
	// renderer
	Renderer* m_pRenderer;

	// scene
	Scene* m_pScene;

	// tooltip displayed
	bool m_isDisplayed = false;


	// sourcerect x
	int m_sourceX;

	// trigger
	TriggerEntity* m_pTrigger;

	// tooltip
	TexturedEntity* m_pTooltip;
};