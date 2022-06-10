#include "GameScene.h"
#include <iostream>
#include "../App.h"

GameScene::GameScene(App* _app): Scene(), appPtr(_app)
{
	boardPtr = new Board(appPtr, fenCode);

}
GameScene::~GameScene()
{
	delete boardPtr;
}

App* GameScene::GetAppPtr()
{
	return this->appPtr;
}
Board* GameScene::GetBoardPtr()
{
	return boardPtr;
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
