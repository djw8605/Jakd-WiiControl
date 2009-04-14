#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <cstring>

Audio::Audio()
{
    initialized = false;
    if(SDL_Init(SDL_INIT_AUDIO) != 0)
    {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        return;
    }

    int audio_rate = 22050;
    Uint16 audio_format = AUDIO_S16SYS;
    int audio_channels = 2;
    int audio_buffers = 1024;

    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
            fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
            return;
    }

    audioList = 0;
    initialized = true;



}

Audio::~Audio()
{
    Mix_CloseAudio();
    SDL_Quit();
}

Audio* Audio::GetInstance()
{
    static Audio* instance = new Audio();
    return instance;


}

void Audio::PlaySound(const char* audioFile)
{
    /* As always, don't do anything if something fialed with SDL */
    if(!initialized)
        return;

    Mix_Chunk *sound = NULL;

    sound = FindAudio(audioFile);

    if(sound == NULL) {
            fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
            return;
    }

    int channel;

    channel = Mix_PlayChannel(-1, sound, 0);
    if(channel == -1) {
            fprintf(stderr, "Unable to play WAV file: %s\n", Mix_GetError());
            return;
    }


}


Mix_Chunk* Audio::FindAudio(const char* audioFile)
{
	if (!initialized)
		return NULL;

	AudioSave* tmp;
	/* Find the sound */
	tmp = audioList;
	while(tmp != 0)
	{
		if(strcmp(tmp->name, audioFile) == 0)
			return tmp->sound;
		tmp = tmp->next;
	}

	/* make the sound */
	Mix_Chunk *sound = NULL;

	sound = Mix_LoadWAV(audioFile);
	if (sound == NULL) {
		fprintf(stderr, "Unable to load WAV file: %s\n", Mix_GetError());
		return NULL;
	}

	printf("Adding\n");
	AudioSave* tmpAudio = new AudioSave;
	tmpAudio->name = new char[strlen(audioFile) + 1];
	strcpy(tmpAudio->name, audioFile);
	tmpAudio->next = NULL;
	tmpAudio->sound = sound;

	/* Add to the list */
	if (!audioList) {
		audioList = tmpAudio;

	} else {
		tmp = audioList;
		while(tmp->next != 0)
			tmp = tmp->next;

		tmp->next = tmpAudio;

	}

	return tmpAudio->sound;


}



