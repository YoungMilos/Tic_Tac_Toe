#pragma once

#include "GameScreen.h"
#include "Board.h"
#include "StateManager.h"
#include "Settings.h"
#include "Window.h"
#include "Button.h"
#include "GUIComponent.h"


#include <vector>

extern Window* gWindow;
extern bool gDevMode;

class SettingScreen : public GameScreen
{
public:
    SettingScreen(StateManager* stateManager);
    ~SettingScreen();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);

private:
	std::vector <std::string> cell_x_assets;
	std::vector <std::string> cell_o_assets;
	std::vector <std::string> time_assets;

	void createGUI();
	void gotoMenu();
	void changeX(bool increase);
	void changeO(bool increase);
	void changeTime(bool increase);
	void startGame();

	SDL_Rect* x_rect;
	SDL_Rect* o_rect;

	int x_pos = 0;
	int o_pos = 0;
	int time_pos;

    Board* board;
};