/*
 Scaled Light Theremin 1
 based on combining: 
   gwarbeh, "Arduino Optical Theremin", http://www.instructables.com/id/Arduino-Optical-Theremin/?ALLSTEPS#intro
   Scott Fitzgerald, "p06_LightTeremin", 2012 http://www.arduino.cc/starterKit
 
 by evanwill 2016, https://github.com/evanwill/arduinoTeaching
 [see lightTereminBasic for full annotation]
 
 Parts required:
 UNO, 
 photoresistor (connected to pin A0) and 10 kilohm resistor, 
 piezo (connected to pin 8)
*/

// create variable to hold sensor value
int sensorValue;
// create variable for sensor calibration
int sensorLow = 1023;
int sensorHigh = 0;
// set the LED pin, 13 is the built in LED
const int ledPin = 13;

// create variables to calibrate tones to a musical scale
float normf = 0;    // normalized frequency 
int klogf = 0;      // logarithm of normalized frequency
int ilogf = 0;        // rounded logarithm
int i = 0;            // loop dummy variable
float factor = 0;    // scaling factor for calibration
float shift = 0;     // shift for calibration
long maxfreq = 1048;  // maximum desired frequency after calibration
long minfreq = 131;   // minimum desired frequency after calibration
double gap = 1.148698355; //ratio of consecutive notes (pentatonic) the 5th root of 2

void setup() {
  // blinking LED to signal calibration start
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

  // calibration loop
  while (millis() < 5000) {
    // get a reading from the photoresistor
    sensorValue = analogRead(A0);
    // set sensor max value
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // set sensor min value
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    } 
  }
  
  // calculate scale based on calibration
  factor = (float)(maxfreq - minfreq)/(float)(sensorHigh - sensorLow);
  shift = factor * sensorLow - minfreq;
  
  // turn the LED off, calibration is done!
  digitalWrite(ledPin, LOW); 
}

void loop() {
  // read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);
  // use some math to figure out the scaled tone
  int pitch = factor*sensorValue - shift;
  normf = pitch / (float) minfreq;  // Dividing an exponential function by the min value
  klogf = log(normf) / log(gap); // allows us to take the log (base gap) and the result 
  ilogf = round(klogf);           // is the number of notes above the lowest, once we round it.
  pitch = minfreq * pow(gap,ilogf);  // we better "unlog" it.
  
  // send the tone to piezo (play around with the last value)
  tone(8, pitch, 10);

  // add a delay to make the current tone sustained for a few ms if desired 
  // delay(5);
}

