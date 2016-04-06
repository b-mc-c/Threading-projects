#include "Play.h"

Play::Play( int SCREEN_WIDTH, int SCREEN_HEIGHT)
{
	player = new Player(SCREEN_WIDTH / 2, SCREEN_HEIGHT/2 );
	backGroundImage = new Sprite("background_clouds.png", SDL_Rect{ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }, SDL_Rect{ 0, 0, 7467, 2053 });
	EnemyManager::GetInstance()->init();
	

}

void Play::Init(){
}

void Play::Update(float time){


	//Update game entities.
	player->Update(time);

	//EnemyManager::GetInstance()->update( time, player);
	
}

void Play::Draw() {
	Renderer::GetInstance()->ClearRenderer();

	/*Call Draw on objects here*/
	AddAssetsToRenderer();

	Renderer::GetInstance()->RenderScreen();
}

void Play::AddAssetsToRenderer(){

	backGroundImage->DrawNoCamOffset();
	player->Draw();
	EnemyManager::GetInstance()->draw();
	
}
