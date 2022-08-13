#include <IRremote.h>

const int RECV_PIN = 7; //connect receiver pin
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup(){
  Serial.begin(9600); //start serial
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop(){
  if (irrecv.decode(&results)){
        Serial.println(results.value, HEX);//print pressed button on serial monitor
        irrecv.resume();
  }
}
