#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>


const int relayPin = null; //to be decided later.
int sensorPin = A0;// For calculating the voltage.
String networkName="to be decided";
String networkPass"to be decided";
int rxPin=0;// Wifi rx pin
int txPin=1;// Wifi tx pin

String ip;
WiFiServer ESPserver(80);

SoftwareSerial esp(rxPin,txPin);// Will come back here once

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPin,OUTPUT); //Chosen relay pin as output.
  Serial.begin(9600);
   esp.begin(115200); 
   esp.println("AT"); 
   while(!esp.find("OK")){                                     //Modül hazır olana kadar bekliyoruz.
    esp.println("AT");
    Serial.println("ESP8266 Bulunamadı.");
  }
  esp.println("AT+CWMODE=1");                                 //ESP8266 modülünü client olarak ayarlıyoruz.
  while(!esp.find("OK")){                                     //Ayar yapılana kadar bekliyoruz.
    esp.println("AT+CWMODE=1");
    Serial.println("Ayar Yapılıyor....");
  }
  Serial.println("Client olarak ayarlandı");
  Serial.println("Aga Baglaniliyor...");
  esp.println("AT+CWJAP=\""+agAdi+"\",\""+agSifresi+"\"");    //Ağımıza bağlanıyoruz.
  while(!esp.find("OK"));                                     //Ağa bağlanana kadar bekliyoruz.
  Serial.println("Aga Baglandi.");
  delay(1000);
   
 

}

void loop() {

  esp.println("AT+CIPSTART=\"TCP\",\""+ip+"\",80");           //Thingspeak'e bağlanıyoruz.
  if(esp.find("Error")){                                      //Bağlantı hatası kontrolü yapıyoruz.
    Serial.println("AT+CIPSTART Error");
  }
  
  /* App configuration and connecting to a wifi will be decided here
  */
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

}
