#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

class Aircraft
{
public:

    Aircraft();
    void init(int x,int height,int width);
    void draw(N5110 &lcd,UserInput input);
    void update(UserInput input);
    Position2D get_pos();
    int get_height();
    int get_width();
    void set_pos(Position2D p);

private:

    int _height;
    int _width;
    int _x;
    int _y;
    int _speed;

};
#endif