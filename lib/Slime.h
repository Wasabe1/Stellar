#ifndef SLIME_H
#define SLIME_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position


/** Slime Class
@author Li, University of Leeds
@brief Controls the slime in the Stellar game 
@date Febraury 2023
*/ 

class Slime
{

public:
    Slime();
    void init(int height,int width,int speed);
    void draw(N5110 &lcd);
    void update();
    /// accessors and mutators
    void set_velocity(Position2D v);
    Position2D get_velocity();
    Position2D get_pos();
    int get_height();
    int get_width();
    void set_pos(Position2D p);
    
private:

    Position2D _velocity;
    int _act;
    int _height;
    int _width;
    int _x;
    int _y;
};
#endif