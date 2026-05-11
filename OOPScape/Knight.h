#pragma once

#include "Hero.h"

class Knight : public Hero
{
public:
    Knight(Point pos);

    void useAbility(Board& board, std::vector<std::unique_ptr<Enemy>>& enemies) override;
};