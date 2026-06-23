#include "Pathfinding.h"
#include <queue>
#include <vector>

Point bfsNextStep(Point from, Point to, const Board& board)
{
    int W = board.getSize();

    int start = from.y * W + from.x;
    int goal = to.y * W + to.x;

    if (start == goal) return from;

    std::vector<int> parent(W * W, -1);
    parent[start] = start;

    std::queue<Point> q;
    q.push(from);

    const int dx[4] = { -1, 1,  0, 0 };
    const int dy[4] = { 0, 0, -1, 1 };

    bool found = false;
    while (!q.empty())
    {
        Point cur = q.front(); q.pop();
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

    if (!found) return from;

    int cur = goal;
    while (parent[cur] != start && cur != start)
        cur = parent[cur];

    if (cur == start) return from;
    return { cur % W, cur / W };
}