#pragma once

#include <functional>
#include "GameScreen.h"

extern bool gQuit;

class PveEndScreen : public GameScreen
{
public:
    PveEndScreen(StateManager* stateManager);
    ~PveEndScreen();
    void handleEvent(const SDL_Event& event);
    void renderScreen();
    void updateScreen(float deltaTime);
private:
    void createGUI();
    void goToMenu();
    void goToGame();
    double timePauseMusic;
};
