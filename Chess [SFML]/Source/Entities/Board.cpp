#include "Board.h"

Board::Board(App* _app, FEN fenString) : appPtr(_app)
{
	InitArrayOfSquares();
	InitBoardGameObjectVisualProperties();
}

Board::~Board()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (arrayOfSquares[i][j] != nullptr)
			{
				delete arrayOfSquares[i][j];
			}
		}
	}
}

void Board::Update()
{
	/*for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arrayOfSquares[i][j].update();
		}
	}*/

}
void Board::InitBoardGameObjectVisualProperties()
{
	this->boardGameObject.setPosition({ 100, 50 });
	this->boardGameObject.setSize(sf::Vector2f(800.0f, 800.0f));
	this->boardGameObject.setFillColor(sf::Color::Yellow);
	this->boardGameObject.setOutlineColor(sf::Color::Black);
	this->boardGameObject.setOutlineThickness(2.f);
}
void Board::InitArrayOfSquares()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			arrayOfSquares[i][j] = new Square(appPtr);
		}
	}

}
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(boardGameObject);
}
