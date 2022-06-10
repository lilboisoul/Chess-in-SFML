#pragma once
#include "Scene.h"
#include "../FEN.h"
class App;
class SetupGameScene : public Scene
{
private:
	App* appPtr;
	FEN fenCode;
public:

	SetupGameScene(App* _app);
	~SetupGameScene();

	App* GetAppPtr();

	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);
};

