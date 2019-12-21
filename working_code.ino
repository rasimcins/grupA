#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
char auth[]="up83f0V9u3pjV7qBblGaLsQfvdtFxf27";
char networkName[]="AndroidAP9D88";
char networkPass[]="12345678";
const int relayPin=0;
const int sensorPin=A0;
int mVperAmp = 185; // use 100 for 20A Module and 66 for 30A Module
 
double Voltage = 0;
double VRMS = 0;
double AmpsRMS = 0;
int pinValue;
BlynkTimer timer;

void setup() {
  pinMode(relayPin,OUTPUT);
 
  Serial.begin(9600);
  Blynk.begin(auth,networkName,networkPass);
  //Blynk.syncVirtual(V1);
  timer.setInterval(1500L, what);

}

void what(){
   Voltage = getVPP();
   VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
   AmpsRMS = (VRMS * 1000)/mVperAmp;
   Serial.println(AmpsRMS);
   if (AmpsRMS<=0.09){
      digitalWrite(relayPin, HIGH);  // Turn off LED.
      
      }
      else{
       // digitalWrite(relayPin, HIGH);
      }
}
BLYNK_WRITE(V1)
{
  
 Voltage = getVPP();
 VRMS = (Voltage/2.0) *0.707;  //root 2 is 0.707
 AmpsRMS = (VRMS * 1000)/mVperAmp;
int pinValue = param.asInt();  // Get status of V1.
   if(pinValue==1){
   if (AmpsRMS<0.07){
      digitalWrite(relayPin, LOW);  // Turn off LED.
      
      Blynk.virtualWrite(V1, 0.0);
      delay(20);
      }
      else{
        digitalWrite(relayPin, HIGH);
        Blynk.virtualWrite(V1, AmpsRMS);
        delay(20);
      }
   }
   else{
    digitalWrite(relayPin, LOW);  // Turn off LED.
      
      Blynk.virtualWrite(V1, 0.0);
      delay(20);
   }
}
void readVolt(){
 
  int sensorValue = analogRead(sensorPin);         // reading sensor from analog pin
   float voltage=sensorValue;
  Blynk.virtualWrite(V1, voltage);  // sending sensor value to Blynk app
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  timer.run();
 
  

}

float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorPin);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
