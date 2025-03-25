#pragma once

class GameScreen;

class StateManager
{
public:
	StateManager();
	~StateManager();

	enum class Screen
	{
		StartScreen,
		GamePVP,
		EndScreen,
	};

	void switchScreen(Screen newScreen);

	GameScreen* currentScreen;
	GameScreen* nextScreen;
};