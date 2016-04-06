#include "Enemy.h"

Enemy::Enemy(int x, int y, SDL_Texture * text, int i)
{
	pX = x;
	pY = y;
	dirX = 0;
	dirY = 0;
	sprite = new Sprite(text, SDL_Rect{ x, y, 50, 50 }, SDL_Rect{ 0, 0, 33, 64 });
	sprite->SetOffset(SDL_Point{ 25, 25 });
	id = i;
}


void Enemy::Update(float time)
{
	

	
}
void Enemy::updateAI(float targetX, float targetY)
{
	/*The ai plots a course to the target . ie sets direction vector */
	dirX = targetX - pX;
	dirY = targetY - pY;
	//normalise
	float len = sqrt(dirX*dirX + dirY*dirY);
	dirX /= len;
	dirY /= len;

}
void Enemy::physics(float time)
{
	/*The physics moves the object along its set path*/
	pX += dirX * time * speed;
	pY += dirY * time * speed;
}
void Enemy::Draw()
{
	sprite->SetPosition(pX, pY);
	sprite->Draw();
}

pair<bool, int> Enemy::IsColiding(Player *player)
{
	SDL_Rect p = player->sprite->GetPosition();
	SDL_Rect e = sprite->GetPosition();
	if (p.x + p.w > e.x &&
		p.x < e.x + e.w &&
		p.y + p.h > e.y &&
		p.y < e.y + e.h)
	{
		return pair<bool, int>(true,id);
	}
	return pair<bool, int>(false,id);
}