#pragma once
#include <arduino.h>

void navigate (String commands);
int fetchBlock (int location, int block);
void fetchAllTheBlocks();

#define APPROACH_SPEED 140
