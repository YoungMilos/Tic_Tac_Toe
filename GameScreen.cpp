#include "GameScreen.h"

GameScreen::GameScreen()
{
}

GameScreen::GameScreen(StateManager* stateManager) :
	stateManager(stateManager)
{
	createGUI();
}

GameScreen::~GameScreen()
{
}

void GameScreen::renderScreen()
{
	renderWidget();
}

void GameScreen::updateScreen(float deltaTime)
{
}

void GameScreen::loadMedia()
{
}

void GameScreen::handleEvent(const SDL_Event& event)
{

}

void GameScreen::createGUI()
{
}

void GameScreen::renderWidget()
{
	for (auto component : GUIComponents)
	{
		component->render();
	}
}

void GameScreen::handleWidgetEvent(const SDL_Event& event)
{
	for (auto component : GUIComponents)
	{
		component->handleEvent(event);
	}
}

void GameScreen::createButton(const std::string fileName, SDL_Point position, std::function<void()> callback)
{
	GUIComponent* button = new Button(fileName, position, callback);
	GUIComponents.push_back(button);
}