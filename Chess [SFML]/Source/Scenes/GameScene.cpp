#include "GameScene.h"
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../FEN.h"
#include "../App.h"

bool MouseOnChessboard(sf::RenderWindow& window, sf::RectangleShape& board)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return board.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
}

GameScene::GameScene(App* _app, FEN _fen, GameMode _gamemode): Scene(), appPtr(_app), fen(_fen), moveManager(_app), logic(_gamemode, _fen)
{
	boardPtr = new Board(appPtr, fen.GetPieces());
	anySquareClicked = nullptr;
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
void GameScene::SelectPiece(Square* squareHovered, Piece* pieceHovered)
{
	if(!squareHovered || !pieceHovered)
		return;
	 
	squareHovered->SetClicked(true);
	moveManager.SetSquareClicked(squareHovered);
		//m_Board.HighlightTiles(m_Moves);
	
	
}

void GameScene::DropPiece(Square* squareHovered, Piece* pieceHovered)
{
	if (squareHovered) {

		moveManager.GetSquareClicked()->GetPiecePtr()->Moved();
		moveManager.MakeMove(*moveManager.GetSquareClicked(), *squareHovered);
		AfterMove();
		return;
	}
	
}

void GameScene::AfterMove()
{
	moveManager.GetSquareClicked()->SetClicked(false);
	moveManager.SetSquareClicked(nullptr);

	if (logic.GetCurrentPlayer() == Color::BLACK) {
		logic.SetCurrentPlayer("w");
		logic.SetTotalMoves(logic.GetTotalMoves() + 1);
	}
	else
	{
		logic.SetCurrentPlayer("b");
	}
}

void GameScene::HandleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
	{
		appPtr->PopScene();
		return;
	}
	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left && MouseOnChessboard(appPtr->GetWindow(), boardPtr->boardGameObject))
	{
		Square* squareHovered = boardPtr->GetCurrentlyHoveredTile(GetAppPtr()->GetWindow());
		Piece*  pieceHovered = boardPtr->GetCurrentlyHoveredPiece(GetAppPtr()->GetWindow()).get();
		
		if (anySquareClicked == nullptr && pieceHovered)
			if(pieceHovered->GetColor() == logic.GetCurrentPlayer())
		{
			std::cout << "anysquare == nullptr\n";
			anySquareClicked = squareHovered;
			SelectPiece(squareHovered, pieceHovered);
			return;
		}
		if (anySquareClicked != nullptr && (squareHovered == anySquareClicked))
		{
			std::cout << "same square\n";
			squareHovered->SetClicked(false);
			anySquareClicked = nullptr;
			return;
		}
		if (anySquareClicked != nullptr && squareHovered->GetBoardPos() != anySquareClicked->GetBoardPos())
		{
			std::cout << "move\n";
			DropPiece(squareHovered, pieceHovered);
			anySquareClicked->SetClicked(false);
			anySquareClicked = nullptr;
			return;
		}
		//anySquareClicked == nullptr;
		
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
