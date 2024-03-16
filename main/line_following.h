#pragma once
#include "motor_control.h"

void line_init();
void track_straight(int speed);
bool read_left_junction_sensor();
bool read_right_junction_sensor();
void left_turn();
void right_turn();
void stop_in_the_box();
void blink_movement_led();
void movement_led_off();
