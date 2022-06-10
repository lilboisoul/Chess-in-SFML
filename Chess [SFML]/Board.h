#pragma once
#include "SFML/Graphics.hpp"
class App;
class Board : public sf::Drawable
{
private:
	App* appPtr;

public:
	Board(App* _app);
	~Board();
};

