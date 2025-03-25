#include <SDL_image.h>

#include "StartScreen.h"

extern bool gQuit;

StartScreen::StartScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
}

StartScreen::~StartScreen()
{
}

void StartScreen::renderScreen()
{
    //render Background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("start_screen_background.png"), NULL, NULL);
    renderWidget();
}

void StartScreen::updateScreen(float deltaTime)
{
}

void StartScreen::handleEvent(const SDL_Event& event)
{
    for (auto& component : GUIComponents)
    {
        component->handleEvent(event);
    }
}

void StartScreen::createGUI()
{
    createButton("button_pvp.png", { 555, 400 }, std::bind(&StartScreen::startPVPGame, this));
    createButton("button_exit.png", { 555, 480 }, []() { gQuit = true; });
}

void StartScreen::startPVPGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVP);
}


void StartScreen::exitGame()
{
    //stateManager->exitGame();
    std::cout << "Exiting game..." << std::endl;
}

void StartScreen::switchAudioMode()
{
    std::cout << "Audio mode switched" << std::endl;
}
