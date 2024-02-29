#include "map.h"
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

// Turns
#define TURN_ITERATION_DELAY 50
int turn_counter = 0;

// Button input
int button_status;
int prev_button_status = 1;
bool run = false;
bool turned = false;

// the setup function runs once when you press reset or power the board
void setup() {
  log_init(LOG_HIGH);
  mot_init();
  mot_straight();
  log("Running Straight", LOG_HIGH);
  delay(100);
  mot_stop();
  grab_init();
}

// the loop function runs over and over again forever
void loop() {
  button_status = digitalRead(BUTTON_PIN);
  if (button_status == 0 && prev_button_status == 1) {
    run = !run;
  }
  // if (!turned) {
  //   if (detect_right_turn()) {
  //     right_turn();
  //     log("Turned", LOG_HIGH);
  //     turned = true;
  //   }
  // }
  // else if (turn_counter < TURN_ITERATION_DELAY) {
  //   turn_counter++;
  // }
  // else {
  //   turned = false;
  //   turn_counter = 0;
  // }

  if (run) {
   fetchAllTheBlocks();
   run = false;
  }

  prev_button_status = button_status;
}
