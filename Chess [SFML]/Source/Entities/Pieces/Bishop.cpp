#include "Bishop.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
Bishop::Bishop(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wB"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bB"));
	}
}

Piece* Bishop::clone() const
{
	return new Bishop(*this);
}

std::vector<std::pair<int, int>> Bishop::GetPseudoLegalMoves(Board& board)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	std::vector<std::pair<int, int>> legalMoves;
	//checks up-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, 1))
		legalMoves.push_back(i);
	//checks up-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, 1))
		legalMoves.push_back(i);
	//checks down-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, -1))
		legalMoves.push_back(i);
	//checks down-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, -1))
		legalMoves.push_back(i);
	return legalMoves;
}
