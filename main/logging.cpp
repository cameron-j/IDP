#include "logging.h"

// Logging system
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