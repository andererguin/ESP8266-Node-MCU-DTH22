/***************************************************************************
2018-2019 STEAM kurtsorako proposatzen den ariketa.
Ariketa honen helburua ikasleek IOT-arekin, sentsoreekin, 3D Inprimagailuekin,
IKTekin, ... egin daitezkeen gauzen lehen esperientzia izatea da.
 ***************************************************************************/

#include <ArduinoJson.h>
#include "FirebaseESP8266.h" // Datubasea erabiltzeko liburutegiak
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <time.h>


#define FIREBASE_HOST "steam-000000.firebaseio.com" // steam-000000.firebaseio.com NIRE FIREBASE HOST
#define FIREBASE_AUTH "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" //NIRE FIREBASE AUTH
#define WIFI_SSID "NIRE WIFI"
#define WIFI_PASSWORD "NIRE PASSWORD"
#define DHTPIN 2     // DTH 22 sentsorea konektatua dagoen PIN DIGITALA: GPI02 
#define DHTTYPE DHT22   // DHT 22  (AM2302) sentsorea

DHT dht(DHTPIN, DHTTYPE); // Sentsorea definitu

FirebaseData firebaseData; // FirebaseESP8266 (Datubasea) data object Definizioa

WiFiClientSecure client; // WiFi Bezeroa

// Denbora Internet bidez jasotzeko Parametroak
int timezone = 2;
int dst = 0;
char buffer[80];

//Firebase Datubasera bidaltzeko SQL Query-a
String jsonStr;

//Gure gailuare GPS Datuak/Posizioa
String Latitudea = "43.2921336"; // NIRE GAILUAREN POSIZIOA Latitudea
String Longitudea = "-1.8989592"; // NIRE GAILUAREN POSIZIOA Longitudea

//Gure gauluaren izena
String Izena = "Steam-ZENBAKIA"; // "ZENBAKIA" ordezkatu nire eslaitu zaidan zenbakiarekin


void setup() {
  Serial.begin(115200);


// WIFI KONEXIOA EGIN
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  //Denbora zerbitzariarekin bat egin
  configTime(timezone * 3600, 1, "pool.ntp.org", "time.nist.gov");

  dht.begin(); // DTH sentsorea martxan jarri
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // Firebase Datubasearen konektatu
  Firebase.reconnectWiFi(true);


  Serial.println("-----------------------------------");
  Serial.println("----------Abian da Proba-----------");
  Serial.println("-----------------------------------");
  Serial.println();

  
}

void loop() {

    float h = dht.readHumidity();  // Hezetasuna irakurri sentsoretik
    float t = dht.readTemperature();  // Tenperatura irakurri sentsoretik

    Serial.println("Hezetasuna:" + String(h));
    Serial.println("Tenperatura:" + String(t));
    

    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime (buffer,80,"%d %B %Y %H:%M:%S",timeinfo); // Data formatu adibidea 09 May 2019 21:59:51
    Serial.println(buffer);

    
    float co2 = 0;
    float ctv = 0;
    String jsonStr = "";
    jsonStr = "{\"Humidity\":" + String(h) + ",\"Temperature\":" + String(t)+ ",\"Co2\":" + co2 + ",\"Tvoc\":" + ctv + ",\"Izena\":\"" + Izena + "\",\"Latitudea\":" + String(Latitudea) + ",\"Longitudea\":" + String(Longitudea) + ",\"Timestamp\":\"" + buffer + "\"}";
    if (Firebase.pushJSON(firebaseData, "/Datuak", jsonStr))
    {
      Serial.println("PASSED");
      Serial.println("PATH: " + firebaseData.dataPath());
      Serial.print("PUSH NAME: ");
      Serial.println(firebaseData.pushName());
      Serial.println("------------------------------------");
      Serial.println();
    }
    else
    {
      Serial.println("FAILED");
      Serial.println("REASON: " + firebaseData.errorReason());
      Serial.println("------------------------------------");
      Serial.println();
    }
    
    delay(60000);

    
}
