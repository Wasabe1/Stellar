#include "Laser.h"

Laser::Laser() {}

void Laser::init(int size) {
    _size = size;
    _x = WIDTH/2 -  _size/2;
    _y = HEIGHT/2 - _size/2;
    _act = 0;
    _active = false;
    _ready = false;
    _ready_time = 90;
}

void Laser::draw(N5110 &lcd) {
    const int Laserbottom[9][2]= {
             {0,0},
             {1,0},
             {1,1},
             {1,1},
             {1,1},
             {1,1},
             {1,1},
             {1,0},
             {0,0},   
            }; 
 if(_ready == true && _active == false){
    lcd.drawSprite(_x - 2,_y,9,2,(int*)Laserbottom);
    lcd.drawLine(0,_y,_x - 3,_y,1); //laser up side
    lcd.drawLine(0,_y + 8,_x - 3,_y + 8,1); 
    if(_act <= 1){
     for(int i = 1;i <= 84;i = i + 7){
      lcd.drawLine(_x - 83 + i,_y + 1,_x - 89 + i,_y + 7,1); 
      lcd.drawLine(_x - 82 + i,_y + 1,_x - 88 + i,_y + 7,1); 
     }
      _act = _act + 1;
    }
    else if(_act <= 4){_act = _act + 1;}
    else if(_act > 4) {_act = 0;}
 }
 else if(_active == true){
    lcd.drawSprite(_x - 2,_y,9,2,(int*)Laserbottom);
    lcd.drawRect(0,_y,_x - 2,_size,FILL_BLACK);
    if(_act <= 1){
     lcd.drawLine(0,_y + _act,_x - 2,_y + _act,0); //laser
     _act ++;
    }
    else if(_act <= 3){
     lcd.drawLine(0,_y + _act,_x - 2,_y + _act,0);
     _act ++;
    }
    else if(_act <= 5){
     lcd.drawLine(0,_y + _act,_x - 2,_y + _act,0);
     _act ++;
    }
    else if(_act <= 7){
     lcd.drawLine(0,_y + _act,_x - 2,_y + _act,0);
     _act ++;
    }
    else if(_act > 7){_act = 0;}
 }
}

void Laser::update(Position2D pos){
         _x = pos.x;
         _y = pos.y + 10;
    if ( _ready == false && _ready_time <= 30){
         _ready = true;
    }
    else if(_ready_time <= 30){
        _ready_time ++;
    }
    else if(_ready_time <= 60){
         _ready = false;
         _ready_time ++;
         _active = true;
    }
    else if(_ready_time <= 90){
        _ready_time ++;
        _active = false;
    }
    else if(_ready_time <= 180){
        _ready_time ++;
    }
    else if(_ready_time > 180){
        _ready_time = 0;
    }
}

Position2D Laser::get_pos() { return {_x,_y}; }

int Laser::get_size() { return _size; }

bool Laser::get_laser_state(){return _active;}