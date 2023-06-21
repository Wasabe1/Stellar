#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"  // for Position
#include <vector>
#define OBJECT_NUMBER 1
/** Background Class
@author Li, University of Leeds
@brief Controls the Background in the Stellar game 
@date Febraury 2023
*/ 

class Background
{

public:
    Background();
    void init(int speed);
    void draw(N5110 &lcd);
    void update();
    /// accessors and mutators
    vector<int> background_pos = {};

private:
    Position2D _velocity;
};
#endif