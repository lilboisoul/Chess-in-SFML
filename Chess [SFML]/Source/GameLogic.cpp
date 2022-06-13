#include "GameLogic.h"

GameMode GameLogic::GetGameMode()
{
	return currentGameMode;
}

Color GameLogic::GetCurrentPlayer()
{
	return this->currentPlayer;
}

bool GameLogic::GetWhiteKingCastled()
{
	return whiteKingCastled;
}

bool GameLogic::GetBlackKingCastled()
{
	return blackKingCastled;
}

std::string GameLogic::GetEnPassantMove()
{
	return enPassantMove;
}

int GameLogic::GetDrawMoves()
{
	return drawMoves;
}

int GameLogic::GetTotalMoves()
{
	return totalMoves;
}
