#include "PlayerStats.h"

PlayerStats::PlayerStats()
{
}

PlayerStats::~PlayerStats()
{
}


static PlayerStats* PlayerStats::GetInstance() 
{
    static PlayerStats* = new PlayerStats(); 
    return PlayerStats;
}



float PlayerStats::GetPlayerHealth() {
    return m_playerHealth; 
    
}


float PlayerStats::GetPlayerPerc() {
    return m_playerHealth / MAX_PLAYER_HEALTH 
 }


float PlayerStats::AffectPlayerHealth(float amount)
{
    m_playerHealth += amount;
    return this->GetPlayerHealth();

}

float PlayerStats::GetWallHealth()
{
    return m_wallHealth;

}

float PlayerStats::GetWallPerc()
{
    return m_wallHealth / MAX_WALL_HEALTH
}
float PlayerStats::AffectWallHealth(float amount)
{
    m_wallHealth += amount;
    return this->GetWallHealth()
}

