#pragma once

#include "Window.h"
#include "StartScreen.h"

class StateManager;

class Game
{
public:
    Game();
    ~Game();
    void run();
private:
    void processInput();
    void update(float deltaTime);
    void render();

    void renderScreen();

    StateManager* stateManager;

    Button* musicOn;
    Button* musicOff;
    Button* soundOn;
    Button* soundOff;
    void switchMusic();
    void switchAudio();
};