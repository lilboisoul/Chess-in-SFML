#pragma once
#include "Piece.h"
class King : public Piece
{
public:
	King(App* _app, Color _color, std::string& _boardPos, char _id);
	Piece* clone() const;
	std::vector<std::pair<int, int>> GetPseudoLegalMoves(Board& board, std::string enPassantSquare);
	std::vector<std::pair<int, int>> GetAttackedSquares(Board& board);

};

