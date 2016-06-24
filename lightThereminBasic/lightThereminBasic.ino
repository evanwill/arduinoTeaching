/*
 Basic Light Theremin 
 based on Scott Fitzgerald, "p06_LightTeremin", 2012 http://www.arduino.cc/starterKit
 modified and annotated by evanwill 2016, https://github.com/evanwill/arduinoTeaching
 
 Parts required:
 UNO, 
 photoresistor (connected to pin A0) and 10 kilohm resistor, 
 piezo (connected to pin 8)
*/

// create variable to hold sensor value
int sensorValue;
// UNO's analog read sensors use "analog to digital converter" (ADC),
// which means it divides the reading coming from the sensor (0 to 5 volts) into 1024 equal steps.
// Thus, the reading from our photoresistor could range from 0 to 1023,
// however it is unlikely to use the full range so we will calibrate it.
// For now, create variables to hold the high and low value for our photoresistor range, 
// make them the opposite of the max/min values and we will calibrate them down.
int sensorLow = 1023;
int sensorHigh = 0;
// set the LED pin, 13 is the built in LED
const int ledPin = 13;

// the setup() is run once when the program starts
void setup() {
  // First, start a blinking LED to give the user warning that its time to calibrate the sensor!
  // use pinMode() to make the LED pin an output https://www.arduino.cc/en/Reference/PinMode
  pinMode(ledPin, OUTPUT);
  // use digialWrite()to turn the LED on, https://www.arduino.cc/en/Reference/DigitalWrite
  digitalWrite(ledPin, HIGH);
  // add a delay() in milliseconds, https://www.arduino.cc/en/Reference/Delay
  delay(500);
  // then turn off the LED to blink it
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(500);  
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);

  // after it blinks for 2 seconds, its time to calibrate the photoresistor readings
  // create a loop with while() that lasts for 5000 ms, https://www.arduino.cc/en/Reference/While
  while (millis() < 5000) {
    // use analogRead() to get a reading from the photoresistor, https://www.arduino.cc/en/Reference/AnalogRead
    sensorValue = analogRead(A0);
    // create two conditions using if() to calibrate the max and min sensor values, https://www.arduino.cc/en/Reference/If
    // raise the sensorHigh if the current reading is higher:
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    // lower the sensorLow if the current reading is lower:
    if (sensorValue < sensorLow) {
      sensorLow = sensorValue;
    } 
  }
  
  // turn the LED off, calibration is done!
  digitalWrite(ledPin, LOW); 
}

// the loop() will run continuously until we unplug the UNO
// it needs to read the photoresistor then output a tone
void loop() {
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);

  // use map() to re-map our reading to create a tone, https://www.arduino.cc/en/Reference/Map
  // map(currentValue, oldRange1, oldRange2, newRange1, newRange2)
  // our min/max values for the old range are the sensorHigh and sensorLow from calibration
  // I reverse their order (high, low) so that shading the photoresister will cause a higher tone.
  // the new range is the range of Hz to use to produce sound, which for UNO can be from 31 to 65535 Hz.
  // I set it from 0 to 4000, which is a more normal sound range.
  // since we start at 0, full light will make no tone, full shade will make the highest tone.
  int pitch = map(sensorValue, sensorHigh, sensorLow, 0, 4000);
  
  // use the tone function to create sound in the piezo, https://www.arduino.cc/en/Reference/Tone
  // tone(pin#, value, milliseconds)
  tone(8, pitch, 10);

  // add a delay to make the current tone sustained for a few ms
  // play around with this value to change the quality of the tones, 
  delay(5);
}

