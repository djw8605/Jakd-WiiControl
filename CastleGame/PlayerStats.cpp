#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
    m_playerHealth = MAX_PLAYER_HEALTH;
    m_wallHealth = MAX_WALL_HEALTH;
    m_level = 1;
    m_enemiesKilled = 0;
    m_enemiesNotKilled = 0;


   m_EnemyModel = new CModel3DS("Media/SoldierArmor.3DS");
   m_EnemyModel->CreateVBO();

}

PlayerStats::~PlayerStats()
{
}


PlayerStats* PlayerStats::GetInstance()
{
    static PlayerStats* instance= new PlayerStats();
    return instance;
}



float PlayerStats::GetPlayerHealth() {
    return m_playerHealth;

}


float PlayerStats::GetPlayerPerc() {
    return m_playerHealth / MAX_PLAYER_HEALTH;
 }


float PlayerStats::AffectPlayerHealth(float amount)
{
    if ((m_playerHealth + amount) > MAX_PLAYER_HEALTH)
    {
        m_playerHealth = MAX_PLAYER_HEALTH;
    }
    else if ((m_playerHealth + amount) < 0.0)
    {
        m_playerHealth = 0.0;
    }
    else
    {
        m_playerHealth += amount;
    }


    return this->GetPlayerHealth();

}

float PlayerStats::GetWallHealth()
{
    return m_wallHealth;

}

float PlayerStats::GetWallPerc()
{
    return m_wallHealth / MAX_WALL_HEALTH;
}


float PlayerStats::AffectWallHealth(float amount)
{
    if ((m_wallHealth + amount) > MAX_WALL_HEALTH)
    {
        m_wallHealth = MAX_WALL_HEALTH;
    }
    else if ((m_wallHealth + amount) < 0.0)
    {
        m_wallHealth = 0.0;
    }
    else
    {
        m_wallHealth += amount;
    }



    return this->GetWallHealth();
}



int PlayerStats::GetLevel()
{
    return m_level;
}


void PlayerStats::IncrementLevel()
{
    m_level++;
}

int PlayerStats::GetEnemiesKilled()
{
    return m_enemiesKilled;

}
int PlayerStats::GetEnemiesNotKilled()
{
    return m_enemiesNotKilled;

}
void PlayerStats::IncrementEnemiesKilled()
{
    m_enemiesKilled++;

}
void PlayerStats::IncrementEnemiesNotKilled()
{
    m_enemiesNotKilled++;

}

CModel3DS* PlayerStats::GetEnemyModel()
{

    return m_EnemyModel;
}


void PlayerStats::Reset()
{
	this->AffectPlayerHealth(MAX_PLAYER_HEALTH);
	this->AffectWallHealth(MAX_WALL_HEALTH);
	this->m_enemiesKilled = 	0;
	this->m_enemiesNotKilled = 0;
	this->m_level = 1;



}



