#include "GameScene.h"
#include <iostream>
#include "../App.h"

GameScene::GameScene(App* _app): Scene(), appPtr(_app)
{
	
}
GameScene::~GameScene()
{
	
}

App* GameScene::GetAppPtr()
{
	return this->appPtr;
}
void GameScene::HandleEvents(sf::Event& ev)
{
	
}
void GameScene::HandleInput(float deltaTime)
{

}

void GameScene::Update(float deltaTime)
{

}

void GameScene::Render(sf::RenderTarget& renderer)
{
	
}
