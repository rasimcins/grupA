#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <BlynkSimpleEsp32.h>
char auth[]="uUqTFegVHviAto299y2wRwAp3VNtdeNd";
char networkName[]="AndroidAP5778";
char networkPass[]="nztc8375";
const int relayPin=21;
const int sensorPin=14;


void setup() {
  pinMode(relayPin,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth,networkName,networkPass);

}
BLYNK_WRITE(V1)
{
  
 readVolt();
int pinValue = param.asInt();  // Get status of V1.
    if (pinValue == 1) {  // If status of V1 is 1 then do stuff in if().
      int sensorValue = analogRead(relayPin);
      float voltage=(3.3*sensorValue)/(4095.0);
      if (voltage<0.5){
      digitalWrite(relayPin, LOW);  // Turn off LED.
      delay(20);
      }
      else{
        digitalWrite(relayPin, HIGH);
      }
      
}}
void readVolt(){
 
  int sensorValue = analogRead(sensorPin);         // reading sensor from analog pin
   float voltage=sensorValue;
  Blynk.virtualWrite(V1, voltage);  // sending sensor value to Blynk app
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

}
