#include "motor_control.h"
#include "line_following.h"

Adafruit_DCMotor *leftmotor;
Adafruit_DCMotor *rightmotor;
Adafruit_MotorShield AFMS;

// int old_speed = 0; // set initial speed so that motor speed functions do not run unnecessarily

void mot_straight() {
//  if (speed != old_speed) {
    leftmotor->setSpeed(STRAIGHT_SPEED);
    rightmotor->setSpeed(STRAIGHT_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);
//    old_speed = speed;
//  }
}

void mot_reverse() {
    leftmotor->setSpeed(REVERSE_SPEED);
    rightmotor->setSpeed(REVERSE_SPEED);
    leftmotor->run(BACKWARD);
    rightmotor->run(BACKWARD);
}

void mot_stop() {
  movement_led_off();
  leftmotor->run(RELEASE);
  rightmotor->run(RELEASE);
  //old_speed = 0;
}

void mot_turn_right() {
  leftmotor->setSpeed(TURN_SPEED);
  rightmotor->setSpeed(TURN_SPEED);
  leftmotor->run(FORWARD);
  rightmotor->run(BACKWARD);
}

void mot_turn_left() {
  leftmotor->setSpeed(TURN_SPEED);
  rightmotor->setSpeed(TURN_SPEED);
  leftmotor->run(BACKWARD);
  rightmotor->run(FORWARD);
}


void mot_correct_to_left() {
  leftmotor -> setSpeed(CORRECTION_LOW_SPEED);
  rightmotor -> setSpeed(CORRECTION_HIGH_SPEED);
  leftmotor->run(FORWARD);
  rightmotor->run(FORWARD);
}

void mot_correct_to_right() {
  leftmotor -> setSpeed(CORRECTION_HIGH_SPEED);
  rightmotor -> setSpeed(CORRECTION_LOW_SPEED);
  leftmotor->run(FORWARD);
  rightmotor->run(FORWARD);
}



// void mot_correct_to_left(int correction) {
//   leftmotor -> setSpeed(old_speed - correction);
//   rightmotor -> setSpeed(old_speed + correction);
//   leftmotor->run(FORWARD);
//   rightmotor->run(FORWARD);
// }

// void mot_correct_to_right(int correction) {
//   leftmotor -> setSpeed(old_speed + correction);
//   rightmotor -> setSpeed(old_speed - correction);
//   leftmotor->run(FORWARD);
//   rightmotor->run(FORWARD);
// }

void set_rightmotor_speed(int speed) {
  rightmotor -> setSpeed(speed);
}

void set_leftmotor_speed(int speed) {
  leftmotor -> setSpeed(speed);
}

// int get_speed() {
//   return old_speed;
// }

void mot_init() {
  AFMS = Adafruit_MotorShield(); 
  leftmotor = AFMS.getMotor(1);
  rightmotor = AFMS.getMotor(2);
  AFMS.begin();
  //old_speed = 0;
}