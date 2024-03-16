#include "logging.h"

// Initialises serial communication for a given logging level - can be set to record only high priority, high and medium priority, or high, medium and low priority messages.
void log_init(int level) {
    log_level = level;
    Serial.begin(9600);
    log_initialised = true;
    Serial.println(log_levels[level] + "Logging initialised");
}

// Sends a given message to the serial port if the logging level input is >= the logging level input to log_init(int level).
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
