#ifndef PLAYERSTATS_H_
#define PLAYERSTATS_H_


#define _player PlayerStats::GetInstance()
#define MAX_PLAYER_HEALTH 100.0
#define MAX_WALL_HEALTH 100.0

class PlayerStats
{
public:
	PlayerStats();
	virtual ~PlayerStats();
	static PlayerStats* GetInstance();
	
	/* Player Health functions */
	float GetPlayerHealth();
	float GetPlayerPerc();
	float AffectPlayerHealth(float amount);
	
	/* Wall Health Functions */
	float GetWallHealth();
	float GetWallPerc();
	float AffectWallHealth(float amount);
	
	/* Level constant stuff */
	int GetLevel();
	void IncrementLevel();
	
	/* Enemy Stats */
	int GetEnemiesKilled();
	int GetEnemiesNotKilled();
	void IncrementEnemiesKilled();
	void IncrementEnemiesNotKilled();
	
	
	
private:
    float m_playerHealth;
    float m_wallHealth;
    int m_level;
    int m_enemiesKilled;
    int m_enemiesNotKilled;
};

#endif /*PLAYERSTATS_H_*/
