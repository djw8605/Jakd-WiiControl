#ifndef CATAPULT_H_
#define CATAPULT_H_

#define _catapult Catapult::GetInstance()

class Catapult
{
public:
	Catapult();
	virtual ~Catapult();
	void Render();
	static Catapult* GetInstance();
	void GetCurrentPos(float* buf);
	
private:
    float pos[3];
    
    
};

#endif /*CATAPULT_H_*/
