#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


const int relayPin = null; //to be decided later.
int sensorPin = A0;// For calculating the voltage.
String networkName="to be decided";
String networkPass"to be decided";
int rxPin=null;// Wifi rx pin
int txPin=null;// Wifi tx pin

SoftwareSerial esp(rxPin,txPin);// Will come back here once

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT); //Chosen relay pin as output.
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);// Read the value of voltage in terms of bits 
  //digitalWrite(ledPin, HIGH);
  float voltage=(5.0*sensorValue)/(1023.0);// Change it to the voltage value of real.
  Serial.println(voltage);
  /* App configuration and connecting to a wifi will be decided here
  */
  /*if(voltage<0.5){
  digitalWrite(ledPin, LOW);
  }*/
  /*else if(voltage>=0.5){
  digitalWrite(ledPin, HIGH);
  }*/
  /*else if("open"){
  digitalWrite(ledPin, HIGH);
  }*/
  /*else if("close"){
  digitalWrite(ledPin, LOW);
  }*/
  delay(1000);

}
