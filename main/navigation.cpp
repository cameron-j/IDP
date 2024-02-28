#include "navigation.h"
#include "motor_control.h"
#include "line_following.h"
#include "logging.h"
#include "grab.h"

#define BLOCK_COUNT 4
#define LOCATION_START 0
#define LOCATION_RED 1
#define LOCATION_GREEN 2
#define RED 0
#define BLACK 1
#define STRAIGHT_ITERATIONS 500
#define ZONE_REVERSE_TIME 1000

bool instruction_executed;

void navigate (String commands) {
    int counter = 0;
    bool run = true;

    // add in some logging here?

    while (run) {
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
              if (check_block_distance()) {
                mot_stop();
                grab_block();
                // pickUpTheBlockAndDetectColour(); 
                //   this should call the pick up function, the detect colour function, and the led function
                left_turn();
                instruction_executed = true;
                log("B", LOG_HIGH);
              }
                break;
            case 'Z':
            if (left_crash_activated() && right_crash_activated()) {
              mot_stop();
              deposit_block();

              mot_reverse();
              delay(ZONE_REVERSE_TIME);
              mot_stop();

              left_turn();
              instruction_executed = true;
              log("Z", LOG_HIGH);
            }
                break;
            case 'S':
                if (detect_straight()) {
                  stop_in_the_box();
                  // instruction_executed = true;
                  run = false;
                  log("S", LOG_HIGH);
                }
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

