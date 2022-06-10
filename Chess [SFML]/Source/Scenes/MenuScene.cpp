#include "MenuScene.h"
#include <iostream>
#include "GameScene.h"
#include "../App.h"

MenuScene::MenuScene(App* _app) : Scene(), appPtr(_app)
{
	
}

MenuScene::~MenuScene()
{
	
}

App* MenuScene::GetAppPtr()
{
	return this->appPtr;
}
void MenuScene::HandleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
	{
		appPtr->ChangeScene(std::make_unique<GameScene>(appPtr));
		return;
	}
}
void MenuScene::HandleInput(float deltaTime)
{

}

void MenuScene::Update(float deltaTime)
{

}

void MenuScene::Render(sf::RenderTarget& renderer)
{
	//renderer.draw(background);
}
