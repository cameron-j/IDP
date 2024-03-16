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

// Executes a string of given commands.
void navigate (String commands) {
    int counter = 0;
    bool run = true;

    while (counter < commands.length()) {
        instruction_executed = false;
        track_straight(STRAIGHT_SPEED);
        left_junction_sensor = read_left_junction_sensor();
        right_junction_sensor = read_right_junction_sensor();

        switch (commands[counter]) {
            // Go straight at a junction
            case 'F':
              if (left_junction_sensor || right_junction_sensor) {
                instruction_executed = true;
                log("F", LOG_HIGH);
              }

              break;

            // Turn left at a junction
            case 'L':
              if (left_junction_sensor) {
                left_turn();
                instruction_executed = true;
                log("L", LOG_HIGH);
              }

              break;

            // Turn right at a junction
            case 'R':
              if (right_junction_sensor) {
                right_turn();
                instruction_executed = true;
                log("R", LOG_HIGH);
              }

              break;

            // Stop and pick up a block, then detect block colour, then indicate block colour with the respective LED, then turn around.
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

            // Detect the green drop zone, then deposit the block, then reverse a short distance, then turn around.
            case 'X':
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

            // Same as X but for the red zone.
            case 'Y':
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

            // Stops the robot within the start/finish box.
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

// Contains strings relating to each possible path of the robot and selects the correct string to execute based on block colour (for navigating to zones), or current position and number of blocks collected (for navigating to blocks).
int fetchBlock (int location, int block) {
    // empty strings to block 0 as this is always accessed from start box
    String fromRedToBlock[BLOCK_COUNT] = {"","FLLB","FLFRFRRB","FLFRLB"};
    String fromGreenToBlock[BLOCK_COUNT] = {"","FRFRB","FRLFRRB","FRLLB"};

    String fromBlockToRed[BLOCK_COUNT] = {"LFRY","RRFY","LLFLFRFY","RLFRFY"};
    String fromBlockToGreen[BLOCK_COUNT] = {"RLX","LFLFX","LLFRLFX","RRLFX"};

    if (location == LOCATION_START) {
      log("I'm at the start", LOG_HIGH);
      // from start to block 0
      navigate("FLRB");
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

// Uses fetchBlock (int location, int block) to complete the entire task.
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
