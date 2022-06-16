#pragma once
#include "Scene.h"
#include "../FEN.h"
#include "../Entities/Board.h"
#include "../Move.h"
#include "../GameLogic.h"
class App;
class GameScene : public Scene
{

public:
	GameScene(App* _app, FEN _fen, GameMode _gamemode);
	~GameScene();

	App* GetAppPtr();
	Board* GetBoardPtr();

	void SelectPiece(Square* squareHovered, Piece* pieceHovered);
	void DropPiece(Square* squareHovered, Piece* pieceHovered);
	void AfterMove();



	void HandleEvents(sf::Event& ev);
	void HandleInput(float deltaTime);
	void Update(float deltaTime);
	void Render(sf::RenderTarget& renderer);

private:

	App* appPtr;
	Board* boardPtr;
	FEN fen;
	Move moveManager;
	GameLogic logic;
	Square* anySquareClicked;
	std::vector<std::pair<int, int>> moves;
};

