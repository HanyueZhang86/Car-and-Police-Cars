#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
class Game{
public:
    Game();
    void Draw();
    void run();
    void processEvents();
    void update();
    void render();
    void ShowShapes();
    bool inrange(sf::Vector2f mouse);
    void endEvent();

private:
    sf::RenderWindow end;
    sf::RectangleShape restart;
    sf::Text restartbutton;

    sf::RenderWindow window;
    sf::CircleShape mousePoint;
    sf::RectangleShape sideBar;
    sf::Clock clock;
    System system;
    int command;
    sf::Vector2f mouse;
    sf::Font font;
    sf::Text myTextLabel;
    bool mouseIn;
    Sidebar sidebar;
    bool start;
    bool done;
    sf::Text score;


};


#endif // GAME_H
