#include "map.h"

// Logging levels
#define LOG_LOW 0
#define LOG_MID 1
#define LOG_HIGH 2
#define LOG_ERROR 3
#define LOG_CRITICAL_ERROR 4

// Logging system
int log_level;
bool log_initialised = false;
String log_levels[5] = {"[ LOG LOW ] : ", "[ LOG MID ] : ", "[ LOG HIGH ] : ", "[ ERROR ] : ", "[ CRITICAL ERROR ] : "};

void log_init(int level) {
    log_level = level;
    Serial.begin(9600);
    log_initialised = true;
    Serial.println(log_levels[level] + "Logging initialised");
}

void log(String msg, int level) {
    if (!log_initialised) {
        Serial.println("[ ERROR ] : Logging system not initialised");
    }
    else {
        if (level >= log_level) {
            Serial.println(log_levels[level] + msg);
        }
    }
}

// the setup function runs once when you press reset or power the board
void setup() {
  log_init(LOG_MID);
  log("Low level message", LOG_LOW);
  log("Mid level message", LOG_MID);
  log("High level message", LOG_HIGH);
}

// the loop function runs over and over again forever
void loop() {
}
