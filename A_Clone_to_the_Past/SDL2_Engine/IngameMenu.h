// Nils Jungjohann

#pragma once
#include "Entity.h"

class Text;
class Scene;
class Font;

class IngameMenu
	: public Entity
{
public:
	// constructor
	IngameMenu(Scene* _pScene, Renderer* _pRenderer);

	// destructor
	~IngameMenu();

	// update every frame
	void Update(float _deltaTime) override;

	// render every frame
	inline void Render(Renderer* _pRenderer) override {};

	// trigger
	inline bool Trigger(Player* _pPlayer) override { return false; };

	// get rect
	inline Rect* GetRect() override { return nullptr; };

	// set rect
	inline void SetRect(Rect* _pRect) override {};

	// toggle menu
	void ToggleMenu();

private:
	// resume text
	Text* m_pResumeText;

	// current option
	int m_selection;

	// checkpoint text
	Text* m_pCheckpointText;

	// quit text
	Text* m_pQuitText;

	// current scene
	Scene* m_pScene;

	// renderer
	Renderer* m_pRenderer;

	// load texts
	void Load();

	// change option
	void Change();
};