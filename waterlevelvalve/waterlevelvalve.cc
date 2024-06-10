#define WATER_SENSOR A0
#define RELAY_PIN D4

int liquid_level;

void countdown_break(int seconds);
void level_break();

void setup() {
    Serial.begin(115200);
    pinMode(WATER_SENSOR, INPUT);
    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, HIGH);

    // Additional use:
    // countdown_break(300);
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

    if (liquid_level >= 700)
        Serial.println("Closing valves via relay.");
        digitalWrite(RELAY_PIN, LOW);
    } else {
        Serial.println("Opening valves via relay.");
        digitalWrite(RELAY_PIN, HIGH);
    }
}
