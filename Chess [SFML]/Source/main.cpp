#include "..\include\SFML\Graphics.hpp"
#include "..\include\SFML\System.hpp"
#include "..\include\SFML\Window.hpp"
#include "App.h"
#include "Scenes\GameScene.h"
#include "Scenes\MenuScene.h"
#include "Scenes\Scene.h"
#include <iostream>
#include <regex>


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Memory leaks check
	App app(1300, 1000, "Chess");
	app.PushScene(std::make_unique<MenuScene>(&app));
	
	try
	{
		app.Run();
	}
	catch (int exception)
	{
		std::cout << "error: exception nr " << exception;
	}
	return 0;

}