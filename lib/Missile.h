#ifndef MISSILE_H
#define MISSILE_H
#define MAX_BLAST_RADIUS 6

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position


/** Missile Class
@author Li, University of Leeds
@brief Controls the Missile in the Stellar game 
@date Febraury 2023
*/ 

class Missile
{

public:
    Missile();
    void init(int height,int width,int speed);
    void draw(N5110 &lcd);
    void update(bool emit, Position2D target, Position2D aircraft_pos);
    /// accessors and mutators
    void set_velocity(Position2D v);
    Position2D get_velocity();
    Position2D get_pos();
    bool get_missile_state();
    int get_missile_height();
    int get_missile_width();
    void set_pos(Position2D p);
    void is_hit();
    
private:

    Position2D _velocity;
    bool _active;
    bool _hit;
    int _act;
    int _explode_radius;
    int _ex_x;
    int _ex_y;
    int _height;
    int _width;
    int _x;
    int _y;
};
#endif