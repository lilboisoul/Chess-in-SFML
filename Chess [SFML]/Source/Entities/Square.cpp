#include "Square.h"
#include "../App.h"
void Square::InitSquareGameObject(sf::Vector2f _position)
{
	sf::Vector2u windowsize = GetAppPtr()->GetWindowSize();

	squareGameObject.setPosition(_position);
	squareGameObject.setSize({ windowsize.x * 0.1f, windowsize.y * 0.1f });
	squareGameObject.setOutlineColor(sf::Color::Black);
	squareGameObject.setOutlineThickness(1.f);

}

Square::Square(App* _app, std::string _boardPos, sf::Vector2f _position) : appPtr(_app), boardPos(_boardPos)
{
	InitSquareGameObject(_position);
}

Square::~Square()
{
	
}

App* Square::GetAppPtr()
{
	return appPtr;
}
std::unique_ptr<Piece>& Square::GetPiecePtr()
{
	return piecePtr;
}

std::string Square::GetBoardPos()
{
	return boardPos;
}

void Square::SetPiece(std::unique_ptr<Piece>&& piece)
{
	piecePtr = std::move(piece);
	piecePtr->SetBoardPos(boardPos);
	if (piecePtr)
		piecePtr->SetPosition({ squareGameObject.getPosition().x + squareGameObject.getSize().x / 2.0f, squareGameObject.getPosition().y + squareGameObject.getSize().y / 2.0f });
}

void Square::RenderSquare(sf::RenderTarget& renderer)
{
	renderer.draw(squareGameObject);
}
void Square::RenderPiece(sf::RenderTarget& renderer)
{
	if (piecePtr) {
		piecePtr->Render(renderer);
	}
}


