#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(App* _app, Color _color, std::string& _boardPos, char _id);
	Piece* clone() const;
	std::vector<std::pair<int, int>> GetPseudoLegalMoves(Board& board);
	std::vector<std::pair<int, int>> GetAttackedSquares(Board& board);
};

