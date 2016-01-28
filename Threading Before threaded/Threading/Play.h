#ifndef _PLAY_H_
#define _PLAY_H_

#include <iostream>
#include <stdio.h>

#include <SDL.h>
#include "GameStateController.h"
#include "KeyBoardInput.h"
#include "Player.h"
#include "Sprite.h"
#include "EnemyManager.h"


class Play{
private:
	Player* player;
	Sprite* backGroundImage;
public:
	Play(int w, int h);
	~Play(){
		delete player;
		delete backGroundImage;
		
	}
	void Init();
	void AddAssetsToRenderer();
	void Update(float time);
	void Draw();
};
#endif
