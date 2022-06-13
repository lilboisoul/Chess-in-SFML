#include "GameScene.h"
#include <iostream>
#include "../FEN.h"
#include "../App.h"


GameScene::GameScene(App* _app, FEN _fen): Scene(), appPtr(_app), fen(_fen)
{
	boardPtr = new Board(appPtr, fen.GetPieces());
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
	if (ev.type == sf::Event::KeyPressed && ev.key.code == sf::Keyboard::Escape)
	{
		appPtr->PopScene();
		return;
	}
}
void GameScene::HandleInput(float deltaTime)
{

}

void GameScene::Update(float deltaTime)
{

}

void GameScene::Render(sf::RenderTarget& renderer)
{
	boardPtr->Render(renderer);
}
