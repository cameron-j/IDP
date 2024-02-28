#pragma once

void line_init();
void track_straight();
bool detect_left_turn();
bool detect_right_turn();
bool detect_straight();
void left_turn();
void right_turn();
// bool wiggle_check();

typedef struct Sensor_s {
  int back_right;
  int front_right;
  int front_left;
  int back_left;
}SensorValue;

SensorValue read_sensors();