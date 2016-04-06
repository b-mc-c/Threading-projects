#include "Player.h"

Player::Player(int x, int y)
{
	pX = x;
	pY = y;
	sprite = new Sprite("man.png", SDL_Rect{ x, y, 100, 100 }, SDL_Rect{ 0, 0, 33, 64 });
	sprite->SetOffset(SDL_Point{ 50, 50 });
	speed = 200;
}


void Player::Update(float time )
{
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_UP))
	{
		pY -= speed * time;
	}
	 if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_DOWN))
	{
		 pY += speed * time;
	}
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_LEFT))
	{
		pX -= speed * time;
	}
	 if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RIGHT))
	{
		 pX += speed * time;
	}

	// cout << ", X : " << pX << ", Y : " << pY << endl;

	 sprite->SetPosition(pX, pY);
}
void Player::Draw()
{
	sprite->Draw();
}
