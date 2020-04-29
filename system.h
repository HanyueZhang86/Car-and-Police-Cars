#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "car.h"
#include "particle.h"
using namespace std;
class System
{
public:
    System();
    void Step(int command, sf::Vector2f mouse);
    int Size();
    void Draw(sf::RenderWindow& widnow);
    void Gettime(sf::Clock clock);
    int Getlife();
    void decrease();
    void scoreIn();
    int GetScore();
private:
    sf::Clock clock;
    vector<Particle> system;
    vector<car> cars;
    int _num_used;
    int _life;
    int _score;

};

#endif // SYSTEM_H
