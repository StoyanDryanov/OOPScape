// OOPScape
// Стоян Златев Дрянов, ФН: 5MI0600612

#include "Game.h"
#include "Wizard.h"
#include "Knight.h"
#include "Rogue.h"
#include "Console.h"

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

std::unique_ptr<Hero> pickHero()
{
    Console::clear();
    std::cout << "=== OOPScape ===\n\n";
    std::cout << "Choose your hero:\n\n";

    Console::setColor(Console::CYAN);
    std::cout << "  [1] Wizard (W)";
    Console::reset();
    std::cout << " - Teleports to a random free cell (cooldown: 3 turns)\n";

    Console::setColor(Console::BLUE);
    std::cout << "  [2] Knight (K)";
    Console::reset();
    std::cout << " - Kills all adjacent enemies (cooldown: 4 turns)\n";

    Console::setColor(Console::MAGENTA);
    std::cout << "  [3] Rogue  (R)";
    Console::reset();
    std::cout << " - Turns invisible for 3 turns (cooldown: 5 turns)\n";

    std::cout << "\n> ";

    std::string input;
    while (true)
    {
        std::cin >> input;
        if (input == "1") return std::make_unique<Wizard>(Point{ 0, 0 });
        if (input == "2") return std::make_unique<Knight>(Point{ 0, 0 });
        if (input == "3") return std::make_unique<Rogue>(Point{ 0, 0 });
        std::cout << "Invalid choice. Enter 1, 2 or 3: ";
    }
}

int main()
{
    srand((unsigned)time(nullptr));

    std::vector<std::string> levels = {
        "level1.txt",
        "level2.txt",
		"level3.txt",
        "level4.txt"
    };

    auto hero = pickHero();
    char heroSymbol = hero->getSymbol();

    int currentLevel = 0;

    while (currentLevel < (int)levels.size())
    {
        Console::clear();
        std::cout << "=== Level " << currentLevel + 1 << " ===\n";

        if (heroSymbol == 'W') hero = std::make_unique<Wizard>(Point{ 0, 0 });
        else if (heroSymbol == 'K') hero = std::make_unique<Knight>(Point{ 0, 0 });
        else if (heroSymbol == 'R') hero = std::make_unique<Rogue>(Point{ 0, 0 });

        Game game;

        if (!game.loadLevel(levels[currentLevel]))
        {
            std::cerr << "Failed to load level: " << levels[currentLevel] << "\n";
            return 1;
        }

        game.setHero(std::move(hero));
        game.run();

        if (game.isWon())
        {
            currentLevel++;
            if (currentLevel >= (int)levels.size())
            {
                Console::clear();
                Console::setColor(Console::YELLOW);
                std::cout << "\n*** Congratulations! You completed all levels! ***\n";
                Console::reset();
            }
        }
    }

    return 0;
}
