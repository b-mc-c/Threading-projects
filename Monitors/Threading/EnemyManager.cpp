#include "EnemyManager.h"

bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = NULL;

EnemyManager* EnemyManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new EnemyManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}
void EnemyManager::init()
{
	texture = Sprite::loadTexture("man2.png", Renderer::GetInstance()->Get_SDL_RENDERER());
	maxEnemies =10;
	for (int i = 0; i < maxEnemies; i++)
	{
		enemies.push_back(new Enemy(i * 300, 100, texture, i));//int x, int y, SDL_Texture * text
	}


}
void EnemyManager::update(float time, Player* p)
{
	UpdateAI( p);
	UpdatePyhsics(time);
}
void EnemyManager::UpdateAI(Player* p)
{
	float targetX = p->getPosition().first;
	float targetY = p->getPosition().second;

	for each(Enemy* e in enemies)
	{
		e->updateAI(targetX,targetY);
	}
}

void EnemyManager::UpdatePyhsics(float time)
{
	for each(Enemy* e in enemies)
	{
		e->physics(time);
	}
}
void EnemyManager::draw()
{
	for each(Enemy* e in enemies)
	{
		e->Draw();
	}
}
pair<bool, int> EnemyManager::IsColiding(Player* player)
{
	for each(Enemy* e in enemies)
	{
		pair<bool, int> c = e->IsColiding(player);
		if (c.first)
		{
			return c;
		}
	}
	return pair<bool, int>(false,1);
}