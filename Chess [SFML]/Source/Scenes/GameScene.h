#pragma once
#include "Scene.h"
class App;
class GameScene : public Scene
{
private:
	App* appPtr;

public:

	GameScene(App* _app);
	~GameScene();

	App* GetAppPtr();
	
	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);
};

