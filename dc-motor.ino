#include<Stepper.h>
int stepsPerRevolution=2048;
int motspeed=15;
int dt=500;
Stepper myStepper(stepsPerRevolution, 8,10,9,11);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(motspeed);
}
void loop() {
  myStepper.step(stepsPerRevolution);
  delay(dt);
  myStepper.step(-stepsPerRevolution);
  delay(dt);
}
