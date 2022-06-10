#pragma once
#include "Scene.h"
#include "../FEN.h"
#include "../Entities/Board.h"
class App;
class GameScene : public Scene
{
private:
	App* appPtr;
	Board* boardPtr;
	FEN fenCode;
public:
	GameScene(App* _app);
	~GameScene();

	App* GetAppPtr();
	Board* GetBoardPtr();

	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);
};

