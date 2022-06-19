#pragma once
#include <string>
#include "SFML/Graphics.hpp"
class App;
class Board;
enum class Color {
	WHITE,
	BLACK
};
class Piece
{
public:
	Piece(App* _app, Color _color, std::string& _boardPos, char _id);
	Piece(const Piece& _piece);
	virtual Piece* clone() const = 0;


	void Render(sf::RenderTarget& renderer);
	void SetPosition(const sf::Vector2f& pos);
	void SetBoardPos(const std::string& boardPos);
	void Moved();

	App*		 GetAppPtr()   const;
	Color		 GetColor()	   const;
	std::string  GetBoardPos() const;
	char		 GetID()	   const;
	bool		 HasMoved()	   const;

	
	bool isInBounds(int x, int y);
	bool isEmpty(Board& board, int x, int y);
	bool isSameColor(Board& board, int x1, int y1, int x2, int y2);
	std::vector<std::pair<int, int>> checkForAvailableSquares(Board& board, int x, int y, int offsetX, int offsetY);

	virtual std::vector<std::pair<int, int>> GetPseudoLegalMoves(Board& board) = 0;
	virtual std::vector<std::pair<int, int>> GetAttackedSquares(Board& board) = 0;

	sf::RectangleShape pieceGameObject;
private:
	App* appPtr;
	Color pieceColor;
	std::string boardPos;
	char ID;
	bool hasMoved;

};

