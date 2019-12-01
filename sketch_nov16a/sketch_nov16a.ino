#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


const int relayPin = 10; 
const int sensorPin = A0;
String networkName="to be decided";
String networkPass="to be decided";
int rxPin=0;
int txPin=1;

String ip;
WiFiServer ESPserver(80);

//SoftwareSerial esp(rxPin,txPin);// Will come back here once

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT); //Chosen relay pin as output.
  Serial.begin(9600);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(networkName);
  WiFi.begin(networkName, networkPass);
  delay(5000);
  while (WiFi.status() != WL_CONNECTED) 
  {
  delay(100);
  Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
// Start the server
  ESPserver.begin();
  Serial.println("Server started");
 
// Print the IP address
  Serial.print("The URL to control ESP8266: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());

}

void loop() {
  /*
  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           
  if(esp.find("Error")){                                     
    Serial.println("AT+CIPSTART Error");
  }*/
  int sensorValue = analogRead(sensorPin);// Read the value of voltage in terms of bits 
  //digitalWrite(ledPin, HIGH);
  float voltage=(5.0*sensorValue)/(1023.0);// Change it to the voltage value of real.
  Serial.println(voltage);
  if(voltage<0.5){
  digitalWrite(relayPin, LOW);
  }
  else{
    digitalWrite(relayPin, HIGH);
 WiFiClient client = ESPserver.available();
  if (!client) 
  {
  return;
  }
 
// Wait until the client sends some data
  Serial.println("New Client");
  while(!client.available())
  {
  delay(100);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
  int value = LOW;
  if (request.indexOf("/RELAYON") != -1) 
  {
  digitalWrite(relayPin, LOW);
  value = LOW;
  } 
  if (request.indexOf("/RELAYOFF") != -1)
  {
  digitalWrite(relayPin, HIGH);
  value = HIGH;
  }
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  IMPORTANT
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Status of the Lamp: ");
 
  if(value == LOW) 
  {
  client.print("ON");  
  } 
  else
  {
  client.print("OFF");
  }
 
  delay(100);
//client.stop();
  
  Serial.println("");}
  /* App configuration and connecting to a wifi will be decided here
  
  /*if(voltage<0.5){
  digitalWrite(ledPin, LOW);
  }*/
  /*else if(voltage>=0.5){
  digitalWrite(ledPin, HIGH);
  }*/
  /*else if(state=='1'){
  digitalWrite(ledPin, HIGH);
  }*/
  /*else if(state=='1'){
  digitalWrite(ledPin, LOW);
  }*/
  delay(1000);

  }}
