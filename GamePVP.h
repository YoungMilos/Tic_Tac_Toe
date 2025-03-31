#pragma once

#include <vector>

#include "GameScreen.h"
#include "Board.h"



extern Window* gWindow;
extern bool gDevMode;

class GamePVP : public GameScreen
{
public:
    GamePVP(StateManager* stateManager);
    ~GamePVP();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
private:
    void createGUI();
    void goToMenu();
    bool pause;

    Button* pauseButton;
    Button* resumeButton;
    void switchPause();
    void createItem();
};