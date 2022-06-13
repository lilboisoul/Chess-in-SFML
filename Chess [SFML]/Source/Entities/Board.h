#pragma once
#include "SFML/Graphics.hpp"
#include "../FEN.h"
#include "Square.h"
class App;
class Board
{

public:
	Board(App* _app, std::string fen_pieces);
	~Board();

	App* GetAppPtr();
	Square* arrayOfSquares[8][8];

	void Update();
	void Render(sf::RenderTarget& renderer);


private:
	App* appPtr;
	sf::RectangleShape boardGameObject;

	void InitBoardGameObject();
	void InitArrayOfSquares();
	void LoadPosition(std::string fen_pieces);

};

