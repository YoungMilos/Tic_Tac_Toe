#include "GamePVP.h"


void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

GamePVP::GamePVP(StateManager* stateManager) : GameScreen(stateManager)
{
	pause = false;
	createGUI();
	board = new Board();
}

GamePVP::~GamePVP()
{
}

void GamePVP::renderScreen()
{
    //render background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("game_pvp_background.png"), NULL, NULL);
	//render board
	board->renderBoard();

    // std::cout << std::endl;
    renderWidget();


    if (pause)
    {
        resumeButton->render();
    }
    else
    {
        pauseButton->render();
    }
}

void GamePVP::updateScreen(float deltaTime)
{
    if (board->winner != 0)
    {
		stateManager->switchScreen(StateManager::Screen::EndScreen);
    }
}

void GamePVP::handleEvent(const SDL_Event& event)
{
    if (!(startingTime > 0))
    {


        if (pause)
        {
            resumeButton->handleEvent(event);
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pause = false;
            }
        }
        else
        {
            pauseButton->handleEvent(event);
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
            {
                pause = true;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                board->handleBoardEvent();
            }
        }
    }
    handleWidgetEvent(event);

}

void GamePVP::createGUI()
{
    createButton("button_home.png", { 1230, 752 }, std::bind(&GamePVP::goToMenu, this));
    pauseButton = new Button("button_pause.png", { 115, 15 }, std::bind(&GamePVP::switchPause, this));
    resumeButton = new Button("button_resume.png", { 115, 15 }, std::bind(&GamePVP::switchPause, this));
}

void GamePVP::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void GamePVP::switchPause()
{
    if (pause)
    {
        pause = false;
    }
    else
    {
        pause = true;
    }
}
