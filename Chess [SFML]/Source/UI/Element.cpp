#include "Element.h"
#include "../Utility/Resources.h"
//
//if (_color == Color::WHITE) {
//	pieceGameObject.setTexture(ResourceManager::Get().GetTexture("wP"));
//}
//else {
//	pieceGameObject.setTexture(ResourceManager::Get().GetTexture("bP"));
//}
Element::Rectangle::Rectangle(const sf::Vector2f& size)
	: sf::RectangleShape(size) { }

bool Element::Rectangle::IsRolledOn(const sf::RenderWindow& window) const {
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);

	return getGlobalBounds().contains(sf::Vector2f(mousePos));
}

bool Element::Rectangle::IsClickedOn(const sf::RenderWindow& window, sf::Event& ev) const {
	if (IsRolledOn(window) && ev.type == sf::Event::MouseButtonPressed)
		return ev.mouseButton.button == sf::Mouse::Left;

	return false;
}

Element::Text::Text() {
	setFillColor(sf::Color::White);
	setOutlineColor(sf::Color::Black);
	setOutlineThickness(1.0f);
	setFont(*ResourceManager::Get().GetFont("OpenSans"));
}

void Element::Text::SetFont(const std::string& name) {
	setFont(*ResourceManager::Get().GetFont("OpenSans"));	
}

void Element::Text::SetFontSize(unsigned size) {
	setCharacterSize(size);
}

void Element::Text::UpdateText() {
	sf::FloatRect textRect = getLocalBounds();

	setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}