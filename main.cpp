#include <iostream>
#include "game.h"
#include "MyVector.h"
#include "random.h"
#include <fstream>
using namespace std;

int main()
{
    sf::Vector2f(3,4);
    Random r;
    r.Seed();

    Vector v;
    Game game;
    game.run();
    return 0;
}
