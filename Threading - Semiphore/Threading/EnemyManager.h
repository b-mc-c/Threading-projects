#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <iostream> 
#include <SDL.h>			//SDL
#include <list>
#include "Enemy.h"
#include "Player.h"

using namespace std;

class EnemyManager
{
public:
	

	static EnemyManager* GetInstance();
	~EnemyManager()
	{
		instanceFlag = false;
		for each(Enemy* e in enemies)
		{
			delete e;
		}
		delete texture;
	}

	void init();
	void update(float time, Player* p);
	void UpdateAI(Player* p);
	void UpdatePyhsics(float time);
	void draw();


private:
	EnemyManager()
	{
		
	}

	static bool instanceFlag;
	static EnemyManager* instance;
	list<Enemy*> enemies;
	SDL_Texture* texture;
	int maxEnemies;

};
#endif
