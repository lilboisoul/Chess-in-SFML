#pragma once
#include "Scene.h"
#include "../FEN.h"
class App;
enum class GameMode
{
	CHESS,
	THREE_CHECKS
};
class SetupGameScene : public Scene
{
private:
	App* appPtr;
	FEN fen;

public:

	SetupGameScene(App* _app);
	~SetupGameScene();

	App* GetAppPtr();
	FEN  GetFen();
	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);
};

