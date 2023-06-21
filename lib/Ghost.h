#ifndef GHOST_H
#define GHOST_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position


/** Ghost Class
@author Li, University of Leeds
@brief Controls the Ghost in the Stellar game 
@date Febraury 2023
*/ 

class Ghost
{

public:
    Ghost();
    void init(int size,int speed);
    void draw(N5110 &lcd);
    void update();
    /// accessors and mutators
    void set_velocity(Position2D v);
    Position2D get_velocity();
    Position2D get_pos();
    int get_size();
    void set_pos(Position2D p);
    
private:

    Position2D _velocity;
    int act;
    int _size;
    int _x;
    int _y;
};
#endif