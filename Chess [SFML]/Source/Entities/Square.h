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

	App* GetAppPtr();
	std::unique_ptr<Piece>& GetPiecePtr();
	std::string GetBoardPos();
	
	void SetPiece(std::unique_ptr<Piece>&& piece);
	void Update() { };
	void Render(sf::RenderTarget& renderer);

private:
	App* appPtr;
	std::unique_ptr<Piece> piecePtr;
	std::string boardPos;

	void InitSquareGameObject(sf::Vector2f _position);
};
