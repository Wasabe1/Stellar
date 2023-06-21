#include "StellarEngine.h"

StellarEngine::StellarEngine(){ _lives = 6; slime_lives = 39; ghost_lives = 100; alien_lives = 500; _score = 0;}

void StellarEngine::init(int aircraft_position, int aircraft_height, int aircraft_width, int slime_height, int slime_width, int ghost_size, int fireball_size, int alien_size, int speed, int bullet_height, int bullet_width,int bullet_speed,int missile_height,int missile_width,int laser_size,int missile_speed){
    _background.init(speed);
    _slime.init(slime_height,slime_width,speed);
    _ghost.init(ghost_size,speed);
    _fireball.init(fireball_size,speed);
    _alien.init(alien_size,speed);
    _laser.init(laser_size);
    _aircraft.init(aircraft_position, aircraft_height, aircraft_width);
    _bullet.init(bullet_height, bullet_width, bullet_speed);
    _missile.init(missile_height,missile_width,missile_speed);
}

int StellarEngine::update(UserInput input, bool fire, bool emit) {
    Position2D aircraft_pos = _aircraft.get_pos();  // aircraft
    if(slime_lives > 0){
    _slime.update();
    Position2D slime_pos = _slime.get_pos();
    _missile.update(emit,slime_pos,aircraft_pos);
    }
    else if(ghost_lives > 0){
    _ghost.update();
    Position2D ghost_pos = _ghost.get_pos();
    _fireball.update(true,ghost_pos);
    _missile.update(emit,ghost_pos,aircraft_pos);
    }
    else if(alien_lives > 0){
    _alien.update(); 
    Position2D alien_pos = _alien.get_pos();
    _laser.update(alien_pos);
    _missile.update(emit,alien_pos,aircraft_pos);
    }
    _background.update();
    _aircraft.update(input);
    _bullet.update(fire,aircraft_pos);
    // important to update aircraft and slime before checking collisions so can
    // correct for it before updating the display
    if(slime_lives > 0){
        check_slime_wall_collision();
        check_bullet_slime_collision();
        check_missile_slime_collision();
        check_slime_aircraft_collision();
    }
    else if (ghost_lives > 0){
        check_ghost_wall_collision();
        check_fireball_aircraft_collision();
        check_bullet_ghost_collision();
        check_missile_ghost_collision();
        check_ghost_aircraft_collision();
    }
    else if (alien_lives > 0){
        check_alien_wall_collision();
        check_bullet_alien_collision();
        check_laser_aircraft_collision();
        check_missile_alien_collision();
        check_alien_aircraft_collision();
    }
    else if(alien_lives <= 0){
        slime_lives = 39; 
        ghost_lives = 100; 
        alien_lives = 500;
    }
    return _lives;
}

void StellarEngine::draw(N5110 &lcd,UserInput input) {
    // draw the elements in the LCD buffer
    // pitch
    const int fullheart[6][7] = {
        {0,1,1,0,1,1,0},
        {1,1,1,1,1,1,1},
        {1,1,1,1,1,1,1},
        {0,1,1,1,1,1,0},
        {0,0,1,1,1,0,0},
        {0,0,0,1,0,0,0},
    };
    const int halfheart[6][7] = {
        {0,1,1,0,1,1,0},
        {1,1,1,1,0,0,1},
        {1,1,1,1,0,0,1},
        {0,1,1,1,0,1,0},
        {0,0,1,1,1,0,0},
        {0,0,0,1,0,0,0},
    };
    const int emptyheart[6][7] = {
        {0,1,1,0,1,1,0},
        {1,0,0,1,0,0,1},
        {1,0,0,0,0,0,1},
        {0,1,0,0,0,1,0},
        {0,0,1,0,1,0,0},
        {0,0,0,1,0,0,0},
    };

    const int score[5][26] = {
        {0,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,0,0,1,1,1,1,0,0},
        {1,0,0,0,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,0,1},
        {0,1,1,0,0,1,0,0,0,0,1,0,0,1,0,1,1,1,0,0,1,1,1,0,0,0},
        {0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,1},
        {1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,1,0,0},
    };
    _background.draw(lcd);
    lcd.drawRect(0,0,27,9,FILL_TRANSPARENT);
    
    lcd.drawSprite(35,2,5,26,(int*)score);
    char buffer[14];
    sprintf(buffer,"%3d",_score);
    lcd.printString(buffer,65,0);
    _aircraft.draw(lcd,input);
    _bullet.draw(lcd);
    if(slime_lives > 0){
        Position2D slime_pos = _slime.get_pos();
        _slime.draw(lcd);
        _missile.draw(lcd);
        lcd.drawRect(slime_pos.x,slime_pos.y - 4,15,3,FILL_TRANSPARENT);  // slime lives display
        lcd.drawLine(slime_pos.x + 1,slime_pos.y - 3,slime_pos.x + slime_lives/3,slime_pos.y - 3,1);  
        }
    else if(ghost_lives > 0){
        Position2D ghost_pos = _ghost.get_pos();
        _ghost.draw(lcd);
        _fireball.draw(lcd);
        _missile.draw(lcd);
        lcd.drawRect(ghost_pos.x,ghost_pos.y - 4,12,3,FILL_TRANSPARENT);  // ghost lives display
        lcd.drawLine(ghost_pos.x + 1,ghost_pos.y - 3,ghost_pos.x + 1 + ghost_lives/10,ghost_pos.y - 3,1);  
        }
    else if(alien_lives > 0){
        Position2D alien_pos = _alien.get_pos();
        _alien.draw(lcd);
        _laser.draw(lcd);
        _missile.draw(lcd);
        lcd.drawRect(alien_pos.x + 1,alien_pos.y - 4,22,3,FILL_TRANSPARENT);  // alien lives display
        lcd.drawLine(alien_pos.x + 2,alien_pos.y - 3,alien_pos.x + 1 + alien_lives/25,alien_pos.y - 3,1);  
        }
    if(_lives == 6){
        lcd.drawSprite(2, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(10, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(18, 2, 6, 7, (int*)fullheart);
    }
    else if(_lives == 5){
        lcd.drawSprite(2, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(10, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(18, 2, 6, 7, (int*)halfheart);
    }
    else if(_lives == 4){
        lcd.drawSprite(2, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(10, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(18, 2, 6, 7, (int*)emptyheart);
    }
    else if(_lives == 3){
        lcd.drawSprite(2, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(10, 2, 6, 7, (int*)halfheart);
        lcd.drawSprite(18, 2, 6, 7, (int*)emptyheart);
    }
    else if(_lives == 2){
        lcd.drawSprite(2, 2, 6, 7, (int*)fullheart);
        lcd.drawSprite(10, 2, 6, 7, (int*)emptyheart);
        lcd.drawSprite(18, 2, 6, 7, (int*)emptyheart);
    }
    else if(_lives == 1){
        lcd.drawSprite(2, 2, 6, 7, (int*)halfheart);
        lcd.drawSprite(10, 2, 6, 7, (int*)emptyheart);
        lcd.drawSprite(18, 2, 6, 7, (int*)emptyheart);
    }
    lcd.drawRect(0,8,WIDTH,HEIGHT - 8,FILL_TRANSPARENT);
}

void StellarEngine::check_slime_wall_collision() {
    // read current slime attributes
    Position2D slime_pos = _slime.get_pos();
    Position2D slime_velocity = _slime.get_velocity();
    int slime_height = _slime.get_height();
    int slime_width = _slime.get_width();

    // check if hit top wall
    if (slime_pos.y <= 13) {  //  1 due to 1 pixel boundary
        slime_pos.y = 13;  // bounce off ceiling without going off screen
        slime_velocity.y = -slime_velocity.y;  // flip velocity
    } else if (slime_pos.y + slime_height >= (HEIGHT-1) ) {
        // hit bottom
        slime_pos.y = (HEIGHT-1) - slime_height;  // stops slime going off screen
        slime_velocity.y = -slime_velocity.y;    // flip velcoity 
    } else if (slime_pos.x + slime_width >= (WIDTH-1) ) {
        // hit right wall
        if(slime_velocity.x > 0){slime_velocity.x = -slime_velocity.x;}    // flip velcoity 
    } 
    else if (slime_pos.x <= 1) {
        // hit left wall
        slime_pos.x = 1;  // stops slime going off screen
        slime_velocity.x = -slime_velocity.x;    // flip velcoity 
    } 

    // update slime parameters
    _slime.set_velocity(slime_velocity);
    _slime.set_pos(slime_pos);
}

void StellarEngine::check_ghost_wall_collision() {
    // read current ghost attributes
    Position2D ghost_pos = _ghost.get_pos();
    Position2D ghost_velocity = _ghost.get_velocity();
    int ghost_size = _ghost.get_size();

    // check if hit top wall
    if (ghost_pos.y <= 13) {  //  1 due to 1 pixel boundary
        ghost_pos.y = 13;  // bounce off ceiling without going off screen
        ghost_velocity.y = -ghost_velocity.y;  // flip velocity
    } else if (ghost_pos.y + ghost_size >= (HEIGHT-1) ) {
        // hit bottom
        ghost_pos.y = (HEIGHT-1) - ghost_size;  // stops ghost going off screen
        ghost_velocity.y = -ghost_velocity.y;    // flip velcoity 
    } else if (ghost_pos.x + ghost_size >= WIDTH-1 ) {
        // hit right wall
        if(ghost_velocity.x > 0){ghost_velocity.x = -ghost_velocity.x;}    // flip velcoity 
    } else if (ghost_pos.x <= 1) {
        // hit left wall
        ghost_pos.x = 1;  // stops ghost going off screen
        ghost_velocity.x = -ghost_velocity.x;    // flip velcoity 
    } 

    // update ghost parameters
    _ghost.set_velocity(ghost_velocity);
    _ghost.set_pos(ghost_pos);
}

void StellarEngine::check_alien_wall_collision() {
    // read current alien attributes
    Position2D alien_pos = _alien.get_pos();
    Position2D alien_velocity = _alien.get_velocity();
    int alien_size = _alien.get_size();

    // check if hit top wall
    if (alien_pos.y <= 11) {  
        alien_pos.y = 11;  // bounce off ceiling without going off screen
        alien_velocity.y = -alien_velocity.y;  // flip velocity
    } else if (alien_pos.y + alien_size + 5 >= (HEIGHT-1) ) {
        // hit bottom
        alien_pos.y = (HEIGHT-1) - alien_size - 5;  // stops alien going off screen
        alien_velocity.y = -alien_velocity.y;    // flip velcoity 
    } if (alien_pos.x + alien_size + 5 >= (WIDTH-1) ) {
        // hit right wall
        if(alien_velocity.x > 0){alien_velocity.x = -alien_velocity.x;}    // flip velcoity 
    } 
      if (alien_pos.x <= 45) {
        // hit left wall
        alien_pos.x = 45;  // stops alien going off screen
        alien_velocity.x = -alien_velocity.x;    // flip velcoity 
    } 

    // update alien parameters
    _alien.set_velocity(alien_velocity);
    _alien.set_pos(alien_pos);
}

void StellarEngine::check_slime_aircraft_collision() {
    // read current slime and Aircraft attributes
    Position2D slime_pos = _slime.get_pos();
    Position2D aircraft_pos = _aircraft.get_pos();  // aircraft
    int slime_height = _slime.get_height();
    int slime_width = _slime.get_width();

    // see if slime has hit the aircraft by checking for overlaps
    if (
        (slime_pos.y + slime_height >= aircraft_pos.y + 2) && //slime hit top
        (slime_pos.y <= aircraft_pos.y + _aircraft.get_height() + 1) && //slime hit bottom
        (slime_pos.x + slime_height >= aircraft_pos.x) &&  //slime hit left
        (slime_pos.x <= aircraft_pos.x + _aircraft.get_width()  )  //slime hit right
    ) {
        // if it has, fix position and reflect x velocity
        slime_pos.x = WIDTH/2;
        slime_pos.y = HEIGHT/2;
        aircraft_pos.y = HEIGHT/2;
        aircraft_pos.x = 1;  
        _lives --;
    }
    // write new attributes
    _aircraft.set_pos(aircraft_pos);
    _slime.set_pos(slime_pos);
}

void StellarEngine::check_ghost_aircraft_collision() {
    // read current ghost and Aircraft attributes
    Position2D ghost_pos = _ghost.get_pos();
    Position2D ghost_velocity = _ghost.get_velocity();
    Position2D aircraft_pos = _aircraft.get_pos();  // aircraft

    // see if ghost has hit the aircraft by checking for overlaps
    if (
        (ghost_pos.y + _ghost.get_size() >= aircraft_pos.y + 2) && //top
        (ghost_pos.y <= aircraft_pos.y + _aircraft.get_height() + 1) && //bottom
        (ghost_pos.x + _ghost.get_size() >= aircraft_pos.x) &&  //left
        (ghost_pos.x <= aircraft_pos.x + _aircraft.get_width()  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        _lives --;
        ghost_pos.x = WIDTH/2;
        ghost_pos.y = HEIGHT/2;
        ghost_velocity.x = -ghost_velocity.x;
        ghost_velocity.y = -ghost_velocity.y;
        aircraft_pos.y = HEIGHT/2;
        aircraft_pos.x = 1;
    }

    // write new attributes
    _aircraft.set_pos(aircraft_pos);
    _ghost.set_velocity(ghost_velocity);
    _ghost.set_pos(ghost_pos);
}

void StellarEngine::check_fireball_aircraft_collision() {
    // read current fireball and Aircraft attributes
    Position2D fireball_pos = _fireball.get_pos();
    Position2D aircraft_pos = _aircraft.get_pos();  // aircraft

    // see if fireball has hit the aircraft by checking for overlaps
    if (
        (fireball_pos.y + _fireball.get_size() >= aircraft_pos.y + 2) && //top
        (fireball_pos.y <= aircraft_pos.y + _aircraft.get_height() + 1) && //bottom
        (fireball_pos.x + _fireball.get_size() >= aircraft_pos.x) &&  //left
        (fireball_pos.x <= aircraft_pos.x + _aircraft.get_width()  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        _lives --;
        fireball_pos.x = 1 - _fireball.get_size();
        aircraft_pos.y = HEIGHT/2;
        aircraft_pos.x = 1;
    }
    // write new attributes
    _aircraft.set_pos(aircraft_pos);
    _fireball.set_pos(fireball_pos);
}

void StellarEngine::check_alien_aircraft_collision() {
    // read current alien and Aircraft attributes
    Position2D alien_pos = _alien.get_pos();
    Position2D aircraft_pos = _aircraft.get_pos();  // aircraft

    // see if alien has hit the aircraft by checking for overlaps
    if (
        (alien_pos.y + _alien.get_size() >= aircraft_pos.y + 2) && //top
        (alien_pos.y <= aircraft_pos.y + _aircraft.get_height() + 1) && //bottom
        (alien_pos.x + _alien.get_size() >= aircraft_pos.x) &&  //left
        (alien_pos.x <= aircraft_pos.x + _aircraft.get_width()  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        _lives --;
        aircraft_pos.y = HEIGHT/2;
        aircraft_pos.x = 1;
    }
     _aircraft.set_pos(aircraft_pos);
}

void StellarEngine::check_laser_aircraft_collision() {
        // read current laser and Aircraft attributes
  if(_laser.get_laser_state() == true){
    Position2D laser_pos = _laser.get_pos();
    Position2D aircraft_pos = _aircraft.get_pos();  // aircraft

    // see if alien has hit the aircraft by checking for overlaps
    if (
        (laser_pos.y + _laser.get_size() >= aircraft_pos.y + 2) && //top
        (laser_pos.y <= aircraft_pos.y + _aircraft.get_height() + 1) && //bottom
        (laser_pos.x >= aircraft_pos.x + _aircraft.get_width())  //right
    ) {
        // if it has, fix position and reflect x velocity
        _lives --;
        aircraft_pos.y = 1;
        aircraft_pos.x = 1;
    }
     _aircraft.set_pos(aircraft_pos);
  }
}

void StellarEngine::check_bullet_slime_collision() {
    // read current slime and aircraft attributes
    Position2D slime_pos = _slime.get_pos();
    int slime_height = _slime.get_height();
    int slime_width = _slime.get_width();
    int bullet_width = _bullet.get_bullet_width();
    int bullet_height = _bullet.get_bullet_height();

 for(int i = 0; i < MAX_BULLETS; i = i+1){
    if(_bullet.get_bullet_state(i) == 1){
    Position2D bullet_pos = _bullet.get_pos(i);  // bullet
    // see if bullet has hit the slime by checking for overlaps
    if (
        (bullet_pos.y + bullet_height >= slime_pos.y) && //top
        (bullet_pos.y <= slime_pos.y + slime_height  ) && //bottom
        (bullet_pos.x + bullet_width >= slime_pos.x) && //left
        (bullet_pos.x <= slime_pos.x + slime_width  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        slime_pos.x = bullet_pos.x + bullet_width + 1;
        bullet_pos.x = WIDTH + 1;
        slime_lives--;
        _score++;
    }
    // write new attributes
    _slime.set_pos(slime_pos);
    _bullet.set_pos(bullet_pos,i);
    }
 }
}

void StellarEngine::check_bullet_ghost_collision() {
    // read current ghost and aircraft attributes
    Position2D ghost_pos = _ghost.get_pos();
    int ghost_size = _ghost.get_size();
    int bullet_width = _bullet.get_bullet_width();
    int bullet_height = _bullet.get_bullet_height();

 for(int i = 0; i < MAX_BULLETS; i = i+1){
    if(_bullet.get_bullet_state(i) == 1){
    Position2D bullet_pos = _bullet.get_pos(i);  // bullet
    // see if bullet has hit the ghost by checking for overlaps
    if (
        (bullet_pos.y + bullet_height >= ghost_pos.y) && //top
        (bullet_pos.y <= ghost_pos.y + ghost_size  ) && //bottom
        (bullet_pos.x + bullet_width >= ghost_pos.x) && //left
        (bullet_pos.x <= ghost_pos.x + ghost_size  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        ghost_pos.x = bullet_pos.x + bullet_width + 1;
        bullet_pos.x = WIDTH + 1;
        ghost_lives--;
        _score++;
    }
    // write new attributes
    _ghost.set_pos(ghost_pos);
    _bullet.set_pos(bullet_pos,i);
    }
 }
}

void StellarEngine::check_bullet_alien_collision() {
    // read current alien and aircraft attributes
    Position2D alien_pos = _alien.get_pos();
    int alien_size = _alien.get_size();
    int bullet_width = _bullet.get_bullet_width();
    int bullet_height = _bullet.get_bullet_height();

 for(int i = 0; i < MAX_BULLETS; i = i+1){
    if(_bullet.get_bullet_state(i) == 1){
    Position2D bullet_pos = _bullet.get_pos(i);  // bullet
    // see if bullet has hit the alien by checking for overlaps
    if (
        (bullet_pos.y + bullet_height >= alien_pos.y) && //top
        (bullet_pos.y <= alien_pos.y + alien_size  ) && //bottom
        (bullet_pos.x + bullet_width >= alien_pos.x) && //left
        (bullet_pos.x <= alien_pos.x + alien_size  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        bullet_pos.x = WIDTH + 1;
        alien_lives--;
        _score++;
    }
    // write new attributes
    _bullet.set_pos(bullet_pos,i);
    }
 }
}

void StellarEngine::check_missile_slime_collision() {
    // read current slime and missile attributes
    Position2D slime_pos = _slime.get_pos();
    int slime_height = _slime.get_height();
    int slime_width = _slime.get_width();
    int missile_width = _missile.get_missile_width();
    int missile_height = _missile.get_missile_height();

    if(_missile.get_missile_state() == 1){
    Position2D missile_pos = _missile.get_pos();  // missile
    // see if missile has hit the slime by checking for overlaps
    if (
        (missile_pos.y + missile_height >= slime_pos.y) && //top
        (missile_pos.y <= slime_pos.y + slime_height  ) && //bottom
        (missile_pos.x + missile_width >= slime_pos.x) && //left
        (missile_pos.x <= slime_pos.x + slime_width  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        slime_pos.x = missile_pos.x + missile_width + 2;
        missile_pos.x = WIDTH + 7;
        _missile.is_hit();
        slime_lives = slime_lives - 5;
        _score = _score + 5;
    }
    // write new attributes
    _slime.set_pos(slime_pos);
    _missile.set_pos(missile_pos);
    }
}

void StellarEngine::check_missile_ghost_collision() {
    // read current ghost and missile attributes
    Position2D ghost_pos = _ghost.get_pos();
    int ghost_size = _ghost.get_size();
    int missile_width = _missile.get_missile_width();
    int missile_height = _missile.get_missile_height();

    if(_missile.get_missile_state() == 1){
    Position2D missile_pos = _missile.get_pos();  // missile
    // see if missile has hit the ghost by checking for overlaps
    if (
        (missile_pos.y + missile_height >= ghost_pos.y) && //top
        (missile_pos.y <= ghost_pos.y + ghost_size  ) && //bottom
        (missile_pos.x + missile_width >= ghost_pos.x) && //left
        (missile_pos.x <= ghost_pos.x + ghost_size  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        ghost_pos.x = missile_pos.x + missile_width + 2;
        missile_pos.x = WIDTH + 7;
        _missile.is_hit();
        ghost_lives = ghost_lives - 5;
        _score = _score + 5;
    }
    // write new attributes
    _ghost.set_pos(ghost_pos);
    _missile.set_pos(missile_pos);
    }
}

void StellarEngine::check_missile_alien_collision() {
    // read current alien and missile attributes
    Position2D alien_pos = _alien.get_pos();
    int alien_size = _alien.get_size();
    int missile_width = _missile.get_missile_width();
    int missile_height = _missile.get_missile_height();

    if(_missile.get_missile_state() == 1){
    Position2D missile_pos = _missile.get_pos();  // missile
    // see if missile has hit the alien by checking for overlaps
    if (
        (missile_pos.y + missile_height >= alien_pos.y) && //top
        (missile_pos.y <= alien_pos.y + alien_size  ) && //bottom
        (missile_pos.x + missile_width >= alien_pos.x) && //left
        (missile_pos.x <= alien_pos.x + alien_size  )  //right
    ) {
        // if it has, fix position and reflect x velocity
        missile_pos.x = WIDTH + 7;
        _missile.is_hit();
        alien_lives = alien_lives - 5;
        _score = _score + 5;
    }
    // write new attributes
    _missile.set_pos(missile_pos); 
    }
}

int StellarEngine::get_score() {
    return _score;
}