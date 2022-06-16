#include "GameLogic.h"
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
	//std::vector<std::pair<int, int>> legalmoves = square_from.getPiecePtr()->getLegalMoves(square_from.getPiecePtr()->getPseudoLegalMoves(board, logic));

	for (int i = 0; i < moves.size(); i++) {
		//std::cout << destination.GetBoardPos()[0] - 96 <<" " <<  destination.GetBoardPos()[1] - 48 << "\n";
		if (destination.GetBoardPos()[0] - 96 == moves[i].first && destination.GetBoardPos()[1] - 48 == moves[i].second) {
			return true;
		}
	}
	return false;
}
