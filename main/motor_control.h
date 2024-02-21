#pragma once

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

#define HIGHSPEED 200 // standard speed when away from junctions
#define LOWSPEED 100 // standard speed when approaching junctions
#define TURNSPEED 150 // turning speed
#define CORRECTION 0.1 // proportional change in motor speed during line following correction

void mot_straight(int speed);
void mot_stop();
void mot_turn_left(int speed);
void mot_turn_right(int speed);
void mot_correct_to_left(int correction);
void mot_correct_to_right(int correction);
void set_rightmotor_speed(int speed);
void set_leftmotor_speed(int speed);
void mot_init();
