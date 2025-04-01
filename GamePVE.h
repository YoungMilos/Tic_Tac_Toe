#pragma once

#include <vector>
//#include "AI.h"
#include "GameScreen.h"


extern Window* gWindow;
extern bool gDevMode;

class GamePVE : public GameScreen
{
public:
    GamePVE(StateManager* stateManager);
    ~GamePVE();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
private:
    void createGUI();
    void goToMenu();
    bool pause;
//    GomokuAI* gomokuAI;

    Button* pauseButton;
    Button* resumeButton;
    void switchPause();
    void createItem();
};