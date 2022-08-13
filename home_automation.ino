/*
  Name:        lightBot.ino
  Created:     26/03/2021
  Author:      Tolentino Cotesta <cotestatnt@yahoo.com>
  Description: a simple example that do:
             1) parse incoming messages
             2) if "LIGHT ON" message is received, turn on the onboard LED
             3) if "LIGHT OFF" message is received, turn off the onboard LED
             4) otherwise, reply to sender with a welcome message

*/


/*
  Set true if you want use external library for SSL connection instead ESP32@WiFiClientSecure
  For example https://github.com/OPEnSLab-OSU/SSLClient/ is very efficient BearSSL library.
  You can use AsyncTelegram2 even with other MCUs or transport layer (ex. Ethernet)
  With SSLClient, be sure "certificates.h" file is present in sketch folder
*/
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <UniversalTelegramBot.h>
#include <DHT.h>
#include <DHT_U.h>
//LED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define MP_ESP32_I2C_SDA 4
#define MP_ESP32_I2C_SCL 5

#define USE_CLIENTSSL false

#include <AsyncTelegram2.h>
// Timezone definition
#include <time.h>
#define MYTZ "CET-1CEST,M3.5.0,M10.5.0/3"

#ifdef ESP8266
#include <ESP8266WiFi.h>
BearSSL::WiFiClientSecure client;
BearSSL::Session   session;
BearSSL::X509List  certificate(telegram_cert);

#elif defined(ESP32)
#include <WiFi.h>
#include <WiFiClient.h>
#if USE_CLIENTSSL
#include <SSLClient.h>
#include "tg_certificate.h"
WiFiClient base_client;
SSLClient client(base_client, TAs, (size_t)TAs_NUM, A0, 1, SSLClient::SSL_ERROR);
#else
#include <WiFiClientSecure.h>
WiFiClientSecure client;
#endif
#endif

#define DHTTYPE    DHT11     // DHT 11

#define DHTPIN 21     // Digital pin connected to the DHT sensor 

DHT dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

AsyncTelegram2 myBot(client);
const char* ssid  =  "xxxxxxxx";     // SSID WiFi network
const char* pass  =  "xxxxxxx";     // Password  WiFi network
#define CHAT_ID "xxxxxx"
const char* token =  "5xxxxxxxxkcfY";  // Telegram token
const unsigned long BOT_MTBS = 600; // mean time between scan messages
unsigned long bot_lasttime; // last time messages' scan has been done
UniversalTelegramBot bot(token, client);
float temperatureC;
float temperatureF;
float humidity;

int red = 23;
int green = 19;
int blue = 22;

const uint8_t LED = 27;
const uint8_t LED2 = 26;
const uint8_t RELAY = 12;
const uint8_t LEDBOARD = LED_BUILTIN;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Wire.begin(MP_ESP32_I2C_SDA, MP_ESP32_I2C_SCL);
  Serial.println("\nStarting TelegramBot...");
  Serial.println(F("DHTxx test!"));

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println("<LIGHT STATE DISPLAY>");
  display.display();

  // set the pin connected to the LED to act as output pin
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(RELAY, OUTPUT);
  digitalWrite(LED, LOW); // turn off the led (inverted logic!)
  digitalWrite(LED2, LOW); // turn off the led (inverted logic!)
  digitalWrite(RELAY, LOW); // turn off the led (inverted logic!)
  pinMode(LEDBOARD, OUTPUT);
  digitalWrite(LEDBOARD, HIGH);
  // initialize the digital pin as an output.
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  digitalWrite(red, LOW);
  digitalWrite(green, LOW);
  digitalWrite(blue, LOW);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  delay(500);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }

#ifdef ESP8266
  // Sync time with NTP, to check properly Telegram certificate
  configTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
  //Set certficate, session and some other base client properies
  client.setSession(&session);
  client.setTrustAnchors(&certificate);
  client.setBufferSizes(1024, 1024);
#elif defined(ESP32)
  // Sync time with NTP
  configTzTime(MYTZ, "time.google.com", "time.windows.com", "pool.ntp.org");
#if USE_CLIENTSSL == false
  client.setCACert(telegram_cert);
#endif
#endif

  // Set the Telegram bot properies
  myBot.setUpdateTime(600);
  myBot.setTelegramToken(token);

  // Check if all things are ok
  Serial.print("\nTest Telegram connection... ");
  myBot.begin() ? Serial.println("OK") : Serial.println("NOK");

  Serial.print("Bot name: @");
  Serial.println(myBot.getBotName());
}

void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);
  for (int i = 0; i < numNewMessages; i++)
  {
    String chat_id = String(bot.messages[i].chat_id);
    if (chat_id != CHAT_ID )
    {
      bot.sendMessage(chat_id, "Unauthorized user", "");
    }
    else
    {
      String text = bot.messages[i].text;
      String from_name = bot.messages[i].from_name;
      if (from_name == "")
        from_name = "Guest";
      if (text == "/temperature")
      { String msg = "Temperature is ";
        msg += msg.concat(temperatureC);
        msg += "C";
        bot.sendMessage(chat_id, msg, "");
      }

      if (text == "/light_on")
      { String msg = "All lights are now on";
        digitalWrite(LED, HIGH);                          // turn off the led (inverted logic!)
        digitalWrite(LED2, HIGH);
        digitalWrite(RELAY, HIGH);
        digitalWrite(LEDBOARD, LOW);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        // Display static text
        display.println("LIGHTS >>> State on!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }


      if (text == "/light_off")
      { String msg = "All lights are now off";
        digitalWrite(LED, LOW);                          // turn off the led (inverted logic!)
        digitalWrite(LED2, LOW);
        digitalWrite(RELAY, LOW);
        digitalWrite(LEDBOARD, HIGH);
        digitalWrite(red, LOW);
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        // Display static text
        display.println("LIGHTS >>> State off!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }

      if (text == "/party")
      { String msg = "Party Mode Activated";
        digitalWrite(LED, LOW);                          // turn off the led (inverted logic!)
        digitalWrite(LED2, LOW);
        digitalWrite(RELAY, LOW);
        digitalWrite(LEDBOARD, LOW);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(red, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(red, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(green, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(green, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        digitalWrite(blue, HIGH); // turn the LED on
        delay(600); // wait for a second
        digitalWrite(blue, LOW); // turn the LED off by making the voltage LOW
        delay(600); // wait for a second
        // Display static text
        display.println("LIGHTS >>> Party!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }

      if (text == "/light_one_on")
      { String msg = "Light one is now on";
        digitalWrite(LED, HIGH);                          // turn off the led (inverted logic!)
        digitalWrite(LEDBOARD, LOW);
        display.clearDisplay();
        display.setTextSize(1);
        display.setTextColor(WHITE);
        display.setCursor(0, 10);
        // Display static text
        display.println("LIGHT 1 >>> State on!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }
      if (text == "/light_one_off")
      { String msg = "Light 1 is now off";
        digitalWrite(LED, LOW);                          // turn off the led (inverted logic!)
        digitalWrite(LEDBOARD, HIGH);
        display.println("LIGHT 1 >>> State Off!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }

      if (text == "/light_two_on")
      { String msg = "All lights are now on";
        digitalWrite(LED2, HIGH);
        digitalWrite(LEDBOARD, LOW);
        display.println("LIGHTS >>> State on!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }
      if (text == "/light_two_off")
      { String msg = "Light 2 is off";
        // turn off the led (inverted logic!)
        digitalWrite(LED2, LOW);
        digitalWrite(RELAY, LOW);
        digitalWrite(LEDBOARD, HIGH);
        display.println("LIGHT 2 >>> State Off!");
        display.display();
        bot.sendMessage(chat_id, msg, "");
      }


      if (text == "/humidity")
      {
        String msg = "Humidity is ";
        msg += msg.concat(humidity);
        msg += "%";
        bot.sendMessage(chat_id, msg, "");
      }

    }
  }
}


void loop() {
  // local variable to store telegram message data
  TBMessage msg;
  humidity = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temperatureC = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  temperatureF = dht.readTemperature(true);

  if (millis() - bot_lasttime > BOT_MTBS)
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages)
    {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    bot_lasttime = millis();
  }
}
