#include "Move.h"
#include "Entities/Square.h"

Move::Move(App* _app) : appPtr(_app)
{
	squareClicked = nullptr;
	pieceClicked = nullptr;
}

void Move::MakeMove(Square& square_from, Square& square_to)
{
	if (square_from.GetPiecePtr() != nullptr)
	{
		square_to.SetPiece(std::move(square_from.GetPiecePtr()));
		square_from.SetPiece(nullptr);
	}
}

void Move::SetSquareClicked(Square* square)
{
	squareClicked = square;
	pieceClicked = std::move(square->GetPiecePtr());
}



App* Move::GetAppPtr()
{
	return appPtr;
}
