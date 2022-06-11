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
	virtual ~Piece() = default;
	virtual void Render(sf::RenderTarget& renderer);
	virtual void SetPosition(const sf::Vector2f& pos);
	virtual void SetBoardPos(const std::string& boardPos);
	virtual void Moved();

	virtual Color		 GetColor()	   const;
	virtual std::string  GetBoardPos() const;
	virtual char		 GetID()	   const;
	virtual bool		 HasMoved()	   const;

private:
	App* appPtr;
	Color pieceColor;
	sf::RectangleShape pieceGameObject;
	std::string boardPos;
	char ID;
	bool hasMoved;
};

