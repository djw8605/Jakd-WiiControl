#include "Audio.h"
#include <SDL.h>
#include <SDL_mixer.h>


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
    int audio_buffers = 4096;
    
    if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
            fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
            return;
    }
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
     
    sound = Mix_LoadWAV(audioFile);
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



