#include <Arduino.h>
#include <WiFi.h>         
#include <math.h>

#include <Firebase_ESP_Client.h>
#include <HTTPClient.h>

#define WIFI_SSID "MySSID"
#define WIFI_PASSWORD "MyPassword"

#define RADIUS_EARTH 6371000

#define API_KEY "AIzaSyAjFGKz7OhQBFSDtOye96V5Z5NZ7fA33rw"

#define DATABASE_URL "https://smarttraffic-57308-default-rtdb.firebaseio.com/"

#define JUNCTION_ID "j1"

#define RANGE 50

FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;
FirebaseJsonArray jsonArray;

HTTPClient HttpClient;

String Signal ="";
String SignalValue="";

int amb = 0;

double lat1, lon1, lat2, lon2;

double distance = 0.0;


unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;               

#define red_pin 13
#define yellow_pin 12
#define green_pin 14

double toRadians(double degrees) {
  return degrees * (PI / 180.0);
}

double stringToDouble(String str) {
  boolean isNegative = false;
  boolean isDecimal = false;
  int decimalPlace = 0;
  double result = 0.0;

  for (int i = 0; i < str.length(); i++) {
    char c = str.charAt(i);
    if (c == '-' && i == 0) {
      isNegative = true;
      continue;
    }
    if (c == '.') {
      isDecimal = true;
      continue;
    }
    int digit = c - '0';
    if (isDecimal) {
      result = result + (double)digit / pow(10, ++decimalPlace);
    } else {
      result = result * 10 + digit;
    }
  }

  if (isNegative) {
    result = -result;
  }

  return result;
}


double calculateDistance(double lat1, double lon1, double lat2, double lon2) {
  double dLat = toRadians(lat2 - lat1);
  double dLon = toRadians(lon2 - lon1);
  double a = sin(dLat/2) * sin(dLat/2) + cos(toRadians(lat1)) * cos(toRadians(lat2)) * sin(dLon/2) * sin(dLon/2);
  double c = 2 * atan2(sqrt(a), sqrt(1-a));
  double distance = RADIUS_EARTH * c;
  return distance;
}

void setup(){
  Serial.begin(115200);
  pinMode(red_pin, OUTPUT);
  pinMode(yellow_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  digitalWrite(red_pin, 1);
  digitalWrite(yellow_pin, 1);
  digitalWrite(green_pin, 1);
  delay(2000);
  
  digitalWrite(red_pin, 0);
  digitalWrite(yellow_pin, 0);
  digitalWrite(green_pin, 0);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }


  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){

  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 1000 || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();
    

if(Firebase.RTDB.getString(&fbdo,"/junction/j1/signalValue")){
  SignalValue = fbdo.stringData();
  Serial.println(SignalValue.toInt());
}


if(Firebase.RTDB.getString(&fbdo,"/users/user1/lattitude")){
  Signal = fbdo.stringData();
  lat1 = stringToDouble(Signal);
}

if(Firebase.RTDB.getString(&fbdo,"/users/user1/longitude")){
  Signal = fbdo.stringData();
  lon1 = stringToDouble(Signal);
}

if(Firebase.RTDB.getString(&fbdo,"/junction/j1/lat")){
  Signal = fbdo.stringData();
  lat2 = stringToDouble(Signal);
}

if(Firebase.RTDB.getString(&fbdo,"/junction/j1/lon")){
    Signal = fbdo.stringData();
  lon2 = stringToDouble(Signal);
}


distance = calculateDistance(lat1, lon1, lat2, lon2);

Serial.println("Location1: " + String(lat1, 7) + ", " + String(lon1, 7) );
Serial.println("Location2: " + String(lat2, 7) + ", " + String(lon2, 7));
Serial.println("Distance: " + String(distance, 6));
Serial.println();

if (distance < RANGE){
  if(!amb){
    amb = 1;
    digitalWrite(red_pin, 0);
    digitalWrite(yellow_pin, 1);
    delay(2000);
    digitalWrite(yellow_pin, 0);
  }
  digitalWrite(green_pin, 1);
   

}else{
  amb = 0;
  digitalWrite(green_pin, 0);
  digitalWrite(red_pin, 1);
}



  }
}
