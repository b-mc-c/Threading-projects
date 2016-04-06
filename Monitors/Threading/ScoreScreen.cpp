#include "ScoreScreen.h"

ScoreScreen::ScoreScreen(int SCREEN_WIDTH, int SCREEN_HEIGHT)
{

}

void ScoreScreen::Init()
{
}
void ScoreScreen::Update()
{
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RETURN)) {

		GameStateController::GetInstance()->SetGameState(GameStateController::CREDITS);
		KeyBoardInput::GetInstance()->clearKeys();
	}
}
void ScoreScreen::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	/*Call Darw on objects here*/


	Renderer::GetInstance()->RenderScreen();
}