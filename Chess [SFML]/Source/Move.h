#pragma once
#include "Entities/Square.h"
class App;
class Move
{
public:
	Move(App* _app);
	~Move() {};

	void MakeMove(Square& square_from, Square& square_to);

	void	SetSquareClicked(Square* square);
	Square* GetSquareClicked();
	App*	GetAppPtr();
private:
	Square* squareClicked;
	std::unique_ptr<Piece> pieceClicked;
	App* appPtr;
};

