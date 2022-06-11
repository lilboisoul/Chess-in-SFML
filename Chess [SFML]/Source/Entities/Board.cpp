#include "Board.h"
#include "../App.h"
constexpr float SQUARE_WIDTH = 100.0f;

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
	int temporaryNumber = 1;
	
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			arrayOfSquares[i][j] = new Square(appPtr);


			if (temporaryNumber % 2 == 1)
			{
				this->arrayOfSquares[i][j]->squareGameObject.setFillColor(sf::Color(155, 103, 60, 255));
			}
			else 
			{
				this->arrayOfSquares[i][j]->squareGameObject.setFillColor(sf::Color(239, 231, 219, 255));
			}
			temporaryNumber++;

			this->arrayOfSquares[i][j]->squareGameObject.setPosition(boardGameObject.getPosition().x + (SQUARE_WIDTH * i),
															         boardGameObject.getPosition().y + (SQUARE_WIDTH * (7 - j)));

			//this->arrayOfSquares[i][j]->setBoardPos(i, j + 1);
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
