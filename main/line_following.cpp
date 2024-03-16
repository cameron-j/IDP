#include "line_following.h"
#include "logging.h"
#include <arduino.h>

#define BRPIN 3
#define FRPIN 4
#define FLPIN 5
#define BLPIN 8

#define INDICATOR_LED_PIN 6

#define TURN_DELAY 100

#define LED_PERIOD 500

#define STOPPING_TIME 1100

#define STATE_ITERATION_LIMIT 500

int correction = 0;

int state_count = 0;

unsigned long previous_led_change = 0;
bool led_state = false;

// Initialises the blue flashing LED as an output
void line_init() {
  pinMode(INDICATOR_LED_PIN, OUTPUT);
}

// Flashes a blue LED at 2 Hz.
void blink_movement_led() {
  log("Blink LED", LOG_LOW);
  if (millis() - previous_led_change >= LED_PERIOD) {
    led_state = !led_state;
    previous_led_change = millis();
    log("Change LED", LOG_LOW);
  }
  if (led_state) {
    digitalWrite(INDICATOR_LED_PIN, HIGH);
  }
  else {
    digitalWrite(INDICATOR_LED_PIN, LOW);
  }
}

// Turns the blue LED off.
void movement_led_off() {
  log("Movement LED switched off", LOG_MID);
  digitalWrite(INDICATOR_LED_PIN, LOW);
}

// Uses mot_straight(), mot_correct_to_right() and mot_correct_to_left() to respond to inputs from the front line sensors to keep the robot tracking the white line. Also runs void blink_movement_led().
void track_straight(int speed) {
  bool front_right = digitalRead(FRPIN);
  bool front_left = digitalRead(FLPIN);

  if (front_right == 0 && front_left == 0){
    mot_straight(speed);
    log("Straight line", LOG_LOW);
  }

  if (front_right == 1 && front_left == 0){
    // straight_iterations = 0;
    mot_correct_to_right();
    log("Turn right", LOG_LOW);
  }

  if (front_right == 0 && front_left == 1){
    // straight_iterations = 0;
    mot_correct_to_left();
    log("Turn left", LOG_LOW);
  }

  if (front_right == 1 && front_left == 1){
    // straight_iterations = 0;
    mot_straight(speed);
    log("Straight line", LOG_LOW);
  }

  blink_movement_led();
}

// Returns true if a left turn junction is detected.
bool read_left_junction_sensor() {
  return digitalRead(BLPIN);
}

// Returns true if a right turn junction is detected.
bool read_right_junction_sensor() {
  return digitalRead(BRPIN);
}

// Runs mot_turn_left() until the front line sensors pick up a new line to follow. Also runs void blink_movement_led().
void left_turn() {
  delay(TURN_DELAY);
  mot_stop();
  int state = 0;
  mot_turn_left();

  while (state < 3) {
    bool front_left = digitalRead(FLPIN);

    // Update state
    if (state == 0 && front_left == 0) {
      if (state_count == STATE_ITERATION_LIMIT) {
        state = 1;
        log("State 1", LOG_HIGH);
        state_count = 0;
      }
      else {
        state_count++;
      }
    }

    else if (state == 1 && front_left == 1) {
      if (state_count == STATE_ITERATION_LIMIT) {
        state = 2;
        log("State 2", LOG_HIGH);
        state_count = 0;
      }
      else {
        state_count++;
      }
    }

    else if (state == 2 && front_left == 0) {
      if (state_count == STATE_ITERATION_LIMIT) {
        state = 3;
        log("State 3", LOG_HIGH);
        state_count = 0;
      }
      else {
        state_count++;
      }
    }

    blink_movement_led();
  }
}

// Runs mot_turn_right() until the front line sensors pick up a new line to follow. Also runs void blink_movement_led().
void right_turn() {
  delay(TURN_DELAY);
  mot_stop();
  int state = 0;
  mot_turn_right();

  while (state < 3) {
    bool front_right = digitalRead(FRPIN);

    // Update state
    if (state == 0 && front_right == 0) {
      if (state_count == STATE_ITERATION_LIMIT) {
        state = 1;
        log("State 1", LOG_HIGH);
        state_count = 0;
      }
      else {
        state_count++;
      }
    }

    else if (state == 1 && front_right == 1) {
      if (state_count == STATE_ITERATION_LIMIT) {
        state = 2;
        log("State 2", LOG_HIGH);
        state_count = 0;
      }
      else {
        state_count++;
      }
    }

    else if (state == 2 && front_right == 0) {
      if (state_count == STATE_ITERATION_LIMIT) {
        state = 3;
        log("State 3", LOG_HIGH);
        state_count = 0;
      }
      else {
        state_count++;
      }
    }

    blink_movement_led();
  }
}

// Runs mot_straight() for a defined number of cycles and then stops the motors.
void stop_in_the_box() {
  mot_straight(STRAIGHT_SPEED);
  delay(STOPPING_TIME);
  mot_stop();
}
