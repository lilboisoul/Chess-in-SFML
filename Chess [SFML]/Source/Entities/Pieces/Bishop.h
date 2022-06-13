#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(App* _app, Color _color, std::string& _boardPos, char _id);
};

