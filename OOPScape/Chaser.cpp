#include "Chaser.h"

#include <queue>
#include <vector>

Chaser::Chaser(Point pos)
    : Enemy(pos, 'E')
{
}

void Chaser::update(const Point& heroPos, Board& board)
{
    if (!m_alive) return;

    int n = board.getSize();
    int W = n;

    std::vector<int> parent(W * W, -1);
    std::queue<Point> q;

    int start = m_pos.y * W + m_pos.x;
    int goal = heroPos.y * W + heroPos.x;

    parent[start] = start;
    q.push(m_pos);

    const int dx[4] = { -1, 1, 0, 0 };
    const int dy[4] = { 0, 0,-1, 1 };

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

    if (!found) return;

    int cur = goal;
    while (parent[cur] != start && cur != start)
        cur = parent[cur];

    if (cur == start) return;

    m_pos.x = cur % W;
    m_pos.y = cur / W;
}