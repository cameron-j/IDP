#include "line_following.h"
#include "motor_control.h"
#include "logging.h"
#include <arduino.h>

#define PIN1 3
#define PIN2 4
#define PIN3 5
#define PIN4 8

// #define WIGGLE_SPEED 100
// #define WIGGLE_TIME 200
// #define WIGGLE_FRONTIER 25

// line sensors
int ls1;
int ls2; // right line following
int ls3; // left line following
int ls4;

int correction = 0;

// int straight_iterations = 0;

void line_init() {

}

void track_straight() {
    ls1 = digitalRead(PIN1);
    ls2 = digitalRead(PIN2);
    ls3 = digitalRead(PIN3);
    ls4 = digitalRead(PIN4);

    if (ls2 == 0 && ls3 == 0){
      mot_straight();
      // straight_iterations++;
      log("Straight line", LOG_LOW);
    }
    if (ls2 == 1 && ls3 == 0){
      // straight_iterations = 0;
      mot_correct_to_right();
      log("Turn right", LOG_LOW);
    }
    if (ls2 == 0 && ls3 == 1){
      // straight_iterations = 0;
      mot_correct_to_left();
      log("Turn left", LOG_LOW);
    }
    if (ls2 == 1 && ls3 == 1){
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
  return (bool)ls4;
}

bool detect_right_turn() {
  return (bool)ls1;
}

void left_turn() {
  delay(100);
  mot_stop();
  int state = 0;
  mot_turn_left();

  while (state < 3) {
    ls1 = digitalRead(PIN1);
    ls2 = digitalRead(PIN2);
    ls3 = digitalRead(PIN3);
    ls4 = digitalRead(PIN4);

    // Update state
    if (state == 0 && ls3 == 0) {
      state = 1;
      log("State 1", LOG_HIGH);
    }
    else if (state == 1 && ls3 == 1) {
      state = 2;
      log("State 2", LOG_HIGH);
    }
    else if (state == 2 && ls3 == 0) {
      state = 3;
      log("State 3", LOG_HIGH);
    }
  }
}

void right_turn() {
  delay(100);
  mot_stop();
  int state = 0;
  mot_turn_right();

  while (state < 3) {
    ls1 = digitalRead(PIN1);
    ls2 = digitalRead(PIN2);
    ls3 = digitalRead(PIN3);
    ls4 = digitalRead(PIN4);

    // Update state
    if (state == 0 && ls2 == 0) {
      state = 1;
      log("State 1", LOG_HIGH);
    }
    else if (state == 1 && ls2 == 1) {
      state = 2;
      log("State 2", LOG_HIGH);
    }
    else if (state == 2 && ls2 == 0) {
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
