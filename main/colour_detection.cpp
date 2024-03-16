#include "colour_detection.h"
#include "logging.h"
#include <arduino.h>

#define IR_SENSOR_PIN 12
#define RED_LED_PIN 13
#define GREEN_LED_PIN 11

// Initialises infra-red sensor as input, green and red LEDs as outputs.
void colour_detection_init() {
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

// Returns colour of block.
int detect_colour() {
  if (digitalRead(IR_SENSOR_PIN) == BLACK) {
    return BLACK;
  }
  else {
    return RED;
  }
}

// Turns on the green/red LED for 6 seconds if a black/red block is detected.
void blink_LED(int colour){
  if (colour == RED) {
    digitalWrite(GREEN_LED_PIN, LOW);
    digitalWrite(RED_LED_PIN, HIGH);
    log("Detected red", LOG_HIGH);
  }

  else {
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);
    log("Detected black", LOG_HIGH);
  }

  delay(5000);

  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
}
