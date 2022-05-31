/*
pin formation format
VCC - 3.3 volt -> pin 19
Gnd - ground -> pin 6
SCL - sens1 -> pin 43
SDA -> sens2 -> pin 46
*/

//--------------------------------------------------------------------// 
// Wifi and Thingspeak setup:
#include <WiFi.h>
#include "ThingSpeak.h";

unsigned long myChannelNumber = 1374514;
const char * myWriteAPIKey = "B0VP3R0CXNWEOXE1";

//const char* ssid = "HUJI-guest"; // your wifi SSID name
//const char* password = "" ;// wifi pasword
const char* ssid = "NIR"; 
const char* password = "abcd123456" ;// wifi pasword


//const char* ssid = "NIR-HOTSPOT"; // your wifi SSID name
//const char* password = "123456abcd" ;// wifi pasword

const char* server = "api.thingspeak.com";

WiFiClient client;

//-------------------------------------------------------------------------//
//BME280 setup
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1013.25) // setup the sea level pressure 

Adafruit_BME280 bme; // I2C

unsigned long delayTime;

////////////////////////////////////////////////////////////////////////////////

float Met_Val[5]; // same as above try to be smarter :-)
float SVP;
int  divide= 10; // how many samples taken
/* Temp - Temperature
 *  RH - Reletive humidity
 *  PR - pressure
 *  ALT - alttitude
 *  KEl - Kelvin
 *  VPD - VPD
 */
#include "i2cArduino.h"


void setup() {
  // code runs once! setting up wifi and thingspeak 
  //Wifi
  Serial.begin(9600);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

    ThingSpeak.begin(client);
 
  WiFi.begin(ssid, password);
  
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();

  //BME chckup
    Serial.println(F("BME280 test"));

  bool status;

  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);  
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  Serial.println("-- Default Test --");
  delayTime = 1000;

  Serial.println();



}

void loop() {
  Serial.println("Collecting Average Data from the last 10 seconds");
  float SVP,Temp,RH,VPD;
  float Met_Val[5]; // same as above try to be smarter :-)
  // Reading the Sensor Data

  /// set variables to 0 each run
  for(int idx=0;idx<7;idx++)
  {
    Met_Val[idx]=0;
    SVP=0;
    Temp=0;
    RH=0;
  }
// Collecting Data from sensor and sum it in 10 seccond interval
  for (int count=0;count<10;count++)
  {
    Met_Val[0] += bme.readTemperature();
    Temp = bme.readTemperature();
    Met_Val[1] += bme.readHumidity();
    RH =  bme.readHumidity();
    Met_Val[2] += bme.readPressure(); 
    Met_Val[3] += bme.readAltitude(SEALEVELPRESSURE_HPA);
    Met_Val[4] += bme.readTemperature()+ 273;

    SVP = 0.61078*(exp(Temp/(Temp+238.3) * 17.2694));
    //SVP = 0.61078*exp((Temp/(Temp+238.3))*17.2694);
    VPD += (SVP*(1-(RH/100.0)))/10; 
    delay(1000);
  }

  // divide values by count times
  for (int idx=0;idx<7;idx++)
  {
    Met_Val[idx]/=10;
  }
  VPD /=10;
  
    // UpLoad to ThingSpeak
  ThingSpeak.setField(1,Met_Val[0]);
  ThingSpeak.setField(2,Met_Val[1]);
  ThingSpeak.setField(3,Met_Val[2]);
  ThingSpeak.setField(4,Met_Val[3]);
  ThingSpeak.setField(5,Met_Val[4]);
  ThingSpeak.setField(6,VPD);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  // printing
  Serial.println("Uploading Following Data to ThingspeakServer");
  // values
  Serial.print("Temperature = ");
  Serial.print(Met_Val[0]);
  Serial.println(" *C");

  Serial.print("Humidity = ");
  Serial.print(Met_Val[1]);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(Met_Val[2]);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(Met_Val[3]);
  Serial.println(" m");

  Serial.print("Temperature = ");
  Serial.print(Met_Val[4]);
  Serial.println(" *K");

  Serial.print("VPD = ");
  Serial.print(VPD);
  Serial.println(" kPa");

  Serial.println("");
  Serial.println("Next Upload in 1 min");

  delay(50000);


}
