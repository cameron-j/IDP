#pragma once
#include "map.h"

#define RED 0
#define BLACK 1

void colour_detection_init();
int detect_colour();
void blink_LED(int colour);
