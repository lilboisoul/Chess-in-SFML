#pragma once
#include "SFML/Graphics.hpp"
#include "../FEN.h"
#include "Square.h"
class App;
class Board
{

public:
	Board(App* _app, std::string fen_pieces);
	~Board();
	sf::RectangleShape boardGameObject;

	App* GetAppPtr();
	Square* arrayOfSquares[8][8];

	void HighlightMoves(std::vector<std::pair<int, int>> _moves);
	void UnhighlightMoves(std::vector<std::pair<int, int>> _moves);

	Square*					 GetCurrentlyHoveredTile (sf::RenderWindow& window);
	std::unique_ptr<Piece>&& GetCurrentlyHoveredPiece(sf::RenderWindow& window);

	void Render(sf::RenderTarget& renderer);
private:
	App* appPtr;

	void InitBoardGameObject();
	void InitArrayOfSquares();
	void LoadPosition(std::string fen_pieces);

};

