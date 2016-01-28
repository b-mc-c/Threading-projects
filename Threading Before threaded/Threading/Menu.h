#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <stdio.h>

#include <SDL.h>
#include "GameStateController.h"
#include "SoundManager.h"
#include "Sprite.h"


class Menu
{
private:
	Sprite* backGroundImage;
public:

	Menu(int w,int h);
	~Menu()
	{
		delete backGroundImage;
	}
	void Init();
	void  Update();
	void Draw();


};
#endif
