#ifndef AUDIO_H_
#define AUDIO_H_

#define _audio Audio::GetInstance()

class Audio
{
public:
	Audio();
	virtual ~Audio();
	static Audio* GetInstance();
	void PlaySound(const char* audioFile);
	
private:
        bool initialized;
};



#endif /*AUDIO_H_*/
