#pragma once

#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


class AssetManager
{
public:
	static AssetManager* getInstance();
	static SDL_Texture*& getTexture(std::string const& filename);
	static SDL_Texture*& getTexturefromText(std::string const& text_font_size_r_g_b);
	static TTF_Font*& getFont(std::string const& font_size);
	static Mix_Chunk*& getSoundBuffer(std::string const& filename);
	static int**& getMap(std::string const& filename);

private:
	AssetManager();
	~AssetManager();

	std::map<std::string, SDL_Texture*> managerTextures;
	std::map<std::string, TTF_Font*> managerFonts;
	std::map<std::string, Mix_Chunk*> managerSoundBuffers;
	std::map<std::string, int**> managerMaps;
	static AssetManager* singletonInstance;
};
