#pragma once
#include <arduino.h>

// Logging levels
#define LOG_LOW 0
#define LOG_MID 1
#define LOG_HIGH 2
#define LOG_ERROR 3
#define LOG_CRITICAL_ERROR 4

static int log_level;
static String log_levels[5] = {"[ LOG LOW ] : ", "[ LOG MID ] : ", "[ LOG HIGH ] : ", "[ ERROR ] : ", "[ CRITICAL ERROR ] : "};
static bool log_initialised = false;

void log_init(int level);
void log(String msg, int level);
