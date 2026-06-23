#include "Game.h"
#include "Chaser.h"
#include "Patroller.h"
#include "Console.h"
#include "Rogue.h"

#include <iostream>
#include <algorithm>

bool Game::loadLevel(const std::string& filename)
{
    if (!m_board.load(filename))
        return false;

    m_enemies.clear();
    for (const Point& p : m_board.getEnemyStarts())
        m_enemies.push_back(std::make_unique<Chaser>(p));

    if (m_board.getPatrolPoints().size() >= 2)
        m_enemies.push_back(std::make_unique<Patroller>(m_board.getPatrolPoints()));


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

		bool validTurn = handleInput();

        if (!m_running) break;
        if (!validTurn) continue;

        if (checkWin())
        {
            render();
            std::cout << "\n*** You reached the exit! You win! ***\n";
            m_running = false;
            m_won = true;
            break;
        }

        //if (checkLoss())
        //{
        //    render();
        //    std::cout << "\n*** An enemy caught you! You lose! ***\n";
        //    m_running = false;
        //    break;
        //}

		Rogue* rogue = dynamic_cast<Rogue*>(m_hero.get());
		bool invisible = rogue && rogue->isInvisible();

        if (!invisible)
        {
			updateEnemies();
            
            if (checkLoss())
            {
                render();
                std::cout << "\n*** An enemy caught you! You lose! ***\n";
                m_running = false;
                break;
            }
        }

        m_hero->tickCooldown();

		if (rogue) rogue->tickInvisibility();
    }
}

void Game::render() const
{
    Console::clear();

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
        {
            char c = display[y][x];
            switch (c) 
            {
            case '*': Console::setColor(Console::DARK_GRAY);    break;
            case 'F': Console::setColor(Console::GREEN);        break;
            case 'E': Console::setColor(Console::RED);          break;
            case 'W': Console::setColor(Console::CYAN);         break;
			case 'K': Console::setColor(Console::BLUE);         break;
			case 'R': Console::setColor(Console::MAGENTA);      break;
            default:  Console::setColor(Console::GRAY);         break;
            }
            std::cout << c;
        }
        Console::reset();
        std::cout << "\n";
    }

    Console::reset();

    std::cout << "\nHero [" << m_hero->getSymbol() << "]";
    if (m_hero->canUseAbility())
    { 
        Console::setColor(Console::GREEN);
        std::cout << " | Ability: READY";
    }
    else 
    {
        Console::setColor(Console::RED);
        std::cout << " | Ability: " << m_hero->getCooldown() << " turns remaining";
    }
    Console::reset();

    Rogue* rogue = dynamic_cast<Rogue*>(m_hero.get());
    if (rogue && rogue->isInvisible())
    {
        Console::setColor(Console::MAGENTA);
        std::cout << " | INVISIBLE: " << rogue->getInvisibilityTurns() << " turns left";
        Console::reset();
    }


    std::cout << "\n";
    std::cout << "Commands: L R U D | OOP (ability) | Q (quit)\n";
}

bool Game::handleInput()
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
        return true;
    }

    if (input == "OOP")
    {
        if (m_hero->canUseAbility())
            m_hero->useAbility(m_board, m_enemies);
        else
            std::cout << "Ability not ready! (" << m_hero->getCooldown() << " turns remaining)\n";
        return false;
    }

    if (input.size() == 1 && (input[0] == 'L' || input[0] == 'R' || input[0] == 'U' || input[0] == 'D'))
    {
		Point before = m_hero->getPos();
        m_hero->move(input[0], m_board);
        if (m_hero->getPos() == before)
            return false;
        
        return true;
    }

    std::cout << "Unknown command. Use L, R, U, D, OOP or Q.\n";
    return false;
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