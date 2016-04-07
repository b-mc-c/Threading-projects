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
#include "Monitor.h"

using namespace std;

class Play{
private:
	
	Sprite* backGroundImage;
public:
	//The thread that will be used
	
	Player* player;
	Play(int w, int h);
	~Play(){
		delete player;
		delete backGroundImage;
		
	}
	void Init();
	void AddAssetsToRenderer();
	void Update(float time);
	void Draw();

	MonitorBoundedBuffer boundedBuf;
};
#endif
