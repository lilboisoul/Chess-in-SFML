#include "GameScene.h"
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../FEN.h"
#include "../App.h"
#include "../Entities/Pieces/Pieces.h"

bool MouseOnChessboard(sf::RenderWindow& window, sf::RectangleShape& board)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return board.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
}
bool IsPawn(Square& square)
{
	if (square.GetPiecePtr()->GetID() == 'p' || square.GetPiecePtr()->GetID() == 'P')
		return true;
	return false;
}
bool IsPromotionSquare(Square& square)
{
	if (square.GetBoardPos()[1] - 48 == 8 || square.GetBoardPos()[1] - 48 == 1)
		return true;
	return false;
}
std::unique_ptr<Piece> PromotePawn(App* appPtr, Square& squareHovered, char playerChoice)
{
	Color player_color = squareHovered.GetPiecePtr()->GetColor();
	std::string boardPos = squareHovered.GetBoardPos();
	switch (playerChoice)
	{
	case 'q':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Queen>(appPtr, player_color, boardPos, 'q');
		}
		return std::make_unique<Queen>(appPtr, player_color, boardPos, 'Q');
		
	case 'n':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Knight>(appPtr, player_color, boardPos, 'n');
		}
		return std::make_unique<Knight>(appPtr, player_color, boardPos, 'N');
		
	case 'b':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Bishop>(appPtr, player_color, boardPos, 'b');
		}
		return std::make_unique<Bishop>(appPtr, player_color, boardPos, 'B');
		
	case 'r':
		if (player_color == Color::WHITE)
		{
			return std::make_unique<Rook>(appPtr, player_color, boardPos, 'r');
		}
		return std::make_unique<Rook>(appPtr, player_color, boardPos, 'R');
		
	}

}
void PawnPromotionManager(App* appPtr, Square& square)
{
	if (IsPawn(square))
	{
		if (IsPromotionSquare(square))
		{
			char playerChoice = 'q';
			square.SetPiece(PromotePawn(appPtr, square, playerChoice));
		}
	}
}
GameScene::GameScene(App* _app, FEN _fen, GameMode _gamemode): Scene(), appPtr(_app), fen(_fen), moveManager(_app), logic(_gamemode, _fen)
{
	boardPtr = new Board(appPtr, fen.GetPieces());
	background.setSize(static_cast<sf::Vector2f>(appPtr->GetWindowSize()));
	background.setTexture(ResourceManager::Get().GetTexture("backgroundGame"));
	currentlyClickedSquare = nullptr;
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
	moves.clear();
	moves = pieceHovered->GetPseudoLegalMoves(*boardPtr);
	moves = logic.ValidateMoves(squareHovered, moveManager, *boardPtr, moves);

	boardPtr->HighlightMoves(moves);
}

void GameScene::DropPiece(Square* squareHovered, Piece* pieceHovered)
{
	if (squareHovered) {
		if (logic.CheckMoveLegality(*boardPtr, *squareHovered, moves) == true)
		{
			moveManager.GetSquareClicked()->GetPiecePtr()->Moved();
			moveManager.MakeMove(*moveManager.GetSquareClicked(), *squareHovered);
			PawnPromotionManager(appPtr, *squareHovered);
			AfterMove();
			return;
		}
	}
	
}

void GameScene::AfterMove()
{
	moveManager.GetSquareClicked()->SetClicked(false);
	moveManager.SetSquareClicked(nullptr);
	boardPtr->UnhighlightMoves(moves);

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
		
		if (currentlyClickedSquare == nullptr && pieceHovered) 
		{
			if (pieceHovered->GetColor() == logic.GetCurrentPlayer())
			{
				currentlyClickedSquare = squareHovered;
				SelectPiece(squareHovered, pieceHovered);
				return;
			}
		}

		if (currentlyClickedSquare != nullptr)
		{
			if (squareHovered != currentlyClickedSquare)
			{
				DropPiece(squareHovered, pieceHovered);
			}
			currentlyClickedSquare->SetClicked(false);
			currentlyClickedSquare = nullptr;
			boardPtr->UnhighlightMoves(moves);
			return;
		}
	}
	if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Right && MouseOnChessboard(appPtr->GetWindow(), boardPtr->boardGameObject))
	{
		Square* squareHovered = boardPtr->GetCurrentlyHoveredTile(GetAppPtr()->GetWindow());
		if (!squareHovered->IsRightClicked())
		{
			squareHovered->SetRightClicked(true);
			return;
		}
		else
		{
			squareHovered->SetRightClicked(false);
			return;
		}
	}
}

void GameScene::HandleInput(float deltaTime)
{
}


void GameScene::Update(float deltaTime)
{
	logic.CheckGameState(*boardPtr, moveManager);
}

void GameScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(background);
	boardPtr->Render(renderer);
}
