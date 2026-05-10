#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
    Enemy(Point pos, char symbol);

    void move(char direction, Board& board) override;

    virtual void update(const Point& heroPos, Board& board) = 0;

    bool isAlive() const { return m_alive; }
    void kill() { m_alive = false; }

protected:
    bool m_alive = true;
};