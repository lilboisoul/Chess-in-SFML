#include "Rook.h"
#include "../Chess [SFML]/Source/Utility/Resources.h"
Rook::Rook(App* _app, Color _color, std::string& _boardPos, char _id) : Piece(_app, _color, _boardPos, _id)
{
	if (_color == Color::WHITE) {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wR"));
	}
	else {
		pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bR"));
	}
}