#ifndef FIREBALL_H
#define FIREBALL_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position


/** Fireball Class
@author Li, University of Leeds
@brief Controls the Fireball in the Stellar game 
@date Febraury 2023
*/ 

class Fireball
{

public:
    Fireball();
    void init(int size,int speed);
    void draw(N5110 &lcd);
    void update(bool fire, Position2D pos);
    /// accessors and mutators
    Position2D get_pos();
    int get_size();
    bool get_fireball_state();
    void set_pos(Position2D p);
    
private:

    Position2D _velocity;
    int act;
    bool _active;
    int _size;
    int _x;
    int _y;
};
#endif