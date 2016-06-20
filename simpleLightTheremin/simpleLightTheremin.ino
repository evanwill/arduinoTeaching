/*
  Arduino Starter Kit example
 Project 6  - Light Theremin

 modified by evanwill for UIdaho Library Opening 2016
 reversed tone creation (off = full light, high note = full shade), 
 recalibrated range of tones from 0 to 1200,
 adding blinking and longer time to simplify sensor calibration

 This sketch is written to accompany Project 6 in the
 Arduino Starter Kit

 Parts required:
 photoresistor
 10 kilohm resistor
 piezo

 Created 13 September 2012
 by Scott Fitzgerald

 http://www.arduino.cc/starterKit

 This example code is part of the public domain
*/

// variable to hold sensor value
int sensorValue;
// variable to calibrate low value
int sensorLow = 1023;
// variable to calibrate high value
int sensorHigh = 0;
// LED pin
const int ledPin = 13;

void setup() {
  // Make the LED pin an output and blink it for a bit, then turn on.
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);  
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  
  // calibrate for the first 8 seconds after program runs
  while (millis() < 8000) {
    // record the maximum sensor value
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
  }
  // turn the LED off, signaling the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);

  // map the sensor values to a wide range of pitches
  // i reverse map all the way down to zero-- thus full light = no tone.
  int pitch = map(sensorValue, sensorLow, sensorHigh, 1200, 0);

  // (pin#, pitch, ms time) play with ms and delay
  tone(8, pitch, 10);

  // wait for a moment
  delay(10);
}

