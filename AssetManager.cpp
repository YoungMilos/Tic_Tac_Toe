#include "AssetManager.h"
#include "Settings.h"
#include "Window.h"

extern Window* gWindow;

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	delete singletonInstance;
}

AssetManager* AssetManager::singletonInstance;

AssetManager* AssetManager::getInstance()
{
	if (singletonInstance == NULL)
	{
		singletonInstance = new AssetManager();
	}
	return singletonInstance;
}

SDL_Texture*& AssetManager::getTexture(std::string const& filename)
{
	std::map<std::string, SDL_Texture*>& textureMap = singletonInstance->managerTextures;

	std::map<std::string, SDL_Texture*>::iterator pairFound = textureMap.find(filename);
	if (pairFound != textureMap.end())
	{
		return pairFound->second;
	}
	else
	{
		SDL_Texture*& texture = textureMap[filename];
		SDL_Surface* loadedSurface = IMG_Load((GRAPHICS_PATH + filename).c_str());
		if (loadedSurface == NULL)
		{
			std::cout << "Failed to load image: " << filename << std::endl;
			std::cout << "Error: " << IMG_GetError() << std::endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
			SDL_FreeSurface(loadedSurface);
			if (texture == NULL)
			{
				std::cout << "Failed to create texture: " << filename << std::endl;
				std::cout << "Error: " << SDL_GetError() << std::endl;
			}
		}
		return texture;
	}
}

SDL_Texture*& AssetManager::getTexturefromText(std::string const& text_font_size_r_g_b)
{
	std::map<std::string, SDL_Texture*>& textureMap = singletonInstance->managerTextures;

	std::map<std::string, SDL_Texture*>::iterator pairFound = textureMap.find(text_font_size_r_g_b);
	if (pairFound != textureMap.end())
	{
		return pairFound->second;
	}
	else
	{
		SDL_Texture*& texture = textureMap[text_font_size_r_g_b];
		std::stringstream ss;
		ss << text_font_size_r_g_b;
		std::string text;
		std::string fontName;
		std::string fontSize;
		std::string r_;
		std::string g_;
		std::string b_;
		std::getline(ss, text, ',');
		std::getline(ss, fontName, ',');
		std::getline(ss, fontSize, ',');
		std::getline(ss, r_, ',');
		std::getline(ss, g_, ',');
		std::getline(ss, b_, ',');
		Uint8 r = std::stoi(r_);
		Uint8 g = std::stoi(g_);
		Uint8 b = std::stoi(b_);
		SDL_Color textColor = { r, g, b };
		SDL_Surface* loadedSurface = TTF_RenderText_Solid(getFont(fontName + "," + fontSize), text.c_str(), textColor);
		if (loadedSurface == NULL)
		{
			std::cout << "Failed to load text: " << text_font_size_r_g_b << std::endl;
			std::cout << "Error: " << TTF_GetError() << std::endl;
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(gWindow->getRenderer(), loadedSurface);
			SDL_FreeSurface(loadedSurface);
			if (texture == NULL)
			{
				std::cout << "Failed to create texture: " << text_font_size_r_g_b << std::endl;
				std::cout << "Error: " << SDL_GetError() << std::endl;
			}
		}
		return texture;
	}
}

TTF_Font*& AssetManager::getFont(std::string const& font_size)
{
	std::map<std::string, TTF_Font*>& fontMap = singletonInstance->managerFonts;

	std::map<std::string, TTF_Font*>::iterator pairFound = fontMap.find(font_size);
	if (pairFound != fontMap.end())
	{
		return pairFound->second;
	}
	else
	{
		TTF_Font*& font = fontMap[font_size];
		std::stringstream ss;
		ss.str(font_size);
		std::string fontName;
		std::getline(ss, fontName, ',');
		int fontSize;
		ss >> fontSize;
		font = TTF_OpenFont((FONTS_PATH + fontName).c_str(), fontSize);
		if (font == NULL)
		{
			std::cout << "Failed to load font: " << font_size << std::endl;
			std::cout << "Error: " << TTF_GetError() << std::endl;
		}
		return font;
	}
}

Mix_Chunk*& AssetManager::getSoundBuffer(std::string const& filename)
{
	std::map<std::string, Mix_Chunk*>& soundBufferMap = singletonInstance->managerSoundBuffers;

	std::map<std::string, Mix_Chunk*>::iterator pairFound = soundBufferMap.find(filename);
	if (pairFound != soundBufferMap.end())
	{
		return pairFound->second;
	}
	else
	{
		Mix_Chunk*& soundBuffer = soundBufferMap[filename];
		soundBuffer = Mix_LoadWAV((AUDIO_PATH + filename).c_str());
		if (soundBuffer == NULL)
		{
			std::cout << "Failed to load sound: " << filename << std::endl;
			std::cout << "Error: " << Mix_GetError() << std::endl;
		}
		return soundBuffer;
	}
}

int**& AssetManager::getMap(std::string const& filename)
{
	std::map<std::string, int**>& mapMap = singletonInstance->managerMaps;

	std::map<std::string, int**>::iterator pairFound = mapMap.find(filename);
	if (pairFound != mapMap.end())
	{
		return pairFound->second;
	}
	else
	{
		int**& map = mapMap[filename];
		std::ifstream file((MAPS_PATH + filename).c_str());
		if (file.is_open())
		{
			int width, height;
			file >> width >> height;
			map = new int* [height];
			for (int i = 0; i < height; i++)
			{
				map[i] = new int[width];
				for (int j = 0; j < width; j++)
				{
					file >> map[i][j];
				}
			}
			file.close();
		}
		else
		{
			std::cout << "Failed to load map: " << filename << std::endl;
		}
		return map;
	}
}