#pragma once

#include <functional>
#include "GameScreen.h"

extern bool gQuit;

class EndScreen : public GameScreen
{
public:
    EndScreen(StateManager* stateManager);
    ~EndScreen();
    void handleEvent(const SDL_Event& event);
    void renderScreen();
    void updateScreen(float deltaTime);
private:
    void createGUI();
    void goToMenu();
    void goToGame();
    double timePauseMusic;
};