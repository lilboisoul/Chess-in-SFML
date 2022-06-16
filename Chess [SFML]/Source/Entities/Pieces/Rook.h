#pragma once

#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(App* _app, Color _color, std::string& _boardPos, char _id);
	Piece* clone() const;
	std::vector<std::pair<int, int>> GetPseudoLegalMoves(Board& board);
};

