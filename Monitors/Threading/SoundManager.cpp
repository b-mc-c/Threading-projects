#include "SoundManager.h"


bool SoundManager::instanceFlag = false;
SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new SoundManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

bool SoundManager::load_files()
{
	//Load the music
	gameMusic = Mix_LoadMUS("game-soundtrack2.wav");
	//Load the sound effects
	/*colorDrop = Mix_LoadWAV("Assets/colourdrop.wav");
	darkness = Mix_LoadWAV("Assets/darkness.wav");
	deathScreen1 = Mix_LoadWAV("Assets/death screen1.wav");
	drownBubble = Mix_LoadWAV("Assets/drownbubble.wav");
	longJump = Mix_LoadWAV("Assets/longjump2.wav");
	pipe = Mix_LoadWAV("Assets/pipe.wav");
	shortJump = Mix_LoadWAV("Assets/shortjump4.wav");
	spikeHit = Mix_LoadWAV("Assets/spikehit.wav");*/

	//If there was a problem loading the sound effects
	if (gameMusic == NULL )
		/*|| colorDrop == NULL || darkness == NULL || 
		deathScreen1 == NULL || drownBubble == NULL || longJump == NULL ||
		pipe == NULL || shortJump == NULL || spikeHit==NULL)*/
	{
		return false;
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);//music volume
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);//set volume for all sound effects
	//Mix_Volume(SHORT_JUMP, MIX_MAX_VOLUME / 6);//set volume for all sound effects
	//Mix_Volume(SPIKE_HIT, MIX_MAX_VOLUME);//set volume for all sound effects
	//If everything loaded fine
	return true;
}
void SoundManager::clean_up()
{

	//Free the sound effects
	//Mix_FreeChunk(colorDrop);
	//Mix_FreeChunk(darkness);
	//Mix_FreeChunk(deathScreen1);
	//Mix_FreeChunk(drownBubble);
	//Mix_FreeChunk(longJump);
	//Mix_FreeChunk(pipe);
	//Mix_FreeChunk(shortJump);
	//Mix_FreeChunk(spikeHit);

	//Free the music
	Mix_FreeMusic(gameMusic);

	//Quit SDL_mixer
	Mix_CloseAudio();

	//Quit SDL
	SDL_Quit();
}
void SoundManager::play(int i)
{
	//If there is no music playing
	switch (i)
	{
		
	//case COLOR_DROP:
	//	Mix_PlayChannel(COLOR_DROP, colorDrop, 0);
	//	break;
	//case DARKNESS:
	//	Mix_PlayChannel(DARKNESS, darkness, 0);
	//	break;
	//case DEATH_SCREEN_1:
	//	Mix_PlayChannel(DEATH_SCREEN_1, deathScreen1, 0);
	//	break;
	//case DROWN_BUBBLE:
	//	Mix_PlayChannel(DROWN_BUBBLE, drownBubble, 0);
	//	break;
	//case LONG_JUMP:
	//	Mix_PlayChannel(LONG_JUMP, longJump, 0);
	//	break;
	//case PIPE:
	//	Mix_PlayChannel(PIPE, pipe, 0);
	//	break;
	//case SHORT_JUMP:
	//	Mix_PlayChannel(SHORT_JUMP, shortJump, 0);
	//	break;
	//case SPIKE_HIT:
	//	Mix_PlayChannel(SPIKE_HIT, spikeHit, 0);
	//	break;
	case GAME_SOUND_TRACK:
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(gameMusic, -1);
		
		}
		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1)
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				//Pause the music
				Mix_PauseMusic();
			}
		}
		break;
	}
}
void SoundManager::stopMusic()
{
	//Stop the music
	Mix_HaltMusic();
}
