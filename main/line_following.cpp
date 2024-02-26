#include "line_following.h"
#include "motor_control.h"
#include "logging.h"
#include <arduino.h>

#define BRPIN 3
#define FRPIN 4
#define FLPIN 5
#define BLPIN 8

#define TURN_DELAY 100

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

// int straight_iterations = 0;

void line_init() {

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
  }
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
