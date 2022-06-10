#include "Square.h"

Square::Square(App* _app) : appPtr(_app)
{
}

Square::~Square()
{
}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(squareGameObject);
}
