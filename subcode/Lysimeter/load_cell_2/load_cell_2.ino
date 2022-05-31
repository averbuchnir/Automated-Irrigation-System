/*
VCC - VCC
GND - GND
DT - 22 
SCK - 23
*/
#include "HX711.h"
 
// HX711 circuit wiring
//const int LOADCELL_DOUT_PIN = 22;
//const int LOADCELL_SCK_PIN = 23;

const int LOADCELL_DOUT_PIN = 18;
const int LOADCELL_SCK_PIN = 19;
float zero;
HX711 scale;
 
void setup() {
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  delay(1000);
  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("HX711 Ready to read");
  } else {
    Serial.println("HX711 not found.");
  }
}
 
void loop() {
  if (scale.is_ready()) {
    long reading = scale.read();
    //Serial.print("HX711 reading: ");
    Serial.println(reading*0.0103+123.450);
    //Serial.println(reading);
  } else {
    Serial.println("HX711 not found.");
  }
delay(5000);
}
