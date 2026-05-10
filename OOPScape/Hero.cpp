#include "Hero.h"
#include <iostream>

Hero::Hero(Point pos, char symbol)
    : Entity(pos, symbol)
{
}

void Hero::move(char direction, Board& board)
{
    if (!moveInDirection(direction, board))
        std::cout << "Can't move that way!\n";
}

void Hero::tickCooldown()
{
    if (m_cooldown > 0)
        m_cooldown--;
}