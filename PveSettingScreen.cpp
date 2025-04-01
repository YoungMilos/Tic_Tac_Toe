#include "PveSettingScreen.h"

PveSettingScreen::PveSettingScreen(StateManager* stateManager) : GameScreen(stateManager)
{

	createGUI();
	stateManager->board = new Board();
	cell_o_assets.push_back("cell_o.png");
	cell_o_assets.push_back("cell_o_2.png");

	cell_x_assets.push_back("cell_x.png");
	cell_x_assets.push_back("cell_x_2.png");

	x_rect = new SDL_Rect();
	o_rect = new SDL_Rect();
	x_rect->x = SCREEN_WIDTH / 2 - 40;
	x_rect->y = 200;
	x_rect->w = 80;
	x_rect->h = 80;

	o_rect->x = SCREEN_WIDTH / 2 - 40;
	o_rect->y = 300;
	o_rect->w = 80;
	o_rect->h = 80;

	stateManager->time = 60;
}


PveSettingScreen::~PveSettingScreen()
{
	cell_x_assets.clear();
	cell_o_assets.clear();
}

void PveSettingScreen::renderScreen()
{
	//render background
	SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("setting_screen_background.png"), NULL, NULL);
	// render cell
	SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->cell_x, NULL, x_rect);
	SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->cell_o, NULL, o_rect);
	//render button
	renderWidget();

	//render time
	SDL_Texture* text;
	SDL_Rect time_rect;



	int settingTime = stateManager->time;
	std::stringstream ss;
	ss << "Time: ";
	ss << settingTime;
	std::string time = ss.str();
	text = AssetManager::getInstance()->getTexturefromText(time + ",orange-juice-2.0.ttf,60,255,255,255");
	SDL_QueryTexture(text, NULL, NULL, &time_rect.w, &time_rect.h);
	time_rect.x = (SCREEN_WIDTH - time_rect.w) / 2;
	time_rect.y = 410;
	SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &time_rect);
}

void PveSettingScreen::updateScreen(float deltaTime)
{
}

void PveSettingScreen::handleEvent(const SDL_Event& event)
{
	handleWidgetEvent(event);
}

void PveSettingScreen::createGUI()
{
	createButton("button_start.png", { 555, 500 }, std::bind(&PveSettingScreen::startGame, this));
	createButton("button_back.png", { 555, 570 }, std::bind(&PveSettingScreen::gotoMenu, this));
	createButton("button_right.png", { 800, 200 }, std::bind(&PveSettingScreen::changeX, this, true));
	createButton("button_left.png", { 400, 200 }, std::bind(&PveSettingScreen::changeX, this, false));
	createButton("button_right.png", { 800, 300 }, std::bind(&PveSettingScreen::changeO, this, true));
	createButton("button_left.png", { 400, 300 }, std::bind(&PveSettingScreen::changeO, this, false));
	createButton("button_right.png", { 800, 400 }, std::bind(&PveSettingScreen::changeTime, this, true));
	createButton("button_left.png", { 400, 400 }, std::bind(&PveSettingScreen::changeTime, this, false));
}

void PveSettingScreen::gotoMenu()
{
	stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void PveSettingScreen::changeX(bool increase)
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

void PveSettingScreen::changeO(bool increase)
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

void PveSettingScreen::changeTime(bool increase)
{
	if (increase)
	{
		if (stateManager->time < 120) stateManager->time++;
	}
	else
	{
		if (stateManager->time > 30) stateManager->time--;
	}
}


void PveSettingScreen::startGame()
{
	stateManager->switchScreen(StateManager::Screen::GamePVE);
}