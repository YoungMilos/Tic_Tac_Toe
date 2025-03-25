#include <iostream>

#include <SDL.h>

#include "Game.h"
#include "Button.h"

Window* gWindow = NULL;
bool gQuit = false;
bool gDevMode = false;
bool gSoundOn = true;

Game::Game()
{
    gWindow = new Window();
    if (!gWindow->init())
    {
        std::cout << "Failed to initialize window" << std::endl;
        gQuit = true;
        return;
    }
    stateManager = new StateManager();
    gQuit = false;
    musicOn = new Button("button_music_on.png", { 1230, 10 }, std::bind(&Game::switchMusic, this));
    musicOff = new Button("button_music_off.png", { 1230, 10 }, std::bind(&Game::switchMusic, this));
    soundOn = new Button("button_sound_on.png", { 1190, 10 }, std::bind(&Game::switchAudio, this));
    soundOff = new Button("button_sound_off.png", { 1190, 10 }, std::bind(&Game::switchAudio, this));
}

Game::~Game()
{
	delete stateManager;
	delete gWindow;
	delete musicOn;
	delete musicOff;
	delete soundOn;
	delete soundOff;
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::run()
{
    Mix_Music* music = Mix_LoadMUS(AUDIO_PATH  "music.wav");
    Mix_PlayMusic(music, -1);
    stateManager->switchScreen(StateManager::Screen::StartScreen);
    Uint32 deltaTime = SDL_GetTicks();
    while (!gQuit)
    {
        processInput();
        update((SDL_GetTicks() - deltaTime) / 1000.0f);
        deltaTime = SDL_GetTicks();
        render();
    }
}

void Game::processInput()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            gQuit = true;
        }
        else
        {
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_F11)
            {
                gDevMode = !gDevMode;
            }
            stateManager->currentScreen->handleEvent(e);
        }
        if (Mix_PlayingMusic())
        {
            musicOn->handleEvent(e);
        }
        else
        {
            musicOff->handleEvent(e);
        }
        if (gSoundOn)
        {
            soundOn->handleEvent(e);
        }
        else
        {
            soundOff->handleEvent(e);
        }
    }
}

void Game::update(float deltaTime)
{
    stateManager->currentScreen->updateScreen(deltaTime);
}

void Game::render()
{
    gWindow->clear();
    renderScreen();
    if (Mix_PausedMusic())
    {
        musicOff->render();
    }
    else
    {
        musicOn->render();
    }
    if (gSoundOn)
    {
        soundOn->render();
    }
    else
    {
        soundOff->render();
    }
    gWindow->present();
}

void Game::renderScreen()
{
    stateManager->currentScreen->renderScreen();
}

void Game::switchMusic()
{
    if (Mix_PausedMusic())
    {
        Mix_ResumeMusic();
    }
    else
    {
        Mix_PauseMusic();
    }
}

void Game::switchAudio()
{
    gSoundOn = !gSoundOn;
}