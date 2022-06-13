#include "Piece.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"

Piece::Piece(App* _app, Color _color, std::string& _boardPos, char _id) : appPtr(_app), pieceColor(_color), boardPos(_boardPos), ID(_id), hasMoved(false)
{
	pieceGameObject.setSize({ 100.0f, 100.0f });
	pieceGameObject.setOrigin(pieceGameObject.getSize() / 2.0f);

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


