#include "system.h"
#include "random.h"
#include "MyVector.h"
#include "car.h"
#include <iostream>
#include <cmath>
#include <constants.h>
//void CreateRandomParticles(int n){
//    Random r;
//    int xpos = 100;
//    int ypos = 100;

//    for (int i=0; i<n; i++){
//        Vector pos(r.Next(0,SCREEN_WIDTH),r.Next(0,SCREEN_HEIGHT));
//        xpos += 40;
//        Vector vel(r.Next(-5,5), r.Next(-5,5));
//        Vector acc(0.01,0.02);
//        double mass = r.Next(5,25);


//        int r_ = r.Next(0,255);
//        int g_ = r.Next(0,255);
//        int b_ = r.Next(0,255);

//        Particle p(pos, vel, acc, mass,r_,g_,b_);
//        //system.push_back(p);

//    }

//}
int theOne=0;
System::System()
{
    Random r;
    int xpos = 100;
    int ypos = 100;
    int a =r.Next(0,SCREEN_HEIGHT);
    int b=r.Next(0,SCREEN_WIDTH);
    //num used
    _num_used=0;
    cars.push_back(car());
    _num_used++;
    cars.push_back(car(sf::Color::Blue,sf::Vector2f(a,0),sf::Vector2f(CARSIZE,CARSIZE),5));
    _num_used++;
//    cars.push_back(car(sf::Color::Red,sf::Vector2f(0,b),sf::Vector2f(30,30),5));
//    _num_used++;
//    cars.push_back(car(sf::Color::Blue,sf::Vector2f(SCREEN_HEIGHT,b),sf::Vector2f(30,30),15));
//    _num_used++;
    //life
    _life=4;
    _score=0;
    //particles:
    for (int i=0; i<15; i++){

        Vector pos(r.Next(0,WORK_PANEL-300),r.Next(0,SCREEN_HEIGHT-300));
        //Vector pos(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
        //Vector pos(SCREEN_WIDTH-20,SCREEN_HEIGHT/2);

        Vector vel(r.Next(-0.0,0.0), r.Next(-0.0,0.0));
        Vector acc(0.00,0.00);

        double mass = r.Next(4,40);
        int r_ = r.Next(0,255);
        int g_ = r.Next(0,255);
        int b_ = r.Next(0,255);

        Particle p(pos, vel, acc, mass,r_,g_,b_);
        system.push_back(p);
    }
}

/*------------------------------------------------------------------
            Movement functions:
------------------------------------------------------------------*/
void Fall(vector<Particle>& system){
    for (int i=0; i<system.size(); i++){
        system[i].Move(Vector(0.00, -0.10));
    }
}

//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command, sf::Vector2f mouse){
//    Fall(system);
//    return;
//    Vector f(0.00,0.00);
//    for (int i=0; i<system.size(); i++){
//        for (int j=0; j<system.size(); j++){
//            if (i!=j){
//                cout<<i<<":"<<j<<endl;
//                Vector diff = (system[j].Pos()-system[i].Pos());
//                Vector unit = diff.Unit();

//                double dist = diff.Mag()<5?5:diff.Mag();

//                //m = m1 * m2 / d
//                double m = system[i].Mass() * system[j].Mass() / dist;

//                unit = unit * m;
//                f = f + unit;
//            }
//        }
//    system[i].Move(f);
//    }
//    return;
//    cars[0].step(command);

//    for (int i=0; i<cars.size(); i++){
//        cars[i].step(command);
//    }
        Random r;

        switch (command){
        case 1:
            cars[0].step(sf::Vector2f(-cars[0].speed(),0));
            cars[1].Movetoword(cars[0]);
//            cars[2].Follow(sf::Vector2f(cars[1].Pos().x,cars[1].Pos().y));
//            cars[1].Setspeed(r.Next(0,10));
//            system[i].Move(Vector(-0.01,0));
            break;
        case 2:
            cars[0].step(sf::Vector2f(cars[0].speed(),0));
            cars[1].Movetoword(cars[0]);
//            cars[2].Follow(sf::Vector2f(cars[1].Pos().x,cars[1].Pos().y));
//            cars[1].Setspeed(r.Next(0,10));
            break;
        case 3:
            cars[0].step(sf::Vector2f(0,-cars[0].speed()));
            cars[1].Movetoword(cars[0]);
//            cars[2].Follow(sf::Vector2f(cars[1].Pos().x,cars[1].Pos().y));
//            cars[1].Setspeed(r.Next(0,10));
            break;
        case 4:
            cars[0].step(sf::Vector2f(0,cars[0].speed()));
            cars[1].Movetoword(cars[0]);
//            cars[2].Follow(sf::Vector2f(cars[1].Pos().x,cars[1].Pos().y));
            break;
        case 5:
            cars[0].step(sf::Vector2f(-cars[0].speed(),-cars[0].speed()));
            break;
        case 6:
            cars[0].step(sf::Vector2f(cars[0].speed(),-cars[0].speed()));
            break;
        case 7:
            cars[0].step(sf::Vector2f(-cars[0].speed(),cars[0].speed()));
            break;
        case 8:
            cars[0].step(sf::Vector2f(cars[0].speed(),cars[0].speed()));
            break;
        }
        cars[1].Catch(cars[0]);
        for(int i=1 ;i<cars.size();i++)
            cars[i].Movetoword(cars[0]);
//        cars[1].Movetoword(cars[0]);
//        cars[2].Movetoword(cars[0]);
//        cars[3].Movetoword(cars[0]);
//        cars[3].Follow(sf::Vector2f(cars[1].Pos().x,cars[1].Pos().y),2);
        cars[0].Setpos(mouse);
//        cars[0].Movetoword(mouse);
}

int System::Size(){
    return system.size();
}
void System::Gettime(sf::Clock clock){
    clock=clock;
}
void System::Draw(sf::RenderWindow& window){
    Random r;
    int c=r.Next(0,SCREEN_HEIGHT);
    int b=r.Next(0,SCREEN_WIDTH);
    sf::Time a=clock.getElapsedTime();
//    a==static_cast<int>(a.asSeconds());
    //cout<<a.asSeconds()<<endl;
    //window.clear();
    for(int i=0;i<cars.size();i++)
        cars[i].draw(window);

    int max=static_cast<int>(cars.size());
    if(max>2&&Getlife()>0)
        for(int i=1;i<max;i++)
            for(int j=1; j<max;j++)
                if(i!=j&&cars[i].Catch(cars[j])){
                    if(j<i){
                        cars[j].Setpos(sf::Vector2f(b,c));
                        _score+=10;
                    }else{
                        cars[i].Setpos(sf::Vector2f(b,c));
                        _score+=10;
                    }
                }
    //cars[0].clear(window)
    for(int i=1;i<cars.size();i++){
        if(cars[0].Catch(cars[i])&&cars[i].Gethad()==false){
            decrease();
            cars[i].hadcrash();
            theOne=i;
            //cout<<"theont insdie"<<theOne<<endl;
        }
    }

    const bool debug=false;
    if(debug){
        cout<<"a is "<<a.asSeconds()<<endl<<
              "the one "<<theOne<<endl;
    }
    if(a.asSeconds()>5){
        cars[theOne].nocrash();
        //cout<<" no crash "<<cars[theOne].Gethad();
    }

    if(a.asSeconds()>5&&cars.size()<20){
        //cout<<"size is "<<cars.size()<<endl;
        cars.push_back(car(sf::Color::Blue,sf::Vector2f(0,30),sf::Vector2f(CARSIZE,CARSIZE),5));
        clock.restart();
        if(Getlife()>0)
            scoreIn();
    }




}
int System::Getlife(){
    return cars[0].get_carsh();
}
void System::decrease(){

    cars[0].decr();
}
void System::scoreIn(){
    _score+=25;
}
int System::GetScore(){
    return _score;
}
