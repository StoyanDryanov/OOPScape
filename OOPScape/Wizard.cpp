#include "Wizard.h"

#include <cstdlib>
#include <iostream>

Wizard::Wizard(Point pos)
    : Hero(pos, 'W')
{
    m_cooldownMax = 3;
}

void Wizard::useAbility(Board& board, std::vector<std::unique_ptr<Enemy>>& enemies)
{
    int n = board.getSize();

    for (int attempt = 0; attempt < 100; attempt++)
    {
        int x = rand() % n;
        int y = rand() % n;

        char cell = board.getCell(x, y);
        if (cell != '*')
        {
            m_pos = { x, y };
            m_cooldown = m_cooldownMax;
            std::cout << "Wizard teleports to (" << x << ", " << y << ")!\n";
            return;
        }
    }

    std::cout << "Teleport failed — no free cell found!\n";
}