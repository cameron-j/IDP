#include "grab.h"
#include <arduino.h>
#include <Servo.h>  //include servo library
#include "logging.h"
#include "motor_control.h"
#include "line_following.h"
#include "navigation.h"

#define ULTRASOUND_PIN A3
#define LEFT_CRASH_PIN 2
#define RIGHT_CRASH_PIN 9

#define SERVO_DELAY 30
#define OPEN_POSITION 120
#define CLOSED_POSITION 0
#define DEPOSIT_POSITION 180
#define PICKUP_POSITION 120

Servo servo;  // create servo object to control a servo
int dist_t = 20;
int ultrasound_t;  
int position;
bool grab_ready = false;

void grab_init() {     
  servo.attach(10, 500, 2500);
  PinMode(LEFT_CRASH_PIN, INPUT);
  PinMode(RIGHT_CRASH_PIN, INPUT);
  servo.write(OPEN_POSITION ); // set initial servo position (position mechanism to be vertical)
}

void prepare_for_grab() {
  if (!grab_ready) {
    mot_stop();
    servo.write(PICKUP_POSITION);
    grab_ready = true;
    delay(1000);
  }
}

void grab_block(){
  mot_straight(APPROACH_SPEED);
  if (check_block_distance() < 7){
    mot_stop();
  for (position = PICKUP_POSITION; position >= CLOSED_POSITION; position --) { // goes from open to closed positions in steps of 1 degree     
      servo.write(position);
      delay(SERVO_DELAY);
      log("Angle " + (String)position, LOG_MID);
   }
  }
  grab_ready = false;
}

void deposit_block() { // for final version: change OPEN_POSITION to DEPOSIT_POSITION ?? maybe not
  servo.write(CLOSED_POSITION);
  servo.write(DEPOSIT_POSITION);
  delay(1500);
  servo.write(OPEN_POSITION);
  delay(1000);
  // for (position = CLOSED_POSITION; position <= OPEN_POSITION; position++) { // goes from closed to open position in steps of 1 degree     
  //   servo.write(position);
  //   delay(SERVO_DELAY);
  //   log("Angle " + (String)position, LOG_MID);
  //  }
    // mot_reverse();
    // delay(200);
  // for (position = OPEN_POSITION; position <= DEPOSIT_POSITION; position++) { // goes from open to deposit position in steps of 1 degree     
  //   servo.write(position);
  //   delay(SERVO_DELAY);
  //   log("Angle " + (String)position, LOG_MID);
  //  }
  //  mot_straight();
  //  delay(150);
}

float check_block_distance(){
  ultrasound_t = analogRead(ULTRASOUND_PIN);
  dist_t = ultrasound_t * MAX_RANGE  / ADC_SOLUTION;   
  if (dist_t < GRABBING_DISTANCE){
    return dist_t;
  }
  return -1;
}

bool left_crash_activated() {
  return !digitalRead(LEFT_CRASH_PIN); // crash sensor is active low => this function returns true is sensor activated
}

bool right_crash_activated() {
  return !digitalRead(RIGHT_CRASH_PIN); // crash sensor is active low => this function returns true is sensor activated
}
