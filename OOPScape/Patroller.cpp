#include "Patroller.h"

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

    bool moved = bfsStep(target, board);

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

bool Patroller::bfsStep(const Point& target, Board& board)
{
    int n = board.getSize();
    int W = n;

    std::vector<int> parent(W * W, -1);
    std::queue<Point> q;

    int start = m_pos.y * W + m_pos.x;
    int goal = target.y * W + target.x;

    if (start == goal) return false;

    parent[start] = start;
    q.push(m_pos);

    const int dx[4] = { -1, 1,  0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    bool found = false;
    while (!q.empty())
    {
        Point cur = q.front();
        q.pop();

        int curI = cur.y * W + cur.x;
        if (curI == goal) { found = true; break; }

        for (int k = 0; k < 4; k++)
        {
            int nx = cur.x + dx[k];
            int ny = cur.y + dy[k];

            if (!board.isWalkable(nx, ny)) continue;

            int ni = ny * W + nx;
            if (parent[ni] != -1) continue;

            parent[ni] = curI;
            q.push({ nx, ny });
        }
    }

    if (!found) return false;

    int cur = goal;
    while (parent[cur] != start && cur != start)
        cur = parent[cur];

    if (cur == start) return false;

    m_pos.x = cur % W;
    m_pos.y = cur / W;
    return true;
}