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
    int** map;
    void createGUI();
    void goToMenu();
    double timeOut;
    double startingTime;
    int maxScore;
    bool pause;

    Button* pauseButton;
    Button* resumeButton;
    void switchPause();
    void createItem();
};