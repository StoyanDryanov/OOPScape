#include "Patroller.h"
#include "Pathfinding.h"

#include <queue>
#include <vector>

Patroller::Patroller(const std::vector<Point>& path)
    : Enemy(path.empty() ? Point{ 0, 0 } : path[0], 'P')
    , m_path(path)
{
}

void Patroller::update(const Point& heroPos, Board& board)
{
    if (!m_alive || m_path.size() < 2) return;

    Point target = m_path[m_targetIndex];

    m_pos = bfsNextStep(m_pos, target, board);

    if (m_pos == target)
    {
        if (m_forward)
        {
            m_targetIndex++;
            if (m_targetIndex >= (int)m_path.size())
            {
                m_targetIndex = (int)m_path.size() - 2;
                m_forward = false;
            }
        }
        else
        {
            m_targetIndex--;
            if (m_targetIndex < 0)
            {
                m_targetIndex = 1;
                m_forward = true;
            }
        }
    }
}
