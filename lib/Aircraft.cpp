#include "Aircraft.h"

// nothing doing in the constructor and destructor
Aircraft::Aircraft() { }

void Aircraft::init(int x,int height,int width) {
    _x = x + 1;  // x value on screen is fixed
    _y = HEIGHT/2 - height/2;  // y depends on height of screen and height of Aircraft
    _height = height;
    _width = width;
    _speed = 1;  // default speed
}

void Aircraft::draw(N5110 &lcd,UserInput input) {
    const int shipm[9][11]= {

    { 0,0,0,0,0,1,1,0,0,0,0,},
    { 0,0,0,0,0,1,1,0,0,0,0,},
    { 1,0,0,0,1,1,1,0,0,0,0,},
    { 1,0,0,1,1,1,1,1,1,0,1,},
    { 1,1,1,0,1,1,0,0,0,1,1,},
    { 1,0,0,1,1,1,1,1,1,0,1,},
    { 1,0,0,0,1,1,1,0,0,0,0,},
    { 0,0,0,0,0,1,1,0,0,0,0,},
    { 0,0,0,0,0,1,1,0,0,0,0,},
 
};  
    const int shipu[6][11]= {
    { 1,1,0,0,0,0,0,0,0,0,0,},
    { 1,1,0,0,0,1,1,1,0,0,0,},
    { 1,1,1,1,1,0,0,0,1,0,1,},
    { 0,0,1,1,1,1,1,1,1,1,1,},
    { 0,0,1,0,0,0,0,0,1,0,1,},
    { 0,0,0,0,0,0,0,0,1,0,0,},
};
    const int shipd[6][11]= {
    { 0,0,0,0,0,0,0,0,1,0,0,},
    { 0,0,1,0,0,0,0,0,1,0,1,},  
    { 0,0,1,1,1,1,1,1,1,1,1,},
    { 1,1,1,1,1,0,0,0,1,0,1,},
    { 1,1,0,0,0,1,1,1,0,0,0,},
    { 1,1,0,0,0,0,0,0,0,0,0,},
};
 if(input.d == N||input.d == NE||input.d == NW) {lcd.drawSprite(_x,_y + 1, _height,_width, (int*)shipu);}
 else if(input.d == S||input.d == SE||input.d == SW){lcd.drawSprite(_x,_y + 2, _height,_width, (int*)shipd);}
 else{lcd.drawSprite(_x,_y, 9,_width, (int*)shipm);}
}

void Aircraft::update(UserInput input) {

    _speed = 2;
    // update y value depending on direction of movement
    // North is decrement as origin is at the top-left so decreasing moves up

    if(input.d == N){_y-=_speed;}
    else if(input.d == S){_y+=_speed;}
    else if(input.d == E){_x+=_speed;}
    else if(input.d == W){_x-=_speed;}
    else if(input.d == NE){_y-=_speed;_x+=_speed;}
    else if(input.d == NW){_y-=_speed;_x-=_speed;}
    else if(input.d == SE){_y+=_speed;_x+=_speed;}
    else if(input.d == SW){_y+=_speed;_x-=_speed;} 
    // check the y origin to ensure that the Aircraft doesn't go off screen
    if (_y < 9) { _y = 9; }
    if (_y > HEIGHT - 10) { _y = HEIGHT - 10; }
    if (_x < 1) { _x = 1; }
    if (_x > WIDTH + _width - 1) { _x = WIDTH + _width - 1; }
}

void Aircraft::set_pos(Position2D p) {
    _x = p.x;
    _y = p.y;
}

Position2D Aircraft::get_pos() { return {_x,_y}; }

int Aircraft::get_height() { return _height; }

int Aircraft::get_width() { return _width; }
