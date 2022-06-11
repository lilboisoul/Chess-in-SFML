#include "Square.h"

Square::Square(App* _app) : appPtr(_app)
{
}

Square::~Square()
{
}

void Square::Render(sf::RenderTarget& renderer)
{
	renderer.draw(squareGameObject);
}

