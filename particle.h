#ifndef PARTICLE_H
#define PARTICLE_H
#include "MyVector.h"
#include <SFML/Graphics.hpp>

class Particle
{
public:
    Particle();
    Particle(const Vector& loc_, const Vector& velocity_, const Vector& acc_, double mass_, int r_, int g_, int b_);
//    void SetPosition(const Vector& pos);
//    void SetVelocity(const Vector& velocity_);
//    void SetAcceleration(const Vector& acc_);
//    void SetMass(double m);

    Vector& Pos();
    Vector& Velocity();
    Vector& Acceleration();
    double& Mass();
    friend ostream& operator <<(ostream& outs, const Particle& particle);
    void Move(const Vector& appliedForce=Vector(0,0));
    void Direction();
    void ApplyForce(Vector f);
    void Draw(sf::RenderWindow& window);
    bool Collided(const Particle& other) const;
    void ElasticCollision(const Particle& other);

private:
    double radius;
    sf::Color color;
    Vector pos;
    Vector velocity;
    Vector acc;
    double mass;

};

#endif // PARTICLE_H
