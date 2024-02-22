#include "map.h"
#include "motor_control.h"
#include "line_following.h"
#include "logging.h"

// Logging levels
#define LOG_LOW 0
#define LOG_MID 1
#define LOG_HIGH 2
#define LOG_ERROR 3
#define LOG_CRITICAL_ERROR 4

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
  }
  update_correction(HIGHSPEED, HIGHSPEED);
  prev_button_status = button_status;
}
