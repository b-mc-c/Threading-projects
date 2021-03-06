// Threading.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>			//SDL
#include <SDL_thread.h>
#include "SoundManager.h"
#include "Menu.h"
#include "Play.h"
#include "ScoreScreen.h"

//Screen dimension constants
const int SCREEN_WIDTH = 1248;			//SDL
const int SCREEN_HEIGHT = 704;			//SDL

//gamestates
Menu* menu;
Play* play;
ScoreScreen* scoreScreen;

bool quit;

//methods
void Init();
void ClearPointers();
int  AiThread(void *data);
int  PhysicsThread(void *data);

//The thread that will be used
SDL_Thread *aIThread = NULL;
SDL_Thread *phsicsThread = NULL;

int gameTick = 0;

int frameCounter = 0;
float frameTimer = 0;

bool updateAI = false;
bool updatePhysics = false;



int _tmain(int argc, _TCHAR* argv[])
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//SDL
#pragma region SDL STUFF
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create Renderer for the Window
			if (!Renderer::GetInstance()->Init(window, SCREEN_WIDTH, SCREEN_HEIGHT))
			{
				return 0;
			}

			quit = false;
			Init();

			SoundManager::GetInstance()->play(SoundManager::GAME_SOUND_TRACK);

			// put this as close as possible to the start of the loop (before it starts!)

			// Timing variables
			Uint32 old_time, current_time;
			float ftime;

			// Need to initialize this here for event loop to work
			current_time = SDL_GetTicks();

			//start the ai thread
			int data = 101;
			aIThread = SDL_CreateThread(AiThread, "AiThread", (void*)play);
			phsicsThread = SDL_CreateThread(PhysicsThread, "PhysicsThread", (void*)data);

			SDL_Event e;
			while (!quit)
			{
				 
				// Update the timing information
				old_time = current_time;
				current_time = SDL_GetTicks();
				ftime = (current_time - old_time) / 1000.0f;
				//cout << ftime << endl;
				//printf("fps : %f\n",1/ftime);
				frameTimer += ftime;
				if (frameTimer >= 1)
				{
					if (frameTimer >= 2)
					{
						printf("fps : is less than 1 per second \n");
					}
					else
					{
						printf("fps : %i\n", frameCounter);
					}
					frameTimer = 0;
					frameCounter = 0;
				}
				frameCounter++;


				//cout << "fps : " << 1 / ftime << endl;
				while (SDL_PollEvent(&e) != 0){
					KeyBoardInput::GetInstance()->updateKeyboard(e);
					switch (e.type)
					{
					case SDL_QUIT:
						quit = true;
						break;

					}
				}
				//controls gameState added in game menu feature
				switch (GameStateController::GetInstance()->getGameState())
				{
				case GameStateController::MENU:
					//updateMenu
					menu->Update();
					//draw menu
					menu->Draw();
					break;
				case GameStateController::PLAY:
					//update play 
					play->Update(ftime);
					//draw gane
					play->Draw();
					break;
				case GameStateController::SCORESCREEN:
					//update splash 
					scoreScreen->Update();
					//draw splash
					scoreScreen->Draw();

					break;
				}//end switch
				if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_ESCAPE))
				{
					quit = true;
				}

				// Escape button
				
				//SDL_Delay(500); // 500 should make 2 frames per second.

				
				gameTick++;
				if (gameTick % 300 == 0)
				{
					 updateAI = true;
					 updatePhysics = false;
				}
				else if(gameTick % 50 == 0)
				{
					 updateAI = false;
					 updatePhysics = true;
				}

				


			}//end while quit
		}//end else
	}//end else


	//Remove timer in case the call back was not called
	SDL_WaitThread(aIThread, NULL);
	SDL_WaitThread(phsicsThread, NULL);

	return 0;
}

void Init()
{

	quit = false;
	menu = new Menu(SCREEN_WIDTH, SCREEN_HEIGHT);
	scoreScreen = new ScoreScreen(SCREEN_WIDTH, SCREEN_HEIGHT);;
	play = new Play( SCREEN_WIDTH, SCREEN_HEIGHT);
	GameStateController::GetInstance()->SetGameState(GameStateController::PLAY);
	if (!SoundManager::GetInstance()->load_files())
	{
		printf("Sounds Did not load ");
	}



}

void ClearPointers()
{
	delete menu;
	delete play;
	delete scoreScreen;
}


int AiThread(void *data)
{
	//While the program is not over
	Play* p = (Play*)data;
	while (!quit)
	{
		if (updateAI)
		{
			switch (GameStateController::GetInstance()->getGameState())
			{
			case GameStateController::PLAY:
				EnemyManager::GetInstance()->UpdateAI(p->getPlayer());
				//printf("Running thread AI \n");
				break;
			}//end switch
		}	
	}
	printf("Stopping thread AI \n");
	return 0;
}
int  PhysicsThread(void *data)
{
	//While the program is not over
	Play* p = (Play*)data;
	Uint32 old_t, current_t;
	float ft;

	// Need to initialize this here for event loop to work
	current_t = SDL_GetTicks();

	while (!quit)
	{
		if (updatePhysics)
		{
			old_t = current_t;
			current_t = SDL_GetTicks();
			ft = (current_t - old_t) / 1000.0f;
			switch (GameStateController::GetInstance()->getGameState())
			{

			case GameStateController::PLAY:
				EnemyManager::GetInstance()->UpdatePyhsics(ft);
				//printf("Running thread Physics \n");
				break;
			}//end switch
		}
	}
	printf("Stopping thread Physics \n");
	return 0;
}