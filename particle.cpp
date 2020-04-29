#include "particle.h"
#include "constants.h"
#include "random.h"
#include "car.h"
#include <SFML/Graphics.hpp>
#include <cmath>

Particle::Particle():pos(Vector(0,0)), velocity(Vector(0,0)), acc(Vector(0,0)), mass(0.0){

}

Particle::Particle(const Vector& loc_, const Vector& velocity_, const Vector& acc_, double mass_, int r_, int g_, int b_):
    pos(loc_),
    velocity(velocity_),
    acc(acc_),
    mass(mass_),
    color(sf::Color(r_, g_, b_)){

}

Vector& Particle::Pos(){
    return pos;
}

Vector& Particle::Velocity(){
    return velocity;
}

Vector& Particle::Acceleration(){
    return acc;
}

double& Particle::Mass(){
    return mass;
}

ostream& operator <<(ostream& outs, const Particle& particle){
    outs<<"Position: "<<particle.pos<<", Velocity: "<<particle.velocity<<", Acceleration: "<<particle.acc<<", Mass: "<<particle.mass<<endl;
    return outs;
}

void Particle::Move(const Vector& appliedForce){

    acc = acc + appliedForce/mass; //not counting mass
    velocity = velocity + acc;
    acc = acc *  0;
                //cool way to reset a vector to zero.
                //since applied force is the net force applied to this particle
                //at any given moment (every single frame), acc must be reset to zero
                //after it has acted on this particle

    //cin.get();
//    cout<<endl<<"Move(): posJ: "<<pos<<"velocity: "<<velocity<<endl;
    pos = pos + velocity;
    //return;

    if ((pos.X())>=WORK_PANEL-2*mass)
        velocity = velocity * Vector(-1,1);
    if (pos.X()<=0)
        velocity = velocity*Vector(-1,1);
    if ((pos.Y())>=SCREEN_HEIGHT-2*mass)
        velocity = velocity * Vector(1,-1);
    if (pos.Y()<=0)
        velocity = velocity*Vector(1,-1);



}

void Particle::ApplyForce(Vector f){
    acc = acc + f;
}

void Particle::Direction(){
    //accelerate towards the mouse!
    //call me from move();
    Vector mouseLoc(sf::Mouse::getPosition());
    Vector direction = mouseLoc - pos;
    acc = direction.Unit()*0.1;

}

void Particle::Draw(sf::RenderWindow& window){
    sf::CircleShape c((mass));
    //c.setRadius(mass);
    c.setPosition(pos.V());
    c.setFillColor(color);
    window.draw(c);

}
void Particle::ElasticCollision(const Particle& other){
    //http://hyperphysics.phy-astr.gsu.edu/hbase/elacol2.html
    //v'1 = (m1-m2)/(m1+m2)v1   v'2 = 2m1/(m1+m2) v1
    double multiplier = (mass - other.mass)/(mass + other.mass) ;
    velocity = Vector(velocity.X() * multiplier, velocity.Y() * multiplier);

}

bool Particle::Collided(const Particle& other) const{
    double d = pos.Distance(other.pos);
    cout<<d<<"==="<<mass+other.mass<<endl;
    return (d<=(mass + other.mass)) ? true : false;
}
