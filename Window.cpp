#include "Window.h"

Window::Window()
{
    this->window = NULL;
    this->renderer = NULL;
}

Window::~Window()
{
    free();
}

bool Window::init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;
    }
    window = SDL_CreateWindow("Top Down Shooter", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 164, 69, 255);
    }
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;
        return false;
    }
    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

SDL_Renderer* Window::getRenderer() const
{
    return this->renderer;
}

void Window::present() const
{
    SDL_RenderPresent(this->renderer);
}

void Window::clear() const
{
    SDL_SetRenderDrawColor(renderer, 0, 164, 69, 255);
    SDL_RenderClear(this->renderer);
}

void Window::free()
{
    if (this->renderer != NULL)
    {
        SDL_DestroyRenderer(this->renderer);
        this->renderer = NULL;
    }
    if (this->window != NULL)
    {
        SDL_DestroyWindow(this->window);
        this->window = NULL;
    }
}