//Viral science www.youtube.com/c/viralscience
//Temperature sensor
/**************************************************************
 * Blynk is a platform with iOS and Android apps to control
 * Arduino, Raspberry Pi and the likes over the Internet.
 * You can easily build graphic interfaces for all your
 * projects by simply dragging and dropping widgets.
 *
 *   Downloads, docs, tutorials: http://www.blynk.cc
 *   Blynk community:            http://community.blynk.cc
 *   Social networks:            http://www.fb.com/blynkapp
 *                               http://twitter.com/blynk_app
 *
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 *
 **************************************************************
 * This example shows how value can be pushed from Arduino to
 * the Blynk App.
 *
 * WARNING :
 * For this example you'll need SimpleTimer library:
 *   https://github.com/jfturcot/SimpleTimer
 * and Adafruit DHT sensor library:
 *   https://github.com/adafruit/DHT-sensor-library
 *
 * App project setup:
 *   Value Display widget attached to V5
 *   Value Display widget attached to V6
 *
 **************************************************************/
#define BLYNK_TEMPLATE_ID "TMPL_B2LAy89"
#define BLYNK_DEVICE_NAME "Temperature Monitor and switch activation "
#define BLYNK_AUTH_TOKEN  "2rI1mW3Rn1EfkTptZc-Qyfv5-FMgtbLr"

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <SPI.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

Servo servo;
WidgetLCD lcd(V9);

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = BLYNK_AUTH_TOKEN; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Thakkali";  //Enter your WIFI Name
char pass[] = "3.1415926";  //Enter your WIFI Password

#define DHTPIN 2          // Digital pin 4

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.

BLYNK_WRITE(V1)
{
  int a = param.asInt();
  if (a)
  {
      servo.write(180);
  }
  else 
  {
    servo.write(0);
  }
  
}


void sendSensor()
{
  double h = dht.readHumidity();
  double t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit


  
  Blynk.virtualWrite(V6, h);  //V5 is for Humidity
  Blynk.virtualWrite(V5, t);  //V6 is for Temperature
  
  
}

void setup()
{
  Serial.begin(115200); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);
  lcd.clear();
  lcd.print(0,0,"TEST");
  servo.attach(5); //D1
  servo.write(0);
  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}


