#pragma once

#include <vector>
#include <string>
#include "Point.h"

class Board
{
public:
    Board() = default;

    bool load(const std::string& filename);

    bool isWalkable(int x, int y) const;

    char getCell(int x, int y) const;
    void setCell(int x, int y, char c);

    int getSize() const;

    Point getHeroStart()                         const { return m_heroStart; }
    Point getExitPos()                           const { return m_exitPos; }
    const std::vector<Point>& getEnemyStarts()   const { return m_enemyStarts; }
    const std::vector<Point>& getPatrolPoints()  const { return m_patrolPoints; }

private:
    std::vector<std::string> m_grid;
    int                      m_size = 0;
    Point                    m_heroStart = { 0, 0 };
    Point                    m_exitPos = { 0, 0 };
    std::vector<Point>       m_enemyStarts;
    std::vector<Point>       m_patrolPoints;
};