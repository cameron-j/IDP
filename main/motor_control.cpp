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

// Runs both motors forward at a given speed.
void mot_straight(int speed) {
  if (current_state != STATE_STRAIGHT) {
    leftmotor->setSpeed(speed);
    rightmotor->setSpeed(speed);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_STRAIGHT;
  }
}

// Runs both motors backward at a given speed.
void mot_reverse() {
  if (current_state != STATE_REVERSE) {
    leftmotor->setSpeed(REVERSE_SPEED);
    rightmotor->setSpeed(REVERSE_SPEED);
    leftmotor->run(BACKWARD);
    rightmotor->run(BACKWARD);

    current_state = STATE_REVERSE;
  }
}

// Stops both motors. Also uses movement_led_off() to stop the blue flashing LED.
void mot_stop() {
  if (current_state != STATE_STOP) {
    movement_led_off();
    leftmotor->run(RELEASE);
    rightmotor->run(RELEASE);

    current_state = STATE_STOP;
  }
}

// Runs the left motor forward and the right motor backward at a given speed.
void mot_turn_right() {
  if (current_state != STATE_TURN_RIGHT) {
    leftmotor->setSpeed(TURN_SPEED);
    rightmotor->setSpeed(TURN_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(BACKWARD);

    current_state = STATE_TURN_RIGHT;
  }
}

// Runs the left motor backward and the right motor forward at a given speed.
void mot_turn_left() {
  if (current_state != STATE_TURN_LEFT) {
    leftmotor->setSpeed(TURN_SPEED);
    rightmotor->setSpeed(TURN_SPEED);
    leftmotor->run(BACKWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_TURN_LEFT;
  }
}

// Runs the left motor at a given lower speed and the right motor at a given higher speed.
void mot_correct_to_left() {
  if (current_state != STATE_CORRECT_LEFT) {
    leftmotor -> setSpeed(CORRECTION_LOW_SPEED);
    rightmotor -> setSpeed(CORRECTION_HIGH_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_CORRECT_LEFT;
  }
}

// Runs the left motor at a given higher speed and the right motor at a given lower speed.
void mot_correct_to_right() {
  if (current_state != STATE_CORRECT_RIGHT) {
    leftmotor -> setSpeed(CORRECTION_HIGH_SPEED);
    rightmotor -> setSpeed(CORRECTION_LOW_SPEED);
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);

    current_state = STATE_CORRECT_RIGHT;
  }
}

// Sets speed of right motor
void set_rightmotor_speed(int speed) {
  rightmotor -> setSpeed(speed);
}

// Sets speed of left motor
void set_leftmotor_speed(int speed) {
  leftmotor -> setSpeed(speed);
}

// Initialises the motors to their respective inputs on the Arduino board.
void mot_init() {
  AFMS = Adafruit_MotorShield();
  leftmotor = AFMS.getMotor(1);
  rightmotor = AFMS.getMotor(2);
  AFMS.begin();
}
