#ifndef MUSIC_H
#define MUSIC_H

#include "mbed.h"
#include <cstdio>
#include "N5110.h"
#include "Utils.h"  
#include "Aircraft.h"
#include <vector>

#define NOTE_D4  294
#define NOTE_G4  392
#define NOTE_A5  440
#define NOTE_B5  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_G5  784

#define WAIT_TIME_MS 15


class Music
{
public:
    Music();
    void play_note_1_2(int frequency);
    void play_note_1_3(int frequency);
    void play_note_1(int frequency);
    void play_note_2(int frequency);
    
void starwar();

private:
};
#endif