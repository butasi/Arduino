// Pin configuration
const int gunPins[] = {0, 1, 2, 3}; // Connect LEDs for spaceship guns to pins 0-3
const int relayPin = 4; // Connect the relay to pin 4

void setup() {
  for (int i = 0; i < sizeof(gunPins) / sizeof(gunPins[0]); i++) {
    pinMode(gunPins[i], OUTPUT);
  }
  
  pinMode(relayPin, OUTPUT);
  randomSeed(analogRead(0)); // Seed the random number generator
}

void loop() {
  // Simulate spaceship guns firing
  for (int i = 0; i < sizeof(gunPins) / sizeof(gunPins[0]); i++) {
    digitalWrite(gunPins[i], HIGH);
    delay(random(50, 200)); // Vary the firing time for each gun
    digitalWrite(gunPins[i], LOW);
  }

  // Simulate random explosions using the relay
  digitalWrite(relayPin, HIGH); // Turn on the relay for the explosion
  delay(random(300, 600)); // Vary the explosion duration
  digitalWrite(relayPin, LOW); // Turn off the relay
  
  delay(random(600, 2100)); // Wait before the next round of firing and explosions
}
