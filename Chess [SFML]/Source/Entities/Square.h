#pragma once
#include "SFML/Graphics.hpp"
class App;
class Square
{
private:
	App* appPtr;
	sf::RectangleShape squareGameObject;

public:
	Square(App* _app);
	~Square();
	void Update() {};
	void Render(sf::RenderTarget& renderer);
};
