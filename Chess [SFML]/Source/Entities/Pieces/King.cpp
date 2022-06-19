#include "King.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"

King::King(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wK"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bK"));
	}
	if (_boardPos != "e1" && _color == Color::WHITE) Moved();
	if (_boardPos != "e8" && _color == Color::BLACK) Moved();
}

Piece* King::clone() const
{
	return new King(*this);
}

std::vector<std::pair<int, int>> King::GetPseudoLegalMoves(Board& board, std::string enPassantSquare)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	int one;
	GetColor() == Color::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> pseudoLegalMoves{ {x + one, y + one}, {x + one, y }, {x + one, y - one}, {x, y + one},
													 {x, y - one}, {x - one, y + one}, {x - one, y}, {x - one, y - one} };
	std::vector<std::pair<int, int>> legalMoves;
	for (auto& [moveX, moveY] : pseudoLegalMoves) {
		if (isInBounds(moveX, moveY))
			if (isEmpty(board, moveX, moveY) || !isSameColor(board, x, y, moveX, moveY))
				legalMoves.push_back({ moveX, moveY });
	}

	return legalMoves;
}

std::vector<std::pair<int, int>> King::GetAttackedSquares(Board& board)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	int one;
	GetColor() == Color::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> pseudoLegalMoves{ {x + one, y + one}, {x + one, y }, {x + one, y - one}, {x, y + one},
													 {x, y - one}, {x - one, y + one}, {x - one, y}, {x - one, y - one} };
	std::vector<std::pair<int, int>> attackedSquares;
	for (auto& [moveX, moveY] : pseudoLegalMoves) {
		if (isInBounds(moveX, moveY))
			attackedSquares.push_back({ moveX, moveY });
	}
	return attackedSquares;
}
