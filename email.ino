/*************************************************************

  Simple e-mail example

  App project setup:
    E-mail Widget

  Connect a button to digital pin 2 and GND
  Pressing this button will send an e-mail

  WARNING: You are limited to send ONLY ONE E-MAIL PER 5 SECONDS!
 *************************************************************/

// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLcEBiD1zx"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "awKaoZEfbLYVd6wfIKq_eVwb6vWijQ5H"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
/* Set this to a bigger number, to enable sending longer messages */
//#define BLYNK_MAX_SENDBYTES 128

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Vladimir Routin";
char pass[] = "60366411";

unsigned count = 0;

void emailOnButtonPress()
{
  // *** WARNING: You are limited to send ONLY ONE E-MAIL PER 5 SECONDS! ***

  // Let's send an e-mail when you press the button
  // connected to digital pin 2 on your Arduino

  int isButtonPressed = !digitalRead(2); // Invert state, since button is "Active LOW"

  if (isButtonPressed) // You can write any condition to trigger e-mail sending
  {
    Serial.println("Button is pressed."); // This can be seen in the Serial Monitor

    count++;

    String body = String("You pushed the button ") + count + " times.";

    Blynk.email("your_email@mail.com", "Subject: Button Logger", body);

    // Or, if you want to use the email specified in the App (like for App Export):
    //Blynk.email("Subject: Button Logger", "You just pushed the button...");
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Send e-mail when your hardware gets connected to Blynk Server
  // Just put the recepient's "e-mail address", "Subject" and the "message body"
  Blynk.email("your_email@mail.com", "Subject", "My Blynk project is online.");

  // Setting the button
  pinMode(2, INPUT_PULLUP);
  // Attach pin 2 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(2), emailOnButtonPress, CHANGE);
}

void loop()
{
  Blynk.run();
}
