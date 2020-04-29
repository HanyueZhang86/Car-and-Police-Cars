#include "car.h"
#include "constants.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
using namespace  std;
car::car()
{
    _color = sf::Color(125, 125, 125);
    _pos=sf::Vector2f(0,0);
    _size=sf::Vector2f(CARSIZE,CARSIZE);
    _speed=40;
//    _had=false;
    crash_count=4;
    if (!font.loadFromFile("arial.ttf")){
        cout<<"Car() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
//    if(!image.loadFromFile("4x4.png")){
//        cout<<"Car() CTOR: image failed to load"<<endl;
//        cin.get();
//        exit(-1);
//    }
//    intrect.height=218;
//    intrect.width=218;
//    intrect.left=654;
//    intrect.top=0;
//    sprite.setTexture(image);
//    sprite.setTextureRect(intrect);
//    sprite.setPosition(_pos);
//    sprite.setScale(0.5f,0.5f);

}
car::car(sf::Color color, sf::Vector2f pos, sf::Vector2f size, float speed ){
    _color = color;
    _pos=pos;
    _size=size;
    _speed=speed;
    crash_count=-2;
    _had=false;
    if (!font.loadFromFile("arial.ttf")){
        cout<<"Car() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
//    if(!image.loadFromFile("4x4.png")){
//        cout<<"Car() CTOR: image failed to load"<<endl;
//        cin.get();
//        exit(-1);
//    }

//    intrect.height=218;
//    intrect.width=218;
//    intrect.left=654;
//    intrect.top=0;

}
void car::step(sf::Vector2f direction){
    //calculate your neew pos
    //keeps getting
    //called from system::step
    _pos+=direction;
    wall();
}

sf::Vector2f car::Pos(){
    return _pos;
}
float car::speed(){
    return _speed;
}
void car::Setspeed(float speed){
    _speed=speed;
}
void car::Setpos(sf::Vector2f pos){
    _pos=pos;
    wall();
}
void car::draw(sf::RenderWindow &window){
    //draw me on the window object
    //gets called from system::draw()

    CrashLabel =sf::Text(to_string(crash_count),font);
    CrashLabel.setCharacterSize(30);
    CrashLabel.setStyle(sf::Text::Bold);
    CrashLabel.setColor(sf::Color::Green);
    CrashLabel.setPosition(_pos);

//    sf::RectangleShape m(sf::Vector2f(SCREEN_WIDTH,SCREEN_HEIGHT));
//    m.setPosition(sf::Vector2f(534,234));
//    m.setOutlineThickness(5);
//    m.setOutlineColor(sf::Color::Blue);
//    m.setFillColor(sf::Color::Black);

//    sprite.setTexture(image);
//    sprite.setTextureRect(intrect);
//    sprite.setPosition(_pos);
//    sprite.setScale(_size.x/218,_size.y/218);
 //   sprite.scale(sf::Vector2f(_size.x,218));

    sf::RectangleShape c(_size);
    c.setPosition(_pos);
    c.setFillColor(_color);
    c.setSize(_size);
    window.draw(c);
    if(crash_count>-1)
        window.draw(CrashLabel);
//    window.draw(line);
//    window.draw(m);
 //   window.draw(sprite);

}
bool car::Catch(car e){
    int a = e._pos.x - _pos.x;
        int b = e._pos.y - _pos.y;
        if((a <= 0 && -a <= e._size.x) || (a > 0 && a <= _size.x)){
            if(b >= 0 && b <= e._size.y)
                return true;
            if(b < 0 && -b <= _size.y)
                return true;
            else
                return false;
        }
        else{
            return false;
        }
   // _pos.x cops X,, _pos.y is cops y _size.x is cops width _size.y is cops height e._pos.x
}

void car::wall(){
    sf::Vector2f pos = _pos;
    const bool debug=false;
    if(debug){
        cout<<"x is "<<pos.x<<endl<<
              "y is "<<pos.y<<endl;
    }
    if (pos.x<=0)
        _pos.x=0;
    if (pos.y<=-10)
        _pos.y=0;
    if(pos.y>=SCREEN_HEIGHT-_size.y)
        _pos.y=SCREEN_HEIGHT-_size.y;
    if(pos.x>SCREEN_WIDTH-SIDE_BAR-_size.x)
        _pos.x=SCREEN_WIDTH-SIDE_BAR-_size.x;
}
void car::Movetoword(car user){
    wall();
    if(Catch(user))
        return;
    int dirtx,dirty;
    dirtx=user._pos.x-_pos.x;
    dirty=user._pos.y-_pos.y;
    const bool debug=false;
    if(debug){
        cout<<"dirtx is"<<dirtx<<endl<<
              "dirty is "<<dirty<<endl;
    }

    if(dirtx<0&&dirty<0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y-=_speed;
           // intrect.top=218;
        }else{
            _pos.x-=_speed;
           // intrect.top=218*2;
        }
    }
    if(dirtx>=0&&dirty<0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y-=_speed;
            //intrect.top=218;
        }else{
            _pos.x+=_speed;
           // intrect.top=0;
        }
    }
    if(dirtx>=0&&dirty>=0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y+=_speed;
          //  intrect.top=218*3;
        }else{
            _pos.x+=_speed;
           // intrect.top=0;
        }
    }
    if(dirtx<0&&dirty>=0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y+=_speed;
           // intrect.top=218*3;
        }else{
            _pos.x-=_speed;
           // intrect.top=218*2;
        }
    }
}
void car::Follow(sf::Vector2f cops, int order){
    switch (order) {
    case 1:
        _pos.x=cops.x-_size.x;
        _pos.y=cops.y+_size.y;
        break;
    case 2:
        _pos.x=cops.x+_size.x;
        _pos.y=cops.y+_size.y;
    default:
        break;
    }

}
int car::get_carsh(){
    return crash_count;
}
void car::decr(){
    if(crash_count>0)
        crash_count--;
}
void car::hadcrash(){
    _had=true;
}

bool car::Gethad(){
    return _had;
}
void car::nocrash(){
    _had=false;
}
void car::Movetoword(sf::Vector2f mouse){
    wall();
    int dirtx,dirty;
    dirtx=mouse.x-_pos.x;
    dirty=mouse.y-_pos.y;
    if(dirtx<0&&dirty<0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y-=_speed;
            intrect.top=218;
        }else{
            _pos.x-=_speed;
            intrect.top=218*2;
        }
    }
    if(dirtx>=0&&dirty<0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y-=_speed;
            intrect.top=218;
        }else{
            _pos.x+=_speed;
            intrect.top=0;
        }
    }
    if(dirtx>=0&&dirty>=0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y+=_speed;
            intrect.top=218*3;
        }else{
            _pos.x+=_speed;
            intrect.top=0;
        }
    }
    if(dirtx<0&&dirty>=0){
        if(abs(dirtx)<abs(dirty)){
            _pos.y+=_speed;
            intrect.top=218*3;
        }else{
            _pos.x-=_speed;
            intrect.top=218*2;
        }
    }
}
