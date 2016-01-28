#ifndef _SCORESCREEN_H_
#define _SCORESCREEN_H_

#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include "GameStateController.h"
#include "Sprite.h"
#include "KeyBoardInput.h"




class ScoreScreen
{
private:
	Sprite* backGroundImage;
public:

	ScoreScreen(int w, int h);
	~ScoreScreen()
	{
		delete backGroundImage;
	}
	void Init();
	void Update();
	void Draw();


};
#endif
