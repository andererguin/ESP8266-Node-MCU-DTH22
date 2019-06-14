/***************************************************************************
2018-2019 STEAM kurtsorako proposatzen den ariketa.
Ariketa honen helburua ikasleek IOT-arekin, sentsoreekin, 3D Inprimagailuekin,
IKTekin, ... egin daitezkeen gauzen lehen esperientzia izatea da.
 ***************************************************************************/
#include <DHT.h>


#define DHTPIN 2     // DTH 22 sentsorea konektatua dagoen PIN DIGITALA: GPI02 
#define DHTTYPE DHT22   // DHT 22  (AM2302) sentsorea

DHT dht(DHTPIN, DHTTYPE); // Sentsorea definitu

void setup() {
  Serial.begin(115200);


  dht.begin(); // DTH sentsorea martxan jarri
  
  Serial.println("-----------------------------------");
  Serial.println("----------Abian da Proba-----------");
  Serial.println("-----------------------------------");
  Serial.println();

  
}

void loop() { // Behin eta berriz errepikatu

    float h = dht.readHumidity();  // Hezetasuna irakurri sentsoretik
    float t = dht.readTemperature();  // Tenperatura irakurri sentsoretik

    Serial.println("Hezetasuna:" + String(h)); // Monitor Serie-an Hezetasuna pantailaratu
    Serial.println("Tenperatura:" + String(t)); // Monitor Serie-an Tenperatura pantailaratu
    

    delay(5000); // 5 Segundu itxaron

    
}
