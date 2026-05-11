#include "Game.h"
#include "Chaser.h"

#include <iostream>
#include <algorithm>

Game::Game()
{
}

bool Game::loadLevel(const std::string& filename)
{
    if (!m_board.load(filename))
        return false;

    m_enemies.clear();
    for (const Point& p : m_board.getEnemyStarts())
        m_enemies.push_back(std::make_unique<Chaser>(p));

    return true;
}

void Game::setHero(std::unique_ptr<Hero> hero)
{
    m_hero = std::move(hero);
    m_hero->setPos(m_board.getHeroStart());
}

void Game::run()
{
    m_running = true;
    m_won = false;

    while (m_running)
    {
        render();
        handleInput();

        if (!m_running) break;

        if (checkWin())
        {
            render();
            std::cout << "\n*** You reached the exit! You win! ***\n";
            m_running = false;
            m_won = true;
            break;
        }

        if (checkLoss())
        {
            render();
            std::cout << "\n*** An enemy caught you! You lose! ***\n";
            m_running = false;
            break;
        }

        updateEnemies();

        if (checkLoss())
        {
            render();
            std::cout << "\n*** An enemy caught you! You lose! ***\n";
            m_running = false;
            break;
        }

        m_hero->tickCooldown();
    }
}

void Game::render() const
{
    int n = m_board.getSize();

    std::vector<std::string> display(n);
    for (int y = 0; y < n; y++)
    {
        display[y].resize(n);
        for (int x = 0; x < n; x++)
            display[y][x] = m_board.getCell(x, y);
    }

    for (const auto& enemy : m_enemies)
        if (enemy->isAlive())
            display[enemy->getPos().y][enemy->getPos().x] = enemy->getSymbol();

    display[m_hero->getPos().y][m_hero->getPos().x] = m_hero->getSymbol();

    std::cout << "\n";
    for (int y = 0; y < n; y++)
    {
        for (int x = 0; x < n; x++)
            std::cout << display[y][x];
        std::cout << "\n";
    }

    std::cout << "\nHero [" << m_hero->getSymbol() << "]";
    if (m_hero->canUseAbility())
        std::cout << " | Ability: READY";
    else
        std::cout << " | Ability: " << m_hero->getCooldown() << " turns remaining";
    std::cout << "\n";
    std::cout << "Commands: L R U D | OOP (ability) | Q (quit)\n";
}

void Game::handleInput()
{
    std::string input;
    std::cout << "> ";
    std::cin >> input;

    for (char& c : input)
        c = toupper(c);

    if (input == "Q")
    {
        std::cout << "Quitting...\n";
        m_running = false;
        return;
    }

    if (input == "OOP")
    {
        if (m_hero->canUseAbility())
            m_hero->useAbility(m_board);
        else
            std::cout << "Ability not ready! (" << m_hero->getCooldown() << " turns remaining)\n";
        return;
    }

    if (input.size() == 1 && (input[0] == 'L' || input[0] == 'R' || input[0] == 'U' || input[0] == 'D'))
    {
        m_hero->move(input[0], m_board);
        return;
    }

    std::cout << "Unknown command. Use L, R, U, D, OOP or Q.\n";
}

bool Game::checkWin() const
{
    return m_hero->getPos() == m_board.getExitPos();
}

bool Game::checkLoss() const
{
    for (const auto& enemy : m_enemies)
        if (enemy->isAlive() && enemy->getPos() == m_hero->getPos())
            return true;
    return false;
}

void Game::updateEnemies()
{
    for (auto& enemy : m_enemies)
        if (enemy->isAlive())
            enemy->update(m_hero->getPos(), m_board);
}