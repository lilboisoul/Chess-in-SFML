#pragma once
#include "SFML\Graphics.hpp"
#include "Utility/Resources.h"
#include <memory>
#include <stack>
#include <string>
#include <stack>
#include <memory>

class Scene;
class App
{
public:
	App(unsigned int width, unsigned int height, std::string title);
	~App();

	void Run();
	
	void PushScene(std::unique_ptr<Scene>&& scene);
	void ChangeScene(std::unique_ptr<Scene>&& scene); //pop + push
	void PopScene();

	sf::RenderWindow& GetWindow();
	sf::Vector2u GetWindowSize();
private:
	sf::RenderWindow window;
	std::stack<std::unique_ptr<Scene>> scenes;
};

