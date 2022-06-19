#include "Queen.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
Queen::Queen(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wQ"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bQ"));
	}
	if (_boardPos != "d1" && _color == Color::WHITE) Moved();
	if (_boardPos != "d8" && _color == Color::BLACK) Moved();
}

Piece* Queen::clone() const
{
	return new Queen(*this);
}

std::vector<std::pair<int, int>> Queen::GetPseudoLegalMoves(Board& board)
{
	int x = GetBoardPos()[0] - 96;
	int y = GetBoardPos()[1] - 48;
	std::vector<std::pair<int, int>> legalMoves;

	//checks up-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, 1))
		legalMoves.push_back(i);
	//checks up
	for (auto i : checkForAvailableSquares(board, x, y, 0, 1))
		legalMoves.push_back(i);
	//checks up-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, 1))
		legalMoves.push_back(i);
	//checks to the right
	for (auto i : checkForAvailableSquares(board, x, y, 1, 0))
		legalMoves.push_back(i);
	//checks down-right diagonal
	for (auto i : checkForAvailableSquares(board, x, y, 1, -1))
		legalMoves.push_back(i);
	//checks down
	for (auto i : checkForAvailableSquares(board, x, y, 0, -1))
		legalMoves.push_back(i);
	//checks down-left diagonal
	for (auto i : checkForAvailableSquares(board, x, y, -1, -1))
		legalMoves.push_back(i);
	//checks to the left
	for (auto i : checkForAvailableSquares(board, x, y, -1, 0))
		legalMoves.push_back(i);

	return legalMoves;
}

std::vector<std::pair<int, int>> Queen::GetAttackedSquares(Board& board)
{
	return GetPseudoLegalMoves(board);
}
