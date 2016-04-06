#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <SDL.h>

class Renderer
{
private:
	static bool instanceFlag; //instance flag to indicate if renderer object already exists 
	static Renderer* instance; // the insatance of the renderer
	Renderer::Renderer(){
		camera = new SDL_Point{ 0, 0 };
	}
	//renderer
	SDL_Renderer* gRenderer = NULL;
	int SCREEN_WIDTH, SCREEN_HEIGHT;
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;
	SDL_Point* camera = NULL; /*Camera point is the coordinates of the top left cornmer of the viewport */
public:

	static Renderer* GetInstance();
	~Renderer()
	{
		instanceFlag = false;
		delete instance;
		delete gRenderer;
		delete screenSurface;
		delete camera;
	}
	bool Init(SDL_Window* window, int screen_Width, int screen_Height);
	void ClearRenderer();
	void RenderScreen();
	void Draw(SDL_Rect rectangle);
	void DrawImage(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre);
	void DrawImageNoCameraOffset(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre);
	SDL_Renderer* Get_SDL_RENDERER();
	SDL_Point* GetCamera();
	void SetCamera(SDL_Point);
	void MoveCameraBy(SDL_Point);
};
#endif




