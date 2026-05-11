#pragma once

#include "Hero.h"

class Rogue : public Hero
{
public:
    Rogue(Point pos);

    void useAbility(Board& board, std::vector<std::unique_ptr<Enemy>>& enemies) override;

    bool isInvisible()          const { return m_invisibilityTurns > 0; }
    void tickInvisibility();
    int  getInvisibilityTurns() const { return m_invisibilityTurns; }

private:
    int m_invisibilityTurns = 0;
    static const int INVISIBILITY_DURATION = 3;
};