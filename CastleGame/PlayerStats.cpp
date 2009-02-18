#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
    m_playerHealth = MAX_PLAYER_HEALTH;
    m_wallHealth = MAX_WALL_HEALTH;
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

