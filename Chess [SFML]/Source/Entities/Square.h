#pragma once
#include "SFML/Graphics.hpp"
class App;
class Square : public sf::Drawable
{
private:
	App* appPtr;
	sf::RectangleShape squareGameObject;

public:
	Square(App* _app);
	~Square();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
