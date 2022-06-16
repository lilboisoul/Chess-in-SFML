#pragma once
#include "Piece.h"
class Knight : public Piece
{
public:
	Knight(App* _app, Color _color, std::string& _boardPos, char _id);
	Piece* clone() const;
	std::vector<std::pair<int, int>> GetPseudoLegalMoves(Board& board);

};

