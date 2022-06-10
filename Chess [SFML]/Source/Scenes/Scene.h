#pragma once
#include "SFML/Graphics.hpp"
class Scene
{
public:
	virtual ~Scene() = default;

	virtual void HandleEvents(sf::Event& ev) = 0;
	virtual void HandleInput(float deltaTime) = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void Render(sf::RenderTarget& renderer) = 0;
};

