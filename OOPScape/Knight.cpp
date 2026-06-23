#include "Knight.h"
#include <iostream>

Knight::Knight(Point pos)
    : Hero(pos, 'K')
{
    m_cooldownMax = 4;
}

void Knight::useAbility(Board& board, std::vector<std::unique_ptr<Enemy>>& enemies)
{
    const int dx[8] = { -1, -1, -1,  0, 0,  1, 1, 1 };
    const int dy[8] = { -1,  0,  1, -1, 1, -1, 0, 1 };

    int killCount = 0;

    for (auto& enemy : enemies)
    {
        if (!enemy->isAlive()) continue;

        for (int k = 0; k < 8; k++)
        {
            int nx = m_pos.x + dx[k];
            int ny = m_pos.y + dy[k];

            if (enemy->getPos().x == nx && enemy->getPos().y == ny)
            {
                enemy->kill();
                killCount++;
                break;
            }
        }
    }

    if (killCount > 0)
        std::cout << "Knight strikes! " << killCount << " enemy(s) defeated!\n";
    else
        std::cout << "No enemies in range!\n";

    m_cooldown = m_cooldownMax;
}