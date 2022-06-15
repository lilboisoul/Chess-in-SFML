#include "GameScene.h"
#include <iostream>
#include "../FEN.h"
#include "../App.h"


GameScene::GameScene(App* _app, FEN _fen, GameMode _gamemode): Scene(), appPtr(_app), fen(_fen), moveManager(_app), logic(_gamemode, _fen)
{
	boardPtr = new Board(appPtr, fen.GetPieces());
	anySquareClicked = false;
}
GameScene::~GameScene()
{
	delete boardPtr;
}

App* GameScene::GetAppPtr()
{
	return this->appPtr;
}
Board* GameScene::GetBoardPtr()
{
	return boardPtr;
}
void GameScene::HandleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
	{
		appPtr->PopScene();
		return;
	}
	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left)
	{
		Square* squareHovered = boardPtr->GetCurrentlyHoveredTile(GetAppPtr()->GetWindow());
		Piece*  pieceHovered = boardPtr->GetCurrentlyHoveredPiece(GetAppPtr()->GetWindow()).get();

		if (!squareHovered->GetClicked() && pieceHovered && !anySquareClicked)
		{
			squareHovered->SetClicked(true);
			anySquareClicked = true;
			return;
		}
		if (squareHovered->GetClicked() && pieceHovered)
		{
			squareHovered->SetClicked(false);
			anySquareClicked = false;
			return;
		}
		
	}
}
void GameScene::HandleInput(float deltaTime)
{
	
}

void GameScene::Update(float deltaTime)
{

}

void GameScene::Render(sf::RenderTarget& renderer)
{
	boardPtr->Render(renderer);
}
