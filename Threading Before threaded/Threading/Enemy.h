#ifndef _ENEMY_H_
#define _ENEMY_H_

#include <iostream>

#include <SDL.h>
#include "Sprite.h"



class Enemy{
private:
	Sprite* sprite;
	float pX;
	float pY;
	float dirX;
	float dirY;
	const float speed = 100;
public:
	Enemy(int x, int y, SDL_Texture * text);
	~Enemy(){
		delete sprite;
	}
	void Init();
	void Update(float time);
	void Draw();
	void updateAI(float targetX, float targetY);
	void physics(float time);
	void setPosition(float x , float y)
	{
		pX = x;
		pY = y;
	}
	pair<float, float> getPosition()
	{
		return pair<float, float>(pX, pY);
	}
};
#endif
