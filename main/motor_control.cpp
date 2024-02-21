#include "motor_control.h"

Adafruit_DCMotor *leftmotor;
Adafruit_DCMotor *rightmotor;
Adafruit_MotorShield AFMS;

int old_speed = 0; // set initial speed so that motor speed functions do not run unnecessarily


void mot_straight(int speed) {
    if (speed != old_speed) {
      leftmotor->setSpeed(speed);
      rightmotor->setSpeed(speed);
      leftmotor->run(FORWARD);
      rightmotor->run(FORWARD);
      old_speed = speed;
    }
  }

void mot_stop() {
      leftmotor->run(RELEASE);
      rightmotor->run(RELEASE);
}

void mot_turn_left(int speed) {
      leftmotor->setSpeed(speed);
      rightmotor->setSpeed(speed);
      leftmotor->run(FORWARD);
      rightmotor->run(BACKWARD);
}


void mot_turn_right(int speed) {
      leftmotor->setSpeed(speed);
      rightmotor->setSpeed(speed);
      leftmotor->run(BACKWARD);
      rightmotor->run(FORWARD);
}


void mot_correct_to_left(int speed) {
    leftmotor->setSpeed(speed*(1-CORRECTION));
    rightmotor->setSpeed(speed*(1+CORRECTION));
    leftmotor->run(FORWARD);
    rightmotor->run(FORWARD);
}


void mot_correct_to_right(int speed) {
    leftmotor->setSpeed(speed*(1+CORRECTION));
    rightmotor->setSpeed(speed*(1-CORRECTION));
    leftmotor->run(BACKWARD);
    rightmotor->run(BACKWARD);
}

void mot_init() {
  AFMS = Adafruit_MotorShield(); 
  leftmotor = AFMS.getMotor(1);
  rightmotor = AFMS.getMotor(2);
  AFMS.begin();
}