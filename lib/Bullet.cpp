
#include "Bullet.h"


Bullet::Bullet() {}

void Bullet::init(int height, int width, int speed) {
    _bullets_state = vector<bool>(MAX_BULLETS, false); 
    bullets_pos = vector<Position2D>(MAX_BULLETS);
    _bullet_height = height;
    _bullet_width = width;
    _velocity.x = speed;
}

void Bullet::draw(N5110 &lcd) {
    const int bullet[3][5] = {
        {0,0,0,1,0},
        {1,1,1,0,1},
        {0,0,0,1,0},
    };
    
    for(int i = 0; i <= MAX_BULLETS; i = i+1){
     if (_bullets_state[i] == 1){
        lcd.drawSprite(bullets_pos[i].x, bullets_pos[i].y, _bullet_height, _bullet_width, (int*)bullet);
     }
    }
}

void Bullet::update(bool fire, Position2D a_pos) {
    bool is_fire = fire;
    for(int i = 0; i < MAX_BULLETS; i = i+1){
     if (_bullets_state[i] == 0 && is_fire == 1){
        _bullets_state[i] = 1; //active this bullet
        bullets_pos[i].x = a_pos.x + 11;
        bullets_pos[i].y = a_pos.y + 3;
        is_fire = 0;
     }
     else if (_bullets_state[i] == 1){bullets_pos[i].x += _velocity.x;}
     if (bullets_pos[i].x >= WIDTH -1){_bullets_state[i] = 0;}
    }
}

void Bullet::set_velocity(Position2D v) {
    _velocity.x = v.x;
}

Position2D Bullet::get_pos(int i) { return bullets_pos[i]; }

int Bullet::get_bullet_state(int i){
    return _bullets_state[i];
}

void Bullet::set_pos(Position2D p, int i) {
    bullets_pos[i].x = p.x;
    bullets_pos[i].y = p.y;
}

int Bullet::get_bullet_height() { 
    return _bullet_height; 
}

int Bullet::get_bullet_width() { 
    return _bullet_width; 
}
