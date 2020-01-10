#include"Game.h"
/*
void pause()
{
	UI::Instance->gotoXY(0, 25);
	UI::Instance->SetTextColor(Color::white, Color::black);
	system("pause");
}*/

int main()
{
	Game::Instance->start();
	
	/*pause();
	UI::Instance->showBlock(GameMode::DuoPlaying, Block::Regret);
	pause();
	UI::Instance->showScreen(GameMode::DuoPlaying);
	UI::Instance->showBlock(GameMode::DuoPlaying, Block::Pause);
	pause();*/
}