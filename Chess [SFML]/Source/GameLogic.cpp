#include "GameLogic.h"
#include "Move.h"
#include <iostream>
GameLogic::GameLogic(GameMode _gamemode, FEN fenString) : currentGameMode(_gamemode)
{
	SetCurrentPlayer(fenString.GetCurrentPlayer());
	SetDrawMoves(std::stoi(fenString.GetDrawMoves()));
	SetTotalMoves(std::stoi(fenString.GetTotalMoves()));
}

GameMode GameLogic::GetGameMode()
{
	return currentGameMode;
}

Color GameLogic::GetCurrentPlayer()
{
	return this->currentPlayer;
}

//bool GameLogic::GetWhiteKingCastled()
//{
//	return whiteKingCastled;
//}
//
//bool GameLogic::GetBlackKingCastled()
//{
//	return blackKingCastled;
//}
//
//std::string GameLogic::GetEnPassantMove()
//{
//	return enPassantMove;
//}

int GameLogic::GetDrawMoves()
{
	return drawMoves;
}

int GameLogic::GetTotalMoves()
{
	return totalMoves;
}

void GameLogic::SetCurrentPlayer(std::string player)
{
	if (player == "w")
	{
		this->currentPlayer = Color::WHITE;
	}
	else
	{
		this->currentPlayer = Color::BLACK;
	}
}

void GameLogic::SetDrawMoves(unsigned int _moves)
{
	this->drawMoves = _moves;
}

void GameLogic::SetTotalMoves(unsigned int _moves)
{
	this->totalMoves = _moves;
}

bool GameLogic::CheckMoveLegality(Board& board, Square& destination, std::vector<std::pair<int, int>> moves)
{
	
	for (int i = 0; i < moves.size(); i++) {
		//std::cout << destination.GetBoardPos()[0] - 96 <<" " <<  destination.GetBoardPos()[1] - 48 << "\n";
		if (destination.GetBoardPos()[0] - 96 == moves[i].first 
			&& destination.GetBoardPos()[1] - 48 == moves[i].second) {
			return true;
		}
	}
	return false;
}

std::vector<std::pair<int, int>> GameLogic::ValidateMoves(Square* currentSquare, Move& moveManager, Board& board, std::vector<std::pair<int, int>> moves)
{
	Color playerColor;
	GetCurrentPlayer() == Color::WHITE ? playerColor = Color::BLACK : playerColor = Color::WHITE;
	std::vector<std::pair<int, int>> validatedMoves;
	std::unique_ptr<Piece> temp = nullptr;
	for (auto [x, y] : moves)
	{
		temp = moveManager.SimulateMove(*currentSquare, *board.arrayOfSquares[x-1][y-1]);
		if (!IsPlayerKingChecked(board, GetCurrentPlayer()))
		{
			validatedMoves.push_back({ x, y });
		}
		moveManager.MakeMove(*board.arrayOfSquares[x-1][y-1], *currentSquare);
		if (temp)
		{
			board.arrayOfSquares[x - 1][y - 1]->SetPiece(std::move(temp));
			temp = nullptr;
		}
	}	
	return validatedMoves;
}

std::string GameLogic::GetKingBoardPos(Board& board, Color player)
{
	char id;
	player == Color::WHITE ? id = 'k' : id = 'K';
	std::pair<int, int> boardPos = { 0, 0 };
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			Square* sqr = board.arrayOfSquares[i][j];
			if (sqr->GetPiecePtr() != nullptr) {
				if ((sqr->GetPiecePtr()->GetID() == id && GetCurrentPlayer() == player))
					return sqr->GetPiecePtr()->GetBoardPos();
				
			}
		}
	}
	return "a1";
}

std::vector<std::pair<int, int>> GameLogic::GetSquaresPlayerAttacks(Board& board, Color _color)
{
	std::vector<std::pair<int, int>> pieceLegalMoves;
	std::vector<std::pair<int, int>> attackedSquares;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pieceLegalMoves.resize(0);
			if (board.arrayOfSquares[i][j]->GetPiecePtr() != nullptr) {
				if (board.arrayOfSquares[i][j]->GetPiecePtr()->GetColor() == _color) {
					pieceLegalMoves = board.arrayOfSquares[i][j]->GetPiecePtr()->GetPseudoLegalMoves(board);
					for (auto i : pieceLegalMoves) attackedSquares.push_back(i);
				}

			}
		}
	}
	return attackedSquares;
}

bool GameLogic::IsPlayerKingChecked(Board& board, Color player)
{
	Color enemyPlayer;
	player == Color::WHITE ? enemyPlayer = Color::BLACK : enemyPlayer = Color::WHITE;

	std::string allyKingBoardPos= GetKingBoardPos(board, player);
	std::vector<std::pair<int, int>> allPseudoLegalMoves = GetSquaresPlayerAttacks(board, enemyPlayer);

	for (auto [x, y] : allPseudoLegalMoves)
	{
		if (x == allyKingBoardPos[0] - 96 
			&& y == allyKingBoardPos[1] - 48) {
			return true;
		}
	}
	return false;
}
