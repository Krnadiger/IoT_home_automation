                                            
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#define relay1 D0
#define relay2 D1
#define relay3 D2
#define relay4 D3
#define relay5 D4
/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "kkk"
#define WLAN_PASS       "kkk123**"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "krishna_nadiger"
#define AIO_KEY         "c583ed91b5c44d31b10777289a87a84b"

/************ Global State (you don't need to change this!) ******************/

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
//Adafruit_MQTT_Publish photocell1 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
//Adafruit_MQTT_Publish photocell2 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/fan");
//Adafruit_MQTT_Publish photocell3 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/television");
//Adafruit_MQTT_Publish photocell4 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/water_pump");
//Adafruit_MQTT_Publish photocell5 = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/master_key");
// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton1 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/light");
Adafruit_MQTT_Subscribe onoffbutton2 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/fan");
Adafruit_MQTT_Subscribe onoffbutton3 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/television");
Adafruit_MQTT_Subscribe onoffbutton4 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/water_pump");
Adafruit_MQTT_Subscribe onoffbutton5 = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/master_key");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  pinMode(relay5,OUTPUT);

  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton1);
  mqtt.subscribe(&onoffbutton2);
  mqtt.subscribe(&onoffbutton3);
  mqtt.subscribe(&onoffbutton4);
  mqtt.subscribe(&onoffbutton5);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton1) {

        Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton1.lastread);
      uint16_t state1 = atoi((char *)onoffbutton1.lastread);
      digitalWrite(relay1,!state1);
    }
    if (subscription == &onoffbutton2) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton2.lastread);
      uint16_t state2 = atoi((char *)onoffbutton2.lastread);
      digitalWrite(relay2,!state2);
    }
   if (subscription == &onoffbutton3) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton3.lastread);
      uint16_t state3 = atoi((char *)onoffbutton3.lastread);
      digitalWrite(relay3,!state3);
    }
   if (subscription == &onoffbutton4) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton4.lastread);
      uint16_t state4 = atoi((char *)onoffbutton4.lastread);
      digitalWrite(relay4,!state4);
    }
   if (subscription == &onoffbutton5) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton5.lastread);
      uint16_t state5 = atoi((char *)onoffbutton5.lastread);
      digitalWrite(relay5,state5);

    }
    
  }

 // Now we can publish stuff!
 /* Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! photocell1.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

    Serial.print(x);
  Serial.print("...");
  if (! photocell2.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

    Serial.print(x);
  Serial.print("...");
  if (! photocell3.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

    Serial.print(x);
  Serial.print("...");
  if (! photocell4.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

    Serial.print(x);
  Serial.print("...");
  if (! photocell5.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }

*/
  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
