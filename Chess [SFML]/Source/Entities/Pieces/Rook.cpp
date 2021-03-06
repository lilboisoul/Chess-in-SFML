#include "Rook.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
Rook::Rook(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wR"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bR"));
	}
	if ((_boardPos != "a1" && _boardPos != "h1") && _color == Color::WHITE) Moved();
	if ((_boardPos != "a8" && _boardPos != "h8") && _color == Color::BLACK) Moved();
}

Piece* Rook::clone() const
{
	return new Rook(*this);
}

std::vector<std::pair<int, int>> Rook::GetPseudoLegalMoves(Board& board, std::string enPassantSquare)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	std::vector<std::pair<int, int>> legalMoves;
	//checks up
	for (auto i : checkForAvailableSquares(board, x, y, 0, 1))
		legalMoves.push_back(i);
	//checks to the right
	for (auto i : checkForAvailableSquares(board, x, y, 1, 0))
		legalMoves.push_back(i);
	//checks down
	for (auto i : checkForAvailableSquares(board, x, y, 0, -1))
		legalMoves.push_back(i);
	//checks to the left
	for (auto i : checkForAvailableSquares(board, x, y, -1, 0))
		legalMoves.push_back(i);
	return legalMoves;
}

std::vector<std::pair<int, int>> Rook::GetAttackedSquares(Board& board)
{
	return GetPseudoLegalMoves(board, "a1");
}
