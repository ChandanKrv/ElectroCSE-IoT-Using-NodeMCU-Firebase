#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<ESP8266Ping.h>

#define FIREBASE_HOST "example.firebaseio.com"
#define FIREBASE_AUTH "Your_Auth"

const char *ssid = "WiFi_Name";
const char *password = "WiFi_Password";

#define led D1

const IPAddress remote_ip(208, 80, 153, 224);

void setup() {
  Serial.begin(9600);
  while (WiFi.status() == WL_DISCONNECTED) {
    myNetwork();
  }
  Serial.println("Successfully Connected ");
  Firebase.setInt("ledDb", 0);
  pinMode(led, OUTPUT);

}
void myNetwork() {
  Serial.println("Searching Wifi......");

  int network = WiFi.scanNetworks();
  for (int i = 0 ; i < network; i++) {
    if (WiFi.SSID(i) == ssid) {
      WiFi.begin(ssid, password);
      Serial.println("/n Wifi Found");
      delay(2000);
      Serial.println("Connecting Please Wait ");
      delay(8000);
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    }
  }
}

int ledStatus;

void loop() {
  if (!Ping.ping(remote_ip)) {
    Serial.println("No Internet");
    myNetwork();
  } else {
    Serial.println("Internet Access");
    ledStatus = Firebase.getInt("ledDb");
    if (ledStatus == 1) {
      digitalWrite(led, HIGH);
    } else {
       digitalWrite(led, LOW);
    }

  }
}
