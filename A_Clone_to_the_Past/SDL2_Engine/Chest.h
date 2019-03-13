// Nils Jungjohann

#pragma once
#include "InteractiveEntity.h"

class Chest :
	public InteractiveEntity
{
public:
	// constructor
	Chest(Renderer* _pRenderer, const char* _pFileName,
		Rect* _pRect, Collider* _pCollider, Scene* _pScene);

	// render every frame
	void Render(Renderer* _pRenderer) override;

	// interact
	void Interact() override;

	// Drop
	void Drop(int _amount);

	// Health potion (Chest Drop)
	void HealthPotion();

	// Stamina potion (Chest Drop)
	void StaminaPotion();

	/// TO:DO GOLD MUSS NOCH GEMACHT WERDEN
	/// DIES IST NUR EIN PLACEHOLDER
	// Gold (Chest Drop)
	void Gold();

	// get tooltip displayed
	static bool GetTooltipDisplayed() { return m_isDisplayed; };

	// set tooltip displayed
	static void SetTooltipDisplayed(bool _isDisplayed) { m_isDisplayed = _isDisplayed; };

	// is tooltip already displayed for chests
	static bool m_isDisplayed;

private:

	// check if chest is opened
	bool m_isOpened = false;
};