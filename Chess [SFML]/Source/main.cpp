#include "..\include\SFML\Graphics.hpp"
#include "..\include\SFML\System.hpp"
#include "..\include\SFML\Window.hpp"
#include "App.h"
#include "Scenes\GameScene.h"
#include "Scenes\MenuScene.h"
#include "Scenes\Scene.h"
#include <iostream>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Memory leaks check

	App app(1000, 1000, "Chess");
	app.PushScene(std::make_unique<MenuScene>(&app));
	app.Run();

	return 0;

}