#include "grab.h"
#include <arduino.h>
#include <Servo.h>  //include servo library

#define SENSITIVITY_PIN A3

Servo IDP207servo;  // create servo object to control a servo // twelve servo objects can be created on most boards 
int dist_t = 20;
int sensitivity_t;  
int pos; int opening_pos = 0; int closing_pos = 260;

void grab_init() {     
  IDP207servo.attach(13);  // attaches the servo on pin 13 to the servo object 
} 

void grab(){ //what action will the servo do to pick up the block? Depends on mechanical design
   for (pos = opening_pos; pos <= closing_pos; pos += 1) { // goes from 0 degrees to 260 degrees  // in steps of 1 degree     
    IDP207servo.write(pos);
    delay(15);
   }
}

bool check_distance(){
  sensitivity_t = analogRead(SENSITIVITY_PIN);
  dist_t = sensitivity_t * MAX_RANGE  / ADC_SOLUTION;   
  if (dist_t < GRABBING_DISTANCE){
    return true;
  }
  return false;
}

void deposit(){ //what action will the servo do to pick up the block? Depends on mechanical design
   for (pos = closing_pos; pos >= opening_pos; pos -= 1) { // goes from 260 degrees to 0 degrees  // in steps of 1 degree     
    IDP207servo.write(pos);
    delay(15);
   }
}

