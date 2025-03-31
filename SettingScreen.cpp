#include "SettingScreen.h"

SettingScreen::SettingScreen(StateManager* stateManager) : GameScreen(stateManager)
{
	createGUI();
	stateManager->board = new Board();
	cell_o_assets.push_back("cell_o.png");
	cell_o_assets.push_back("cell_o_2.png");

	cell_x_assets.push_back("cell_x.png");
	cell_x_assets.push_back("cell_x_2.png");

	x_rect = new SDL_Rect();
	o_rect = new SDL_Rect();
	x_rect->x = SCREEN_WIDTH/2-40;
	x_rect->y = 200;
	x_rect->w = 80;
	x_rect->h = 80;

	o_rect->x = SCREEN_WIDTH/2-40;
	o_rect->y = 300;
	o_rect->w = 80;
	o_rect->h = 80;
}


SettingScreen::~SettingScreen()
{
	cell_x_assets.clear();
	cell_o_assets.clear();
}

void SettingScreen::renderScreen()
{
	//render background
	SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("setting_screen_background.png"), NULL, NULL);
	// render cell
	SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->cell_x, NULL, x_rect);
	SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->cell_o, NULL, o_rect);
	//render button
	renderWidget();
}

void SettingScreen::updateScreen(float deltaTime)
{
}

void SettingScreen::handleEvent(const SDL_Event& event)
{
	handleWidgetEvent(event);
}

void SettingScreen::createGUI()
{
	createButton("button_start.png", { 555, 500 }, std::bind(&SettingScreen::startGame, this));
	createButton("button_back.png", { 555, 570 }, std::bind(&SettingScreen::gotoMenu, this));
	createButton("button_right.png", { 800, 200 }, std::bind(&SettingScreen::changeX, this, true));
	createButton("button_left.png", { 400, 200 }, std::bind(&SettingScreen::changeX, this, false));
	createButton("button_right.png", { 800, 300 }, std::bind(&SettingScreen::changeO, this, true));
	createButton("button_left.png", { 400, 300 }, std::bind(&SettingScreen::changeO, this, false));
}

void SettingScreen::gotoMenu()
{
	stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void SettingScreen::changeX(bool increase)
{
	if (increase)
	{
		x_pos = (x_pos + 1 + cell_x_assets.size()) % cell_x_assets.size();
		stateManager->board->cell_x = AssetManager::getInstance()->getTexture(cell_x_assets[x_pos]);
	}
	else
	{
		x_pos = (x_pos - 1 + cell_x_assets.size()) % cell_x_assets.size();
		stateManager->board->cell_x = AssetManager::getInstance()->getTexture(cell_x_assets[x_pos]);
	}
}

void SettingScreen::changeO(bool increase)
{
	if (increase)
	{
		o_pos = (o_pos + 1 + cell_o_assets.size()) % cell_o_assets.size();
		stateManager->board->cell_o = AssetManager::getInstance()->getTexture(cell_o_assets[o_pos]);
	}
	else
	{
		o_pos = (o_pos - 1 + cell_o_assets.size()) % cell_o_assets.size();
		stateManager->board->cell_o = AssetManager::getInstance()->getTexture(cell_o_assets[o_pos]);
	}
}

void SettingScreen::startGame()
{
	stateManager->switchScreen(StateManager::Screen::GamePVP);
}





