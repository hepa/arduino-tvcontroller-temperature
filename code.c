#include <DallasTemperature.h>
#include <OneWire.h>
#include <IRremote.h>

const int TEMPERATURE_PIN = 12;
const int INFRA_PIN = 11;

OneWire oneWire(TEMPERATURE_PIN);
IRrecv irrecv(INFRA_PIN);
DallasTemperature sensors(&oneWire);
decode_results results;

unsigned long sensorPreviousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long sensorInterval = 30000;           // interval at which to blink (milliseconds)


void setup() {
  Serial.begin(9600);  
  sensors.begin();
  irrecv.enableIRIn();    
}

void loop() { 
  unsigned long currentMillis = millis();

  // Temperature sensor
  if (currentMillis - sensorPreviousMillis >= sensorInterval) {    
    sensorPreviousMillis = currentMillis;
    sensors.requestTemperatures();
    Serial.print("TEMP:");
    Serial.println(sensors.getTempCByIndex(0));   
  }

  if (irrecv.decode(&results)) {
    Serial.print("INFRA:");
    Serial.println(results.value, DEC);
    irrecv.resume(); // Receive the next value
  }

  delay(90);
}
