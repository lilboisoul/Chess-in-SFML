#include "Board.h"
#include "../App.h"
#include "../FEN.h"
#include "Pieces/Pieces.h"
#include <string>
constexpr float SQUARE_WIDTH = 100.0f;

void ColorSquare(int temp, Square* sqr) {
	if (temp % 2 == 1)
	{
		sqr->squareGameObject.setFillColor(sf::Color(155, 103, 60, 255));
		sqr->SetColor(Color::BLACK);
	}
	else
	{
		sqr->squareGameObject.setFillColor(sf::Color(239, 231, 219, 255));
		sqr->SetColor(Color::WHITE);
	}
}


Board::Board(App* _app, std::string fen_pieces) : appPtr(_app)
{
	InitBoardGameObject();
	InitArrayOfSquares();
	LoadPosition(fen_pieces);
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

void Board::HighlightMoves(std::vector<std::pair<int, int>> _moves)
{
	for (auto [x, y] : _moves)
	{
		arrayOfSquares[x-1][y-1]->SetHighlighted(true);
	}
}

void Board::UnhighlightMoves(std::vector<std::pair<int, int>> _moves)
{
	for (auto [x, y] : _moves)
	{
		arrayOfSquares[x-1][y-1]->SetHighlighted(false);
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
void Board::LoadPosition(std::string fen_pieces)
{

	//temporary variables
	char temporaryCharacter;
	int row = 7, column = 0;

	//initializes the array
	char fenPosition[8][8];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			fenPosition[i][j] = '-';
		}
	}


	for (int i = 0; i < fen_pieces.length(); i++)
	{
		temporaryCharacter = fen_pieces[i];
		if (temporaryCharacter >= 'a' && temporaryCharacter <= 'z' || temporaryCharacter >= 'A' && temporaryCharacter <= 'Z')
		{
			fenPosition[row][column] = temporaryCharacter;

			column++;
		}
		else if (temporaryCharacter == '/')
		{
			row--;
			column = 0;
		}
		else {
			column += static_cast<int>(temporaryCharacter - 48);
		}
		if (row == 0 && column == 8) break; //checks for the end of piece placement section of the FEN code
	}

	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			std::string tempBoardPos = arrayOfSquares[i][j]->GetBoardPos();
			switch (fenPosition[7 - j][i])
			{
				case 'p':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Pawn>(appPtr, Color::WHITE, tempBoardPos, 'p'));
					break;

				case 'P':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Pawn>(appPtr, Color::BLACK, tempBoardPos, 'P'));
					break;

				case 'n':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Knight>(appPtr, Color::WHITE, tempBoardPos, 'n'));
					break;

				case 'N':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Knight>(appPtr, Color::BLACK, tempBoardPos, 'N'));
					break;

				case 'b':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Bishop>(appPtr, Color::WHITE, tempBoardPos, 'b'));
					break;

				case 'B':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Bishop>(appPtr, Color::BLACK, tempBoardPos, 'B'));
					break;

				case 'r':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Rook>(appPtr, Color::WHITE, tempBoardPos, 'r'));
					break;

				case 'R':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Rook>(appPtr, Color::BLACK, tempBoardPos, 'R'));
					break;

				case 'q':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Queen>(appPtr, Color::WHITE, tempBoardPos, 'q'));
					break;

				case 'Q':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<Queen>(appPtr, Color::BLACK, tempBoardPos, 'Q'));
					break;

				case 'k':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<King>(appPtr, Color::WHITE, tempBoardPos , 'k'));
					break;

				case 'K':
					arrayOfSquares[i][j]->SetPiece(std::make_unique<King>(appPtr, Color::BLACK, tempBoardPos, 'pK'));
					break;
				}

			}
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

std::unique_ptr<Piece>&& Board::GetCurrentlyHoveredPiece(sf::RenderWindow& window) 
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arrayOfSquares[i][j]->IsHovered(mousePos))
				return std::move(arrayOfSquares[i][j]->GetPiecePtr());
		}
	}

	return nullptr;
}

Square* Board::GetCurrentlyHoveredTile(sf::RenderWindow& window) 
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (arrayOfSquares[i][j]->IsHovered(mousePos))
				return arrayOfSquares[i][j];
		}
	}
}

