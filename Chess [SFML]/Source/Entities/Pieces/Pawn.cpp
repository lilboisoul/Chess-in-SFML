#include "Pawn.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
#include "../Board.h"
#include "../../App.h"


Pawn::Pawn(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wP"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bP"));
	}
	if (_boardPos[1] - 48 != 2 && _color == Color::WHITE) Moved();
	if (_boardPos[1] - 48 != 7 && _color == Color::BLACK) Moved();
}

Piece* Pawn::clone() const
{
	return new Pawn(*this);
}

std::vector<std::pair<int, int>> Pawn::GetPseudoLegalMoves(Board& board, std::string enPassantSquare)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	int one;
	GetColor() == Color::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> pseudoLegalMoves;
	if (HasMoved() == false)
		if (isEmpty(board, x, y + one))
			if (isEmpty(board, x, y + one * 2))
			{
				pseudoLegalMoves.push_back({ x , y + one * 2 });
				pseudoLegalMoves.push_back({ x , y + one });
			}
	if (HasMoved() == true)
		if (isEmpty(board, x, y + one))
		{
			pseudoLegalMoves.push_back({ x , y + one });
		}
	if (isInBounds(x - 1, y + one))
		if (!isEmpty(board, x - 1, y + one)) {
			if (!isSameColor(board, x, y, x - 1, y + one))
			{
				pseudoLegalMoves.push_back({ x - 1, y + one });
			}
		}
		else if (board.arrayOfSquares[x - 2][y + one - 1]->GetBoardPos() == enPassantSquare)
		{
			pseudoLegalMoves.push_back({ x - 1, y + one });
		}
	if (isInBounds(x + 1, y + one))
		if (!isEmpty(board, x + 1, y + one)) {
			if (!isSameColor(board, x, y, x + 1, y + one))
			{
				pseudoLegalMoves.push_back({ x + 1, y + one });
			}
		}
		else if (board.arrayOfSquares[x][y + one - 1]->GetBoardPos() == enPassantSquare)
		{
			pseudoLegalMoves.push_back({ x + 1, y + one });
		}
		


	return pseudoLegalMoves;
 
}

std::vector<std::pair<int, int>> Pawn::GetAttackedSquares(Board& board)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	int one;
	GetColor() == Color::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> attackedSquares;
	if (isInBounds(x - 1, y + one))
		{
			attackedSquares.push_back({ x - 1, y + one });
		}
	if (isInBounds(x + 1, y + one))
		{
			attackedSquares.push_back({ x + 1, y + one });
		}
	return attackedSquares;
}
