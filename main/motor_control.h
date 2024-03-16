#pragma once
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define STRAIGHT_SPEED 230
#define REVERSE_SPEED 175
#define TURN_SPEED 200
#define CORRECTION_LOW_SPEED 110
#define CORRECTION_HIGH_SPEED 235

void mot_straight(int speed);
void mot_reverse();
void mot_stop();
void mot_turn_left();
void mot_turn_right();
void mot_correct_to_left();
void mot_correct_to_right();
void set_rightmotor_speed(int speed);
void set_leftmotor_speed(int speed);
void mot_init();
