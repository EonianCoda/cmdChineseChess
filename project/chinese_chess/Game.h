#pragma once
#include"GameSystem.h"


class Game {
	Screen screen;
public:
	static Game *Instance;
	void start();
	Game();
	~Game();
};
