#pragma once
#include "Piece.h"
class King : public Piece
{
	King(App* _app, Color _color, std::string& _boardPos, char _id);
};

