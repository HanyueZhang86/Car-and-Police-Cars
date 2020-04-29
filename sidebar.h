#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
private:
    sf::RectangleShape rect;
    vector<string> items;
    float _left;
    float _width;
    sf::Font font;
    sf::Text text;

};

#endif // SIDEBAR_H
