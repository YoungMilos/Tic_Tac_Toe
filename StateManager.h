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
		EndScreen,
	};

	void switchScreen(Screen newScreen);

	Board* board;

	GameScreen* currentScreen;
	GameScreen* nextScreen;
};