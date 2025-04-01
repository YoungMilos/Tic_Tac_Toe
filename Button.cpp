#include "Button.h"
#include <iostream> 

Button::Button(const std::string fileName_, SDL_Point position, std::function<void()> callback_)
{
    rect.x = position.x;
    rect.y = position.y;
    SDL_QueryTexture(AssetManager::getInstance()->getTexture(fileName_), NULL, NULL, &rect.w, &rect.h);
    fileName = fileName_;
    callback = callback_;
    buttonSound = AssetManager::getInstance()->getSoundBuffer("button_click_sound.wav");
}

Button::~Button()
{
	Mix_FreeChunk(buttonSound);
}

bool Button::isSelectable()
{
    return true;
}

void Button::handleEvent(const SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        if (e.button.button == SDL_BUTTON_LEFT)
        {
            if (e.button.x >= rect.x && e.button.x <= rect.x + rect.w && e.button.y >= rect.y && e.button.y <= rect.y + rect.h)
            {
                if (gSoundOn)
                    Mix_PlayChannel(-1, buttonSound, 0);
                callback();
            }
        }
    }
}

void Button::render()
{
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture(fileName), NULL, &rect);
}