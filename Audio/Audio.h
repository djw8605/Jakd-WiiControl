#ifndef AUDIO_H_
#define AUDIO_H_

#define _audio Audio::GetInstance()

class Audio
{
public:
	Audio();
	virtual ~Audio();
	static Audio* GetInstance();
	
private:
        bool initialized;
};



#endif /*AUDIO_H_*/
