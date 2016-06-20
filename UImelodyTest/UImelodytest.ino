/*
  Melody

 Plays a melody

 circuit:
 * 8-ohm speaker on digital pin 8

 modified by evanwill for UI library opening 2016
 
 merged with 
   Arduino Mario Bros Tunes
  With Piezo Buzzer and PWM
  by: Dipto Pratyaksa
  last updated: 31/3/13
  http://www.linuxcircle.com/2013/03/31/playing-mario-bros-tune-with-arduino-and-piezo-buzzer/

 created 21 Jan 2010
 modified 30 Aug 2011
 by Tom Igoe

This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/Tone

 */
#include "pitches.h"

// notes in the melody:
//int melody[] = {
//  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
//};
// start of go idaho
//int melody[] = {
// NOTE_F6, NOTE_F6, NOTE_F6, NOTE_C6, NOTE_C6, NOTE_C6, NOTE_A5, NOTE_A5, NOTE_F5
// };

//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7, 0, NOTE_C7, NOTE_E7, 0, NOTE_G7, 0, 0,  0, NOTE_G6, 0, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0, NOTE_C7, 0, 0, NOTE_G6, 0, 0, NOTE_E6, 0, 0, NOTE_A6, 0, NOTE_B6, 0, NOTE_AS6, NOTE_A6, 0, NOTE_G6, NOTE_E7, NOTE_G7, NOTE_A7, 0, NOTE_F7, NOTE_G7, 0, NOTE_E7, 0,NOTE_C7, NOTE_D7, NOTE_B6, 0, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0, NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_AS3, NOTE_AS4, 0, 0, NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4, 0, 0, NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4, NOTE_DS3, NOTE_DS4, 0, 0, NOTE_DS4, NOTE_CS4, NOTE_D4, NOTE_CS4, NOTE_DS4, NOTE_DS4, NOTE_GS3, NOTE_G3, NOTE_CS4, NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4, NOTE_GS4, NOTE_DS4, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_GS3, 0, 0, 0
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
//int noteDurations[] = {
//  4, 8, 8, 4, 4, 4, 4, 4
//};
// start of go idaho
// int noteDurations[] = {
//  4, 2, 6, 4, 2, 6, 4, 2, 12 
// };

//Mario main them tempo
int noteDurations[] = {
  12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 9, 9, 9, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
  1,
  12, 12, 12, 12, 12, 12, 6, 3, 12, 12, 12, 12, 12, 12, 6, 3, 12, 12, 12, 12, 12, 12, 6, 3, 12, 12, 12, 12, 12, 12, 6, 6, 18, 18, 18, 6, 6, 6, 6, 6, 6, 18, 18, 18,18, 18, 18, 10, 10, 10, 10, 10, 10, 3, 3, 3
};

void setup() {
  // iterate over the notes of the melody:
  int size = sizeof(melody) / sizeof(int);
  for (int thisNote = 0; thisNote < size; thisNote++) {

    // to calculate the note duration, take one second
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.50;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
}

void loop() {
  // no need to repeat the melody.
}
