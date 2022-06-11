#include "Square.h"
#include "../App.h"
void Square::InitSquareGameObject()
{
	sf::Vector2u windowsize = GetAppPtr()->GetWindowSize();

	squareGameObject.setSize({ windowsize.x * 0.1f, windowsize.y * 0.1f });
	squareGameObject.setOutlineColor(sf::Color::Black);
	squareGameObject.setOutlineThickness(1.f);

}

Square::Square(App* _app) : appPtr(_app)
{
	InitSquareGameObject();
}

Square::~Square()
{
}

App* Square::GetAppPtr()
{
	return appPtr;
}
Piece* Square::GetPiecePtr()
{
	return piecePtr;
}

void Square::Render(sf::RenderTarget& renderer)
{
	renderer.draw(squareGameObject);
}

