#pragma once
#include "Entities/Pieces/Piece.h"
#include "Entities/Pieces/King.h"
#include "Scenes/SetupGameScene.h"
#include <vector>
class Move;
enum class GameState
{
	NORMAL,
	CHECK,
	CHECKMATE,
	STALEMATE,
	DRAW
};

class GameLogic
{
public:
	GameLogic(GameMode _gamemode, FEN fenString);
	~GameLogic() {};

	Board*		GetBoardPtr();
	GameMode	GetGameMode();
	Color		GetCurrentPlayer();
	bool		CanWhiteCastleKingside();
	bool		CanWhiteCastleQueenside();
	bool		CanBlackCastleKingside();
	bool		CanBlackCastleQueenside();
	std::string GetEnPassantMove();
	int			GetDrawMoves();
	int			GetTotalMoves();

	void SetBoardPtr(Board* _boardPtr);
	void SetCastlingVariables(FEN fen);
	void SetCurrentPlayer(std::string player);
	void SetGameState(GameState state);
	void SetWhiteKingCastleKingside(bool _val);
	void SetWhiteKingCastleQueenside(bool _val);
	void SetBlackKingCastleKingside(bool _val);
	void SetBlackKingCastleQueenside(bool _val);
	void WhiteCastled();
	void BlackCastled();
	void SetDrawMoves(unsigned int _moves);
	void SetTotalMoves(unsigned int _moves);
	void CheckGameState(Move& moveManager);
	void PawnPromotionManager(App* appPtr, Square& square);
	void Castle(int side, Move& moveManager, Square& square);
	
	std::string SetEnPassantSquare(Square& square);
	void TakeEnPassant(Square& square);

	bool							 CheckMoveLegality(Square& destination, std::vector<std::pair<int, int>> moves);
	std::vector<std::pair<int, int>> ValidateMoves(Square* currentSquare, Move& moveManager, std::vector<std::pair<int, int>> moves);
	std::string						 GetKingBoardPos(Color player);
	std::vector<std::pair<int, int>> GetSquaresPlayerAttacks(Color playerColor);
	std::vector<std::pair<int, int>> GetPlayerValidMoves(Move& moveManager, Color playerColor);
	bool						     IsPlayerKingChecked(Color player);

	std::vector<std::pair<int, int>> ValidateCastlingMoves(Square& square, std::vector<std::pair<int, int>> moves);


private:
	Board* boardPtr;
	GameMode currentGameMode;
	GameState currentGameState;
	Color currentPlayer;

	bool whiteKingChecked;
	bool blackKingChecked;

	bool canWhiteCastleKingside;
	bool canWhiteCastleQueenside;
	bool canBlackCastleKingside;
	bool canBlackCastleQueenside;
	bool whiteCastled;
	bool blackCastled;

	std::string enPassantMove;

	unsigned int drawMoves;
	unsigned int totalMoves;
};

