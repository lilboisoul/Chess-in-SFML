#pragma once
#include "SFML/Graphics.hpp"
#include "Pieces/Piece.h"
class App;
class Square
{

public:
	Square(App* _app);
	~Square();
	sf::RectangleShape squareGameObject;

	App* GetAppPtr();
	Piece* GetPiecePtr();
	void Update() {};
	void Render(sf::RenderTarget& renderer);
private:
	App* appPtr;
	Piece* piecePtr;

	void InitSquareGameObject();
};
