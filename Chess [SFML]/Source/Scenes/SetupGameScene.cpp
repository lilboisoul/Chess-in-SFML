#include "SetupGameScene.h"
#include "GameScene.h"
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
FEN SetupGameScene::GetFen()
{
	return this->fen;
}
void SetupGameScene::HandleEvents(sf::Event& ev)
{
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Space)
	{
		appPtr->ChangeScene(std::make_unique<GameScene>(appPtr, GetFen(), GameMode::CHESS));
		return;
	}
}
void SetupGameScene::HandleInput(float deltaTime)
{

}

void SetupGameScene::Update(float deltaTime)
{
	GetAppPtr()->GetWindow().clear({88,88,88 });
}

void SetupGameScene::Render(sf::RenderTarget& renderer)
{

}
