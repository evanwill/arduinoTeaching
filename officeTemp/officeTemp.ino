/*
  OfficeTemp:
  Is Evan's Office Too Hot?
  
  based on: 
      Arduino Starter Kit, Project 3  - Love-O-Meter
      
  Parts required:
  UNO
  1 TMP36 temperature sensor (center pin connects to pin A0)
  4 LEDs: blue, green, orange, red (connect long leg to pins 2,3,4,5)
  4 220 ohm resistors (connect short leg of LED to GND)
  wires, usb 

 */

// set the pin the temp sensor is connected to
const int sensorPin = A0;

// set pins for LED colors
const int blue = 2;
const int green = 3;
const int yellow = 4;
const int red = 5;

// set temp threshholds in F
// < cold = blue on
const float cold = 66.0;
// > cold & < warm = green on
const float warm = 72.0;
// > warm & < hot = yellow on
const float hot = 78.0;
// > hot = red on

void setup() {
  // open a serial connection
  // so you can display temps if desired
  Serial.begin(9600);
  // set the LED pins as outputs
  // and set to LOW
  pinMode(blue, OUTPUT);
  digitalWrite(blue, LOW);
  pinMode(green, OUTPUT);
  digitalWrite(green, LOW);
  pinMode(yellow, OUTPUT);
  digitalWrite(yellow, LOW);
  pinMode(red, OUTPUT);
  digitalWrite(red, LOW);
}

void loop() {
  // read the value on AnalogIn pin 0
  // and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // temp is calculated by: 
  // 1. convert the ADC sensor reading to voltage: 
  //    float voltage = (sensorVal / 1024.0) * 5.0;
  // 2. convert voltage to C degrees based on components datasheet
  //    sensor changes 10 mV per degree, minus 500mV offset
  //    float temperatureC = (voltage - .5) * 100;
  // 3. convert C to F degrees
  //    float temperatureF = temperatureC * 1.8 + 32;
  // combined as one calculation:
  float tempF = ((sensorVal / 1024.0) * 5.0 - .5) * 180 + 32;
  // print the Temp reading to the serial console
  Serial.print("temp F: ");
  Serial.println(tempF);

  // turn on LEDs for different temp thresholds
  // cold:
  if (tempF < cold) {
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  } 
  // warm:
  else if (tempF >= cold && tempF < warm) {
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(yellow, LOW);
    digitalWrite(red, LOW);
  } 
  // hot:
  else if (tempF >= warm && tempF < hot) {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, HIGH);
    digitalWrite(red, LOW);
  } 
  // too hot:
  else if (tempF >= hot) {
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(yellow, LOW);
    digitalWrite(red, HIGH);
  }
  // wait before next reading
  delay(500);
}
