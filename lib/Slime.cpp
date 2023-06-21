#include "Slime.h"

Slime::Slime() {}

void Slime::init(int height, int width, int speed) {
    _height = height;
    _width = width;
    _x = WIDTH + 1;
    _y = HEIGHT/2 - _height/2;
    _act = 0;

    _velocity.x = speed;
    _velocity.y = speed;
}

void Slime::draw(N5110 &lcd) {
    const int slime1[13][17]= {

        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,1,0,0,1,0,0,0,0,1,0,0,0,0,1,0,0},
        {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0},
        {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0},
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
    }; 
    const int slime2[13][17]= {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},  
        {0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0},
        {0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0},
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
        {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0},
        {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
        {0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0},
        {0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    };  
    if (_act <= 1){
        lcd.drawSprite(_x,_y,_height,_width,(int*)slime1);
        _act = _act + 1;
    }
    else if (_act <= 3){
        lcd.drawSprite(_x,_y,_height,_width,(int*)slime2);
        _act = _act + 1;
    }
    else if (_act >3 ){
        _act = 0;
    }
}

void Slime::update(){ 
    _x += _velocity.x;
    _y += _velocity.y;
}

void Slime::set_velocity(Position2D v){
    _velocity.x = v.x;
    _velocity.y = v.y;
}

void Slime::set_pos(Position2D p) {
    _x = p.x;
    _y = p.y;
}

Position2D Slime::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Slime::get_pos() { return {_x,_y}; }

int Slime::get_height() { return _height; }

int Slime::get_width() { return _width; }
