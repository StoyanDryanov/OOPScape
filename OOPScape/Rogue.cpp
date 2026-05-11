#include "Rogue.h"

Rogue::Rogue(Point pos)
    : Hero(pos, 'R')
{
    m_cooldownMax = 5;
}

void Rogue::useAbility(Board& board, std::vector<std::unique_ptr<Enemy>>& enemies)
{
    m_invisibilityTurns = INVISIBILITY_DURATION;
    m_cooldown = m_cooldownMax;
}

void Rogue::tickInvisibility()
{
    if (m_invisibilityTurns > 0)
        m_invisibilityTurns--;
}