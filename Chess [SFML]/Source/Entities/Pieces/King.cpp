#include "King.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
King::King(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wK"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bK"));
	}
}