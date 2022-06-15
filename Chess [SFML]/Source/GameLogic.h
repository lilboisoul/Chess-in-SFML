#pragma once
#include "Entities/Pieces/Piece.h"
#include "Scenes/SetupGameScene.h"
class GameLogic
{
public:
	GameLogic(GameMode _gamemode, FEN fenString);
	~GameLogic() {};

	GameMode	GetGameMode();
	Color		GetCurrentPlayer();
	//bool		GetWhiteKingCastled();
	//bool		GetBlackKingCastled();
	//std::string GetEnPassantMove();
	int			GetDrawMoves();
	int			GetTotalMoves();
	
	void SetCurrentPlayer(std::string player);
	//void SetWhiteKingCastled(bool _val);
	//void SetBlackKingCastled(bool _val);
	void SetDrawMoves(unsigned int _moves);
	void SetTotalMoves(unsigned int _moves);
private:

	GameMode currentGameMode;
	Color currentPlayer;

	bool whiteKingCastled;
	bool blackKingCastled;

	std::string enPassantMove;

	unsigned int drawMoves;
	unsigned int totalMoves;
};

