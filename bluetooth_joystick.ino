#include <BleCombo.h>



int horzPin = 32; // Analog output of horizontal joystick pin

int vertPin = 33;

int lastDebounceTime=0;



signed char limit_xy(int const xy)

{

if (xy < -127) return -127;

else if(xy > 127) return 127;

else return xy;

}



int vertZero, horzZero; // Stores the initial value of each axis, usually around 512

int vertValue, horzValue; // Stores current analog output of each axis

const int sensitivity = 200; // Higher sensitivity value = slower mouse, should be <= about 500

void setup()

{

Keyboard.begin();

Mouse.begin();

Serial.begin(9600);

pinMode(horzPin, INPUT); // Set both analog pins as inputs

pinMode(vertPin, INPUT);

delay(1000); // short delay to let outputs settle

vertZero = analogRead(vertPin); // get the initial values

horzZero = analogRead(horzPin); // Joystick should be in neutral position when reading these

}



void loop()

{

if(Keyboard.isConnected()){

if ((millis() - lastDebounceTime) > 20) {

lastDebounceTime = millis();

vertValue = analogRead(vertPin)- vertZero ;

horzValue = analogRead(horzPin)- horzZero ;

if (vertValue != 0)

Mouse.move(0, limit_xy(vertValue/sensitivity));

if (horzValue != 0)

Mouse.move(limit_xy((horzValue/sensitivity)*-1), 0); //<<<<<<<

}

}

}
