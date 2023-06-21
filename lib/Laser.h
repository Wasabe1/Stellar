#ifndef LASER_H
#define LASER_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position


/** Laser Class
@author Li, University of Leeds
@brief Controls the Laser in the Stellar game 
@date Febraury 2023
*/ 

class Laser
{

public:
    Laser();
    void init(int size);
    void draw(N5110 &lcd);
    void update(Position2D pos);
    /// accessors and mutators
    Position2D get_pos();
    int get_size();
    bool get_laser_state();
    void set_pos(Position2D p);
    


private:

    Position2D _velocity;
    int _act;
    bool _active;
    bool _ready;
    int _ready_time;
    int _size;
    int _x;
    int _y;
};
#endif