#include "Alien.h"

Alien::Alien() {}

void Alien::init(int size, int speed) {
    _size = size;
    _x = WIDTH + 1;
    _y = 13;
    _act = 0;
    _velocity.x = speed;
    _velocity.y = speed;
}

void Alien::draw(N5110 &lcd) {
    
    if (_act <= 2){
        lcd.drawSprite(_x,_y,39,26,(int*)alien1);
        _act = _act + 1;
        }
    else if (_act <= 5){
        lcd.drawSprite(_x,_y,35,27,(int*)alien2);
        _act = _act + 1;
    }
    else if (_act <= 8){
        lcd.drawSprite(_x,_y,30,28,(int*)alien3);
        _act = _act + 1;
    }
    else if (_act <= 11){
        lcd.drawSprite(_x,_y,29,29,(int*)alien4);
        _act = _act + 1;
    }
    else if (_act <= 14){
        lcd.drawSprite(_x,_y,30,28,(int*)alien3);
        _act = _act + 1;
    }
    else if (_act <= 15){
        lcd.drawSprite(_x,_y,35,27,(int*)alien2);
        _act = 0;
    }
}

void Alien::update(){
    _x += _velocity.x;
    _y += _velocity.y;
}

void Alien::set_velocity(Position2D v){
    _velocity.x = v.x;
    _velocity.y = v.y;
}

void Alien::set_pos(Position2D p) {
    _x = p.x;
    _y = p.y;
}

Position2D Alien::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Alien::get_pos() { return {_x,_y}; }

int Alien::get_size() { return _size; }