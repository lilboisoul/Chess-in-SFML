#include "Square.h"
#include "Board.h"
#include "../App.h"

constexpr float SQUAREWIDTH = 100.0f;

void ResetSquareColor(sf::RectangleShape& square, Color squareColor)
{
	if (squareColor == Color::WHITE)
	{
		square.setFillColor(sf::Color(239, 231, 219, 255));
	}
	else
	{
		square.setFillColor(sf::Color(155, 103, 60, 255));

	}
}
void ClickSquare(sf::RectangleShape& square)
{
	square.setFillColor(sf::Color(229, 107, 107, 255));
}
void UnclickSquare(sf::RectangleShape& square, Color _color)
{
	if (_color == Color::WHITE)
	{
		square.setFillColor(sf::Color(239, 231, 219, 255));
	}
	else
	{
		square.setFillColor(sf::Color(155, 103, 60, 255));
		
	}
}


Square::Square(App* _app, std::string _boardPos, sf::Vector2f _position) : appPtr(_app), boardPos(_boardPos)
{
	sf::Vector2u windowsize = GetAppPtr()->GetWindowSize();

	squareGameObject.setPosition(_position);
	squareGameObject.setSize({ SQUAREWIDTH, SQUAREWIDTH });
	squareGameObject.setOutlineColor(sf::Color::Black);
	squareGameObject.setOutlineThickness(1.f);
	isClicked = false;
	isRightClicked = false;
	isAttacked = false;
}

Square::~Square()
{

}

App* Square::GetAppPtr()
{
	return appPtr;
}
std::unique_ptr<Piece>& Square::GetPiecePtr()
{
	return piecePtr;
}

std::string Square::GetBoardPos()
{
	return boardPos;
}

void Square::SetPiece(std::unique_ptr<Piece>&& piece)
{
	piecePtr = std::move(piece);
	if (piecePtr)
	{
		piecePtr->SetBoardPos(boardPos);
		piecePtr->SetPosition({ squareGameObject.getPosition().x + squareGameObject.getSize().x / 2.0f, squareGameObject.getPosition().y + squareGameObject.getSize().y / 2.0f });
	}
}

void Square::Render(sf::RenderTarget& renderer)
{
	renderer.draw(squareGameObject);
	if (piecePtr) {
		piecePtr->Render(renderer);
	}
}

bool Square::IsHovered(sf::Vector2i& mousePos)
{
	return squareGameObject.getGlobalBounds().contains((float)mousePos.x, (float)mousePos.y);
}

void Square::SetHighlighted(bool _val)
{
	if (_val)
	{
		squareGameObject.setFillColor(sf::Color(220, 59, 25, 255));
		return;
	}
	else 
	{
		ResetSquareColor(squareGameObject, squareColor);
		return;
	}
}

bool Square::IsHighlighted()
{
	if (squareGameObject.getFillColor() == sf::Color(220, 59, 25, 255))
		return true;
	return false;
}

bool Square::IsRightClicked()
{
	return isRightClicked;
}

void Square::SetAttacked(bool _val)
{
	isAttacked = _val;
}

bool Square::IsAttacked()
{
	return isAttacked;
}

void Square::SetRightClicked(bool _val)
{
	if (!GetClicked() && !IsHighlighted())
	{
		if (_val)
		{
			squareGameObject.setFillColor(sf::Color::Red);
			isRightClicked = true;
			return;
		}
		else
		{
			ResetSquareColor(squareGameObject, squareColor);
			isRightClicked = false;
			return;
		}
	}
}

void Square::SetClicked(bool val)
{
	this->isClicked = val;
	if (val == true)
	{
		ClickSquare(squareGameObject);
	}
	else
	{
		ResetSquareColor(squareGameObject, squareColor);
	}

}

void Square::SetColor(Color _color)
{
	squareColor = _color;
}

bool Square::GetClicked()
{
	return isClicked;
}



