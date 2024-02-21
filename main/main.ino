#include "map.h"
#include "motor_control.h"

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

// Button input
int buttonPin = 5;
int button_status;
int prev_button_status = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  log_init(LOG_MID);
  mot_init();
}

// the loop function runs over and over again forever
void loop() {
  button_status = digitalRead(buttonPin);
  if (button_status == 1 && prev_button_status == 0) {
    mot_straight(LOWSPEED);
    log("Low speed", LOG_HIGH);
    delay(2000);
    mot_correct_to_right(50);
    log("Correct right", LOG_HIGH);
    delay(1000);
    mot_correct_to_left(100);
    log("Correct left", LOG_HIGH);
    delay(1000);
    mot_correct_to_right(50);
    log("Correct right", LOG_HIGH);
    delay(1000);
    mot_stop();
  }
  prev_button_status = button_status;
}
