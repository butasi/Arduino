
#include <AFMotor.h>

AF_DCMotor motor(4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("BUTASI IS HERE!");

  motor.setSpeed(200);
  motor.run(RELEASE);
}
int i;

void loop() {
  // put your main code here, to run repeatedly:
  motor.run(FORWARD);
  for (i = 0; i < 255; i++) {
    motor.setSpeed(i);
    delay(30);
  }

  for (i = 255; i != 0; i--) {
    motor.setSpeed(i);
    delay(3);
  }

   motor.run(BACKWARD);
  for (i = 0; i < 255; i++) {
    motor.setSpeed(i);
    delay(300);
  }
  
  for (i = 255; i != 0; i--) {
    motor.setSpeed(i);
    delay(3);
  }

}
