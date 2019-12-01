#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include <ESP8266Wifi.h>
#include <BlynkSimpleEsp8266.h>
char auth[]="acqwtXtU16xMAKVtf8AxQsA0Eo1DECOf"

const int relayPin = 10; //to be decided later.
int sensorPin = A0;// For calculating the voltage.
String networkName="to be decided";
String networkPass"to be decided";
int rxPin=0;// Wifi rx pin
int txPin=1;// Wifi tx pin

SoftwareSerial esp(rxPin,txPin);// Will come back here once



void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT); //Chosen relay pin as output.
  Serial.begin(9600);
  esp.begin(115200);
  Blynk.begin(auth,networkName,networkPass);

}

BLYNK_WRITE(V1)
{
  
int pinValue = param.asInt();  // Get status of V1.
    if (pinValue == 1) {  // If status of V1 is 1 then do stuff in if().
      sensorValue = analogRead(sensorPin);
      float voltage=(5.0*sensorValue)/(1023.0);
      if (voltage<0.5){
      digitalWrite(relayPin, LOW);  // Turn off LED.
      delay(20);
      }
      else{
        digitalWrite(relayPin, HIGH);
      }
}
{
  sensorValue = analogRead(A0);         // reading sensor from analog pin
  Blynk.virtualWrite(V1, sensorValue);  // sending sensor value to Blynk app
}
void loop() {
  // put your main code here, to run repeatedly:
  //esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           
  //if(esp.find("Error")){                                     
    //Serial.println("AT+CIPSTART Error");
  //}
  //sensorValue = analogRead(sensorPin);// Read the value of voltage in terms of bits 
  //digitalWrite(ledPin, HIGH);
  //float voltage=(5.0*sensorValue)/(1023.0);// Change it to the voltage value of real.
  //Serial.println(voltage);
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
 // delay(100);
 Blynk.begin();

}
