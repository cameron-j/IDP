#include "line_following.h"
#include "motor_control.h"
#include "logging.h"
#include <arduino.h>

#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4

// line sensors
int ls1;
int ls2; // right line following
int ls3; // left line following
int ls4;

int correction = 0;


void line_init() {

}


void update_correction(int straightspeed, int turnspeed) {
    ls1 = digitalRead(PIN1);
    ls2 = digitalRead(PIN2);
    ls3 = digitalRead(PIN3);
    ls4 = digitalRead(PIN4);

    if (ls2 == 0 && ls3 == 0){
      mot_straight(straightspeed);
      log("Straight line", LOG_HIGH);
    }
    if (ls2 == 1 && ls3 == 0){
      mot_correct_to_right(turnspeed);
      log("Turn right", LOG_HIGH);
    }
    if (ls2 == 0 && ls3 == 1){
      mot_correct_to_left(turnspeed);
      log("Turn left", LOG_HIGH);
    }
    if (ls2 == 1 && ls3 == 1){
      mot_straight(straightspeed);
      log("Straight line", LOG_HIGH);
    }    
}