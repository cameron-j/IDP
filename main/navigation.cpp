#include "navigation.h"
#include "motor_control.h"
#include "line_following.h"
#include "logging.h"
#include "grab.h"
#include "colour_detection.h"

#define BLOCK_COUNT 4
#define LOCATION_START 0
#define LOCATION_RED 1
#define LOCATION_GREEN 2
#define RED 0
#define BLACK 1
#define STRAIGHT_ITERATIONS 10000
#define ZONE_REVERSE_TIME 500
#define PICKUP_REVERSE_TIME 700

bool instruction_executed;

bool left_junction_sensor;
bool right_junction_sensor;

int dist_to_block = -1;

void navigate (String commands) {
    int counter = 0;
    bool run = true;

    while (counter < commands.length()) {
        instruction_executed = false;
        track_straight(STRAIGHT_SPEED);
        left_junction_sensor = read_left_junction_sensor();
        right_junction_sensor = read_right_junction_sensor();

        switch (commands[counter]) {
            case 'F':
                if (left_junction_sensor || right_junction_sensor) {
                  instruction_executed = true;
                  log("F", LOG_HIGH);
                }
                break;
            case 'L':
                if (left_junction_sensor) {
                  left_turn();
                  instruction_executed = true;
                  log("L", LOG_HIGH);
                }
                break;
            case 'R':
                if (right_junction_sensor) {
                  right_turn();
                  instruction_executed = true;
                  log("R", LOG_HIGH);
                }
                break;
            case 'B':
              dist_to_block = -1;
              //prepare_for_grab();
              // track_straight(APPROACH_SPEED);
              while (dist_to_block == -1) {
                track_straight(STRAIGHT_SPEED);
                dist_to_block = check_block_distance();
                log("distance" + (String)dist_to_block, LOG_HIGH);
              }
              mot_stop();
              delay(200);
              mot_straight(APPROACH_SPEED);
              delay(800 * dist_to_block / GRABBING_DISTANCE);
              mot_stop();
              grab_block();
              blink_LED(detect_colour());
              mot_reverse();
              delay(400);
              left_turn();
              instruction_executed = true;
              log("B", LOG_HIGH);
              break;
            case 'X': //green zone
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
            case 'Y': //red zone
            if (left_crash_activated() && right_crash_activated()) {
              mot_stop();
              deposit_block();

              mot_reverse();
              delay(ZONE_REVERSE_TIME);
              mot_stop();

              right_turn();
              instruction_executed = true;
              log("Z", LOG_HIGH);
            }
                break;                
            case 'S':
                if (left_junction_sensor && right_junction_sensor) {
                  stop_in_the_box();
                  log("S", LOG_HIGH);
                  return;
                }
                break;
        }

        if (instruction_executed) {
          for (int _ = 0; _ < STRAIGHT_ITERATIONS; _++) {
            track_straight(STRAIGHT_SPEED);
          }
          counter++;
        }
    }
}

// from location go to block and return to drop location
int fetchBlock (int location, int block) {

    // empty strings to block 0 as this is always accessed from start box
    String fromRedToBlock[BLOCK_COUNT] = {"","FLLB","FLFRFRRB","FLFRLB"};
    String fromGreenToBlock[BLOCK_COUNT] = {"","FRFRB","FRLFRRB","FRLLB"};

    String fromBlockToRed[BLOCK_COUNT] = {"LFRY","RRFY","LLFLFRFY","RLFRFY"};
    String fromBlockToGreen[BLOCK_COUNT] = {"RLX","LFLFX","LLFRLFX","RRLFX"};

    // add some logging here?

    if (location == LOCATION_START) {
      log("I'm at the start", LOG_HIGH);
      navigate("FLRB"); // from start to block 0
    }
    if (location == LOCATION_RED) {
      log("I'm at the red zone", LOG_HIGH);
      navigate(fromRedToBlock[block]);
    }
    if (location == LOCATION_GREEN) {
      log("I'm at the green zone", LOG_HIGH);
      navigate(fromGreenToBlock[block]);
    }

    log("I'm at the block", LOG_HIGH);
    int colour = detect_colour();

    if (colour == RED) {
      log("Navigating route: " + fromBlockToRed[block], LOG_HIGH);
      navigate(fromBlockToRed[block]);
    }
    else {
      log("Navigating route: " + fromBlockToGreen[block], LOG_HIGH);
      navigate(fromBlockToGreen[block]);
    }

    return colour == RED ? LOCATION_RED : LOCATION_GREEN;
}

void fetchAllTheBlocks() {
    int location = LOCATION_START;

    for (int block = 0; block < BLOCK_COUNT; ++block)
        location = fetchBlock(location, block);

    // return to start
    if (location == LOCATION_RED) 
        navigate("LLS"); // from red to start
    else 
        navigate("RFRS"); // from green to start
}