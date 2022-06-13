#pragma once
#include "Entities/Pieces/Piece.h"
#include "Scenes/SetupGameScene.h"
class GameLogic
{
public:
	GameLogic(GameMode _gamemode, FEN fenString) {};
	~GameLogic() {};

	GameMode	GetGameMode();
	Color		GetCurrentPlayer();
	bool		GetWhiteKingCastled();
	bool		GetBlackKingCastled();
	std::string GetEnPassantMove();
	int			GetDrawMoves();
	int			GetTotalMoves();
	

private:

	GameMode currentGameMode;
	Color currentPlayer;

	bool whiteKingCastled;
	bool blackKingCastled;

	std::string enPassantMove;

	unsigned int drawMoves;
	unsigned int totalMoves;
};

