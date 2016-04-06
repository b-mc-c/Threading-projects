#ifndef SPRITE_H
#define SPRITE_H

#include <iostream> 
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include "Renderer.h"

using namespace std;

class Sprite
{
public:
	Sprite();
	Sprite(std::string imagePath, SDL_Rect destination, SDL_Rect source);
	Sprite(SDL_Texture* imageText, SDL_Rect destination, SDL_Rect source);
	~Sprite()
	{
		delete myTexture;
	}
	void SetPosition(float x, float y);
	SDL_Rect GetPosition();
	void SetWidth(float w);
	void SetHeight(float h);
	void SetDestinationRect(SDL_Rect destination);
	SDL_Rect GetDestinationRect();
	void SetSourceRect(SDL_Rect source);
	void SetOffset(SDL_Point offset);/*offset is relative width and height of the sprite not the texture */
	void SetRotation(double rot);	
	static SDL_Texture* loadTexture(std::string path, SDL_Renderer*);
	//void Draw();
	void Draw();//draw affected by camera
	void DrawNoCamOffset(); //draw not affected by camera , for ui elements 

private:

	SDL_Texture* myTexture;
	SDL_Point m_offset;
	SDL_Rect m_Destrination, m_Source;
	double rotation;
};
#endif