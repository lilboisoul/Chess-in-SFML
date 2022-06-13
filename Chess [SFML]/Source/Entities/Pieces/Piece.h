#pragma once
#include <string>
#include "SFML/Graphics.hpp"
class App;
enum class Color {
	WHITE,
	BLACK
};
class Piece
{
public:
	Piece(App* _app, Color _color, std::string& _boardPos, char _id);
	//virtual ~Piece() = default;
	void Render(sf::RenderTarget& renderer);
	void SetPosition(const sf::Vector2f& pos);
	void SetBoardPos(const std::string& boardPos);
	void Moved();

	Color		 GetColor()	   const;
	std::string  GetBoardPos() const;
	char		 GetID()	   const;
	bool		 HasMoved()	   const;

	sf::RectangleShape pieceGameObject;
private:
	App* appPtr;
	Color pieceColor;
	std::string boardPos;
	char ID;
	bool hasMoved;

};

