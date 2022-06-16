#pragma once
#include "Entities/Pieces/Piece.h"
#include "Entities/Pieces/King.h"
#include "Scenes/SetupGameScene.h"
#include <vector>
class Move;
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

	bool CheckMoveLegality(Board& board, Square& destination, std::vector<std::pair<int, int>> moves);

	std::vector<std::pair<int, int>> ValidateMoves(Square* currentSquare, Move& moveManager, Board& board, std::vector<std::pair<int, int>> moves);
	std::string GetKingBoardPos(Board& board, Color player);
	std::vector<std::pair<int, int>> GetSquaresPlayerAttacks(Board& board, Color playerColor);

	bool IsPlayerKingChecked(Board& board, Color player);
private:

	GameMode currentGameMode;
	Color currentPlayer;

	bool whiteKingCastled;
	bool blackKingCastled;

	std::string enPassantMove;

	unsigned int drawMoves;
	unsigned int totalMoves;
};

