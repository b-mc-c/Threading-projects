#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream> 
#include <SDL.h>			//SDL
#include <stdio.h>
#include "SDL_mixer.h"
#include <list>

#pragma comment(lib, "SDL2_mixer.lib")

using namespace std;

class SoundManager
{
public:
	static const int GAME_SOUND_TRACK = 0;// COLOR_DROP = 1, DARKNESS = 2, DEATH_SCREEN_1 = 3,
					//DROWN_BUBBLE=4, LONG_JUMP=5, PIPE=6, SHORT_JUMP=7, SPIKE_HIT=8;
	
	static SoundManager* GetInstance();
	void play(int);
	void stopMusic();
	bool load_files();
	void clean_up();
	~SoundManager()
	{
		instanceFlag = false;
	}
private:
	SoundManager()
	{
		
		
		//Initialize SDL_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			
		}
	}
	
	Mix_Music* gameMusic = NULL;
	//Mix_Chunk* colorDrop = NULL;
	//Mix_Chunk* darkness = NULL;
	//Mix_Chunk* deathScreen1 = NULL;
	//Mix_Chunk* drownBubble = NULL;
	//Mix_Chunk* longJump = NULL;
	//Mix_Chunk* pipe = NULL;
	//Mix_Chunk* shortJump = NULL;
	//Mix_Chunk* spikeHit = NULL;
	static bool instanceFlag;
	static SoundManager* instance;
	
};
#endif
