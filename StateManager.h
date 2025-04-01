#pragma once
#include "Board.h"

class GameScreen;

class StateManager
{
public:
	StateManager();
	~StateManager();

	enum class Screen
	{
		StartScreen,
		SettingScreen,
		GamePVP,
		GamePVE,
		PveEndScreen,
		EndScreen,
		PveSettingScreen,
	};

	void switchScreen(Screen newScreen);

	Board* board;
	GameScreen* currentScreen;
	GameScreen* nextScreen;

	int time = 60;
	double timeOut;
};