#include "Enemy.h"

Enemy::Enemy(int x, int y, SDL_Texture * text)
{
	pX = x;
	pY = y;
	dirX = 0;
	dirY = 0;
	sprite = new Sprite(text, SDL_Rect{ x, y, 50, 50 }, SDL_Rect{ 0, 0, 33, 64 });
	sprite->SetOffset(SDL_Point{ 25, 25 });

	//Initialize semaphore
	gDataLock = SDL_CreateSemaphore(1);
}


void Enemy::Update(float time)
{
	

	
}
void Enemy::updateAI(float targetX, float targetY)
{
	//SDL_LockMutex(Update_mutex);

	//Lock
	SDL_SemWait(gDataLock);

	/*The ai plots a course to the target . ie sets direction vector */
	dirX = targetX - pX;
	dirY = targetY - pY;
	//normalise
	float len = sqrt(dirX*dirX + dirY*dirY);
	dirX /= len;
	dirY /= len;

	//Unlock
	SDL_SemPost(gDataLock);

	//SDL_UnlockMutex(Update_mutex);

}
void Enemy::physics(float time)
{
	//SDL_LockMutex(Update_mutex);

	//Lock
	SDL_SemWait(gDataLock);

	/*The physics moves the object along its set path*/
	pX += dirX * time * speed;
	pY += dirY * time * speed;

	//SDL_UnlockMutex(Update_mutex);
	//Unlock

	SDL_SemPost(gDataLock);
}
void Enemy::Draw()
{
	sprite->SetPosition(pX, pY);
	sprite->Draw();
}

