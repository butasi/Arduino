/*https://create.arduino.cc/editor/D-Castillo/70cb86af-8cc0-4147-afb2-cb5959584a6b/preview

*/
#include<Wire.h>
#include <AFMotor.h>
#include <IRremote.h>
#include<Servo.h>
AF_DCMotor motor(1);
AF_DCMotor motor1(4);

#define Button0 0xFF9867
#define Button1 0xFFA25D
#define Button2 0xFF9867
#define Button3 0xFFB04F
#define Button4 0xFF30CF
#define Button7 0xFF10EF
#define Button8 0xFF38C7
#define Button9 0xFF5AA5
#define Buttonhash 0xFF52AD
#define Forward 0xFF18E7
#define Backward 0xFF4AB5
#define left 0xFF10EF
#define right 0xFF5AA5



//*int = entero "cifra o nº entero"
int SensorIR = 23;                      //sentencia int: declaramos/nombramos el pin 11 como "SensorIR"
int Relay = 5;
Servo myservo;

IRrecv irrecv(SensorIR);                //Asociamos el receptor o SensorIR

decode_results results ;                 //Declaramos/nombramos los resultados (de los resultss emitidos)

uint32_t delayMS;




void setup()
{
  motor.setSpeed(200);
  motor.run(RELEASE);
  motor1.setSpeed(200);
  motor1.run(RELEASE);

  Serial.begin(9600);                   //Activamos el "monitor serie"
  // En caso de que el controlador de interrupción se bloquee en la configuración, dará una pista
  // al usuario de lo que esta sucediendo.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn();                  //Se inicia/activa el receptor
  Serial.println("Enabled IRin");

  myservo.attach(10);
  pinMode (Relay, OUTPUT) ;               //Declaramos el pin 8 o "Relay" como salida
}
int i;
void loop() {
  // Delay between measurements


  if (irrecv.decode(&results)) {          //Decodifica o "lee" el results emitido por el mando/control remoto
    Serial.println(results.value, HEX);   //Imprime el results en valor hexadecimal y lo muestra en el "monitor serie"

    if (results.value == Button0) {        //Orden condicional: si el results recibido corresponde al Button 1
      myservo.write(0);
      motor.setSpeed(0);
      motor1.setSpeed(0);
      motor.run(RELEASE);
      motor1.run(RELEASE);
      delay(3);
    }

    if (results.value == Button1) {        //Orden condicional: si el results recibido corresponde al Button 2
      myservo.write(180);
      delay(600);
    }

    if (results.value == Forward) {        //Orden condicional: si el results recibido corresponde al Button 2
      motor.run(FORWARD);
      for (i = 0; i < 255; i++) {
        motor.setSpeed(i);

      }
    }

    if (results.value == Backward) {        //Orden condicional: si el results recibido corresponde al Button 2
      motor.run(BACKWARD);
      for (i = 0; i < 255; i++) {
        motor.setSpeed(i);
      }
    }


    if (results.value == left) {        //Orden condicional: si el results recibido corresponde al Button 2
      motor1.run(FORWARD);
      motor1.setSpeed(100);
        motor1.run(RELEASE);
      myservo.write(90);

    }

    if (results.value == right) {        //Orden condicional: si el results recibido corresponde al Button 2
      motor1.run(BACKWARD);
      motor1.setSpeed(100);
        motor1.run(RELEASE);
      myservo.write(180);
    }

    if (results.value == Button2) {        //Orden condicional: si el results recibido corresponde al Button 2
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
    }

    if (results.value == Button3) {        //Orden condicional: si el results recibido corresponde al Button 2
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
      delay(3600);
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
    }

    if (results.value == Button4) {        //Orden condicional: si el results recibido corresponde al Button 2
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
      delay(3600);
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
      delay(3600);
      digitalWrite(Relay, HIGH) ;        //Acción: entonces el Relay se activa (en este caso se apaga el punto de luz)
      delay(3600);
      digitalWrite(Relay, LOW) ;
    }

    if (results.value == Buttonhash) {        //Orden condicional: si el results recibido corresponde al Button 1
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);          //Acción: entonces el Relay se desactiva (en este caso se enciende el punto de luz)
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
      digitalWrite(Relay, LOW);
      delay(600);
      digitalWrite(Relay, HIGH);
      delay(600);
    }


    if (results.value == Button0)  // change according to your IR remote button number
    {
      myservo.write(0);
      delay(15);
    }
    if (results.value == Button8)  // change according to your IR remote button number
    {
      myservo.write(30);
      delay(15);
    }

    if (results.value == Button7)  // change according to your IR remote button number
    {
      myservo.write(60);
      delay(15);
    }
    if (results.value == Button1)  // change according to your IR remote button number
    {
      myservo.write(180);
      delay(15);
    }

    irrecv.resume();                     // Recibe el siguiente valor
  }
  delay(100);
}
