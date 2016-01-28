#include "Renderer.h"

bool Renderer::instanceFlag = false;
Renderer* Renderer::instance = NULL;

Renderer* Renderer::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Renderer;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
bool Renderer::Init(SDL_Window* window, int screen_Width, int screen_Height){
	//Create Renderer for the Window
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	camera = new SDL_Point{ 0, 0 };
	SCREEN_WIDTH = screen_Width;
	SCREEN_HEIGHT = screen_Height;
	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		screenSurface = SDL_GetWindowSurface(window);
	}
	return true;
}
void Renderer::Draw(SDL_Rect rectangle){
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(gRenderer, &rectangle);
}
void Renderer::DrawImageNoCameraOffset(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre) {
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(gRenderer, text, source, dest, angle, centre, flip);//Copy the image to the rendering object.
}
void Renderer::DrawImage(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre) {
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_Rect offSetRect = { dest->x - camera->x, dest->y - camera->y , dest->w, dest->h };
	SDL_RenderCopyEx(gRenderer, text, source, &offSetRect, angle, centre, flip);//Copy the image to the rendering object.
}
void Renderer::ClearRenderer(){
	// Sets colour that we're clearing the screen with
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// This clears the screen
	SDL_RenderClear(gRenderer);

}
void Renderer::RenderScreen(){
	SDL_RenderPresent(gRenderer);
}
SDL_Renderer* Renderer::Get_SDL_RENDERER(){
	return gRenderer;
}
SDL_Point* Renderer::GetCamera(){ return camera; }
void Renderer::SetCamera(SDL_Point p){ *camera = p; }
void Renderer::MoveCameraBy(SDL_Point p)
{
	*camera = { camera->x + p.x, camera->y + p.y };
}