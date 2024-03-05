#include "line_following.h"
#include "motor_control.h"
#include "logging.h"
#include <arduino.h>

#define BRPIN 3
#define FRPIN 4
#define FLPIN 5
#define BLPIN 8

#define INDICATOR_LED_PIN 6

#define TURN_DELAY 100

#define LED_PERIOD 500

#define STOPPING_ITERATIONS 600

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

void track_straight() {
  sv = read_sensors();
  if (sv.front_right == 0 && sv.front_left == 0){
    mot_straight();
    // straight_iterations++;
    log("Straight line", LOG_LOW);
  }
  if (sv.front_right == 1 && sv.front_left == 0){
    // straight_iterations = 0;
    mot_correct_to_right();
    log("Turn right", LOG_LOW);
  }
  if (sv.front_right == 0 && sv.front_left == 1){
    // straight_iterations = 0;
    mot_correct_to_left();
    log("Turn left", LOG_LOW);
  }
  if (sv.front_right == 1 && sv.front_left == 1){
    // straight_iterations = 0;
    mot_straight();
    log("Straight line", LOG_LOW);
  }

  blink_movement_led();

  // if (straight_iterations == WIGGLE_FRONTIER) {
  //   if (wiggle_check()) {
  //     // PANIC!!!!!!!!!!!!!
  //     delay(5000);
  //   }
  //   straight_iterations = 0;
  // }
}

bool detect_left_turn() {
  sv = read_sensors();
  return (bool)sv.back_left;
}

bool detect_right_turn() {
  sv = read_sensors();
  return (bool)sv.back_right;
}

bool detect_straight() {
  sv = read_sensors();
  return (bool)(sv.back_left or sv.back_right);
}

void left_turn() {
  delay(TURN_DELAY);
  mot_stop();
  int state = 0;
  mot_turn_left();

  while (state < 3) {
    sv = read_sensors();

    // Update state
    if (state == 0 && sv.front_left == 0) {
      state = 1;
      log("State 1", LOG_HIGH);
    }
    else if (state == 1 && sv.front_left == 1) {
      state = 2;
      log("State 2", LOG_HIGH);
    }
    else if (state == 2 && sv.front_left == 0) {
      state = 3;
      log("State 3", LOG_HIGH);
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
    sv = read_sensors();

    // Update state
    if (state == 0 && sv.front_right == 0) {
      state = 1;
      log("State 1", LOG_HIGH);
    }
    else if (state == 1 && sv.front_right == 1) {
      state = 2;
      log("State 2", LOG_HIGH);
    }
    else if (state == 2 && sv.front_right == 0) {
      state = 3;
      log("State 3", LOG_HIGH);
    }
    blink_movement_led();
  }
}

// TODO: test blinking led here
void stop_in_the_box() {
  for (int _ = 0; _ < STOPPING_ITERATIONS; _++) {
    mot_straight();
  }
  // mot_straight();
  // log("Stopping in the box", LOG_HIGH);
  // delay(STOPPING_TIME);
  // log("STOP", LOG_HIGH);
  mot_stop();
}

// // Checks that the line is between the sensors
// bool wiggle_check() {
//   log("Starting wiggle", LOG_HIGH);
//   bool panic = false;
//   mot_turn_left(WIGGLE_SPEED);
//   delay(WIGGLE_TIME);
//   mot_stop();
//   panic = !ls2;
//   mot_turn_right(WIGGLE_SPEED);
//   delay(2 * WIGGLE_TIME);
//   mot_stop();
//   panic = panic || !ls3;
//   mot_turn_left(WIGGLE_SPEED);
//   delay(WIGGLE_TIME);
//   mot_stop();
//   log("Wiggle result: panic = " + panic, LOG_HIGH);
//   return panic;
// }
