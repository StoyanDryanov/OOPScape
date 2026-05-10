#include "Entity.h"

Entity::Entity(Point pos, char symbol)
    : m_pos(pos), m_symbol(symbol)
{
}

bool Entity::moveInDirection(char direction, Board& board)
{
    Point next = m_pos;

    switch (direction)
    {
    case 'U': next.y--; break;
    case 'D': next.y++; break;
    case 'L': next.x--; break;
    case 'R': next.x++; break;
    default: return false;
    }

    if (!board.isWalkable(next.x, next.y))
        return false;

    m_pos = next;
    return true;
}