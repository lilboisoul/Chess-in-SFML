#pragma once
#include "Scene.h"
class App;
class MenuScene : public Scene
{
private:
	App* appPtr;

public:

	MenuScene(App* _app);
	~MenuScene();


	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);
	
	App* GetAppPtr();
};

