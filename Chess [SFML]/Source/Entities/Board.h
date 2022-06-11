#pragma once
#include "SFML/Graphics.hpp"
#include "../FEN.h"
#include "Square.h"
class App;
class Board
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
	void Render(sf::RenderTarget& renderer);

};

