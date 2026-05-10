#pragma once

#include "Enemy.h"

class Chaser : public Enemy
{
public:
    Chaser(Point pos);

    void update(const Point& heroPos, Board& board) override;
};