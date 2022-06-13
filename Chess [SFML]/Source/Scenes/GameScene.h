#pragma once
#include "Scene.h"
#include "../FEN.h"
#include "../Entities/Board.h"
class App;
class GameScene : public Scene
{

public:
	GameScene(App* _app, FEN _fen);
	~GameScene();

	App* GetAppPtr();
	Board* GetBoardPtr();

	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);
private:
	App* appPtr;
	Board* boardPtr;
	FEN fen;
};

