#include "App.h"
#include "Scenes/Scene.h"

App::App(unsigned int width, unsigned int height, std::string title) : window({ width, height }, title, sf::Style::Titlebar | sf::Style::Close)
{
	window.setFramerateLimit(60);
}

App::~App()
{
	while (!scenes.empty())
	{
		scenes.pop();
	}
}

void App::Run()
{
	sf::Clock timer;
	sf::Event ev;
	float defaultTime = 1.0f / 5.0f;
	float deltaTime = defaultTime;

	while (window.isOpen())
	{
		while (window.pollEvent(ev))
		{
			scenes.top()->HandleEvents(ev);
			if (ev.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		window.clear({255,182,193,255}); //light pink color
		scenes.top()->HandleInput(deltaTime);
		scenes.top()->Update(deltaTime);
		scenes.top()->Render(window);

		window.display();

		deltaTime = std::min(timer.restart().asSeconds(), defaultTime);
	}
}

void App::PushScene(std::unique_ptr<Scene>&& scene)
{
	scenes.push(std::move(scene));
}

void App::ChangeScene(std::unique_ptr<Scene>&& scene)
{
	PopScene();
	scenes.push(std::move(scene));
}
void App::PopScene()
{
	if(!scenes.empty()) scenes.pop();
}

sf::RenderWindow& App::GetWindow()
{
	return this->window;
}

sf::Vector2u App::GetWindowSize()
{
	return window.getSize();
}
