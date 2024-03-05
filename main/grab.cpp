#include "grab.h"
#include <arduino.h>
#include <Servo.h>  //include servo library
#include "logging.h"

#define ULTRASOUND_PIN A3
#define LEFT_CRASH_PIN 2
#define RIGHT_CRASH_PIN 9

#define SERVO_DELAY 30
#define OPEN_POSITION 100
#define CLOSED_POSITION 0
#define DEPOSIT_POSITION 180

Servo servo;  // create servo object to control a servo
int dist_t = 20;
int ultrasound_t;  
int position;

void grab_init() {     
  servo.attach(10, 500, 2500);
  PinMode(LEFT_CRASH_PIN, INPUT);
  PinMode(RIGHT_CRASH_PIN, INPUT);
  servo.write(OPEN_POSITION ); // set initial servo position (position mechanism to be vertical)
}

void grab_block(){
   for (position = OPEN_POSITION; position >= CLOSED_POSITION; position --) { // goes from open to closed positions in steps of 1 degree     
    servo.write(position);
    delay(SERVO_DELAY);
    log("Angle " + (String)position, LOG_MID);
   }
}

void deposit_block() {
  servo.write(CLOSED_POSITION);
  for (position = CLOSED_POSITION; position <= 180; position++) { // goes from open to deposit position in steps of 1 degree     
    servo.write(position);
    delay(SERVO_DELAY);
    log("Angle " + (String)position, LOG_MID);
   }
   delay(500);
   servo.write(OPEN_POSITION);
}


bool check_block_distance(){
  ultrasound_t = analogRead(ULTRASOUND_PIN);
  dist_t = ultrasound_t * MAX_RANGE  / ADC_SOLUTION;   
  if (dist_t < GRABBING_DISTANCE){
    return true;
  }
  return false;
}

bool left_crash_activated() {
  return !digitalRead(LEFT_CRASH_PIN); // crash sensor is active low => this function returns true is sensor activated
}

bool right_crash_activated() {
  return !digitalRead(RIGHT_CRASH_PIN); // crash sensor is active low => this function returns true is sensor activated
}
