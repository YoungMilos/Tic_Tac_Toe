#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Settings.h"

class Window
{
public:
	Window();
	~Window();
	bool init();
	SDL_Renderer* getRenderer() const;
	void clear() const;
	void present() const;
	void free();

private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};
