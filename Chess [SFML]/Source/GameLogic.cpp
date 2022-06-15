#include "GameLogic.h"

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
