#include "Game.h"

Game* Game::Instance = new Game;


Game::Game()
{
	GameSystem::instance = new GameSystem;
	UI::Instance = new UI;
	screen = Screen::MainMenu;
}


Game::~Game()
{
}

void Game::start()
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top,1050, 650, TRUE); // 800 width, 100 height
	UI::Instance->showScreen(screen);
	UI::Instance->gotoXY(47, 13);
	while (true)
	{
		if (_kbhit())
		{
			GameSystem::instance->keyInput();
		}
	}
}