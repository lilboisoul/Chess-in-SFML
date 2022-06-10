#pragma once
#include "SFML/Graphics.hpp"
#include "../FEN.h"
#include "Square.h"
class App;
class Board : public sf::Drawable
{
private:
	App* appPtr;
	sf::RectangleShape boardGameObject;

	void InitBoardGameObjectVisualProperties();
	void InitArrayOfSquares();

	void LoadPosition(FEN fenPieces);

public:
	Board(App* _app, FEN fenString);
	~Board();

	Square* arrayOfSquares[8][8];

	void Update();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

