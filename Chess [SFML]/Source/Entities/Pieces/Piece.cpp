#include "Piece.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
#include "../Board.h"
bool Piece::isInBounds(int x, int y)
{
	if (x > 0 && x <= 8 && y > 0 && y <= 8)
	{
		return true;
	}
	return false;
}
bool Piece::isEmpty(Board& board, int x, int y)
{
	if (isInBounds(x, y))
	{
		if (board.arrayOfSquares[x - 1][y - 1]->GetPiecePtr() == nullptr)
		{
			return true;
		}
	}
	return false;
}
bool Piece::isSameColor(Board& board, int x1, int y1, int x2, int y2)
{
	if (!isInBounds(x2, y2))
		return false;
	if (isEmpty(board, x2, y2))
		return false;
	if (board.arrayOfSquares[x1 - 1][y1 - 1]->GetPiecePtr()->GetColor() != board.arrayOfSquares[x2 - 1][y2 - 1]->GetPiecePtr()->GetColor())
		return false;

	return true;
}
std::vector<std::pair<int, int>> Piece::checkForAvailableSquares(Board& board, int x, int y, int offsetX, int offsetY)
{
	std::vector <std::pair<int, int>> availableSquares;
	int tempOffsetX = offsetX;
	int tempOffsetY = offsetY;
	while (isInBounds(x + offsetX, y + offsetY))
	{
		if (isEmpty(board, x + offsetX, y + offsetY)) {
			availableSquares.push_back({ x + offsetX, y + offsetY });
			offsetX += tempOffsetX;
			offsetY += tempOffsetY;
		}
		else if (!isSameColor(board, x, y, x + offsetX, y + offsetY))
		{
			availableSquares.push_back({ x + offsetX, y + offsetY });
			break;
		}
		else break;
	}
	return availableSquares;
}
Piece::Piece(App* _app, Color _color, std::string& _boardPos, char _id) : appPtr(_app), pieceColor(_color), boardPos(_boardPos), ID(_id), hasMoved(false)
{
	pieceGameObject.setSize({ 100.0f, 100.0f });
	pieceGameObject.setOrigin(pieceGameObject.getSize() / 2.0f);

}

Piece::Piece(const Piece& _piece)
{
	*this = _piece;
}

void Piece::Render(sf::RenderTarget& renderer)
{
	renderer.draw(pieceGameObject);
}

void Piece::SetPosition(const sf::Vector2f& pos)
{
	pieceGameObject.setPosition(pos);
}

void Piece::SetBoardPos(const std::string& _boardPos)
{
	boardPos = _boardPos;
}

void Piece::Moved()
{
	hasMoved = true;
}

App* Piece::GetAppPtr() const
{
	return appPtr;
}

Color Piece::GetColor() const
{
	return pieceColor;
}

std::string Piece::GetBoardPos() const
{
	return boardPos;
}

char Piece::GetID() const
{
	return ID;
}

bool Piece::HasMoved() const
{
	return hasMoved;
}


