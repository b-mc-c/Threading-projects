// Threading.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SDL.h>			//SDL
#include <chrono>

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

int frameCounter = 0;
float frameTimer = 0;

SDL_Thread *consumer = NULL;
SDL_Thread *producer = NULL;

int Consumer(void *data);
int  Producer(void *data);

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

			bool quit = false;
			Init();

			SoundManager::GetInstance()->play(SoundManager::GAME_SOUND_TRACK);

			float time = 0;
			// put this as close as possible to the start of the loop (before it starts!)

			// Timing variables
			Uint32 old_time, current_time;
			float ftime;

			// Need to initialize this here for event loop to work
			current_time = SDL_GetTicks();

			int data = 101;
			consumer = SDL_CreateThread(Consumer, "consumer", (void*)data);
			producer = SDL_CreateThread(Producer, "producer", (void*)data);

			SDL_Event e;
			while (!quit)
			{
				 
				// Update the timing information
				old_time = current_time;
				current_time = SDL_GetTicks();
				ftime = (current_time - old_time) / 1000.0f;
				//cout << ftime << endl;

				

				//cout << "fps : " << 1 / ftime  << endl;
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

				

			}//end while quit
		}//end else
	}//end else
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
int Producer(void *data)
{
	while (!quit)
	{
		pair<bool, int> c = EnemyManager::GetInstance()->IsColiding(play->player);
		if (c.first)
		{
			play->boundedBuf.Deposit(to_string(c.second));
		}
	}
	return 0;
}
int  Consumer(void *data)
{
	while (true)
	{
		string s = "";
		play->boundedBuf.Fetch(s);
		cout << s << endl;
		SDL_Delay(100 + rand() % 32);
	}
	return 0;
}