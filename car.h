#ifndef CAR_H
#define CAR_H
#include <SFML/Graphics.hpp>


class car
{
public:
    car();
    car(sf::Color color, sf::Vector2f pos, sf::Vector2f size, float speed );
    void step(sf::Vector2f direction);
    void draw(sf::RenderWindow &window);
    void Movetoword(car user);
    void Movetoword(sf::Vector2f mouse);
    void wall();
    sf::Vector2f Pos();
    float speed();
    void Setspeed(float speed);
    void Setpos(sf::Vector2f pos);
    bool Catch(car e);
    void Follow(sf::Vector2f cops,int order);
    int get_carsh();
    void decr();
    void hadcrash();
    void nocrash();
    bool Gethad();
private:
    sf::Vector2f _pos;
    sf::Vector2f _size;
    float _speed;
    sf::Color _color;
    int crash_count;
    sf::Text CrashLabel;
    sf::Font font;
    bool _had;
    sf::Texture image;
    sf::Sprite sprite;
    sf::IntRect intrect;
};

#endif // CAR_H
