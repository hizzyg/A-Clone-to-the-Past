#pragma once
#include "Scene.h"

class MenuPlayer;
class Music;

class MenuScene : public Scene
{
public:
	// constructor
	MenuScene(Engine* _pEngine);

	// destructor
	~MenuScene();

	// update every frame
	virtual void Update(float _deltaTime) override;

	// render every frame
	virtual void Render(Renderer* _pRenderer) override;

	// load images
	virtual void Load(Renderer* _pRenderer) override;

	// unload images
	virtual void Unload() override;

	// get start text
	inline Text* GetStartText() { return m_pStartText; };

	// get end text
	inline Text* GetEndText() { return m_pEndText; };

private:
	// start game text
	Text* m_pStartText;

	// end game text
	Text* m_pEndText;

	// menu player
	MenuPlayer* m_pPlayer;

	// background music
	Music* m_pBackgroundMusic;
};