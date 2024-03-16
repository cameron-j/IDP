#pragma once

#define  MAX_RANGE 520 // the max measurement value of the module is 520cm(a little bit longer than  effective max range) 
#define  ADC_SOLUTION 1023.0 // ADC accuracy of Arduino UNO is 10bit
#define GRABBING_DISTANCE 10

void grab_init();
void grab_block();
void prepare_for_grab();
void deposit_block();
float check_block_distance();
bool left_crash_activated();
bool right_crash_activated();
