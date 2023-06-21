#ifndef BULLET_H
#define BULLET_H
#define MAX_BULLETS 9

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position
#include "Aircraft.h"
#include <vector>
/** Bullet Class
@author Li, University of Leeds
@brief Controls the Bullet in the Stellar game 
@date Febraury 2023
*/ 

class Bullet
{

public:
    Bullet();
    void init(int height,int width,int speed);
    void draw(N5110 &lcd);
    void update(bool fire, Position2D a_pos);
    /// accessors and mutators
    void set_velocity(Position2D v);
    Position2D get_pos(int i);
    int get_bullet_height();
    int get_bullet_width();
    int get_bullet_state(int i);
    void set_pos(Position2D p, int i);
    vector<Position2D> bullets_pos = {};

private:
    Position2D _velocity;
    vector<bool> _bullets_state = {};
    int _bullet_height;
    int _bullet_width;
    Aircraft _aircraft;
};
#endif