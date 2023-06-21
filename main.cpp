/*   Stellar Game
*    =========
*
*    Function:               Stellar game
*    Required Libraries:     
*
*    Authored by:            Wasabi
*    Date:                   2023
*    Collaborators:          Andrew Knowles
*                            Dr Tim Amsdon 
*    Version:                1.0
*    Revision Date:          04/2023 
*    MBED Studio Version:    1.4.1
*    MBED OS Version:        6.12.0
*    Board:	                NUCLEO L476RG   */

///////////// includes /////////////////////
#include "mbed.h"
#include "Joystick.h"
#include "N5110.h"  
#include "StellarEngine.h"
#include "Music.h"
#include "Utils.h"

///////////// defines /////////////////////
#define AIRCRAFT_WIDTH 11
#define AIRCRAFT_HEIGHT 8
#define SLIME_SIZE 7
#define SLIME_SPEED 1

///////////// objects ///////////////////
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn buttonA(BUTTON1); //onboard user button
InterruptIn fireButton(PC_10); //InterruptIn button(PC_10);
InterruptIn emitButton(PC_11); //InterruptIn button(PC_11);
InterruptIn pauseButton(PC_12); //InterruptIn button(PC_12);
StellarEngine stellar;
Music music;

///////////// prototypes ///////////////
void init();
void render(UserInput input);
void welcome();
void game_over();
volatile int g_fireButton_flag = 0;
volatile int g_emitButton_flag = 0;
volatile int g_pauseButton_flag = 0;
void fireButton_isr();
void emitButton_isr();
void pauseButton_isr();
bool fire = false;
bool emit = false;
bool pause = false;
////////////////////////////////////////


int main() {
    
    init();      // initialise devices and objects
    welcome();   // waiting for the user to start 
    int fps = 10;
    //render(input);    // first draw the initial frame 
    thread_sleep_for(1000/fps);  // and wait for one frame period - millseconds
    
    int lives = 6;   // display lives on LEDs
    
    while (lives > 0) {  // keep looping while lives remain
        //read the joystick input and store in a struct
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        if (g_fireButton_flag) {
            g_fireButton_flag = 0;  // if it has, clear the flag
			 fire = 1;
        }
        if (g_emitButton_flag) {
            g_emitButton_flag = 0;  // if it has, clear the flag
			 emit = 1;
        }
        
        lives = stellar.update(input,fire,emit);   // update the game engine based on input    
        fire = 0;
        emit = 0;
        render(input);                     // draw frame on screen
        thread_sleep_for(1000/fps);      // and wait for one frame period - ms

        while(g_pauseButton_flag){
           lcd.drawRect(25,22,33,11,FILL_TRANSPARENT);
           lcd.drawRect(26,23,31,9,FILL_WHITE);
           lcd.printString("Pause",27,3);
           lcd.refresh();
           thread_sleep_for (1000/fps); 
        }
    }   

    game_over();
}

void init() {
    lcd.init(LPH7366_1);
    lcd.setContrast(0.5);
    fireButton.rise(&fireButton_isr);
    emitButton.rise(&emitButton_isr);
    pauseButton.rise(&pauseButton_isr);
    fireButton.mode(PullDown);
    emitButton.mode(PullDown);
    pauseButton.mode(PullDown);
    joystick.init();
    stellar.init(0, //paddle x position
              6, //paddle_height
              11,//paddle_width
              13, //slime_height          
              17, //slime_width        
              13,//ghost_size
              6, //fireball_size
              25,//alien_size        
              1, //slime_speed         
              3, //bullet_height           
              5, //bullet_width          
              5,  //bullet_speed          
              4,  //missile_height            
              7,  //missile_width     
              9,  //laser_size          
              3); //missile_speed     
}

void render(UserInput input) {  // clear screen, re-draw and refresh
    lcd.clear();  
    stellar.draw(lcd,input);
    lcd.refresh();
}

const int stellar_logo[10][59]= {
    
     {0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0},  
     {1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
     {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1},
     {1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1},
     {1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0},
     {0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1},
     {0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1},
     {0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1},
     {1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1},
     {1,1,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1},
    };

const int earth[25][27]= {
     {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1,0,0,0,0},
     {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0},
     {0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
     {0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0},
     {1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
     {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {0,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
     {0,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0},
     {0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0},
     {0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
     {0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0},
     {0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0},
     {0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0},
     {0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0},
     {0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0},   
     };    

void welcome() { // splash screen
    lcd.drawSprite(13,4,10,59, (int*)stellar_logo);
    lcd.printString("Press ",40,3);
    lcd.printString("Blue",40,4);
    lcd.printString("button",40,5);
    lcd.drawSprite(3,22,25,27, (int*)earth);
    lcd.refresh();
    music.starwar();
        while (buttonA.read() == 1){
         ThisThread::sleep_for(100ms);
        }
}

void game_over() { // splash screen 
    while (1) {
        lcd.clear();
        lcd.printString("  Game Over ",0,1);
        char buffer[14];
        lcd.printString(" Final Score",0,3);
        sprintf(buffer,"%3d",stellar.get_score());
        lcd.printString(buffer,32,4);  
        lcd.refresh();
        ThisThread::sleep_for(250ms);
        lcd.clear();
        lcd.refresh();
        ThisThread::sleep_for(250ms);
    }
}

void fireButton_isr(){
    g_fireButton_flag = 1;   // set flag in ISR
}

void emitButton_isr(){
    g_emitButton_flag = 1;   // set flag in ISR
}

void pauseButton_isr(){
    g_pauseButton_flag = !g_pauseButton_flag;   // set flag in ISR
}