#pragma once
#include "Piece.h"
class Queen : public Piece
{
	Queen(App* _app, Color _color, std::string& _boardPos, char _id);
};

