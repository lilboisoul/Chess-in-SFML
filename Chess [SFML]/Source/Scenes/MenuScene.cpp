#include "MenuScene.h"
#include "SetupGameScene.h"
#include <iostream>
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
		appPtr->PushScene(std::make_unique<SetupGameScene>(appPtr));
		return;
	}
}
void MenuScene::HandleInput(float deltaTime)
{

}

void MenuScene::Update(float deltaTime)
{
	GetAppPtr()->GetWindow().clear({ 255,255,0 });
}

void MenuScene::Render(sf::RenderTarget& renderer)
{
	
	//renderer.draw(background);
}
