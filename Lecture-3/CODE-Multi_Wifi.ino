#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ESP8266Ping.h>

#define FIREBASE_HOST "xyz.firebaseio.com"
#define FIREBASE_AUTH "Your_AUTH_CODE_PASTE_HERE"

const char *ssid1 = "1st-WiFiName"; //
const char *password1 = "1st-WiFiPass";

const char *ssid2 = "2nd-WiFiName";
const char *password2 = "2nd-WiFiPass";

//#define TCP_MSS whatever
//#define LWIP_IPV6 whatever
//#define LWIP_FEATURES whatever
//#define LWIP_OPEN_SRC whatever

#define led D1

const IPAddress remote_ip(208, 80, 153, 224);
//const IPAddress remote_ip(8, 8, 8, 8); //Google

void setup()
{
  Serial.begin(9600);
  while (WiFi.status() == WL_DISCONNECTED)
  {
    myNetwork();
  }
  Serial.println("Successfully Connected ");
  Firebase.setInt("ledDb", 0);
  pinMode(led, OUTPUT);
}
void myNetwork()
{
  int flag = 1;
  Serial.println("Searching Wifi......");
  int network = WiFi.scanNetworks(); //5
  for (int i = 0; i < network; i++)
  {
    switch (flag)
    {
    case 1:
      flag = 2;
      if (WiFi.SSID(i) == ssid1)
      {
        WiFi.begin(ssid1, password1);
        Serial.println("/n Wifi Found");
        delay(2000);
        Serial.println("Connecting with candyxt Please Wait ");
        delay(8000);
        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        break;
      }
    case 2:
      flag = 1;
      if (WiFi.SSID(i) == ssid2)
      {
        WiFi.begin(ssid2, password2);
        Serial.println("/n Wifi Found");
        delay(2000);
        Serial.println("Connecting with candyasus Please Wait ");
        delay(8000);
        Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
        break;
      }
    }
  }
}

int ledStatus;

void loop()
{
  if (!Ping.ping(remote_ip))
  {
    Serial.println("No Internet");
    myNetwork();
  }
  else
  {
    Serial.println("Internet Access");
    ledStatus = Firebase.getInt("ledDb");
    if (ledStatus == 1)
    {
      digitalWrite(led, HIGH);
    }
    else
    {
      digitalWrite(led, LOW);
    }
  }
}
