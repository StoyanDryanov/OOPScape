#pragma once

#include "Point.h"
#include "Board.h"

class Entity
{
public:
    Entity(Point pos, char symbol);
    virtual ~Entity() = default;

    Point getPos()    const { return m_pos; }
    char  getSymbol() const { return m_symbol; }

    void setPos(Point pos) { m_pos = pos; }

    virtual void move(char direction, Board& board) = 0;

protected:
    bool moveInDirection(char direction, Board& board);

    Point m_pos;
    char  m_symbol;
};
