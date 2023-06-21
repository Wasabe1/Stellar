#ifndef STELLARENGINE_H
#define STELLARENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "Background.h"
#include "Slime.h"
#include "Ghost.h"
#include "Fireball.h"
#include "Alien.h"
#include "Laser.h"
#include "Bullet.h"
#include "Missile.h"
#include "Utils.h"
#include "Aircraft.h"


class StellarEngine {
    public:
        StellarEngine();  // pass in the lcd object from the main file
        void init(int aircraft_position,int aircraft_height,int aircraft_width,int slime_height,int slime_width,int ghost_size,int fireball_size,int alien_size,int speed,int bullet_height,int bullet_width,int bullet_speed,int missile_height, int missile_width,int laser_size,int missile_speed);
        int update(UserInput input, bool fire, bool emit);
        void draw(N5110 &lcd,UserInput input);
        int get_score();
    private:
        void check_slime_wall_collision();
        void check_ghost_wall_collision();
        void check_alien_wall_collision();
        void check_slime_aircraft_collision();
        void check_ghost_aircraft_collision();
        void check_fireball_aircraft_collision();
        void check_alien_aircraft_collision();
        void check_laser_aircraft_collision();
        void check_bullet_slime_collision();
        void check_bullet_ghost_collision();
        void check_bullet_alien_collision();
        void check_missile_slime_collision();
        void check_missile_ghost_collision();
        void check_missile_alien_collision();  
        Background _background;
        Slime _slime;
        Ghost _ghost;
        Fireball _fireball;
        Alien _alien;
        Aircraft _aircraft;
        Bullet _bullet;
        Missile _missile;
        Laser _laser;
        int _score;
        int _lives;
        int slime_lives;
        int ghost_lives;
        int alien_lives;
};

#endif