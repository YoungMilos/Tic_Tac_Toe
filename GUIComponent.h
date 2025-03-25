#pragma once
#pragma once

#include <SDL.h>
#include "AssetManager.h"

class GUIComponent
{
public:
    GUIComponent();
    ~GUIComponent();

    virtual bool isSelectable() = 0;
    virtual void handleEvent(const SDL_Event& e);
    virtual void render();

protected:
    SDL_Rect rect;
};