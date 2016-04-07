// ReadersWriters.cpp : Defines the entry point for the console application.
//
#include<windows.h>
#include <SDL.h>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <vector>
#include "Renderer.h"
#include <SDL_image.h>

using namespace std;

int Reader(void *data);
int Writer(void *data);
SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer);

int nr = 0;/*number of active readers*/
SDL_sem*rw =  NULL; /*lock for readers/writer exclusion*/
SDL_sem* nrLock = NULL; /*lock for readers/writer exclusion*/

//Screen dimension constants
int SCREEN_WIDTH = 1248;			//SDL
int SCREEN_HEIGHT = 704;			//SDL

list<SDL_Thread*> readerThreads;
list<SDL_Thread*> writerThreads;
vector<SDL_Rect> threadSrc;

int main(int argc, char* argv[])
{
	rw = SDL_CreateSemaphore(1);
	nrLock = SDL_CreateSemaphore(1);
	//The thread that will be used
	
	

	
	SDL_Texture* playerTexture;
	SDL_Rect playerPos = { 500, 350, 100, 100 };
	SDL_Rect playerSrc = { 0, 0, 292, 526 };
	int speed = 15;

	SDL_Texture* ballTexture;
	
	SDL_Rect ballSrc = { 0, 0, 292, 526 };
	
	vector<SDL_Rect> balls;
	balls.push_back(SDL_Rect{ 0, 0, 100, 100 });
	balls.push_back(SDL_Rect{ 1100, 0, 100, 100 });
	balls.push_back(SDL_Rect{ 0, 600, 100, 100 });
	balls.push_back(SDL_Rect{ 1100, 600, 100, 100 });

	SDL_Texture* output;
	SDL_Rect outputPos1 = { 400, 350, 50, 50 };
	SDL_Rect outputPos2 = { 600, 350, 50, 50 };


	
	threadSrc.push_back(SDL_Rect{ 0, 0, 50, 50 });
	threadSrc.push_back(SDL_Rect{ 0, 0, 50, 50 });

	//The window we'll be rendering to
	SDL_Window* window = NULL;
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create Renderer for the Window
			if (!Renderer::GetInstance()->Init(window, SCREEN_WIDTH, SCREEN_HEIGHT)) {
				return 0;
			}
			

			int i = 0;
			readerThreads.push_back(SDL_CreateThread(Reader, "AiThread", (void*)&i));
			//Wait randomly
			SDL_Delay(16 + rand() % 32);
			int t = 1;
			readerThreads.push_back(SDL_CreateThread(Reader, "AiThread", (void*)&t));
			//Wait randomly
			SDL_Delay(16 + rand() % 32);



			playerTexture = loadTexture("player.png", Renderer::GetInstance()->Get_SDL_RENDERER());

			ballTexture = loadTexture("ball.png", Renderer::GetInstance()->Get_SDL_RENDERER());

			output = loadTexture("num.png", Renderer::GetInstance()->Get_SDL_RENDERER());

			bool quit = false;
			SDL_Event event;

			// For Game Update Loop Pattern
			float previous = SDL_GetTicks();// double previous = getCurrentTime();
			float current, elapsed;
			while (!quit)
			{
				// For Game Update Loop Pattern
				current = SDL_GetTicks();// double current = getCurrentTime();
				elapsed = current - previous;// double elapsed = current - previous;
				previous = current;
				while (SDL_PollEvent(&event)){
					switch (event.type){
						/* Look for a keypress */
					case SDL_KEYDOWN:
						/* Check the SDLKey values and move change the coords */
						switch (event.key.keysym.sym){
						case SDLK_LEFT:
							playerPos.x -= speed;

							break;
						case SDLK_RIGHT:
							playerPos.x += speed;
							break;
						case SDLK_UP:
							playerPos.y -= speed;
							break;
						case SDLK_DOWN:
							playerPos.y += speed;
							break;
						default:
							break;
						}
					}
				}
				for (int i = 0; i < balls.size(); i++)
				{
					if (playerPos.x + playerPos.w > balls[i].x &&
						playerPos.x < balls[i].x + balls[i].w &&
						playerPos.y + playerPos.h > balls[i].y &&
						playerPos.y < balls[i].y + balls[i].h)
					{
						
						writerThreads.push_back(SDL_CreateThread(Writer, "WriterThread", (void*)&i));
						SDL_Delay(16+ rand() % 16);
					}
				}



				Renderer::GetInstance()->ClearRenderer();

				//add stuff to renderer here 
				Renderer::GetInstance()->DrawImage(&playerSrc, &playerPos, playerTexture);
				for (int i = 0; i < balls.size(); i++)
				{
					Renderer::GetInstance()->DrawImage(&ballSrc, &balls[i], ballTexture);
				}
				Renderer::GetInstance()->DrawImage(&threadSrc[0], &outputPos1, output);
				Renderer::GetInstance()->DrawImage(&threadSrc[1], &outputPos2, output);

				Renderer::GetInstance()->RenderScreen();


			}//end while quit
		}//end else
	}//end else

	
	//Free semaphore
	SDL_DestroySemaphore(rw);
	rw = NULL;
	return 0;
}

int Reader(void *data)
{
	int threadNum = *((int*)data);
	int num = 1;
	while (true)
	{
		
		SDL_SemWait(nrLock);
			nr = nr++;
			if (nr == 1)/*if first get lock*/
			{
				SDL_SemWait(rw);
			}
		SDL_SemPost(nrLock);
		/*Read from file*/
		cout << "Reading\n";
		string line;
		ifstream myfile("file.txt");
		std::stringstream ss;
		if (myfile.is_open())
		{
			myfile >> num;
			//while (getline(myfile, line))
			//{
			//	ss << line << '\n';
			//}
			myfile.close();

			

		}
		else cout << "Unable to open file";
		cout << ss.str();
		SDL_SemWait(nrLock);
			nr = nr--;
			if (nr == 0)/*if last , release lock*/
			{
				SDL_SemPost(rw);
			}
		SDL_SemPost(nrLock);
		
		threadSrc[threadNum].x = num * 50;
		//Wait randomly
		SDL_Delay(16 + rand() % 640);
	}
	return 0;
}
int Writer(void *data)
{
		int message = *((int*) data);
		SDL_SemWait(rw);
		/*Write to the file*/
		cout << "Writing\n";

		
		std::ofstream out("file.txt");
		out << message;
		out.close();

		SDL_SemPost(rw);
		//Wait randomly
		return 0;
}

SDL_Texture* loadTexture(std::string path, SDL_Renderer* gRenderer)
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}