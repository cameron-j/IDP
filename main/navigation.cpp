#include "navigation.h"
#include "motor_control.h"
#include "line_following.h"
#include "logging.h"

#define BLOCK_COUNT 4
#define LOCATION_START 0
#define LOCATION_RED 1
#define LOCATION_GREEN 2
#define RED 0
#define BLACK 1
#define STRAIGHT_ITERATIONS 500

bool instruction_executed;

void navigate (String commands) {
    int counter = 0;

    // add in some logging here?

    while (true) {
        instruction_executed = false;
        track_straight();
        switch (commands[counter]) {

            case 'F':
                if (detect_straight()) {
                  instruction_executed = true;
                  log("F", LOG_HIGH);
                }
                break;
            case 'L':
                if (detect_left_turn()) {
                  left_turn();
                  instruction_executed = true;
                  log("L", LOG_HIGH);
                }
                break;
            case 'R':
                if (detect_right_turn()) {
                  right_turn();
                  instruction_executed = true;
                  log("R", LOG_HIGH);
                }
                break;
            case 'T': // turn around
                left_turn();
                instruction_executed = true;
                log("L", LOG_HIGH);
                break;
            case 'B':
                // moveToBlock();
                break;
            case 'Z':
                // moveToZone();
                break;
            case 'S':
                // stop inside the box
                break;
            default:
                track_straight();
        }

        if (instruction_executed) {
          for (int _ = 0; _ < STRAIGHT_ITERATIONS; _++) {
            track_straight();
          }
          counter++;
        }
    }
}

