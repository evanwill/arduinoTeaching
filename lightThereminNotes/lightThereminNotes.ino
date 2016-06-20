/*
 based on Arduino Starter Kit example
 Project 6  - Light Theremin
 modifed by evanwill 
 combining elements from http://www.instructables.com/id/Arduino-Optical-Theremin/?ALLSTEPS#intro
 to produce stepped notes
 
 Parts required:
 photoresistor
 10 kilohm resistor
 piezo

 originally Created 13 September 2012
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

long val = 0;        //stores raw value from photocell
long maxread = 0;    //maximum value from calibration phase
long minread = 1000;  // minimum value from calibration phase

float normf = 0;    // normalized frequency 
int klogf = 0;      // logarithm of normalized frequency
int ilogf = 0;        // rounded logarithm
int i = 0;            // loop dummy variable
float factor = 0;    // scaling factor for calibration
float shift = 0;     // shift for calibration
long maxfreq = 1048;  // maximum desired frequency after calibration
long minfreq = 131;   // minimum desired frequency after calibration

double gap = 1.148698355; //ratio of consecutive notes (pentatonic)
                             // it's the 5th root of 2
//double gap = 1.059463094;  //ratio of consecutive notes (chromatic)
                              // its the 12th root of 2


void setup() {
  // Make the LED pin an output and turn it on
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
  
  // calibrate for the first five seconds after program runs
  while (millis() < 5000) {
    // record the maximum sensor value
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // record the minimum sensor value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    }
   factor = (float)(maxfreq - minfreq)/(float)(sensorHigh - sensorLow);
   shift = factor * sensorLow - minfreq; 
  }
  // turn the LED off, signaling the end of the calibration period
  digitalWrite(ledPin, LOW);
}

void loop() {
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);

  // map the sensor values to a wide range of pitches
  int pitch = map(sensorValue, sensorLow, sensorHigh, 131, 1048);
  
  normf = pitch / (float) minfreq;  // Dividing an exponential function by the min value
  klogf = log(normf) / log(gap); // allows us to take the log (base gap) and the result 
  ilogf = round(klogf);           // is the number of notes above the lowest, once we round it.
  pitch = minfreq * pow(gap,ilogf);  // we better "unlog" it.
  
  
  tone(8, pitch, 10);              // this produces the tone signal

  // wait for a moment
  delay(5);
}

