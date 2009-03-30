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
    initialized = true;
    
}

Audio::~Audio()
{
}

Audio* Audio::GetInstance()
{
    static Audio* instance = new Audio();
    return instance;
    
    
}





