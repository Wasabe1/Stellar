#include "Fireball.h"

Fireball::Fireball() {}

void Fireball::init(int size, int speed) {
    _size = size;
    _x = WIDTH/2 -  _size/2;
    _y = HEIGHT/2 - _size/2;
    act = 0;
    _active = false;
    _velocity.x = -speed;
}

void Fireball::draw(N5110 &lcd) {
    const int fireball1[6][6]= {
             {0,0,0,1,1,0},
             {1,1,1,1,1,0},
             {1,1,1,1,1,0},
             {0,1,1,1,1,1},
             {0,1,1,1,1,1},
             {0,1,1,0,0,0},
}; 
    const int fireball2[6][6]= {
             {0,0,1,1,0,0},
             {0,0,1,1,0,0},
             {1,1,1,1,1,1},
             {1,1,1,1,1,1},
             {0,0,1,1,0,0},
             {0,0,1,1,0,0},
}; 
    const int fireball3[6][6]= {
             {0,1,1,0,0,0},
             {0,1,1,1,1,1},
             {0,1,1,1,1,1},
             {1,1,1,1,1,0},
             {1,1,1,1,1,0},
             {0,0,0,1,1,0},
}; 

 if(_active == true){
    if (act <= 1){
        lcd.drawSprite(_x,_y,_size,_size,(int*)fireball1);
        act = act + 1;
        }
    else if (act <= 3){
        lcd.drawSprite(_x,_y,_size,_size,(int*)fireball2);
        act = act + 1;
    }
    else if (act <= 4){
        lcd.drawSprite(_x,_y,_size,_size,(int*)fireball3);
        act = act + 1;
    }
    else if (act == 5){
        lcd.drawSprite(_x,_y,_size,_size,(int*)fireball3);
        act = 0;
    }
 }
}

void Fireball::update(bool fire, Position2D pos){
    if (fire == true && _active == false){
        _x = pos.x - _size;
        _y = pos.y + 7;
        _active = true;
    }
    else if(_active == true){_x += _velocity.x;}
    if(_x + _size <= 0){_active = false;}
}


void Fireball::set_pos(Position2D p) {
    _x = p.x;
    _y = p.y;
}


Position2D Fireball::get_pos() { return {_x,_y}; }

int Fireball::get_size() { return _size; }

bool Fireball::get_fireball_state(){return _active;}