#pragma once
#include "Entity.h"

class Text;
class Scene;

class MenuPlayer : public Entity
{
public:
	// constructor
	MenuPlayer();

	// get rect
	virtual Rect* GetRect() override;

	// set rect
	virtual void SetRect(Rect* _pRect) override;

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// trigger
	bool Trigger(Player* _pPlayer) override;

	// set start game text reference
	inline void SetStartText(Text* _ptext) { m_pStartText = _ptext; };

	// set end game text reference
	inline void SetEndText(Text* _pText) { m_pEndText = _pText; };

	// set scene reference
	inline void SetScene(Scene* _pScene) { m_pScene = _pScene; };

private:
	// if start chosen
	bool m_start = true;

	// reference start game text
	Text* m_pStartText; 

	// reference end game text
	Text* m_pEndText;

	// scene reference
	Scene* m_pScene;
};