#include "Move.h"
#include "Entities/Square.h"
#include <iostream>
#include "App.h"

Move::Move(App* _app) : appPtr(_app)
{
	squareClicked = nullptr;
	pieceClicked = nullptr;
}



void Move::MakeMove(Square& square_from, Square& square_to)
{
	if (square_from.GetPiecePtr() != nullptr && square_from.GetBoardPos() != square_to.GetBoardPos())
	{
		std::cout << square_from.GetBoardPos()[0] << square_from.GetBoardPos()[1] << " " << square_to.GetBoardPos()[0] << square_to.GetBoardPos()[1] << "\n";
		square_to.SetPiece(std::move(square_from.GetPiecePtr()));
		square_from.SetPiece(nullptr);
	}
}

void Move::SetSquareClicked(Square* square)
{
	squareClicked = square;
	//pieceClicked = std::move(square->GetPiecePtr());
}

Square* Move::GetSquareClicked()
{
	return squareClicked;
}



App* Move::GetAppPtr()
{
	return appPtr;
}
