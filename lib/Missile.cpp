#include "Missile.h"

Missile::Missile() {}

void Missile::init(int height,int width, int speed) {
    _active = false;
    _height = height;
    _width = width;
    _act = 0;
    _explode_radius = 0;
    _hit = false;
    _velocity.x = speed;
    _velocity.y = speed;
}

void Missile::draw(N5110 &lcd) {
    const int Missile[4][7]= {
    {0,1,1,0,0,0,0},
    {1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1},
    {0,1,1,0,0,0,0},
}; 

    const int flame1[4][5]= {
    { 0,1,1,1,0},
    { 1,1,0,0,1},
    { 0,1,1,0,1},
    { 1,0,1,1,0},
}; 

    const int flame2[4][5]= {
    { 0,1,1,1,0},
    { 0,1,1,0,1},
    { 1,1,1,0,1},
    { 0,0,1,1,0},
}; 

    const int flame3[4][5]= {
    { 1,0,1,1,0},
    { 0,1,0,0,1},
    { 0,1,1,0,1},
    { 1,1,1,1,0},
};

 if(_active == true){
    if (_act <= 1){
        lcd.drawSprite(_x,_y,_height,_width,(int*)Missile);
        lcd.drawSprite(_x-6,_y,4,5,(int*)flame1);
        _act = _act + 1;
        }
    else if (_act <= 3){
        lcd.drawSprite(_x,_y,_height,_width,(int*)Missile);
        lcd.drawSprite(_x-6,_y,4,5,(int*)flame2);
        _act = _act + 1;
    }
    else if (_act <= 4){
        lcd.drawSprite(_x,_y,_height,_width,(int*)Missile);
        lcd.drawSprite(_x-6,_y,4,5,(int*)flame3);
        _act = 0;
    }
    else if (_act <= 5){
        lcd.drawSprite(_x,_y,_height,_width,(int*)Missile);
        lcd.drawSprite(_x-6,_y,4,5,(int*)flame3);
        _act = 0;
    }
 }

 if(_hit == true){
     if(_explode_radius <= MAX_BLAST_RADIUS){ 
         lcd.drawCircle(_ex_x + 6,_ex_y + 2,_explode_radius,FILL_BLACK); 
         lcd.drawCircle(_ex_x + 6,_ex_y + 2,_explode_radius + 2,FILL_TRANSPARENT);
         lcd.drawCircle(_ex_x + 6,_ex_y + 2,_explode_radius + 3,FILL_TRANSPARENT);
        _explode_radius ++;
        }
    if (_explode_radius > MAX_BLAST_RADIUS){
        _hit = false;
        _explode_radius = 0;
        }
    }
}



void Missile::update(bool emit, Position2D target, Position2D aircraft_pos){
    if(emit == true && _active == false){
       _active = true;
       _x = aircraft_pos.x + 4;
       _y = aircraft_pos.y + 4;
    }
    else if(_active == true){
        if (_x + _width <= target.x && _y + _height/2 < target.y + 4){
            _x += _velocity.x;
            _y += 1;
        }
        else if (_x + _width <= target.x && _y + _height/2 > target.y + 4){
            _x += _velocity.x;
            _y -= 1;
        }
        else{
            _x += _velocity.x;
        }
    }
    if (_x >= WIDTH + 7){_active = false;}
}

void Missile::set_velocity(Position2D v){
    _velocity.x = v.x;
    _velocity.y = v.y;
}

void Missile::set_pos(Position2D p) {
    _x = p.x;
    _y = p.y;
}

Position2D Missile::get_velocity(){ return {_velocity.x,_velocity.y}; }

Position2D Missile::get_pos() { return {_x,_y}; }

int Missile::get_missile_height() { return _height; }

int Missile::get_missile_width() { return _width; }

bool Missile::get_missile_state(){return _active;}

void Missile::is_hit(){
     _ex_x = _x;
     _ex_y = _y;
     _hit = true; 
}