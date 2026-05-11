#pragma once

#include "Board.h"
#include "Hero.h"
#include "Enemy.h"

#include <vector>
#include <memory>
#include <string>

class Game
{
public:
    Game();

    bool loadLevel(const std::string& filename);
    void setHero(std::unique_ptr<Hero> hero);

    void run();

private:
    void render() const;
    bool handleInput();
    bool checkWin()  const;
    bool checkLoss() const;
    void updateEnemies();

    Board                               m_board;
    std::unique_ptr<Hero>               m_hero;
    std::vector<std::unique_ptr<Enemy>> m_enemies;

    bool m_running = false;
    bool m_won = false;
};