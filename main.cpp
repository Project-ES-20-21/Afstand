#include <WiFi.h>
#include <WiFiMulti.h>
#include <Arduino.h>
#include <circ-buffer.h>
 
char* ssid1 = "ESP32-Access-Point";
char* password1 =  "123456789";
char* ssid2 = "telenet-apn-e3c7c";
char* password2 = "lnk799ew4r6y";
char* ssid3="TheForceB";
char* password3="Vis73Gat,28Okt06";
WiFiMulti wifiMulti;

 
CircBuffer buffer;
int teller=0;
float * avg;

CircBufferStatus_t initBuffers(uint8_t size){
  CircBufferStatus_t status = buffer.init(size);
  if(status != CB_SUCCESS){
  return status;
}
  return CB_SUCCESS;
}

 
void setup() {
 
  Serial.begin(115200);
  pinMode(2,OUTPUT);  
  wifiMulti.addAP(ssid1, password1);
  wifiMulti.addAP(ssid2, password2);
  wifiMulti.addAP(ssid3,password3);
  Serial.println("Connecting Wifi...");
  if(wifiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("Wifi name: ");
      Serial.println(WiFi.SSID());
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
  }
  initBuffers(10);
}
 
void loop() {
  delay(500);
  unsigned long tijd1=millis();
  wifiMulti.run();
  if(wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
  }
  long rssi = WiFi.RSSI();
  buffer.put(rssi);
  teller++;
  if(teller%10==0){
    Serial.printf("Gemiddelde: %f\n", buffer.getAverage());
    if(buffer.getAverage()>-40){
      digitalWrite(2,HIGH);
    }
    else{
      if(buffer.getAverage()<-45){
        digitalWrite(2,LOW);
      }
    }
  }
  unsigned long tijd2 = millis();
  unsigned long tijd= tijd2 - tijd1;
  Serial.println(tijd);
}