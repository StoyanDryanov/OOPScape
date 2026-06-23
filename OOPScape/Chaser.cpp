#include "Chaser.h"
#include "Pathfinding.h"

#include <queue>
#include <vector>

Chaser::Chaser(Point pos)
    : Enemy(pos, 'E')
{
}

void Chaser::update(const Point& heroPos, Board& board)
{
    if (!m_alive) return;

    m_pos = bfsNextStep(m_pos, heroPos, board);
}