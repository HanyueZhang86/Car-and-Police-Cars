#ifndef RANDOM_H
#define RANDOM_H

class Random
{
public:
    Random();
    void Seed();//call this only once per program
    int Next(int lo, int hi);
};

#endif // RANDOM_H
