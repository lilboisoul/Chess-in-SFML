#include "Knight.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
Knight::Knight(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wN"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bN"));
	}
	if ((_boardPos != "b1" && _boardPos != "g1") && _color == Color::WHITE) Moved();
	if ((_boardPos != "b8" && _boardPos != "g8") && _color == Color::BLACK) Moved();
}

Piece* Knight::clone() const
{
	return new Knight(*this);
}

std::vector<std::pair<int, int>> Knight::GetPseudoLegalMoves(Board& board, std::string enPassantSquare)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	int one;
	GetColor() == Color::WHITE ? one = 1 : one = -1;
	std::vector<std::pair<int, int>> pseudoLegalMoves = { {x - 1, y + one * 2}, { x - 1, y - one * 2 },
		{x + 1, y + one * 2},{x + 1, y - one * 2}, 
		{x - 2, y + one}, {x - 2, y - one}, 
		{x + 2, y + one}, {x + 2, y - one} };
	std::vector<std::pair<int, int>> legalMoves;

	for (auto& [moveX, moveY] : pseudoLegalMoves) {
		if (isInBounds(moveX, moveY))
			if (isEmpty(board, moveX, moveY) || !isSameColor(board, x, y, moveX, moveY))
				legalMoves.push_back({ moveX, moveY });
	}
	return legalMoves;
}

std::vector<std::pair<int, int>> Knight::GetAttackedSquares(Board& board)
{
	return GetPseudoLegalMoves(board, "a1");
}
