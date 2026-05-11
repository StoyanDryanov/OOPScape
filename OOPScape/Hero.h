#pragma once

#include "Entity.h"
#include "Enemy.h"
#include <vector>
#include <memory>

class Hero : public Entity
{
public:
    Hero(Point pos, char symbol);

    void move(char direction, Board& board) override;

    virtual void useAbility(Board& board, std::vector<std::unique_ptr<Enemy>>& enemies) = 0;

    int  getCooldown()    const { return m_cooldown; }
    int  getCooldownMax() const { return m_cooldownMax; }
    bool canUseAbility()  const { return m_cooldown == 0; }

    void tickCooldown();

protected:
    int m_cooldown = 0;
    int m_cooldownMax = 0;
};