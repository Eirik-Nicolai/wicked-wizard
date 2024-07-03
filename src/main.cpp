#include <iostream>
#include <string>
#include <chrono>

#include "engine/game.hpp"

auto main(int argc, char *argv[]) -> int
{
    Game g;
    if (g.Construct(1600, 900, 1, 1, true))
        g.Start();

    return 0;
}
