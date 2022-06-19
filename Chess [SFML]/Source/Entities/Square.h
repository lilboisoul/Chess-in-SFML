#pragma once
#include "SFML/Graphics.hpp"
#include "Pieces/Piece.h"
class App;
class Square
{

public:
	Square(App* _app, std::string boardPos, sf::Vector2f position);
	~Square();

	sf::RectangleShape squareGameObject;

	void					SetPiece(std::unique_ptr<Piece>&& piece);
	void					SetClicked(bool val);
	void					SetColor(Color _color);

	App*					GetAppPtr();
	std::unique_ptr<Piece>& GetPiecePtr();
	std::string				GetBoardPos();
	bool					GetClicked();


	
	bool IsHovered(sf::Vector2i& mousePos);
	void SetHighlighted(bool _val);
	bool IsHighlighted();
	void SetRightClicked(bool _val);
	bool IsRightClicked();
	void SetAttacked(bool _val);
	bool IsAttacked();
	void Render(sf::RenderTarget& renderer);
private:
	App* appPtr;
	Color squareColor;
	std::unique_ptr<Piece> piecePtr;
	std::string boardPos;
	bool isClicked;
	bool isRightClicked;
	bool isAttacked;
};
