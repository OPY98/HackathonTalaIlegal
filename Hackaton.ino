#include <NMEAGPS.h>
#include <GPSport.h>
#include "DHT.h"
#define DHTPIN 2    
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

float h;
float t;
float f;
int valor;
int led = 13;
float temperatura;
float humedad;

NMEAGPS  gps; // This parses the GPS characters
gps_fix  fix; // This holds on to the latest values


void setup() {
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  dht.begin();
  DEBUG_PORT.begin(9600);
  while (!Serial);
  DEBUG_PORT.print( F("NMEAsimple.INO: started\n") );
  gpsPort.begin(9600);
}

void loop() {     
  while (gps.available( gpsPort )) {
    fix = gps.read();
  }
   ldr();
   sensorHT();

  if(valor < 400 && temperatura >= 25 && humedad < 40){
    Serial.println("alerta de incendio");
    digitalWrite(13,HIGH);
      DEBUG_PORT.print( F("Location: ") );
    if (fix.valid.location) {
      DEBUG_PORT.print( fix.latitude(), 6 );
      DEBUG_PORT.print( ',' );
      DEBUG_PORT.print( fix.longitude(), 6 );
    }

    DEBUG_PORT.print( F(", Altitude: ") );
    if (fix.valid.altitude)
      DEBUG_PORT.print( fix.altitude() );

    DEBUG_PORT.println();
  
    }   
  else {
    Serial.println("Todo tranquilo");
    digitalWrite(13,LOW);
    }
}

void sensorHT(){
    
  float h = dht.readHumidity();  
  float t = dht.readTemperature();  
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  float hif = dht.computeHeatIndex(f, h);
  
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.print(" *C ");
  Serial.print(hif);
  Serial.println(" *F");
  temperatura = t;
  humedad = h;
  }
  
  void ldr(){
     valor = analogRead(A0);    
    Serial.println(valor);
    delay(500);
    }
