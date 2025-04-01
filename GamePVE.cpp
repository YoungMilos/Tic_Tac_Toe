#include "GamePVE.h"


void drawRect(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

GamePVE::GamePVE(StateManager* stateManager) : GameScreen(stateManager)
{
    stateManager->timeOut = stateManager->time;
    pause = false;
    createGUI();
    stateManager->board->reset();
	stateManager->board->isGamePVE = true;
}

GamePVE::~GamePVE()
{
	delete pauseButton;
	delete resumeButton;
}

void GamePVE::renderScreen()
{
    //render background
    SDL_RenderCopy(gWindow->getRenderer(), AssetManager::getInstance()->getTexture("game_pvp_background.png"), NULL, NULL);
    //render board
    stateManager->board->renderBoard();
    //render winner
    if (stateManager->board->winner != 0)
    {
        SDL_RenderCopy(gWindow->getRenderer(), stateManager->board->win_case, NULL, &stateManager->board->rect);
    }
    //render time
    SDL_Texture* text;
    SDL_Rect time_rect;
    std::stringstream ss;
    ss << "Thinking time: ";
    ss << (int)stateManager->timeOut;
    std::string time = ss.str();
    text = AssetManager::getInstance()->getTexturefromText(time + ",orange-juice-2.0.ttf,60,255,255,255");
    SDL_QueryTexture(text, NULL, NULL, &time_rect.w, &time_rect.h);
    time_rect.x = (SCREEN_WIDTH - time_rect.w) / 2;
    time_rect.y = 10;
    SDL_RenderCopy(gWindow->getRenderer(), text, NULL, &time_rect);
    //render button



    renderWidget();

    if (pause)
    {
        resumeButton->render();
    }
    else
    {
        pauseButton->render();
    }
}

void GamePVE::updateScreen(float deltaTime)
{
    stateManager->timeOut -= deltaTime;
    if (stateManager->timeOut < 0)
    {
        stateManager->board->winner = stateManager->board->nextMove;
    }

    if (stateManager->board->winner != 0)
    {
        SDL_Delay(2000);
        stateManager->switchScreen(StateManager::Screen::PveEndScreen);
    }
}

void GamePVE::handleEvent(const SDL_Event& event)
{
    if (pause)
    {
        resumeButton->handleEvent(event);
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
        {
            pause = false;
        }
    }
    else
    {
        pauseButton->handleEvent(event);
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
        {
            pause = true;
        }
        
        if (stateManager->board->nextMove == X_CELL)
        {
            stateManager->board->handleBoardEvent();
        }

        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            stateManager->board->handleBoardEvent();
            
            /*
            if (stateManager->board->nextMove == 1)
            {
                int tmp_board[BOARD_WIDTH][BOARD_HEIGHT];
                int** tmp_board_ptr = new int* [BOARD_WIDTH];
                for (int i = 0; i < BOARD_WIDTH; i++)
                {
                    tmp_board_ptr[i] = new int[BOARD_HEIGHT];
                }

                stateManager->board->getGameBoard(tmp_board_ptr);
                for (int i = 0; i < BOARD_WIDTH; i++)
                {
                    for (int j = 0; j < BOARD_HEIGHT; j++)
                    {
                        tmp_board[i][j] = tmp_board_ptr[i][j];
						cout << tmp_board[i][j] << " ";
                    }
                    cout << endl;
                }
				pair<int, int> AI_move = gomokuAI->bestMove(tmp_board);
				stateManager->board->move(AI_move.first, AI_move.second);
			}
            */
            if (stateManager->board->moved)
            {
                stateManager->timeOut = stateManager->time;
                stateManager->board->moved = false;
            }
        }
    }
    handleWidgetEvent(event);
}

void GamePVE::createGUI()
{
    createButton("button_home.png", { 1090, 10 }, std::bind(&GamePVE::goToMenu, this));
    pauseButton = new Button("button_pause.png", { 115, 15 }, std::bind(&GamePVE::switchPause, this));
    resumeButton = new Button("button_resume.png", { 115, 15 }, std::bind(&GamePVE::switchPause, this));
}

void GamePVE::goToMenu()
{
    stateManager->switchScreen(StateManager::Screen::StartScreen);
}

void GamePVE::switchPause()
{
    if (pause)
    {
        pause = false;
    }
    else
    {
        pause = true;
    }
}
