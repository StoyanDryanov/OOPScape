#include "Game.h"
#include "Wizard.h"
#include "Knight.h"
#include "Rogue.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    srand((unsigned)time(nullptr));

    Game game;

    if (!game.loadLevel("level1.txt"))
    {
        std::cerr << "Failed to load level.\n";
        return 1;
    }

    game.setHero(std::make_unique<Rogue>(Point{ 0, 0 }));

    game.run();

    return 0;
}