#pragma once

#include <vector>

#include "GameScreen.h"
#include "Window.h"
#include "GUIComponent.h"
#include "Button.h"

extern Window* gWindow;

class StartScreen : public GameScreen
{
public:
    StartScreen(StateManager* stateManager);
    ~StartScreen();
    void renderScreen();
    void updateScreen(float deltaTime);
    void handleEvent(const SDL_Event& event);
private:
    void createGUI();
    void startPVPGame();
    void exitGame();
    void switchAudioMode();
};