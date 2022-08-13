#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

// Wifi network station credentials
#define WIFI_SSID "Vladimir Routin"
#define WIFI_PASSWORD "Rumple123"
// Telegram BOT Token (Get from Botfather)
#define BOT_TOKEN "5521386787:AAHzF_eTh1og0k1aC_qYXZnQD9HcKwskcfY"

const unsigned long BOT_MTBS = 1000; // mean time between scan messages

unsigned long bot_lasttime; // last time messages' scan has been done
WiFiClientSecure secured_client;
UniversalTelegramBot bot(BOT_TOKEN, secured_client);

void handleNewMessages(int numNewMessages)
{
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);

  String answer;
  for (int i = 0; i < numNewMessages; i++)
  {
    telegramMessage &msg = bot.messages[i];
    Serial.println("Received " + msg.text);
    if (msg.text == "/light_on")
      answer = "Light On";
    else if (msg.text == "/light_off")
      answer = "Light Off";
    else if (msg.text == "/start")
      answer = "Welcome my new friend! You are the first *" + msg.from_name + "* I've ever met";
    else if (msg.text == "/anime")
      answer = "Mood for Anime and Chill!";
    else if (msg.text == "/about_me")
      answer = "Upcoming Everything!";
    else if (msg.text == "/light_one_on")
      answer = "Light One Is ON!";
    else if (msg.text == "/light_one_off")
      answer = "Light One Is OFF!";

    else if (msg.text == "/temperature")
      answer = "TEMPERATURE!";
    else if (msg.text == "/humidity")
      answer = "HUMIDITY!";
    else if (msg.text == "/light_two_on")
      answer = "Light Two Is ON!";
    else if (msg.text == "/light_two_off")
      answer = "Light Two is Off!";
    else if (msg.text == "/desk_light")
      answer = "Attatched Light!";
    else if (msg.text == "/help")
      answer = "So you need _help_, uh? me too! use /start or /status!";
    else
      answer = "Say what?";

    bot.sendMessage(msg.chat_id, answer, "Markdown");
  }
}

void bot_setup()
{
  const String commands = F("["
                            "{\"command\":\"start\",  \"description\":\"Start the BOT\"},"
                            "{\"command\":\"light_on\",  \"description\":\"Turn All Lights ON\"},"
                            "{\"command\":\"light_one_on\",  \"description\":\"Turn Light 1 ON\"},"
                            "{\"command\":\"light_one_off\",  \"description\":\"Turn Light 1 OFF\"},"
                            "{\"command\":\"light_two_on\",  \"description\":\"Turn Light 2 ON\"},"
                            "{\"command\":\"light_two_off\",  \"description\":\"Turn Light 1 OFF\"},"
                            "{\"command\":\"temperature\",  \"description\":\"Temperature\"},"
                            "{\"command\":\"humidity\",  \"description\":\"Humidity\"},"
                            "{\"command\":\"anime\",  \"description\":\"Set MOOD \"},"
                            "{\"command\":\"desk_light\", \"description\":\"Turn Light Desk Light ON\"},"
                            "{\"command\":\"about_me\",  \"description\":\"About Bot\"},"
                            "{\"command\":\"light_off\",  \"description\":\"Turn All Lights OFF\"},"
                            "{\"command\":\"status\",\"description\":\"Answer device current status\"}" // no comma on last command
                            "]");
  bot.setMyCommands(commands);
  //bot.sendMessage("25235518", "Hola amigo!", "Markdown");
}

void setup()
{
  Serial.begin(115200);
  Serial.println();

  // attempt to connect to Wifi network:
  Serial.print("Connecting to Wifi SSID ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  secured_client.setCACert(TELEGRAM_CERTIFICATE_ROOT); // Add root certificate for api.telegram.org
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("\nWiFi connected. IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Retrieving time: ");
  configTime(0, 0, "pool.ntp.org"); // get UTC time via NTP
  time_t now = time(nullptr);
  while (now < 24 * 3600)
  {
    Serial.print(".");
    delay(100);
    now = time(nullptr);
  }
  Serial.println(now);

  bot_setup();
}

void loop()
{
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
