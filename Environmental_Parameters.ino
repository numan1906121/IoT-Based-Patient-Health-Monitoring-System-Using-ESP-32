#include #include #include #include
#include "MAX30105.h" #include "heartRate.h" #include
#include
#include "OneWire.h"
#include "DallasTemperature.h" #include
#define ONE_WIRE_BUS 4	//DS18B20 sensor's
yellow pin
#define OLED_RESET 4	//OLED reset value
Adafruit_SSD1306 display(OLED_RESET);
OneWire oneWire(ONE_WIRE_BUS); DallasTemperature sensors(&oneWire);
MAX30105 particleSensor;	//MAX30102 sensor
declaratioin

const byte RATE_SIZE = 4;	//We can increase
this for more averaging
byte rates[RATE_SIZE];	//Array of heart
rates
byte rateSpot = 0;
long lastBeat = 0;	//Time at which
the last beat occurred float beatsPerMinute; float beatAvg;
float BPM = 0; int count = 0;
const char* ssid = "caution 101";	//Wifi name
const char* password = "caution101";	//Wifi password const char* serverName = "http://api.thingspeak.com/update";
String apiKey = "W4QCLASE7LIN3ALQ";	//API key for
thingspeak server
String phoneNumber = "+8801788240334";	//WhatsApp phone number
String apiKey1 = "3702186";	//API key for Bot
that is sending messages


void setup(){ Serial.begin(9600);
Serial.println("Initializing...");
// OLED display setup display.begin(SSD1306_SWITCHCAPVCC, 0x3C); display.clearDisplay();
// Testing max30102
if (!particleSensor.begin(Wire, I2C_SPEED_FAST)){ Serial.println("MAX30102 was not found. Please check wiring/power. "); while (1);
}	
 
Serial.println("Place your index finger on the sensor with steady pressure.");
// MAX30102 Setup
particleSensor.setup();	//Configure sensor
with default settings
particleSensor.setPulseAmplitudeRed(0x0A);	//Turn Red LED to low to indicate sensor is running
particleSensor.setPulseAmplitudeGreen(0);	//Turn off Green LED
// Wifi Setup WiFi.begin(ssid, password); Serial.println("Connecting");
while(WiFi.status() != WL_CONNECTED) { delay(500);
Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: "); Serial.println(WiFi.localIP());
// body temperature sensor setup sensors.begin();
}
// function for sending message void sendMessage(String message){
String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey1 + "&text=" + urlEncode(message);
HTTPClient http; http.begin(url);
http.addHeader("Content-Type", "application/x-www-form-urlencoded"); int httpResponseCode = http.POST(url);
if (httpResponseCode == 200){ Serial.print("Message sent successfully"); Serial.println();
}
else{
Serial.println("Error sending the message"); Serial.print("HTTP response code: "); Serial.println(httpResponseCode);
}
http.end();
}
void BeatPM(float x){
// temperature measurement sensors.requestTemperatures();
float tempF = sensors.getTempFByIndex(0);
// serial printing Serial.print("Temperature: "); Serial.print(tempF); Serial.print("F	");
Serial.print("BPM: "); Serial.print(x); Serial.print("bpm	"); Serial.println();
// sending to IOT if(WiFi.status()== WL_CONNECTED){
WiFiClient client; HTTPClient http;
http.begin(client, serverName);
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
String httpRequestData2 = "api_key=" + apiKey + "&field5=" + String(x) + "&field6=" + String(tempF); int httpResponseCode2 = http.POST(httpRequestData2);
Serial.print("HTTP Response code2: "); Serial.println(httpResponseCode2); http.end();
}
else {
Serial.println("WiFi Disconnected");
}
// message for critical situations if(x>100){
sendMessage("EMERGENCY!!!! Patient's BPM is Critical.");
}
if(tempF>100){
sendMessage("EMERGENCY!!!! Patient's Body Temperature is Critical.");
}
// displaying in OLED display