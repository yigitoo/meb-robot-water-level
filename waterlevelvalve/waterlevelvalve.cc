#define WATER_SENSOR A0
#define RELAY_PIN D4

/*
// If you have WiFi Module.
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

*/

int liquid_level;

void countdown_break(int seconds);
void level_break();
void make_request();

void setup() {
    Serial.begin(115200);
    pinMode(WATER_SENSOR, INPUT);
    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, HIGH);

    // Additional use:
    // countdown_break(300);

/*
    // If you have WiFi Module.

    WiFi.begin(ssid, password);
    Serial.println("Connecting");
    while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    }

    if(WiFi.status() == WL_CONNECTED) {
    cardDataServer = getCardDataServer();
    } else {
    for(;;){Serial.println("Cannot fetch the CardDataServer");}
    }

*/

}

void loop() {
    delay(500);
    level_break();
}


void countdown_break(int seconds) {
    delay(seconds * 1000);
    digitalWrite(RELAY_PIN, LOW);
}

void level_break() {
    liquid_level = analogRead(WATER_SENSOR);

    Serial.println("Level of liquid: " + (String)liquid_level);

    if (liquid_level >= 700) {
        Serial.println("Closing valves via relay.");
        digitalWrite(RELAY_PIN, LOW);
        make_request(false);
    } else {
        Serial.println("Opening valves via relay.");
        digitalWrite(RELAY_PIN, HIGH);
        make_request(true);
    }
}

void make_request(bool is_open) {
    WiFiClient client;
    HTTPClient http;
    String state;

    if (is_open == true) {
        state = "open";
    } else {
        state = "close";
    }

    // Your Domain name with URL path or IP address with path
    http.begin(client, "http://localhost:8080/data");

    // Specify content-type header
    http.addHeader("Content-Type", "application/json");

    String httpRequestData = "{\"level\":"+ String(liquid_level) + ",\"state\": \"" + state + "\"}";
    int httpResponseCode = http.POST(httpRequestData);

    http.end();
}
