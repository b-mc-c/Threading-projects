#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <iostream>

#include <SDL.h>
#include "Sprite.h"
#include "KeyBoardInput.h"


class Player{
private:
	
	float pX;
	float pY;
	float speed;
public:
	Sprite* sprite;
	Player(int x, int y);
	~Player(){
		delete sprite;
	}
	void Init();
	void Update(float time);
	void Draw();
	pair<float, float> getPosition()
	{

		return pair<float ,float> (pX,pY);
	}
};
#endif
