#include "DHT.h" #include #include #include #include #include

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 4	// Digital pin connected to the DHT
sensor
#define DHTTYPE DHT11	// DHT 11

const int flamepin = 15;	// Digital pin connected to flame sensor
const int redled = 5;	// Digital pin connected to RED LED
const int greenled = 18;	// Digital pin connected to GREEN LED
const int buzzerpin = 23;	// Digital pin connected to BUZZER
int smokeA0 = 34;	// Analog pin connected to smoke sensor
int flame = HIGH;	// presence of flame
int sensorThres = 1000;	// Threshold for smoke detection
int x = 0; int y = 0;

const char* ssid = "caution 101";	//wifi name
const char* password = "caution101";	//wifi password
const char* serverName = "http://api.thingspeak.com/update";	//server name
String apiKey = "W4QCLASE7LIN3ALQ";	//apikey for thingspeak
String phoneNumber = "+8801788240334";	//doctor's number
String apiKey1 = "3702186";	//apikey for whatsapp
DHT dht(DHTPIN, DHTTYPE);	//DHT11 initialization

void setup() {
// LCD setup lcd.init(); lcd.backlight();
// Pin setup pinMode(redled, OUTPUT); pinMode(greenled, OUTPUT); pinMode(buzzerpin, OUTPUT); pinMode(flamepin, INPUT); pinMode(smokeA0, INPUT);

Serial.begin(9600);
// DHT11 setup dht.begin();
// wifi setup WiFi.begin(ssid, password); Serial.println("Connecting");
// wait until get connected while(WiFi.status() != WL_CONNECTED) {
delay(500); Serial.print(".");
}
Serial.println("");
Serial.print("Connected to WiFi network with IP Address: "); Serial.println(WiFi.localIP());
}

// function for sending SOS to whatsapp void sendMessage(String message){
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
void loop() { delay(5000); lcd.clear();
// data reading from DHT11 float h = dht.readHumidity();
float t = dht.readTemperature();
// If DHT11 doesnot work if (isnan(h) || isnan(t)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;
}
// data reading from fire sensor flame = digitalRead(flamepin);
// alarm system for fire if (flame == LOW) {
digitalWrite(redled, HIGH); digitalWrite(greenled, LOW); digitalWrite(buzzerpin, HIGH); lcd.clear();
lcd.setCursor(5, 0); lcd.print("FIRE!"); delay(2000);
x = 15;
}
else {
digitalWrite(redled, LOW); digitalWrite(greenled, HIGH); digitalWrite(buzzerpin, LOW); lcd.clear();
lcd.setCursor(4, 0); lcd.print("NO FIRE"); delay(2000);
x = 5;
}
// data reading from smoke sensor
int analogSensor = analogRead(smokeA0);
// alarm system for smoke
if (analogSensor > sensorThres) { digitalWrite(redled, HIGH); digitalWrite(greenled, LOW); digitalWrite(buzzerpin, HIGH); lcd.setCursor(5, 0); lcd.print("SMOKE");
y = 15;
} else { digitalWrite(redled, LOW);
digitalWrite(greenled, HIGH); digitalWrite(buzzerpin, LOW); lcd.setCursor(4, 0); lcd.print("NO SMOKE");
y = 5;
}
Serial.println("::Humidity::"); Serial.println(h); Serial.println("::Temperature::"); Serial.println(t);
delay(2000); lcd.clear(); lcd.setCursor(2, 0);
lcd.print("::Humidity::"); lcd.setCursor(5, 1); lcd.print(h); lcd.print("%"); delay(2000);
lcd.clear(); lcd.setCursor(1, 0);
lcd.print("::Temperature::"); lcd.setCursor(5, 1); lcd.print(t); lcd.print(F("C")); delay(2000);
lcd.clear(); lcd.setCursor(3, 0); lcd.print("::EEE-416::"); lcd.setCursor(1, 1); lcd.print("Measuring.	");
// Sending data to IOT dashboard if(WiFi.status()== WL_CONNECTED){
WiFiClient client; HTTPClient http;
http.begin(client, serverName);
http.addHeader("Content-Type", "application/x-www-form-urlencoded");
// field1 = room temperature, field2 = humidity, field3 = fire, field4 = smoke
String httpRequestData1 = "api_key=" + apiKey + "&field1=" + String(t) +"&field2=" + String(h) +"&field3=" + String(x) + "&field4=" + String(y);
int httpResponseCode1 = http.POST(httpRequestData1); Serial.print("HTTP Response code1: "); Serial.println(httpResponseCode1);
http.end();
}
else {
Serial.println("WiFi Disconnected");
}
// messages for different critical situations if(t>45){
 
	sendMessage("EMERGENCY!!!! Room temperature is HIGH.");
}
if(t<20){
sendMessage("EMERGENCY!!!! Room temperature is LOW.");
}
if(h>60){
sendMessage("EMERGENCY!!!! Humidity is HIGH.");
}
if(h<20){
sendMessage("EMERGENCY!!!! Humidity is LOW.");
}
if(x == 15){
sendMessage("EMERGENCY!!!! FIRE! FIRE! FIRE!.");
}
if(y == 15){
sendMessage("EMERGENCY!!!! SMOKE! SMOKE! SMOKE!.");
}
}	