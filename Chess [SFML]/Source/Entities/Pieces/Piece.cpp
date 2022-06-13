#include "Piece.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"

void Piece::SetTexture()
{
	switch (GetID()) {
		case('p'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bP.png"));
			break;
		case('P'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wP.png"));
			break;
		case('n'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bN.png"));
			break;
		case('N'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wN.png"));
			break;
		case('b'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bB.png"));
			break;
		case('B'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wB.png"));
			break;
		case('r'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bR.png"));
			break;
		case('R'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wR.png"));
			break;
		case('q'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bQ.png"));
			break;
		case('Q'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wQ.png"));
			break;
		case('k'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bK.png"));
			break;
		case('K'):
			pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wK.png"));
			break;
	}
	
}
Piece::Piece(App* _app, Color _color, std::string& _boardPos, char _id) : appPtr(_app), pieceColor(_color), boardPos(_boardPos), ID(_id), hasMoved(false)
{
	SetTexture();

}

void Piece::Render(sf::RenderTarget& renderer)
{
	renderer.draw(pieceGameObject);
}

void Piece::SetPosition(const sf::Vector2f& pos)
{
	pieceGameObject.setPosition(pos);
}

void Piece::SetBoardPos(const std::string& _boardPos)
{
	boardPos = _boardPos;
}

void Piece::Moved()
{
	hasMoved = true;
}

Color Piece::GetColor() const
{
	return pieceColor;
}

std::string Piece::GetBoardPos() const
{
	return boardPos;
}

char Piece::GetID() const
{
	return ID;
}

bool Piece::HasMoved() const
{
	return hasMoved;
}

void Piece::InitPieceGameOBject()
{
	
}


