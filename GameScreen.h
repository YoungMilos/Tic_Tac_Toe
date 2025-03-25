#pragma once

#include <vector>

#include "SDL.h"

#include "StateManager.h"
#include "GUIComponent.h"
#include "Button.h"

class GameScreen
{
public:
    GameScreen();
    GameScreen(StateManager* stateManager);
    virtual ~GameScreen();
    virtual void renderScreen();
    virtual void updateScreen(float deltaTime) = 0;

    //TODO: remove
    virtual void loadMedia();
    virtual void handleEvent(const SDL_Event& event);

protected:
    StateManager* stateManager;
    std::vector<GUIComponent*> GUIComponents;
    virtual void createGUI();
    void createButton(const std::string fileName, SDL_Point position, std::function<void()> callback);
    void renderWidget();
    void handleWidgetEvent(const SDL_Event& event);
};