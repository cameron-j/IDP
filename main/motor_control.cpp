#include "motor_control.h"
#include "line_following.h"

#define STATE_STRAIGHT 0
#define STATE_REVERSE 1
#define STATE_STOP 2
#define STATE_TURN_RIGHT 3
#define STATE_TURN_LEFT 4
#define STATE_CORRECT_RIGHT 5
#define STATE_CORRECT_LEFT 6

int current_state = STATE_STOP;

Adafruit_DCMotor *leftmotor;
Adafruit_DCMotor *rightmotor;
Adafruit_MotorShield AFMS;

void mot_straight(int speed) {
  if (current_state != STATE_STRAIGHT) {
    leftmotor->setSpeed(speed);
    rightmotor->setSpeed(speed);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_STRAIGHT;
  }
}

void mot_reverse() {
  if (current_state != STATE_REVERSE) {
    leftmotor->setSpeed(REVERSE_SPEED);
    rightmotor->setSpeed(REVERSE_SPEED);
    leftmotor->run(BACKWARD);
    rightmotor->run(BACKWARD);

    current_state = STATE_REVERSE;
  }
}

void mot_stop() {
  if (current_state != STATE_STOP) {
    movement_led_off();
    leftmotor->run(RELEASE);
    rightmotor->run(RELEASE);

    current_state = STATE_STOP;
  }
}

void mot_turn_right() {
  if (current_state != STATE_TURN_RIGHT) {
    leftmotor->setSpeed(TURN_SPEED);
    rightmotor->setSpeed(TURN_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(BACKWARD);

    current_state = STATE_TURN_RIGHT;
  }
}

void mot_turn_left() {
  if (current_state != STATE_TURN_LEFT) {
    leftmotor->setSpeed(TURN_SPEED);
    rightmotor->setSpeed(TURN_SPEED);
    leftmotor->run(BACKWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_TURN_LEFT;
  }
}


void mot_correct_to_left() {
  if (current_state != STATE_CORRECT_LEFT) {
    leftmotor -> setSpeed(CORRECTION_LOW_SPEED);
    rightmotor -> setSpeed(CORRECTION_HIGH_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_CORRECT_LEFT;
  }
}

void mot_correct_to_right() {
  if (current_state != STATE_CORRECT_RIGHT) {
    leftmotor -> setSpeed(CORRECTION_HIGH_SPEED);
    rightmotor -> setSpeed(CORRECTION_LOW_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_CORRECT_RIGHT;
  }
}

void set_rightmotor_speed(int speed) {
  rightmotor -> setSpeed(speed);
}

void set_leftmotor_speed(int speed) {
  leftmotor -> setSpeed(speed);
}

void mot_init() {
  AFMS = Adafruit_MotorShield(); 
  leftmotor = AFMS.getMotor(1);
  rightmotor = AFMS.getMotor(2);
  AFMS.begin();
}