// Load Wi-Fi library
#include <WiFi.h>
#include <DHT.h>
#include <Ucglib.h>
//#include <SPI.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

static const int RXPin = 13, TXPin = 14;
static const uint32_t GPSBaud = 9600;


//Serial connector for GPS unit, output is pin 14, input is 13
SoftwareSerial ss(RXPin, TXPin);
  
#define DHTPIN 8 // we're using pin 2
#define DHTTYPE DHT11 // we're using the DHT11

// define our DHT object using the pin and type from above
DHT dht(DHTPIN, DHTTYPE);

// Replace with your network credentials
const char* ssid = "StinkyCompound";
const char* password = "1securepassword";

//Ucglib_ST7735_18x128x160_SWSPI ucg(/*sclk=*/ 13, /*data=*/ 11, /*cd=*/ 9 , /*cs=*/ 10, /*reset=*/ 8);
// rs = 3, sda = 4, clk = 5, cs = 6, rst = 7 
Ucglib_ST7735_18x128x160_SWSPI ucg(5,4,3,6,7);

WiFiClient client;

TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);

  ss.begin(GPSBaud);

  ucg.begin(UCG_FONT_MODE_TRANSPARENT);
  ucg.clearScreen();
  ucg.setFont(ucg_font_helvR08_tr);
  ucg.setColor(255,255,255);
  ucg.setColor(1,0,255,0);


  ucg.setPrintPos(0,25);

  ucg.println("Connecting to ");
  ucg.println(ssid);

  WiFi.begin(ssid, password);
  ucg.setPrintPos(0, 35);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    ucg.print(".");
  }
  ucg.println("");
  
  ucg.setPrintPos(0, 45);
  ucg.println(WiFi.localIP());  
  delay(500);
  
  pinMode(DHTPIN, OUTPUT);

}


void loop() {
    // create a float and read the temperature sensor
  float myTemperature = dht.readTemperature(true);
  float myHumidity = dht.readHumidity(false);

  char buffer[50];
  // print the temperature on the screen in Celsius

  ucg.clearScreen();
  ucg.setFont(ucg_font_7x14_tr);
  ucg.setColor(255,255,255);
  ucg.setColor(1,255,0,0);

  ucg.setPrintPos(5,25);
  ucg.print("Temp: ");
  ucg.print(myTemperature);
  ucg.println((char)223);

  ucg.setPrintPos(5,55);
  ucg.print("Humidity: ");
  ucg.print(myHumidity);
  ucg.println("%");

/*
  while (ss.available() > 0){
    // get the byte data from the GPS
    gps.encode(ss.read());
      ucg.setPrintPos(5,80);
      ucg.print("Lat: ");
      ucg.println(gps.location.lat());

      ucg.setPrintPos(5,110);
      ucg.print("Long: ");
      ucg.println(gps.location.lng());

      ucg.setPrintPos(5, 140);
      ucg.print("Sats: ");
      ucg.println(gps.satellites.value());

  }

  Serial.print(ss.available());
  
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
  Serial.print(gps.location.isUpdated());
  Serial.print(ss.read());
*/

  delay(10000);  
}