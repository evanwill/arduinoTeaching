/*
 Scaled Light Theremin 2 
 
 based on: 
  Tom Igoe, "Melody", 2010 https://www.arduino.cc/en/Tutorial/ToneMelody?from=Tutorial.Tone
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

// create a scale of tones as a set 
#define SCALE_LEN 90
int scale[SCALE_LEN] = {
  0,  
  31,
  33,
  35,
  37,
  39,
  41,
  44,
  46,
  49,
  52,
  55,
  58,
  62,
  65,
  69,
  73,
  78,
  82,
  87,
  93,
  98,
  104,
  110,
  117,
  123,
  131,
  139,
  147,
  156,
  165,
  175,
  185,
  196,
  208,
  220,
  233,
  247,
  262,
  277,
  294,
  311,
  330,
  349,
  370,
  392,
  415,
  440,
  466,
  494,
  523,
  554,
  587,
  622,
  659,
  698,
  740,
  784,
  831,
  880,
  932,
  988,
  1047,
  1109,
  1175,
  1245,
  1319,
  1397,
  1480,
  1568,
  1661,
  1760,
  1865,
  1976,
  2093,
  2217,
  2349,
  2489,
  2637,
  2794,
  2960,
  3136,
  3322,
  3520,
  3729,
  3951,
  4186,
  4435,
  4699,
  4978
};

// the setup() is run once when the program starts
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
  
  // turn the LED off, calibration is done!
  digitalWrite(ledPin, LOW); 
}

void loop() {
  // read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);
  
  // map the photoresistor reading on to a note in the scale
  int note = map(sensorValue, sensorLow, sensorHigh, SCALE_LEN, 0);
  int current_tone = scale[note];
  
  // send the note to the piezo
  tone(8, current_tone, 10);

  // add a delay to make the current tone sustained for a few ms
  // play around with this value to change the quality of the tones, 
  delay(5);
}

