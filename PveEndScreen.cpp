#include "PveEndScreen.h"

PveEndScreen::PveEndScreen(StateManager* stateManager) : GameScreen(stateManager)
{
    createGUI();
    Mix_Chunk* sound = AssetManager::getInstance()->getSoundBuffer("end_screen_sound.wav");
    if (gSoundOn) Mix_PlayChannel(-1, sound, 0);
    if (!Mix_PausedMusic())
    {
        Mix_PauseMusic();
        timePauseMusic = 5;
    }
    else
    {
        timePauseMusic = -1;
    }
}

PveEndScreen::~PveEndScreen()
{

}

void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

void PveEndScreen::renderScreen()
{
    //load background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("pve_end_screen_background.png"), NULL, NULL);
    renderWidget();

    //render winner


    SDL_Texture* text;
    SDL_Rect text_rect;
	if (stateManager->board->winner == 1) {
		text = AssetManager::getInstance()->getTexturefromText("you win,orange-juice-2.0.ttf,120,255,255,255");
	}
	else if (stateManager->board->winner == 2)
	{
		text = AssetManager::getInstance()->getTexturefromText("computer win,orange-juice-2.0.ttf,120,255,255,255");
	}
	else
	{
		text = AssetManager::getInstance()->getTexturefromText("Draw,orange-juice-2.0.ttf,120,255,255,255");
	}
    
    SDL_QueryTexture(text, NULL, NULL, &text_rect.w, &text_rect.h);
    text_rect.x = (SCREEN_WIDTH - text_rect.w) / 2;
    text_rect.y = (SCREEN_HEIGHT-text_rect.h)/2;
    SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &text_rect);
}

void PveEndScreen::updateScreen(float deltaTime)
{
    if (timePauseMusic != -1)
    {
        timePauseMusic -= deltaTime;
        if (timePauseMusic < 0 && Mix_PausedMusic())
        {
            Mix_ResumeMusic();
        }
    }
}

void PveEndScreen::handleEvent(const SDL_Event& event)
{
    handleWidgetEvent(event);
}

void PveEndScreen::createGUI()
{
    createButton("button_restart.png", { 555, 500 }, std::bind(&PveEndScreen::goToGame, this));
    createButton("button_exit.png", { 555, 570 }, []() { gQuit = true; });
    createButton("button_home.png", { 1090, 10 }, std::bind(&PveEndScreen::goToMenu, this));
}

void PveEndScreen::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void PveEndScreen::goToGame()
{
    stateManager->switchScreen(StateManager::Screen::GamePVE);
}