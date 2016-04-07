#include "GameStateController.h"

bool GameStateController::instanceFlag = false;
GameStateController* GameStateController::instance = nullptr;

GameStateController* GameStateController::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new GameStateController();
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void GameStateController::SetGameState(int g) { GameState = g; }
int GameStateController::getGameState() const
{ return GameState; }
