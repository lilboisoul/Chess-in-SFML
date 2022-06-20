#include "GameScene.h"
#include <iostream>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "../FEN.h"
#include "../App.h"
#include "../Entities/Pieces/Pieces.h"
std::string SecondsToStringTime(float secs) {
	int minutes = (int)secs / 60;
	int seconds = (int)secs % 60;

	std::string out = "";

	if (minutes == 0)
		out += "00:";
	else if (minutes < 10) {
		out += "0";
		out += (char)(minutes + 48);
		out += ":";
	}
	else
		out += std::to_string(minutes) + ':';

	if (seconds == 0)
		out += "00";
	else if (seconds < 10) {
		out += "0";
		out += (char)(seconds + 48);
	}
	else
		out += std::to_string(seconds);

	return out;
}
bool MouseOnChessboard(sf::RenderWindow& window, sf::RectangleShape& board)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	return board.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
}

GameScene::GameScene(App* _app, FEN _fen, GameMode _gamemode): Scene(), appPtr(_app), fen(_fen), moveManager(_app), logic(_gamemode, _fen), currentlyClickedSquare(nullptr), enPassantSquare(""),
endResult({ 300.0f, 100.0f }), whiteClock({ 200.0f, 100.0f }, "10:00"), blackClock({ 200.0f, 100.0f }, "10:00")
{
	boardPtr = new Board(appPtr, fen.GetPieces());
	logic.SetBoardPtr(boardPtr);

	whiteSecondsLeft = 60 * 10.0f;
	blackSecondsLeft = 60 * 10.0f;


	if (_gamemode == GameMode::THREE_CHECKS) {
		threeChecksWinCondition = true;
	}

	background.setSize(static_cast<sf::Vector2f>(appPtr->GetWindowSize()));
	background.setTexture(ResourceManager::Get().GetTexture("backgroundGame"));

	endResult.SetBgColor({ 0, 0, 0, 0 });
	endResult.SetPosition({ 500.0f, 500.0f });

	whiteClock.SetBgColor({ 0, 0, 0, 255 });
	whiteClock.SetPosition({ 950.0f, 850.0f });

	blackClock.SetBgColor({ 0, 0, 0, 255 });
	blackClock.SetPosition({ 950.0f, 150.0f });

	
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
	moves = pieceHovered->GetPseudoLegalMoves(*boardPtr, enPassantSquare);
	moves = logic.ValidateMoves(squareHovered, moveManager, moves);
	if (pieceHovered->GetID() == 'k' || pieceHovered->GetID() == 'K')
	{
		moves = logic.ValidateCastlingMoves(*squareHovered, moves);
	}

	boardPtr->HighlightMoves(moves);
}

void GameScene::DropPiece(Square* squareHovered, Piece* pieceHovered)
{
	if (squareHovered) {
		if (logic.CheckMoveLegality(*squareHovered, moves))
		{
			//temporary variables for castling and en passant
			int x_distance = std::abs(((int)moveManager.GetSquareClicked()->GetBoardPos()[0] - 96) - (int)(squareHovered->GetBoardPos()[0] - 96));
			int y_distance = std::abs(((int)moveManager.GetSquareClicked()->GetBoardPos()[1] - 48) - (int)(squareHovered->GetBoardPos()[1] - 48));
			int side = ((int)(squareHovered->GetBoardPos()[0] - 96) - ((int)moveManager.GetSquareClicked()->GetBoardPos()[0] - 96));

			if (moveManager.GetSquareClicked()->GetPiecePtr())
			{
				logic.SetDrawMoves(1);
			}
			moveManager.GetSquareClicked()->GetPiecePtr()->Moved();
			moveManager.MakeMove(*moveManager.GetSquareClicked(), *squareHovered);

			if (squareHovered->GetPiecePtr()->GetID() == 'p' || squareHovered->GetPiecePtr()->GetID() == 'P')
			{
				if (y_distance == 2) {
					enPassantSquare = logic.SetEnPassantSquare(*squareHovered);
				}
				if (x_distance != 0) {
					logic.TakeEnPassant(*squareHovered);
				}
				logic.PawnPromotionManager(appPtr, *squareHovered);
				logic.SetDrawMoves(1);
			}
			else if ((squareHovered->GetPiecePtr()->GetID() == 'k' || squareHovered->GetPiecePtr()->GetID() == 'K') && x_distance > 1)
			{	
				logic.Castle(side, moveManager, *squareHovered);
				logic.SetDrawMoves(logic.GetDrawMoves() + 1);
			}

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
	logic.CheckGameState(moveManager);
	if (whiteSecondsLeft <= 0.0f) {
		whiteSecondsLeft = 0.0f;
		endResult.SetText("Black won by\ntimeout!");

		return;
	}

	if (blackSecondsLeft <= 0.0f) {
		blackSecondsLeft = 0.0f;
		endResult.SetText("White won by\ntimeout!");

		return;
	}
	if (logic.GetCurrentPlayer() == Color::WHITE) {
		whiteSecondsLeft -= deltaTime;
		whiteClock.SetText(SecondsToStringTime(whiteSecondsLeft));

		return;
	}

	blackSecondsLeft -= deltaTime;
	blackClock.SetText(SecondsToStringTime(blackSecondsLeft));
}

void GameScene::Render(sf::RenderTarget& renderer)
{
	renderer.draw(background);
	boardPtr->Render(renderer);
	whiteClock.Render(renderer);
	blackClock.Render(renderer);
}
