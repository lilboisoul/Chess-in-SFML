#include "SetupGameScene.h"
#include <iostream>
#include "../App.h"

SetupGameScene::SetupGameScene(App* _app) : Scene(), appPtr(_app)
{

}
SetupGameScene::~SetupGameScene()
{

}

App* SetupGameScene::GetAppPtr()
{
	return this->appPtr;
}
void SetupGameScene::HandleEvents(sf::Event& ev)
{

}
void SetupGameScene::HandleInput(float deltaTime)
{

}

void SetupGameScene::Update(float deltaTime)
{

}

void SetupGameScene::Render(sf::RenderTarget& renderer)
{

}
