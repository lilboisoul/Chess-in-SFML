#include "Board.h"
#include "../App.h"
#include <string>
constexpr float SQUARE_WIDTH = 100.0f;

void ColorSquare(int temp, Square* sqr) {
	if (temp % 2 == 1)
	{
		sqr->squareGameObject.setFillColor(sf::Color(155, 103, 60, 255));
	}
	else
	{
		sqr->squareGameObject.setFillColor(sf::Color(239, 231, 219, 255));
	}
}


Board::Board(App* _app, FEN fenString) : appPtr(_app)
{
	InitBoardGameObject();
	InitArrayOfSquares();
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

App* Board::GetAppPtr()
{
	return appPtr;
}

void Board::Update()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			arrayOfSquares[i][j]->Update();
		}
	}

}
void Board::InitBoardGameObject()
{
	sf::Vector2u windowsize = GetAppPtr()->GetWindowSize();

	this->boardGameObject.setPosition({ windowsize.x / 30.0f, windowsize.y / 30.0f });
	this->boardGameObject.setSize({ windowsize.x * 0.8f, windowsize.y * 0.8f });
	this->boardGameObject.setFillColor(sf::Color::Black);
	this->boardGameObject.setOutlineColor(sf::Color::White);
	this->boardGameObject.setOutlineThickness(2.f);
}
void Board::InitArrayOfSquares()
{
	//temp variables
	int temporaryNumber = 1;
	std::string BoardPos = "a1";
	sf::Vector2f BoardPosition = { boardGameObject.getPosition().x , boardGameObject.getPosition().y };
	sf::Vector2f SquarePosition;
	//

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			BoardPos[0] = 'a' + i; BoardPos[1] = '0' + j + 1;
			SquarePosition = { BoardPosition.x + (SQUARE_WIDTH * i), BoardPosition.y + (SQUARE_WIDTH * (7 - j)) };
			arrayOfSquares[i][j] = new Square(appPtr, BoardPos, SquarePosition);
			ColorSquare(temporaryNumber, arrayOfSquares[i][j]);
			temporaryNumber++;
		}
		temporaryNumber++;
	}

}
void Board::Render(sf::RenderTarget& renderer)
{
	renderer.draw(boardGameObject);
	for (int i = 0; i < 8; i++)	
	{
		for (int j = 0; j < 8; j++)
		{
			arrayOfSquares[i][j]->Render(renderer);
		}
	}
}
