#pragma once

#include "Hero.h"

class Wizard : public Hero
{
public:
    Wizard(Point pos);

    void useAbility(Board& board) override;
};