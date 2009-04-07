#ifndef AUDIO_H_
#define AUDIO_H_

#include <SDL.h>
#include <SDL_mixer.h>

#define _audio Audio::GetInstance()

struct AudioSave {
	char* name;
	Mix_Chunk *sound;
	AudioSave* next;
};


class Audio
{
public:
	Audio();
	virtual ~Audio();
	static Audio* GetInstance();
	void PlaySound(const char* audioFile);
	Mix_Chunk* FindAudio(const char* audioFile);


private:
    AudioSave* audioList;
	bool initialized;
};



#endif /*AUDIO_H_*/
