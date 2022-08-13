#include <OzIDManager.h>
#include <OzDHTSensor.h>
 
// global pointers
OzIDManager* manager;
OzDHTSensor* dhtTemperature;
OzDHTSensor* dhtHumidity;
 
void setup()
{
  Serial.begin(115200);
 
  // instantiate objects
  manager = new OzIDManager;
  manager->_sendACK = true;
  manager->_checksum = true;
 
  OzCommunication::setIDManager(manager);
  
  //DHT11 sensor connected to D2 pin
  dhtTemperature = new OzDHTSensor(DHT11,DHTMode::Temperature,2);
  dhtHumidity = new OzDHTSensor(DHT11,DHTMode::Humidity,2);
  //Set it to DHT22 if using DHT22
 
  // welcome devices
  int x = 1;
  manager->sendLinkSetup();
  manager->PrintWelcomeLine(dhtTemperature, x++, "TemperatureSensor_1");
  manager->PrintWelcomeLine(dhtHumidity, x++, "HumiditySensor_1");
}
 
void loop()
{
  dhtTemperature->ownLoop();
  dhtHumidity->ownLoop();
  OzCommunication::communicate();
}
/if u use mq7 sensor/
#include <dht11.h>
#include <MQ7.h>
#define DHT11PIN A0
dht11 DHT11;
int mqx_analogPin = A1; // connected to the output pin of MQ-X

void setup() {
  Serial.begin(9600);
}

void loop() {
  //dht
Serial.println();
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);
  Serial.print("Temperature (C): ");
  Serial.println((float)DHT11.temperature, 2);
  //mq7
  int mqx_value = analogRead(mqx_analogPin);
  Serial.println(mqx_value);
  //ldr
  unsigned int AnalogValue;
  AnalogValue = analogRead(A2);
  Serial.println(AnalogValue);
  
  delay(5000);
}
