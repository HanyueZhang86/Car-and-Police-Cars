#include "random.h"
#include <ctime>
#include <iostream>
#include <stdlib.h>
using namespace std;

Random::Random()
{
}
void Random::Seed(){
    srand(time(0));

}

int Random::Next(int lo, int hi){
    int r = rand()%(hi-lo+1)+lo;

    return r;

}
//string Random::colour(){
//    int r =rand()%5;
//    if(r==1)
//        return "Blue";

//}
