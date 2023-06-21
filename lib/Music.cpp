#include "Music.h"

// nothing doing in the constructor and destructor
PwmOut buzzer(PA_15);

Music::Music() {}

const int C_major_scale[] = {NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_DS5, NOTE_E5, NOTE_B5, NOTE_D5, NOTE_C5, NOTE_A5}; // create array with the required notes (in order)
const int C_major_scale1[] = {NOTE_D4, NOTE_D4, NOTE_D4};
const int C_major_scale2[] = {NOTE_G4, NOTE_D5, NOTE_G5};
const int C_major_scale3[] = {NOTE_C5, NOTE_B5, NOTE_A5};
const int C_major_scale4[] = {NOTE_C5, NOTE_B5, NOTE_C5, NOTE_A5};

void Music::starwar(){                                     // Music: Star wars (Program end reminder song)

            for(int i = 0; i < 3; i++){

             play_note_1_3(C_major_scale1[i]);
             buzzer.pulsewidth_us(0);
             thread_sleep_for(WAIT_TIME_MS);
            }
             buzzer.pulsewidth_us(0);

            for(int i = 0; i < 2; i++){
                play_note_2(C_major_scale2[i]);
                buzzer.pulsewidth_us(0);
                thread_sleep_for(WAIT_TIME_MS);
            }

            for (int i=0; i<2; i++) {

            for(int i = 0; i < 3; i++){

                play_note_1_3(C_major_scale3[i]);
                buzzer.pulsewidth_us(0);

                thread_sleep_for(WAIT_TIME_MS);
            }
                 play_note_2(C_major_scale2[2]);
                 buzzer.pulsewidth_us(0);
                 thread_sleep_for(WAIT_TIME_MS);
                 play_note_1(C_major_scale2[1]);
                 buzzer.pulsewidth_us(0);
                 thread_sleep_for(WAIT_TIME_MS);
            }
            buzzer.pulsewidth_us(0);
            for(int i = 0; i < 3; i++){
 
                play_note_1_3(C_major_scale4[i]);
                buzzer.pulsewidth_us(0);
                thread_sleep_for(WAIT_TIME_MS);
            }
                play_note_2(C_major_scale4[3]);
                buzzer.pulsewidth_us(0);
                thread_sleep_for(WAIT_TIME_MS);
            
}


// music rhythm

void Music::play_note_1_3(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);  //set the period of the pwm signal (in us)
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);          //set pulse width of the pwm to 1/2 the period
    ThisThread::sleep_for(200ms);                             //play sound for 200ms
}

void Music::play_note_1_2(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);   
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);         
    ThisThread::sleep_for(250ms);                            
}

void Music::play_note_1(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);   
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);         
    ThisThread::sleep_for(600ms);                            
}

void Music::play_note_2(int frequency){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);    
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);           
    ThisThread::sleep_for(1200ms);                      
}