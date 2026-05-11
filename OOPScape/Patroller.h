#pragma once

#include "Enemy.h"
#include <vector>

class Patroller : public Enemy
{
public:
    Patroller(const std::vector<Point>& path);

    void update(const Point& heroPos, Board& board) override;

private:
    bool bfsStep(const Point& target, Board& board);

    std::vector<Point> m_path;
    int                m_targetIndex = 1;
    bool               m_forward = true;
};