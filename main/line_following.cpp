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


SensorValue read_sensors(){
  SensorValue s_value;
  // line sensors
  s_value.back_right = digitalRead(BRPIN); // right turn sensor
  s_value.front_right = digitalRead(FRPIN); // right line following
  s_value.front_left = digitalRead(FLPIN); // left line following
  s_value.back_left = digitalRead(BLPIN); // left turn sensor
  return s_value;
}


int correction = 0;

int state_count = 0;

SensorValue sv;

unsigned long previous_led_change = 0;
bool led_state = false;

// int straight_iterations = 0;

void line_init() {
  pinMode(INDICATOR_LED_PIN, OUTPUT);
}

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

void movement_led_off() {
  log("Movement LED switched off", LOG_MID);
  digitalWrite(INDICATOR_LED_PIN, LOW);
}

void track_straight(int speed) {
  bool front_right = digitalRead(FRPIN);
  bool front_left = digitalRead(FLPIN);
  if (front_right == 0 && front_left == 0){
    mot_straight(speed);
    // straight_iterations++;
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


bool read_left_junction_sensor() {
  return digitalRead(BLPIN);
}

bool read_right_junction_sensor() {
  return digitalRead(BRPIN);
}

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

// TODO: test blinking led here
void stop_in_the_box() {
  mot_straight(STRAIGHT_SPEED);
  delay(STOPPING_TIME);
  mot_stop();
}