#include "motor_control.h"
#include "line_following.h"
#include "logging.h"
#include "navigation.h"
#include "grab.h"

// Logging levels
#define LOG_LOW 0
#define LOG_MID 1
#define LOG_HIGH 2
#define LOG_ERROR 3
#define LOG_CRITICAL_ERROR 4

// Pins
#define BUTTON_PIN 9

// Button input
int button_status;
int prev_button_status = 1;
bool run = false;

void setup() {
  log_init(LOG_MID);
  mot_init();
  grab_init();

  // Wheels spin to indicate that code has uploaded successfully
  mot_straight(STRAIGHT_SPEED);
  log("Running Straight", LOG_HIGH);
  delay(100);
  mot_stop();
}

void loop() {
  // When button is pressed, run is toggled
  button_status = digitalRead(BUTTON_PIN);
  if (button_status == 0 && prev_button_status == 1) {
    run = !run;
  }

  if (run) {
    fetchAllTheBlocks();
    run = false;
  }

  prev_button_status = button_status;
}
