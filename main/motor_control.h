#pragma once

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define STRAIGHT_SPEED 200
#define REVERSE_SPEED 150
#define TURN_SPEED 180
#define CORRECTION_LOW_SPEED 40
#define CORRECTION_HIGH_SPEED 235

void mot_straight();
void mot_reverse();
void mot_stop();
void mot_turn_left();
void mot_turn_right();
void mot_correct_to_left();
void mot_correct_to_right();
void set_rightmotor_speed(int speed);
void set_leftmotor_speed(int speed);
int get_speed();
void mot_init();
